/// opt / local / include


#include <sys/syslimits.h>

#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define	VERSION	"0.0.1"

static void	print_version(void);
static void	usage(void);


int
main(int argc, char **argv)
{
	int		opt;
	bool		hflag    , qflag, vflag;
	hflag = false;
	qflag = false;
	vflag = false;

	while ((opt = getopt(argc, argv, "hqv")) != -1) {
		switch (opt) {
		case 'h':
			hflag = true;
			printf("h\n");
			continue;

		case 'q':
			qflag = true;
			printf("q\n");
			continue;

		case 'v':
			vflag = true;
			printf("v\n");
			continue;

		case '?':
		default:
			usage();
			exit(1);
		}
	}

	if (!(hflag ^ qflag ^ vflag) || (hflag | qflag | vflag)) {
		/* (flags are mutually exclusive) and (all flags can't be on) */
		usage();
		exit(2);
	}
	exit(99);
}

static void
print_version(void)
{
	printf("%s\n", VERSION);
}

static void
usage(void)
{
	printf("Usage: realpath [-q] [path ...]\n"
	       "       realpath -h\n"
	       "       realpath -v\n");
}
