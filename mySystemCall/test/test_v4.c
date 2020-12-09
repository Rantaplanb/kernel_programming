#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#define set_deadlines(a1, a2, a3) syscall(341, a1, a2, a3)

int main()
{
    int currentPid, parentPid, pid, status, flag = 0;
	int* deadlinePtr = malloc(sizeof(int));
	int* compTimePtr = malloc(sizeof(int));
	*deadlinePtr = 10;
	*compTimePtr = 5;

    pid = fork();

    if (pid > 0) /*parent process*/
    {
        waitpid(pid, &status, 0);
        currentPid = getpid();

        flag = set_deadlines(-1, *deadlinePtr, *compTimePtr);
        // flag = set_deadlines(currentPid, *deadlinePtr, *compTimePtr);
        // flag = set_deadlines(pid, *deadlinePtr, *compTimePtr);
        // flag = set_deadlines(-5, *deadlinePtr, *compTimePtr);
        if (flag)
            printf("syscall() returned an erroneous value!");
    }
    else if (pid == 0) /*child process*/
    {
        waitpid(pid, &status, 0);
        waitpid(getppid(), &status, 0);
        currentPid = getpid();
        //parentPid = getppid();

        flag = set_deadlines(currentPid, *deadlinePtr, *compTimePtr);
		// flag = set_deadlines(parentPid, *deadlinePtr, *compTimePtr);
        // flag = set_deadlines(-1, *deadlinePtr, *compTimePtr);
        // flag = set_deadlines(-5, *deadlinePtr, *compTimePtr);
    }
    else
        printf("Fork error!");
}
