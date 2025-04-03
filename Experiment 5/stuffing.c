#include<stdio.h>
#include<string.h>
#define MAX 100
#define FLAG '%'
#define ESC '\'

// Character count encoding
void charStuffing(char *str){
    for(int i = 0; i < strlen(str); i++){

    }
}

int main(){
    char str[MAX];
    printf("Enter a string: "); // enter a line with spaces included
    
    int choice;
    while (choice != 7){
        printf("Character Count:\n");
        printf("1. Transmitter\n");
        printf("2. Receiver\n");
        printf("Bit Stuffing\n");
        printf("3. Transmitter\n");
        printf("4. Reciever\n");
        printf("Byte Stuffing\n");
        printf("5. Transmitter\n");
        printf("6. Reciever\n");
        printf("7. Exit\n");
        switch (choice){
        case 1:
            charStuffing(str);
            break;
        case 2:
            charDestuffing(str);
            break;
        case 3:
            bitStuffing(str);
            break;
        case 4:
            bitDestuffing(str);
            break;
        case 5:
            byteStuffing(str);
            break;
        case 6:
            byteDestuffing(str);
            break;
        default:
            printf("Invalid choice\n");
        }
    }
}