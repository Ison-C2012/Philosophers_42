#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

int	main(void)
{
	struct timeval	tv;

	while (1)
	{
		gettimeofday(&tv, NULL);
		printf("%ld %ld\n", tv.tv_sec, tv.tv_usec);
		usleep(1000);
	}
	return 0;
}
