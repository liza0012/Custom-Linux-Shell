
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>


int custom_alphasort(const struct dirent **a, const struct dirent **b) {
    return strcasecmp((*a)->d_name, (*b)->d_name);
}

void ls(char *arr[])
{
    char cwd[10000];
    getcwd(cwd, sizeof(cwd));

    struct dirent **files;
    int size = scandir(cwd, &files, NULL, custom_alphasort);

    if (size < 0) {
        perror("scandir");
        return;
    }

    if (arr[1] != NULL)
    {
        if (!strcmp(arr[1], "-a\n") || !strcmp(arr[1], "-a"))
        {
        	int i;
            for ( i = 0; i < size; i++)
            {
                char f[256];
                strncpy(f, files[i]->d_name, sizeof(f) - 1);
                f[sizeof(f) - 1] = '\0';

                printf("%s  ", f);
            }
            printf("\n");
        }

        else if (!strcmp(arr[1], "-m\n") || !strcmp(arr[1], "-m"))
        {
        	int i;
            for (i = 0; i < size; i++)
            {
                char f[256];
                strncpy(f, files[i]->d_name, sizeof(f) - 1);
                f[sizeof(f) - 1] = '\0';

                if ((int)f[0] != 46)
                {
                    printf("%s, ", f);
                }
            }
            printf("\n");
        }

        else
        {
            printf("ls: invalid option %s\n", arr[1]);
        }
    }

    else
    {
    	int i;
        for (i = 0; i < size; i++)
        {
            char f[256];
            strncpy(f, files[i]->d_name, sizeof(f) - 1);
            f[sizeof(f) - 1] = '\0';

            if ((int)f[0] != 46)
            {
                printf("%s  ", f);
            }
        }
        printf("\n");
    }
    
    int i;

    for (i = 0; i < size; i++) {
        free(files[i]);
    }
    free(files);
}

int main(int argc, char *argv[])
{
    char *arr[] = {argv[0], argv[1]};
    ls(arr);

    return 0;
}

