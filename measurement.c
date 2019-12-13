#include <stdio.h>
#include <time.h>

long long getElapsedTime(unsigned int nFlag)
{
	const long long NANOS = 1000000000LL;
	static struct timespec startTS, endTS;
	static long long retDiff = 0;

	if (nFlag == 0) {
		retDiff = 0;
		if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &startTS) == -1) {
			printf("Failed to call clock_gettime\n");
		}
	}
	else {
		if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &endTS) == -1) {
			printf("Failed to call clock_gettime\n");
		}
		retDiff = NANOS * (endTS.tv_sec - startTS.tv_sec) + (endTS.tv_nsec - startTS.tv_nsec);
 	}

	return retDiff;
}

int main(const int argc, char **argv)
{
	getElapsedTime(0);

	// do something...

	printf("Elapsed Time: %lld\n", getElapsedTime(1));

	return 0;
}
