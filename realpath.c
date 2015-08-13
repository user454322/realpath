/*-
 * Copyright (c) 2014, Javier
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <sys/syslimits.h>

#include <err.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


#define	VERSION	"1.0.0"
#define	INVALID_OPTION_ERROR	1
#define	REAL_PATH_ERROR	2

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
		if ('h' == opt && valid_index == optind) {
			usage(stdout);
			exit(0);

		} else if ('q' == opt && valid_index == optind) {
			qflag = true;
			break;

		} else if ('v' == opt && valid_index == optind) {
                        print_version();
			exit(0);
			
		} else {
			usage(stderr);
			exit(INVALID_OPTION_ERROR);
		}

	}

	char *rp;
	char *path;
	char resolved_name[PATH_MAX];
	int exit_val = 0;

	argv += optind;
	path = NULL != *argv ? *argv++ : ".";
	do{
		if (NULL != (rp = realpath(path, resolved_name))) {
			printf("%s\n", rp);

		} else {
			if (!qflag)
				/* If resolved_name was non-NULL, it will
				 * contain the pathname which caused the
				 * problem. realpath(3)
				 */
				warn("%s", resolved_name);
			exit_val = REAL_PATH_ERROR;
		}
	} while (NULL != (path = *argv++));

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

