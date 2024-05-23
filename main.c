#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <windows.h>
#include <process.h>

#define MAX_PATH_LENGTH 10000
#define MAX_CMD_LENGTH 10000

// Thread function to execute commands
unsigned __stdcall function(void* arguments) {
    system((char*)arguments);
    return 0;
}

int main() {
    printf("\n\n******************** WELCOME TO MY SHELL ********************\n\n");

    char original_directory[MAX_PATH_LENGTH];
    _getcwd(original_directory, MAX_PATH_LENGTH);

    while (1) {
        char cwd[MAX_PATH_LENGTH];
        _getcwd(cwd, MAX_PATH_LENGTH);

        printf("\nLiza_08001012021 @DESKTOP-IP0PV11:%s $ ", cwd);

        char input[MAX_CMD_LENGTH];
        fgets(input, sizeof(input), stdin);

        int i = 0;
        char* cmdArr[MAX_CMD_LENGTH / 2];
        char* cmd = strtok(input, " \n");

        while (cmd != NULL) {
            cmdArr[i] = cmd;
            cmd = strtok(NULL, " \n");
            i++;
        }
        cmdArr[i] = NULL; // Null-terminate the array

        char arrr[MAX_CMD_LENGTH * 2] = "";
        char path[MAX_CMD_LENGTH * 2] = "";

        if (cmdArr[0] == NULL) {
            continue; // Empty input, continue the loop
        }

        if (strcmp(cmdArr[0], "cd") == 0) {
            if (cmdArr[1] != NULL) {
                if (strcmp(cmdArr[1], "~") == 0) {
                    _chdir(original_directory);
                } else if (_chdir(cmdArr[1]) != 0) {
                    printf("-bash: cd: %s: No such file or directory\n", cmdArr[1]);
                }
            } else {
                _chdir(original_directory);
            }
        } else if (strcmp(cmdArr[0], "echo") == 0) {
            if (cmdArr[1] != NULL) {
                if (strcmp(cmdArr[1], "*") == 0) {
                    WIN32_FIND_DATA findFileData;
                    HANDLE hFind = FindFirstFile("*", &findFileData);

                    if (hFind != INVALID_HANDLE_VALUE) {
                        do {
                            const char* name = findFileData.cFileName;
                            if (name[0] != '.') {
                                printf("%s ", name);
                            }
                        } while (FindNextFile(hFind, &findFileData));
                        FindClose(hFind);
                    }
                    printf("\n");
                } else if (strcmp(cmdArr[1], "--help") == 0) {
                    system("echo --help");
                } else {
                	int j;
                    for (j = 1; j < i; j++) {
                        printf("%s ", cmdArr[j]);
                    }
                    printf("\n");
                }
            } else {
                printf("\n");
            }
        } else if (strcmp(cmdArr[0], "pwd") == 0) {
            _getcwd(cwd, MAX_PATH_LENGTH);
            printf("%s\n", cwd);
        } else if (strcmp(cmdArr[0], "ls") == 0) {
            strcat(path, "dir"); // 'dir' is the equivalent command in Windows
            if (cmdArr[i - 1] && strcmp(cmdArr[i - 1], "&t") == 0) {
                HANDLE thread = (HANDLE)_beginthreadex(NULL, 0, function, path, 0, NULL);
                WaitForSingleObject(thread, INFINITE);
                CloseHandle(thread);
            } else {
                system(path);
            }
        } else if (strcmp(cmdArr[0], "cat") == 0 || strcmp(cmdArr[0], "date") == 0 || strcmp(cmdArr[0], "rm") == 0 || strcmp(cmdArr[0], "mkdir") == 0) {
            // For 'cat', 'date', 'rm', 'mkdir', map them to appropriate Windows commands
            // 'cat' -> 'type', 'rm' -> 'del', 'mkdir' remains 'mkdir', 'date' -> 'date /T'
            if (strcmp(cmdArr[0], "cat") == 0) {
                strcat(path, "type ");
            } else if (strcmp(cmdArr[0], "date") == 0) {
                strcat(path, "date /T");
            } else if (strcmp(cmdArr[0], "rm") == 0) {
                strcat(path, "del ");
            } else if (strcmp(cmdArr[0], "mkdir") == 0) {
                strcat(path, "mkdir ");
            }
            int j;

            for (j = 1; cmdArr[j] != NULL; j++) {
                strcat(path, cmdArr[j]);
                strcat(path, " ");
            }

            if (cmdArr[i - 1] && strcmp(cmdArr[i - 1], "&t") == 0) {
                HANDLE thread = (HANDLE)_beginthreadex(NULL, 0, function, path, 0, NULL);
                WaitForSingleObject(thread, INFINITE);
                CloseHandle(thread);
            } else {
                system(path);
            }
        } else if (strcmp(input, "exit\n") == 0 || strcmp(input, "exit") == 0) {
            printf("\n\nThanks For Using My Shell!!!\n\n");
            exit(0);
        } else {
            input[strcspn(input, "\n")] = 0;
            if (strlen(input) == 0) {
            } else {
                printf("%s: command not found\n", input);
            }
        }

        memset(input, 0, MAX_CMD_LENGTH);
        memset(cmdArr, 0, sizeof(cmdArr));
        memset(arrr, 0, sizeof(arrr));
        memset(path, 0, sizeof(path));
    }
    return 0;
}


