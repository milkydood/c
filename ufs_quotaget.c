#include <fcntl.h>
#include <stdio.h>
#include <sys/fs/ufs_quota.h>

int main(int argc, char **argv) {
	struct quotctl user_quota_out;
	struct dqblk user_quota_blk;
	int fd, ret;

	fd = open("/home/quotas", O_RDONLY);

	if (fd == -1) {
		fprintf(stderr,"Can't open quota file");
		exit(1);
	}

	user_quota_out.op=Q_GETQUOTA;
	user_quota_out.uid=3007;
	user_quota_out.addr=&user_quota_blk;

	ret = ioctl(fd, Q_QUOTACTL, &user_quota_out);
	if (ret != 0) {
		perror("ioctl failed");
		
		exit(1);
	}

	fprintf(stderr,"Cur, %u, Hard: %u soft: %u\n",
		(uint) user_quota_blk.dqb_curblocks,
		(uint) user_quota_blk.dqb_bhardlimit,
		(uint) user_quota_blk.dqb_bsoftlimit);
}
