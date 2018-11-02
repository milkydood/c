// build with: gcc -Wl,--no-as-needed -shared -fPIC -ldl  -o unlink.so unlink.c 

#define _GNU_SOURCE
#define BUFSIZE 200
#include <stdio.h>
#include <dlfcn.h>
#include <string.h>


static int (*next_unlinkat)(int dirfd, const char *pathname, int flags) = NULL;
static int (*next_unlink)(const char *pathname) = NULL;
static buf[BUFSIZE];
static buf2[BUFSIZE + 20];
int bread;

int unlink(const char *pathname) {
        buf[0]=buf2[0]=0;
        if (next_unlink== NULL) {
                next_unlink = dlsym(RTLD_NEXT,"unlink");
        }

        trace_pid();

        //fprintf(stderr,"Request to unlink %s\n", pathname);
        return next_unlink(pathname);
}

int unlinkat(int dirfd, const char *pathname, int flags) {
        if (next_unlinkat == NULL) {
                next_unlinkat = dlsym(RTLD_NEXT,"unlinkat");
        }

        trace_pid();

        //fprintf(stderr,"Request to unlink %s\n", pathname);
        return next_unlinkat(dirfd, pathname, flags);
}

int trace_pid(void) {
        bread = readlink("/proc/self", buf, BUFSIZE - 1 );

        if (bread) {
                buf[bread]='\0';
                strcat((char *) &buf2, "pstree -a -s ");
                strcat((char *) &buf2, (char *) &buf);
                system(buf2);
        } else {
                perror("lstat");
                return 1;
        }
}
