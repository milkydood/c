#include <stdio.h>
#include <time.h>

int main(int argc, char **argv) {
	time_t tm;
	tm = time(0);
	printf ("%d\n",tm);

	return 0;
}
