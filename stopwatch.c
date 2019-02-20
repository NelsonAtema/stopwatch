#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void start(void)
{
	time_t t = time(NULL);
	FILE *f;

	f = fopen("time.txt", "r");
	if (f == NULL)
	{
		f = fopen("time.txt", "w");
		if (f == NULL)
		{
			printf("Error opening file!\n");
			exit(1);
		}
		fprintf(f, "%u", t); // print unix timestamp in file
		fclose(f);
	}
	else
	{
		printf("file already present, use stop to reset");
		exit(1);
	}
}

void lap(void)
{
	time_t t = time(NULL); // get current time
	struct tm tm = *localtime(&t);

	FILE *f;
	f = fopen("time.txt", "r");
	if (f == NULL)
	{
		printf("no file found");
		exit(1);
	}
	time_t t2;
	fscanf(f, "%d", &t2); // get saved time
	struct tm tm2 = *localtime(&t2);

	time_t t3 = t - t2; // calculate diference between saved & current time
	printf("Saved time:   %4d-%02d-%02d %02d:%02d:%02d\n", tm2.tm_year + 1900, tm2.tm_mon + 1, tm2.tm_mday, tm2.tm_hour, tm2.tm_min, tm2.tm_sec);
	printf("Current time: %4d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	printf("Seconds: %d\n", (t3 % 60));
	printf("Minutes: %d\n", ((t3 / 60) % 60));
	printf("Hours  : %d\n", (((t3 / 60) / 60) % 24));
	printf("Days   : %d\n", (((t3 / 60) / 60) / 24));
	fclose(f);
}

void printhelp(void)
{
	printf("Please use one of the following arguments: \n \
	start	writes file \"time.txt\" to current dir with current time.\n \
	lap	shows time difference from start\n \
	stop	shows time difference from start and deletes \"time.txt\"\n");
}

int main(int argc, char const *argv[])
{
	if (argv[1] == NULL) // doesnt print help otherwise if no argument is given
	{
		printhelp();
		return 0;
	}

	if (strcmp(argv[1], "start") == 0)
	{
		start();
		return 0;
	};
	if (strcmp(argv[1], "lap") == 0)
	{
		lap();
		return 0;
	}
	if (strcmp(argv[1], "stop") == 0)
	{
		lap();
		remove("time.txt");
		return 0;
	}
	printhelp();
	return 0;
}
