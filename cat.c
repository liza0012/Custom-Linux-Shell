#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void cat(char *arr[])
{
    if (arr[2] != NULL)
    {
        arr[2][strcspn(arr[2], "\n")] = 0;

        FILE *f;
        f = fopen(arr[2], "r");

        if (f != NULL)
        {
            if (!strcmp(arr[1], "-n"))
            {
                int i = 1;
                char arrr[1000];

                while (fgets(arrr, sizeof(arrr), f))
                {
                    printf("    %d  ", i);
                    printf("%s", arrr);
                    i++;
                }
            }

            else if (!strcmp(arr[1], "-E"))
            {
                char arrr[1000];

                while (fgets(arrr, sizeof(arrr), f))
                {
                    arrr[strcspn(arrr, "\n")] = 0;
                    printf("%s", arrr);
                    printf("$\n");
                }
            }

            else
            {
                printf("cat: invalid option  %s\n", arr[1]);
            }

            fclose(f);
        }

        else if (!strcmp("SHELL=/bin/bash", arr[2]) || !strcmp("LESSOPEN=| /usr/bin/lesspipe %s", arr[2]))
        {
            printf("cat: missing operand\n");
        }

        else
        {
            printf("cat: %s: No such file or directory\n", arr[2]);
        }
    }

    else if (arr[1] != NULL)
    {
        arr[1][strcspn(arr[1], "\n")] = 0;

        FILE *f;
        f = fopen(arr[1], "r");

        if (f != NULL)
        {
            char content = fgetc(f);
            while (content != EOF)
            {
                printf("%c", content);
                content = fgetc(f);
            }

            fclose(f);
        }

        else
        {
            printf("cat: %s: No such file or directory\n", arr[1]);
        }
    }
}

int main(int argc, char *argv[])
{
    char *arr[] = {argv[1], argv[2], argv[3]};
    cat(arr);

    return 0;
}
