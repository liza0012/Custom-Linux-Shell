#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void rm(char *arr[])
{
    if (arr[2] != NULL)
    {
        arr[2][strcspn(arr[2], "\n")] = 0;

        if (!strcmp(arr[1], "-v"))
        {
            if (remove(arr[2]))
            {
                printf("rm: cannot remove '%s': No such file or directory\n", arr[2]);
            }

            else
            {
                printf("removed '%s'\n", arr[2]);
            }
        }

        else if (!strcmp(arr[1], "-i"))
        {
            char arrr[1000];
            printf("rm: remove regular file '%s'? ", arr[2]);
            fgets(arrr, sizeof(arrr), stdin);

            if (((int)arrr[0] == 121) || ((int)arrr[0] == 89) || !strcmp(&arrr[0], "y\n") || !strcmp(&arrr[0], "Y\n"))
            {
                if (remove(arr[2]))
                {
                    printf("rm: cannot remove '%s': No such file or directory\n", arr[2]);
                }
            }
        }

        else
        {
            printf("rm: invalid option  %s\n", arr[1]);
        }
    }

    else if (arr[1] != NULL)
    {
        arr[1][strcspn(arr[1], "\n")] = 0;

        if (remove(arr[1]))
        {
            printf("rm: cannot remove '%s': No such file or directory\n", arr[1]);
        }
    }

    else
    {
        printf("rm: missing operand\n");
    }
}

int main(int argc, char *argv[])
{
    char *arr[] = {argv[1], argv[2], argv[3]};
    rm(arr);

    return 0;
}
