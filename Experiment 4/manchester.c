#include<stdio.h>
#include<string.h>
#define MAX 100

// Differential Manchester Encoding
void differentialManchester(char str[]){
    int prev = 0;
    for (int i = 0; i < strlen(str); i++){
        if (str[i] == '0'){
            printf("%d%d",prev,!prev);
            prev=!prev;
        }
        else if (str[i] == '1'){
            printf("%d%d",!prev,prev);
        }
        else{
            printf("Invalid input\n");
            return;
        }
    }
}

// Manchester Encoding
void manchester(char *str){
    for (int i = 0; i < strlen(str); i++){
        if (str[i] == '0')
            printf("10");
        else
            printf("01");
    }
    printf("\n");
}

int main(){
    char str[MAX];
    printf("Enter a string: ");
    scanf("%s", str);
    getchar();
    manchester(str);
    differentialManchester(str);
    return 0;
}