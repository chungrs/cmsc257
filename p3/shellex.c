/*****************************************
* Roy Chung
* CMSC257
* Project 3: Simple Unix Shell
* ---------------------------------
* A simple shell with basic functionality
*****************************************/

/* $begin shellmain */
#include "csapp.h"
#define MAXARGS   128

/* Function prototypes */
void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv); 

//Signal Handler for SIGINT to stop Ctrl+C from exiting shell
void sigintHandler(int sig_num) 
{ 
    signal(SIGINT, sigintHandler); 
    fflush(stdout); 
} 

int main(int argc, char *argv[]) 
{
    //stops ctrl+c from exiting shell
    signal(SIGINT, sigintHandler); 

    char cmdline[MAXLINE]; /* Command line */
    char shell_prompt[100]; /* shell prompt */

    //if no arguments are passed into the program, then use the default prompt "my257sh"
    if (argc == 1)
        strcpy(shell_prompt, "my257sh");

    //if the user enters -p but no custom prompt, return instructions for creating custom prompt
    if (argc == 2)
    {
        printf("%s -p <prompt>\n", argv[0]);
        exit(0);
    }

    //use user-defined prompt
    if (argc > 2)
    {
        //if -p is not used, then return instructions for creating custom prompt
        if(strcmp(argv[1],"-p") != 0)
        {
            printf("%s -p <prompt>\n", argv[0]);
            exit(0);
        }
        
        //copy argv[2] to shell prompt
        strcpy(shell_prompt, argv[2]);
    }

    while (1) {
	/* Read */
	printf("%s> ", shell_prompt); //shell prompt
	Fgets(cmdline, MAXLINE, stdin); //read input
	if (feof(stdin))
	    exit(0);

	/* Evaluate */
	eval(cmdline);
    } 
}
/* $end shellmain */
  
/* $begin eval */
/* eval - Evaluate a command line */
void eval(char *cmdline) 
{
    char *argv[MAXARGS]; /* Argument list execve() */
    char buf[MAXLINE];   /* Holds modified command line */
    int bg;              /* Should the job run in bg or fg? */
    pid_t pid;           /* Process id */
    
    strcpy(buf, cmdline);
    bg = parseline(buf, argv); 
    if (argv[0] == NULL)  
	return;   /* Ignore empty lines */

    if (!builtin_command(argv)) { //if input is not a built-in function
        if ((pid = Fork()) == 0) {   //child runs user job
            if (execvp(argv[0], argv) < 0) {
                printf("Execution failed (in fork)\n: No such file or directory\n");
                fflush(stdout);
                exit(1);
            }
        }

	/* Parent waits for foreground job to terminate */
	if (!bg) {
	    int status;
	    if (waitpid(pid, &status, 0) < 0)
		    unix_error("waitfg: waitpid error");
        printf("Child exit status: %d\n", WEXITSTATUS(status));
        fflush(stdout);
	}
	else
	    printf("%d %s", pid, cmdline);
        fflush(stdout);
    }
    return;
}

//function prints help menu
void help()
{
    printf("\n");
    printf("A custom shell for CMSC 257\n");
    printf("Developed by Roy Chung\n");
    printf("\n");
    printf("Usage: my257sh -p <prompt>\n");
    printf("Args:\n");
    printf("%-10s:\tSpecifies to use a custom prompt for the shell\n", "-p");
    printf("%-10s:\tThe prompt to use for the shell. Defaults to \"my257sh> \"\n", "<prompt>");
    printf("\n");
    printf("****************************************************************************\n");
    printf("\n");
    printf("BUILT-IN COMMANDS:\n");
    printf("%-10s:\tCloses the current shell\n", "exit");
    printf("%-10s:\tPrints the PID of the shell\n", "pid");
    printf("%-10s:\tPrints the PID of the shell's parent\n", "ppid");
    printf("%-10s:\tPrints out this help menu\n", "help");
    printf("%-10s:\tDisplays the current working directory\n", "cd");
    printf("%-10s:\tChanges the current directory to <path>\n", "cd <path>");
    printf("****************************************************************************\n");
    printf("\n");
    printf("SYSTEM COMMANDS:\n");
    printf("\tPlease refer to the `man` for system commands\n");
    return;
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv)
{
    if (!strcmp(argv[0], "exit")) //quit command
    {
        int ret = raise(SIGTERM);

        if (ret != 0)
        {
            printf("Unable to terminate program using raise system call.\n");
            fflush(stdout);
            exit(0);
        }
    } 
    else if (!strcmp(argv[0], "pid")) //get the process id
    {
        printf("%d\n", getpid());
        return 1;
    }
    else if (!strcmp(argv[0], "ppid")) //get parent pid
    {
        printf("%d\n", getppid());
        return 1;
    }
    else if (!strcmp(argv[0], "help")) //print help menu
    {
        help();
        return 1;
    }
    else if (!strcmp(argv[0], "cd")) //go to or print directory
    {
        //if no directory is entered, return current directory
        if (argv[1] == NULL)
        {
            char cwd[100];
            if (getcwd(cwd, sizeof(cwd)) != NULL)
            {
                printf("Current dir: %s\n", cwd);
                fflush(stdout);
            }
            else
            {
                printf("getcwd() error");
                fflush(stdout);
                return 1;
            }
        }
        //if a directory is entered, go to the directory
        else if (argv[1] != NULL)
        {
            chdir(argv[1]);
        }
        return 1;
    }

    if (!strcmp(argv[0], "&")) /* Ignore singleton & */
        return 1;

    return 0; /* Not a builtin command */
}
/* $end eval */

/* $begin parseline */
/* parseline - Parse the command line and build the argv array */
int parseline(char *buf, char **argv) 
{
    char *delim;         /* Points to first space delimiter */
    int argc;            /* Number of args */
    int bg;              /* Background job? */

    buf[strlen(buf)-1] = ' ';  /* Replace trailing '\n' with space */
    while (*buf && (*buf == ' ')) /* Ignore leading spaces */
	buf++;

    /* Build the argv list */
    argc = 0;
    while ((delim = strchr(buf, ' '))) {
	argv[argc++] = buf;
	*delim = '\0';
	buf = delim + 1;
	while (*buf && (*buf == ' ')) /* Ignore spaces */
            buf++;
    }
    argv[argc] = NULL;
    
    if (argc == 0)  /* Ignore blank line */
	return 1;

    /* Should the job run in the background? */
    if ((bg = (*argv[argc-1] == '&')) != 0)
	argv[--argc] = NULL;

    return bg;
}
/* $end parseline */