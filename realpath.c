/// opt / local / include


#include <sys/syslimits.h>

#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define	VERSION	"0.0.1"


static void	print_version(void);
static void	usage(FILE *restrict stream);


int
main(int argc, char **argv)
{
        int opt;
        /* options are mutually exclusive, so they should be at the beginning */
	const int valid_index = 2; 
	bool qflag = false;

	while ((opt = getopt(argc, argv, "hqv")) != -1) {
		if (opt == 'h' && optind == valid_index) {
			usage(stdout);
			exit(0);

		} else if (opt == 'q' && optind == valid_index) {
			qflag = true;
			break;

		} else if (opt == 'v' && optind == valid_index) {
                        print_version();
			exit(0);
			
		} else {
			usage(stderr);
			exit(1);
		}

	}
	
	char *rp;
	char *path = ".";
	char resolved_name[PATH_MAX];
	int exit_val = 0;
	if ((rp = realpath(path, resolved_name)) != NULL){
		printf("%s\n", rp);

	} else {
	//If resolved_name was non-NULL, it will contains the pathname which caused the problem.
		if (!qflag)
			warn("%s", resolved_name);
		exit_val =1;
	}


	exit(exit_val);
}

static void
print_version(void)
{
	printf("%s\n", VERSION);
}

static void
usage(FILE *restrict stream)
{
	fprintf(stream, 
		"Usage: realpath [-q] [path ...]\n"
		"       realpath -h\n"
		"       realpath -v\n");
}
