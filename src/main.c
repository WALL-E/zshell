#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <openssl/md5.h>

#define TRY_MAX 3


int md5sum(const char *from, char *to)
{
    unsigned char md[16];
    char tmp[3] = {'\0'};
    int i;

    MD5(from, strlen(from), md);
    for (i=0; i<16; i++){
        sprintf(tmp, "%2.2x", md[i]);
        strcat(to, tmp);
    }

    return 0;
}

int main(int argc, char *argv[])
{
    char cmd[BUFSIZ];
    char secret[BUFSIZ] = "Ir1v9NkmY3CnNxYs9ntPCY35MUWpW56hTaHgXXXX";
    char *password = "1d99a5252a3c99ce677c690552cc86eb";
    char key[BUFSIZ] = "67JCJinBYKH3tdng5wmM2uqOHQ5BaYW7OYo7XXXX";
    char *prompt = "Password:";
    char *ptr = NULL;
    char to[40] = {'\0'};
    int try = 0;

    if (argc != 2) {
        printf("Usage: %s file\n", argv[0]);
        exit(1);
    }

    while(1) {
        ptr = getpass(prompt);
        md5sum(ptr, to);
        if ((ptr != NULL) && (0 == strncmp(to, password, strlen(password)))) {
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

    printf("Download url: %s%s\n", "http://opduyrvvz.bkt.clouddn.com/", argv[1]);

    return 0;
}
