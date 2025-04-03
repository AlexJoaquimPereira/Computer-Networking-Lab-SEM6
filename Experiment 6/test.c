#include <stdio.h>
#include <stdlib.h>

int data[4];
int code[7];
int rec[7];

void transmiter(int data[4],int code[7]){
    code[2]=data[0];
    code[4]=data[1];
    code[5]=data[2];
    code[6]=data[3];

    code[0]=code[2]^code[4]^code[6];
    code[1]=code[2]^code[5]^code[6];
    code[3]=code[4]^code[5]^code[6];
}

void receiver (int rec[7]){
    int p1,p2,p3,errorPos;
    p1 = rec[0]^rec[2]^rec[4]^rec[6];
    p2 = rec[1]^rec[2]^rec[5]^rec[6];
    p3 = rec[3]^rec[4]^rec[5]^rec[6];

    errorPos = p1 * 1 + p2 * 2 + p3 * 4;

    if (errorPos == 0)
        printf("No errors detected\n");
    else{
        printf("Error detected at position %d\n",errorPos);
        rec[errorPos-1]^=1;

        printf("Corrected Hamming code:");
        for(int i=0;i<7;i++)
            printf("%d ",rec[i]);
        printf("\n");
    }

    printf("Extracted data bits: %d %d %d %d\n",rec[2],rec[4],rec[5],rec[6]);
}
int main(){
    int choice;
    
    do{
        printf("1. Transmitter\n");\
        printf("2. Receiver\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice){
            case 1:
                printf("Enter 4 bit data: ");
                for(int i=0;i<4;i++)
                    scanf("%d", &data[i]);
                transmiter(data,code);

                printf("Encoded data: ");
                for(int i=0;i<7;i++)
                    printf("%d",code[i]);
                printf("\n");
                break;
            case 2:
                printf("Enter recieved 7 bit code:");
                for(int i=0;i<7;i++)
                    scanf("%d",&rec[i]);
                receiver(rec);
                break;                
            case 3:
                break;
            default:
                printf("Invalid input\n");
        }
    }while(choice != 3);
    return 0;

}