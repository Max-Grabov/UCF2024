#include <string.h>
#include <stdio.h>

int main(){
    //size big enough for the homework
    char s[100];
    scanf("%s", s);
    int len = strlen(s);
    for(int i = 1; i < 26; i++){
        for(int j = 0; j < len; j++){
            s[j] + 1 > 'z' ? s[j] = 'a' : s[j]++;
        }

        printf("using a shift of %d, the message is %s\n\n", i, s);
    }
}

//The Original encoded messages for my reference

//eqapqvomdmzgwvmiozmibnittamumabmz

//ncdaodnmzgvodqzgtzvntojwmzvfviyvggjrnnopyzionojbzopnzyojoczxtxgdxivopmzjahjy
