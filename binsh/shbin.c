/*
 * Copyright (C) 2013 Sarzyniec Luc <contact@olbat.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * see the COPYING file for more informations */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define PRINT_FORMAT "\\x%.2x"
#define PRINT_DISPLAY(F,C) __extension__ \
({ \
	printf(F,C); \
	fflush(stdout); \
})

static int fd;

int main(int argc, char **argv)
{
	if (argc > 2)
	{
		char *key;
		unsigned char c;
		unsigned int i;
		size_t len;

		key = *(argv + 2);
		len = strlen(key);

		fd = open(*(argv + 1), O_RDONLY);
		for (i=0;read(fd,&c,sizeof(c)) > 0;i++)
			PRINT_DISPLAY(PRINT_FORMAT,c^key[(i + key[i%len])%len]);
		close(fd);

		puts("");
	        return 0;
	}
	else
	{
		printf("usage: %s <file> <key>\n",*argv);
                return 1;
	}
}
