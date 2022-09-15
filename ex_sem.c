// ввод строк до END, вводим кол-во всех символов

#include <stdio.h>
#define MAX_STR 255

char sbuffer[MAX_STR];
int string[MAX_STR];

int main(void)
{
char c;
int i, j, flag;
flag = 0;

for (i = 0; i <= MAX_STR; i++) 
    sbuffer[i] = 0;
    
printf("Enter strings: \n");

while (flag == 0) {
    i = 0;
    while (flag == 0 && (c = getchar()) != '\n' && i <= MAX_STR) {
        string[i] = c;
        sbuffer[c] ++;
        i ++;
        if (i >= 3) 
            if (string[i - 3] == 'E' && string[i - 2] == 'N' && string[i - 1] == 'D') 
                flag = 1;
    }
    //for (j = 0; j < i; j++)
    //    printf("%c", string[j]);
    //printf("\n");
}
for (i = 0; i <= MAX_STR; i++) {
    if (sbuffer[i] != 0) 
        printf("Count of '%c' is %d\n", i, sbuffer[i]);
}
return 0;
}