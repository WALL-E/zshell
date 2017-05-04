#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define TRY_MAX 3

int main(int argc, char *argv[])
{
    char cmd[BUFSIZ];
    char key[BUFSIZ] = "BIh1dyeDSo9wUOXRCNkvmj7rVgnbi8TAxsS3BB20";
    char secret[BUFSIZ] = "GLSwT6l8ySe4aREimzznTajJI24sA0skzb8N258Z";
    char *prompt = "Password:";
    char password[BUFSIZ] = "123456";
    char *ptr = NULL;
    int try = 0;

    if (argc != 2) {
        printf("Usage: %s file\n", argv[0]);
        exit(1);
    }

    while(1) {
        ptr = getpass(prompt);
        if ((ptr != NULL) && (0 == strncmp(ptr, password, strlen(password)))) {
            break;
        }

        try++;
        if (try >= TRY_MAX) {
            exit(1);
        }           
    }

    if (-1 == access(argv[1], F_OK)) {
        printf("%s not found\n", argv[1]);
        exit(1);
    }

    if (-1 == access(argv[1], R_OK)) {
        printf("%s not readable\n", argv[1]);
        exit(1);
    }

    memset(cmd, 0, BUFSIZ);
    snprintf(cmd, BUFSIZ, "./qshell account %s %s", key, secret);
    system(cmd);

    memset(cmd, 0, BUFSIZ);
    snprintf(cmd, BUFSIZ, "./qshell rput transfer %s %s", argv[1], argv[1]);
    system(cmd);

    memset(cmd, 0, BUFSIZ);
    snprintf(cmd, BUFSIZ, "rm -f ~/.qshell/account.json");
    system(cmd);

    return 0;
}
