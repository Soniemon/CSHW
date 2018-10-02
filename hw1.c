//Arvind Sundar
//afs170230
#include <ctype.h>
#include <stdio.h>
#include <string.h>

void mainMenu();
void readName();
void enterPassword();
void passCriteria(char[]);
void goAgain();

int main() {
    mainMenu();
    return 0;
}

void mainMenu(){
    int holder;

    printf("Choose which function you want use \n");
    printf("1. Name input function \n");
    printf("2. Password criteria checker \n");

    scanf("%d", &holder);
    getchar();
    do{
        if (holder == 1) {
            readName();
        }
        if (holder == 2) {
            enterPassword();
        }
        if(holder!=1 && holder!= 2){
            puts("Please enter valid number");
            scanf("%d", &holder);
            getchar();
        }
    }
    while(holder!=1 && holder!= 2);
}

void readName() {
    char firstName[21] = {'\0'};
    char middleName[21] = {'\0'};
    char lastName[21] = {'\0'};
    char fullInput[63];
    char output[64];
    int num = 0;
    int index = 0;
    int len;
    puts("Please input your First, Middle, then Last name separated by spaces \n");
    gets(fullInput);
    for(int i = 0; i < 63; i++){

        if(num == 0) {
            if (fullInput[i]!=' '){
                firstName[index] = fullInput[i];
                index++;
            }
            if (fullInput[i] == ' ') {
                firstName[index] = '\0';
                num++;
                index = 0;
                continue;
            }
        }
        if(num == 1) {
            if (fullInput[i]!=' '){
                middleName[index] = fullInput[i];
                index++;
            }
            if (fullInput[i] == ' ') {
                middleName[index] = '\0';
                num++;
                index = 0;
                continue;
            }
        }
        if(num == 2) {
            if (fullInput[i]!=' '){
                lastName[index] = fullInput[i];
                index++;
            }
            if (fullInput[i] == ' ') {
                lastName[index] = '\0';
                num++;
                index = 0;
                continue;
            }
        }
        if (fullInput[i] == '\0'){
            break;
        }
    }
    printf("\n");
    strcat(output, lastName);
    strcat(output,", ");
    strcat(output, firstName);
    strcat(output," ");
    strcat(output, middleName);
    printf("%s\n\n", output);
    goAgain();
}

void passCriteria(char password[]) {
    int upperFlag = 0;
    int lowerFlag = 0;
    int digFlag = 0;
    int punctFlag = 0;
    int inBoundFlag = 0;
    int len;

    len = strlen(password);

    if (len <= 14 || len >= 6){
        inBoundFlag = 1;
    }
    if (len > 14){
        inBoundFlag = -1;
    }
    if (len < 6){
        inBoundFlag = -2;
    }

    for(int i = 0; i<15; i++) {
        if(isupper(password[i])){
            upperFlag = 1;
        }
        if(islower(password[i])){
            lowerFlag = 1;
        }
        if(isdigit(password[i])){
            digFlag = 1;
        }
        if(ispunct(password[i])){
            punctFlag = 1;
        }
    }

    if(upperFlag == 0 || lowerFlag == 0 || digFlag == 0 || punctFlag == 0 || inBoundFlag == -1 || inBoundFlag == -2) {
        puts("You're password is invalid because: \n");
        if(upperFlag == 0) {
            puts("You have no uppercase characters\n");
        }
        if(lowerFlag == 0) {
            puts("You have no lowercase characters\n");
        }
        if(digFlag == 0) {
            puts("You have no digits\n");
        }
        if(punctFlag == 0) {
            puts("You have no punctuation\n");
        }
        if(inBoundFlag == -1) {
            puts("Your password is too long\n");
        }
        if(inBoundFlag == -2) {
            puts("Your password is too short\n");
        }
        enterPassword();

    }
    else {
        puts("Valid Password\n");
    }

}

void enterPassword(){
    char password[15];
    puts("Please enter your password\n");
    gets(password);
    passCriteria(password);
    goAgain();
}

void goAgain(){
    int holder;
    puts("Would you like to: \n");
    puts("1. Reset Program\n");
    puts("2. Exit Program");
    scanf("%d", &holder);
    getchar();
    do{
        if (holder == 1) {
            mainMenu();
        }
        if(holder!=1 && holder!= 2){
            puts("Please enter valid number");
            scanf("%d", &holder);
            getchar();
        }
    }
    while(holder!=1 && holder!= 2);
}
