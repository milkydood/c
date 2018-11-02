#include <procfs.h>
#include <stdio.h>

#define offsetof(type, f) ((size_t) ((char *)&((type *)0)->f - (char *)(type *)0))

int main(int argc, char **argv) {
	struct pstatus foo;
	printf("offset: %d & %d\n", offsetof(struct pstatus, pr_utime), offsetof(struct pstatus, pr_stime));
}
