#include <stdio.h>
#include <stdlib.h>

#define DSIZE 50*1024*1024
int main(void) {
int *a;
int i,z;
a=malloc(sizeof(int)*DSIZE);

for (i=0; i<10; i++ ) {
	for (z=0 ; z<DSIZE; z++ ) {
		*(a+z)= (((rand()*200))%1);
	}
	printf("Loop %d done\n",i);
	sleep(30);
}
exit;
}
