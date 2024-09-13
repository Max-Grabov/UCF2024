#include <string.h>
#include <stdio.h>

int main(){
    char s[300];
    char temp[300];
    scanf("%s", s);
    int len = strlen(s);

    for(int i = 1; i < 26; i++){
        for(int j = 0; j < 26; j++){
            //if(i * j < 26) continue;
            if((i * j) % 26 != 1) continue;

            for(int k = 0; k < 26; k++){
                for(int x = 0; x < len; x++){
                    temp[x] = 'a' + (((j * (s[x] - 'a') - k) + 26) % 26);
                }
                temp[len] = '\0';

            printf("With values %d for i, %d for j, and %d for k, the message is %s\n", i, j, k, temp);
            }
        }
    }
}

//The Original encoded message for my reference

//bjdwqbccnwdmhphuizsbcieruxsdurrizcdwsrnbtudxwsrernabnsdfwwsrerqfwxsrerjdiducptudxnwsrpnhpwsrnrxhwrenheruwxshwwsrpfnriwdqrqfwbjdwmrdmcrqhztduchuixsdzdfuwdulr