#include <ctype.h>
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>

#define ARM_RDI_MONITOR

#include "swi.h"

int main(int argc, char** argv);

void initialise_monitor_handles(void);
void __libc_init_array(void);
int kill(pid_t, int);
void qemu_exit(int status);

#ifndef ARGS_BUF_ARRAY_SIZE
#    define ARGS_BUF_ARRAY_SIZE 1024
#endif

#ifndef ARGV_BUF_ARRAY_SIZE
#    define ARGV_BUF_ARRAY_SIZE 10
#endif

struct CommandLineBlock
{
    char* pCommandLine;
    int size;
};

static void __initialize_args(int* p_argc, char*** p_argv)
{
    // Array of chars to receive the command line from the host
    static char args_buf[ARGS_BUF_ARRAY_SIZE];

    // Array of pointers to store the final argv pointers (pointing
    // in the above array).
    static char* argv_buf[ARGV_BUF_ARRAY_SIZE];

    int argc = 0;
    int isInArgument = 0;

    struct CommandLineBlock cmdBlock;
    cmdBlock.pCommandLine = args_buf;
    cmdBlock.size = sizeof(args_buf) - 1;

    int ret = do_AngelSWI(AngelSWI_Reason_GetCmdLine, &cmdBlock);
    if(ret == 0)
    {
        // In case the host send more than we can chew, limit the
        // string to our buffer.
        args_buf[ARGS_BUF_ARRAY_SIZE - 1] = '\0';

        // The command line is a null terminated string
        char* p = cmdBlock.pCommandLine;

        int delim = '\0';
        int ch;

        while((ch = *p) != '\0')
        {
            if(isInArgument == 0)
            {
                if(!isblank(ch))
                {
                    if(argc >= (int)((sizeof(argv_buf) / sizeof(argv_buf[0])) - 1))
                        break;

                    if(ch == '"' || ch == '\'')
                    {
                        // Remember the delimiter to search for the
                        // corresponding terminator
                        delim = ch;
                        ++p; // skip the delimiter
                        ch = *p;
                    }
                    // Remember the arg beginning address
                    argv_buf[argc++] = p;
                    isInArgument = 1;
                }
            }
            else if(delim != '\0')
            {
                if((ch == delim))
                {
                    delim = '\0';
                    *p = '\0';
                    isInArgument = 0;
                }
            }
            else if(isblank(ch))
            {
                delim = '\0';
                *p = '\0';
                isInArgument = 0;
            }
            ++p;
        }
    }
    else
    {
        printf("Buffer too small\n");
        qemu_exit(1);
    }

    if(argc == 0)
    {
        // No args found in string, return a single empty name.
        args_buf[0] = '\0';
        argv_buf[0] = &args_buf[0];
        ++argc;
    }

    // Must end the array with a null pointer.
    argv_buf[argc] = NULL;

    *p_argc = argc;
    *p_argv = &argv_buf[0];
    return;
}

void cpp_heap_init();

void qemu_exit(int status)
{
    do_AngelSWI(
        AngelSWI_Reason_Exit,
        (void*)(status == 0 ? ADP_Stopped_ApplicationExit : ADP_Stopped_RunTimeError));
    for(;;)
        ;
}

void _startup(void)
{
    char** argv;
    int argc;

    initialise_monitor_handles();

    __libc_init_array();

    __initialize_args(&argc, &argv);

    int r = main(argc, argv);

    qemu_exit(r);
}
