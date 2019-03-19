#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int main(void) {

    /* Our process ID and Session ID */
    pid_t pid, sid;

    /* Fork off the parent process */
    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }
    /* If we got a good PID, then
       we can exit the parent process. */
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    /* Change the file mode mask */
    umask(0);

    /* Open any logs here */
    FILE *pLog = NULL;
    pLog = fopen("/tmp/daemonLog.txt", "w");

    if(!pLog)
        exit(EXIT_FAILURE);
    else {
        char cLogMSG[] = "daemon started\n";
        fwrite((void*)cLogMSG, sizeof(char), (strlen(cLogMSG)+1), pLog);
        fflush(pLog);
        fclose(pLog);
        pLog = NULL;
    }
    /* Create a new SID for the child process */
    sid = setsid();
    if (sid < 0) {
        /* Log the failure */
        exit(EXIT_FAILURE);
    }



    /* Change the current working directory */
    if ((chdir("/")) < 0) {
        /* Log the failure */
        exit(EXIT_FAILURE);
    }

    /* Close out the standard file descriptors */
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    /* Daemon-specific initialization goes here */
    int iCnt = 1;

    /* The Big Loop */
    while (1) {
        /* Do some task here ... */
        char cBuffer[512];
        snprintf(cBuffer, sizeof(cBuffer), "loop: %d\n", iCnt);

        char *pLogMSG = cBuffer;

        pLog = fopen("/tmp/daemonLog.txt", "a");
        if(pLog) {
            fwrite((void*)pLogMSG, sizeof(char), (strlen(pLogMSG)+1), pLog);
            fflush(pLog);
            fclose(pLog);
            pLog = NULL;
        }

        sleep(5); /* wait 30 seconds */

        if (iCnt == 10)
            break;
        else
            iCnt++;
    }

    exit(EXIT_SUCCESS);
}
