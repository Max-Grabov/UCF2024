#include <string.h>
#include <stdio.h>
int main(){
    char s[200];
    char tmp[200];
    int x,y;
    scanf("%s", s);
    scanf("%d %d", &x, &y);

    int len = strlen(s);
    tmp[len] = '\0';

    for(int i = 0; i < len; i++){
        tmp[i] = 'a' + ((x*(s[i] - 'a') + y) % 26);
    }
    printf("%s\n", tmp);
}

//whyisitsounbearablyhotinfloridaalsothankyouforgradingthis