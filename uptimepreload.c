#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
//#include <fcntl.h>
#include <string.h>

const char spoofyfile[]="/dev/shm/uptime";
const char spoofyuptime[]="1.00 1.00\n";

int open(const char *path, int flags) {
        int tmpfd;
        int (*original_open)(const char*, int);

        original_open = dlsym(RTLD_NEXT,"open");
        if (strstr(path, "/proc/uptime") != NULL) {
                //tmpfd = open(spoofyfile,O_WRONLY|O_CREAT|O_TRUNC);
              //  write(tmpfd, spoofyuptime,sizeof(spoofyuptime));
               // close(tmpfd);
                return (*original_open)(spoofyfile,flags);
        }
        return (*original_open)(path ,flags);

}
int open64(const char *path, int flags) {
        int tmpfd;
        int (*original_open64)(const char*, int);

        original_open64 = dlsym(RTLD_NEXT,"open64");
        if (strstr(path, "/proc/uptime") != NULL) {
                //tmpfd = open64(spoofyfile,O_WRONLY|O_CREAT|O_TRUNC);
                //write(tmpfd, spoofyuptime,sizeof(spoofyuptime));
                //close(tmpfd);
                return (*original_open64)(spoofyfile,flags);
        }
        return (*original_open64)(path ,flags);

}
