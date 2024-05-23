#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void date(char *arr[])
{
    time_t current_time;

    char date[1000];

    time(&current_time);

    if (arr[1] != NULL)
    {
        if (!strcmp(arr[1], "-u\n") || !strcmp(arr[1], "-u"))
        {
            struct tm *date_time = gmtime(&current_time);

            strftime(date, sizeof(date), "%c", date_time);

            for (int i = 0; i < 25; i++)
            {
                if (i == 19)
                {
                    printf(" UTC ");
                }

                else
                {
                    printf("%c", date[i]);
                }
            }
            printf("\n");
        }

        else if (!strcmp(arr[1], "-I\n") || !strcmp(arr[1], "-I"))
        {
            struct tm *date_time = localtime(&current_time);

            strftime(date, sizeof(date), "%F", date_time);

            printf("%s\n", date);
        }

        else
        {
            printf("date: invalid option  %s\n", arr[1]);
        }
    }

    else
    {
        struct tm *date_time = localtime(&current_time);

        strftime(date, sizeof(date), "%c", date_time);

        for (int i = 0; i < 25; i++)
        {
            if (i == 19)
            {
                printf(" IST ");
            }

            else
            {
                printf("%c", date[i]);
            }
        }
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    char *arr[] = {argv[1], argv[2]};
    date(arr);

    return 0;
}
