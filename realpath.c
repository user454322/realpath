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
	int opt, qindex;
	const int valid_index = 2; //options are mutually exclusive, so they should be the first option	
	bool hflag, qflag, vflag;
	qindex = 0;
	hflag = false;
	qflag = false;
	vflag = false;

	while ((opt = getopt(argc, argv, "hqv")) != -1) {			
		if (opt == 'h') {
			hflag = true;
			printf("h    optind=%d\n",optind);
			continue;

		} else if (opt == 'q') {
			qflag = true;
			qindex = optind;
			printf("q    optind=%d\n",optind);
			if (valid_index == qindex)
				break;
			else
				continue;

		} else if (opt == 'v') {
			vflag = true;
			printf("v    optind=%d\n",optind);
                        print_version();
			continue;
			
		} else {
			usage();
			exit(1);
		}

	}

	if ((valid_index != qindex) || !(hflag ^ qflag ^ vflag)) {
		/* 
		 * (qflag is not at the beginning)
		 *  (options are mutually exclusive) */
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
