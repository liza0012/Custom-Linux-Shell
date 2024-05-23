#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

void mkdirr(char *arr[])
{
    if (arr[2] != NULL)
    {
        arr[2][strcspn(arr[2], "\n")] = 0;

        if (!strcmp(arr[1], "-v"))
        {
            if (mkdir(arr[2], 0777))
            {
                printf("mkdir: cannot create directory ‘%s’\n", arr[2]);
            }

            else
            {
                printf("mkdir: created directory '%s'\n", arr[2]);
            }
        }

        else if (!strcmp(arr[1], "-p"))
        {
            char original_directory[10000];
            getcwd(original_directory, 10000);

            int i = 0;
            char *cmdArr[10000];
            char *cmd = strtok(arr[2], "/");

            while (cmd != NULL)
            {
                cmdArr[i] = cmd;
                cmd = strtok(NULL, "/");
                i++;
            }

            char cwd[10000];
            char arrr[20000];

            for (int j = 0; j < i; j++)
            {
                getcwd(cwd, 10000);

                strcat(arrr, cwd);
                strcat(arrr, "/");
                strcat(arrr, cmdArr[j]);

                mkdir(arrr, 0777);

                chdir(arrr);

                memset(arrr, 0, 20000);
            }

            chdir(original_directory);
        }

        else
        {
            printf("mkdir: invalid option  %s\n", arr[1]);
        }
    }

    else if (arr[1] != NULL)
    {
        arr[1][strcspn(arr[1], "\n")] = 0;

        if (mkdir(arr[1], 0777))
        {
            printf("mkdir: cannot create directory ‘%s’\n", arr[1]);
        }
    }

    else
    {
        printf("mkdir: missing operand\n");
    }
}

int main(int argc, char *argv[])
{
    char *arr[] = {argv[1], argv[2], argv[3]};
    mkdirr(arr);

    return 0;
}
