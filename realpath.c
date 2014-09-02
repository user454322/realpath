///opt/local/include


#include <sys/syslimits.h>

#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define	VERSION	"0.0.1"

static void print_version(void);
static void usage(void);


int
main(int argc, char **argv)
{
	int opt;
	bool qflag = false;
	
	while ((opt = getopt(argc, argv, "qhv")) != -1) {
		switch (opt) {
		case 'q':
			qflag = true;
			break;
			
		case 'v':
			print_version();
			exit(0);
			
		case 'h':
			usage();
			exit(0);
			
		case '?':
		default:
			usage();
			exit(1);		
		}
	}

	char real_path[PATH_MAX];
	char resolved_name[PATH_MAX];
	const char *path = *argv != NULL ? argv++ : "./";
	int exit_val = 0;
		
	real_path = realpath(path, resolved_name);
	
	/*
	 * If resolved_name was non-NULL, it will contains the pathname which
	 * caused the problem.
	 */
	 if (realpath != NULL) {
	 	printf("%s\n", real_path);
	 	
	 } else if (!qflag) {
	 	warn("%s\n", resolved_name);
	 	exit_val = 1;
	 }
	 
	 exit(exit_val);

}

static void
print_version(void)
{
	printf("%s\n", VERSION);
}

static void
usage(void)
{
	printf("usage: realpath [-q] [path]\n");
}
