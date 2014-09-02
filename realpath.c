///opt/local/include


#include <sys/syslimits.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define	VERSION	"0.0.1"

static void print_version(void);
static void usage(void);


int
main(int argc, char **argv)
{
	int opt, qflag;
	
	while ((opt = getopt(argc, argv, "qhv")) != -1) {
		switch (opt) {
		case 'q':
			qflag = 1;
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
	
	printf("Works here %d\n", PATH_MAX);

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
