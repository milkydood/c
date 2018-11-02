#include <stdio.h>

int main(int argc, char **argv[]) {
	char in[]="HELLO!";
	char out[255];
	char smallbuf[4];
	int i=0;

	out[0]=0;

	for (; i<strlen(in); i++ ) {
		sprintf(smallbuf,"%i ",in[i]);
		strcat(out,smallbuf);

	}
	out[strlen(out)-1]=0;
	fprintf(stderr,"%d, >%s<\n",strlen(out),out);
	if (out[2]==0) { printf( "NULL TERM\n"); }

}
