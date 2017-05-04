#include<stdio.h>
#include<string.h>
#include<openssl/md5.h>

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
    char from[40] = "123456";
    char to[40] = {'\0'};
    
    md5sum(from, to);
    printf("md5sum: %s\n", to);

    return 0;
}
