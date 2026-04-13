#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Doctor {

    char name[20];
    char surname[20];

    char *password;

    char *specialisation;

    char contactInfo[15];

    char availability[3];
    

} Doctor ;


typedef struct Patient {

    char name[20];
    char surname[20];

    char *password;


    int age;
    char gender[7];

    char contactInfo[15];

    char *med_history;

    Doctor assigned_doctor;

}Patient;


char *hospitalPassword = "ufaz2026";

void userInterface(void){}


void lowercase (char *word){
    while(*word){
        *word = tolower(*word);
        
        word++;
    }
}


void registerInterface(Patient *userList, int patientNumber){

    Patient patient;


    printf("Enter name: ");
    scanf("%s", patient.name);

    printf("Enter surname: ");
    scanf("%s", patient.surname);

    printf("Enter your age: ");
    scanf("%d", &patient.age);

    printf("Enter gender: ");
    scanf("%s", patient.gender);

    printf("Set a password: ");
    scanf("%s", patient.password);

    printf("Enter your contact info: ");
    scanf("%s", patient.contactInfo);

    Patient *temp = realloc(userList, patientNumber*sizeof(Patient));
    userList = temp;
    userList[patientNumber-1] = patient ;

}


void loginInterface(Patient *userList, int patientNumber){

    printf("Enter the contact info: ");
    char contactInfo[15];
    scanf("%s", contactInfo);


    printf("Enter password:");
    char *password;
    scanf("%s", password);

    for (int i = 0; i < patientNumber; i++){
        if (!strcmp(password, userList[patientNumber].password) && !strcmp(contactInfo, userList[patientNumber].contactInfo)){
            userInterface();
            return;
        }
    }

    printf("Wrong credentials!\n");




        
    

}


void firstInterface(void){
    
    int patientNumber = 0;

    Patient *userList = malloc(patientNumber*sizeof(Patient));

    printf("Login\n");
    printf("Register\n");

    
    againInput :

    char choosing[10];
    scanf("%s", choosing);

    lowercase(choosing);

    if (!strcmp(choosing, "login")){
        loginInterface(userList, patientNumber);
    }
    else if(!strcmp(choosing, "register")){
        patientNumber ++;
        registerInterface(userList, patientNumber);
    }
    else{
        printf("Invalid opeartion\n");
        goto againInput;
    }
    } 



int main(void){

        firstInterface();

    return 0;
}#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Doctor {

    char name[20];
    char surname[20];

    char *password;

    char *specialisation;

    char contactInfo[15];

    char availability[3];
    

} Doctor ;


typedef struct Patient {

    char name[20];
    char surname[20];

    char *password;


    int age;
    char gender[7];

    char contactInfo[15];

    char *med_history;

    Doctor assigned_doctor;

}Patient;


char *hospitalPassword = "ufaz2026";

void userInterface(void){}


void lowercase (char *word){
    while(*word){
        if (*word >= 'A' && *word <='Z'){
            *word = *word + 32;
        }
        word++;
    }
}


void registerInterface(Patient *userList, int patientNumber){

    Patient patient;


    printf("Enter name: ");
    scanf("%s", patient.name);

    printf("Enter surname: ");
    scanf("%s", patient.surname);

    printf("Enter your age: ");
    scanf("%d", &patient.age);

    printf("Enter gender: ");
    scanf("%s", patient.gender);

    printf("Set a password: ");
    scanf("%s", patient.password);

    //printf("Enter your contact info: ");
    //scanf("%s", patient.contactInfo);

    Patient *temp = realloc(userList, patientNumber*sizeof(Patient));
    userList = temp;
    userList[patientNumber-1] = patient ;

}


void loginInterface(Patient *userList, int patientNumber){

    printf("Enter the contact info: ");
    char *contactInfo;
    scanf("%s", contactInfo);


    printf("Enter password:");
    char *password;
    scanf("%s", password);

    for (int i = 0; i < patientNumber; i++){
        if (!strcmp(password, userList[patientNumber].password) && !strcmp(contactInfo, userList[patientNumber].contactInfo)){
            userInterface();
        }
        else{
            printf("Invalid user info\n");
            return ;
            
        }
    }

        
    

}


void firstInterface(void){
    
    int patientNumber = 0;

    Patient *userList = malloc(patientNumber*sizeof(Patient));

    printf("Login\n");
    printf("Register\n");

    
    againInput :

    char choosing[10];
    scanf("%s", choosing);

    lowercase(choosing);

    if (!strcmp(choosing, "login")){
        loginInterface(userList, patientNumber);
    }
    else if(!strcmp(choosing, "register")){
        patientNumber ++;
        registerInterface(userList, patientNumber);
    }
    else{
        printf("Invalid opeartion\n");
        goto againInput;
    }
    } 



int main(void){

        firstInterface();

    return 0;
}
