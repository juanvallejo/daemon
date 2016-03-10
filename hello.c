#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

/**
 * Sample daemon program. Logs to syslog every 3 seconds.
 * To view output logs, use journalctl and scroll to bottom.
 * @juanvallejo
 */

int main(int argc, char **argv) {
	
	pid_t pid, sid;

	// fork off the parent process
	pid = fork();
	if(pid < 0) {
		exit(EXIT_FAILURE);
	}

	// if valid pid, exit parent process
	if(pid > 0) {
		exit(EXIT_SUCCESS);
	}

	// change filemode mask to allow
	// access to any logs / files I write
	umask(0);

	// create new system id for
	// child process
	sid = setsid();
	if(sid < 0) {
		exit(EXIT_FAILURE);
	}

	// change current working dir to
	// safe location
	if(chdir("/") < 0) {
		exit(EXIT_FAILURE);
	}

	// close standard file descriptors
	// a daemon should not attempt to
	// communicate with a user directly
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	// set syslog mask
	setlogmask(LOG_UPTO (LOG_NOTICE));
	openlog("testdaemon", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);

	// main daemon task
	while(1) {

		syslog(LOG_NOTICE, "Test");
		syslog(LOG_INFO, "A tree falls in a forest");
		sleep(3);
	}

	closelog();

	exit(EXIT_SUCCESS);

	return 0;
}
