#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
//Fix Doctor Login
//Fix availability to register with number that is already registered*

typedef enum Gender {
    Male = 1,
    Female = 2
} Gender;

typedef struct Doctor {

    char name[20];
    char surname[20];

    char password[30];

    char specialisation[30];

    char contactInfo[15];

    char availability[30];
    

} Doctor ;


typedef struct Patient {

    char name[20];
    char surname[20];

    char password[30];


    int age;

    Gender gender;

    char contactInfo[15];

    char *med_history;

    Doctor assigned_doctor;

} Patient;

int patientNumber = 0;
int doctorNumber = 0;

char hospitalPassword[] = "admin";
void registerDoctor (Patient *,Doctor **);
void firstInterface(Patient *userList, Doctor *doctorList);

void patientInterface(Patient *patient){
    printf("Welcome, %s\n", (*patient).name);
}

void hospitalInterface(Patient *userList, Doctor *doctorList) {
    int menu;
    int submenu;

    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        sleep(1);
    }
    printf("\nTotal number of patients in the system: %d\n", patientNumber);
    printf("Total number of doctors in the system: %d\n----------------------\n", doctorNumber);
    printf("Choose your action and press proper number:\n");
    printf("Manage patients (1)\nManage doctors (2)\nManage appointments (3)\nRegister a doctor (4)\nView reports (5)\nManage payments (6)\nExit (7)\n");
    do {
        scanf("%d", &menu);
        if (menu < 1 || menu > 7) printf("Invalid number! Choose again!\n");
    } while(menu > 7 || menu < 1);

    switch (menu) {
        case 1:
            for (int i = 0; i < 2; i++) {
                printf(".");
                fflush(stdout);
                sleep(1);
            }
            printf("\n----------------------\nView patients (1)\nDelete patient (2)\n");
            scanf("%d", &submenu);

            if (submenu == 1) {
                for (int i = 0; i < patientNumber; i++) {
                    printf("Patient #%d\n", i+1);
                    printf("Name: %s\n", userList[i].name);
                    printf("Surname: %s\n", userList[i].surname);
                    printf("Age: %d\n", userList[i].age);
                    if (userList[i].gender == 1) {
                        printf("Gender: Male\n");
                    }
                    else if (userList[i].gender == 2) {
                        printf("Gender: Female\n");
                    }
                    printf("Contact info: %s\n", userList[i].contactInfo);
                    printf("Password: %s\n", userList[i].password);
                    //Medical history remains*
                    printf("----------------------\n");
                }
            }
            break;
        case 2:
            for (int i = 0; i < 2; i++) {
                printf(".");
                fflush(stdout);
                sleep(1);
            }
            printf("\n----------------------\nView doctors (1)\nDelete doctor (2)\n");
            scanf("%d", &submenu);

            if (submenu == 1) {
                for (int i = 0; i < doctorNumber; i++) {
                    printf("Doctor #%d\n", i+1);
                    printf("Name: %s\n", doctorList[i].name);
                    printf("Surname: %s\n", doctorList[i].surname);
                    printf("Specialisation: %s\n", doctorList[i].specialisation);
                    printf("Availability: %s\n", doctorList[i].availability);
                    printf("Contact Info: %s\n", doctorList[i].contactInfo);
                    printf("Password: %s\n", doctorList[i].password);
                    printf("----------------------\n");
                }
            }
            break;
        case 4:
            registerDoctor(userList, &doctorList);
            break;
        
        case 7:
            return;
            break;
    }
}

void doctorInterface (Doctor *doctor){
    printf("Welcome, dear Dr. %s", (*doctor).name);
}

void registerDoctor (Patient *userList, Doctor **doctorList){

    Doctor doctor;

    doctorNumber++;

    printf("Enter name: ");
    scanf("%s", doctor.name);

    printf("Enter surname: ");
    scanf("%s", doctor.surname);

    printf("Enter password: ");
    scanf("%s", doctor.password);

    printf("Enter specialisation: ");
    scanf("%s", doctor.specialisation);

    printf("Enter contact info: ");
    scanf("%s", doctor.contactInfo);
    getchar();

    printf("Time availability: ");
    fgets(doctor.availability, 30, stdin);
    doctor.availability[strcspn(doctor.availability, "\n")] = '\0';

    Doctor *temp = realloc(*doctorList, doctorNumber * sizeof(Doctor));
    *doctorList = temp;
    (*doctorList)[doctorNumber-1] = doctor;

    hospitalInterface(userList, *doctorList);   

}

void lowercase (char *word){
    while(*word){
        *word = tolower(*word);
        
        word++;
    }
}


void registerInterface(Patient **userList,Doctor **doctorList, int patientNumber){


    Patient patient;
    int gnd;


    printf("Enter name: ");
    scanf("%s", patient.name);

    printf("Enter surname: ");
    scanf("%s", patient.surname);

    printf("Enter your age: ");
    scanf("%d", &patient.age);

    printf("Enter gender (1 - Male | 2 - Female): ");
    scanf("%d", &gnd);
    patient.gender = gnd;

    printf("Set a password: ");
    scanf("%s", patient.password);

    printf("Enter your contact info: ");
    scanf("%s", patient.contactInfo);

    Patient *temp = realloc(*userList, patientNumber * sizeof(Patient));
    *userList = temp;
    (*userList)[patientNumber-1] = patient;

    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        sleep(1);
    }

    printf("\nDear %s, ", (*userList)[patientNumber - 1].name);

    printf("Registration successful!\n");
    
    printf("Redirecting to main menu");
    for (int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        sleep(1);
    }
    printf("\n----------------------\n");
    return;

}


void loginInterface(Patient *userList, Doctor *doctorList, int patientNumber, int doctorNumber){
    int logincycle = 1;

    while(logincycle) {
        printf("Enter your phone number: ");
        char contactInfo[15];
        scanf("%s", contactInfo);
        
        if (!strcmp(contactInfo, "back")) {
            printf("----------------------\n");
            return;
        }

        printf("Enter your password: ");
        char password[30];
        scanf("%s", password);

        if (!strcmp(password, "back")) {
            printf("----------------------\n");
            return;
        }
        
        if (!strcmp(password, hospitalPassword) && !strcmp(contactInfo, "admin")) {
            logincycle = 0;
            hospitalInterface(userList, doctorList);
            return;
        }

        for (int i = 0; i < patientNumber; i++){
            if (!strcmp(password, userList[i].password) && !strcmp(contactInfo, userList[i].contactInfo)){
                logincycle = 0;
                patientInterface(&userList[i]);
                return;
            }
        }

        for(int i = 0; i < doctorNumber; i++){
            if (!strcmp(password, doctorList[i].password) && !strcmp(contactInfo, doctorList[i].contactInfo)){
                logincycle = 0;
                doctorInterface(&doctorList[i]);
                return;
            }
        }
        printf("Wrong credentials! Try again!\n");
    }
    
}





void firstInterface(Patient *userList, Doctor *doctorList){
    while(1) {
        printf("Welcome to the Hospital Management System\n");
        printf("░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
        printf("░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░████▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
        printf("░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
        printf("░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░▓▓░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
        printf("░░░░░░░░░░░░░░░░        ░░░░░░░░░░░░░░░░░░░░░░  ▓▓▓▓▓▓░░░░░░░░▒▒░░░░░░░░░░░░░░░░░░\n");
        printf("░░░░░░░░░░░░░░░░        ░░░░░░░░░░░░░░░░░░░░░░░░▓▓▓▓░░░░░░░░░░▒▒▒▒▒▒░░░░░░░░░░░░░░\n");
        printf("░░░░░░░░░░░░░░  ██▓▓▓▓██░░░░░░░░░░░░░░░░░░░░░░▓▓▓▓▓▓▓▓░░░░░░░░▒▒▒▒▒▒░░░░░░░░░░░░░░\n");
        printf("░░░░░░░░░░░░░░▓▓▓▓▓▓██▓▓▓▓░░░░░░░░░░░░░░░░░░  ▓▓▒▒  ▓▓██░░░░░░▒▒▒▒▒▒░░░░░░░░░░░░░░\n");
        printf("░░░░      ░░░░        ▒▒▓▓░░░░░░░░▒▒▒▒▒▒░░░░  ▓▓▒▒▓▓▓▓▓▓░░░░░░▒▒░░▒▒░░░░░░░░░░░░░░\n");
        printf("░░  ▓▓██▓▓░░░░  ▒▒▒▒▒▒░░▓▓░░░░░░░░▒▒▒▒▒▒░░░░  ▓▓░░  ░░▓▓░░░░░░▒▒░░▒▒░░░░░░░░░░░░░░\n");
        printf("░░░░▓▓▓▓  ░░░░  ░░░░    ▓▓░░░░░░░░  ▒▒▒▒░░░░  ▓▓▒▒▒▒░░▓▓░░░░░░▒▒░░▒▒░░░░          \n");
        printf("░░░░▒▒▒▒▒▒░░░░  ░░░░    ▓▓░░░░░░░░░░▒▒▒▒░░░░  ▓▓░░    ▓▓░░░░░░▒▒░░▒▒░░░░░░░░░░░░░░\n");
        printf("░░░░▓▓▓▓▒▒░░░░          ▓▓░░░░░░░░▒▒▒▒░░░░░░  ▓▓░░    ▓▓░░░░▒▒░░░░▒▒▒▒░░░░░░░░  ░░\n");
        printf("░░░░▒▒▓▓  ░░░░          ▓▓░░░░░░▒▒▒▒▒▒░░░░░░  ▓▓░░    ▓▓░░░░▒▒░░▒▒▒▒▒▒░░░░░░░░  ░░\n");
        printf("░░░░  ░░░░░░░░  ░░░░░░  ▓▓░░░░▒▒▒▒▒▒▒▒░░░░░░  ▓▓░░▓▓░░▓▓░░░░▒▒░░▒▒▒▒▒▒░░░░░░░░  ░░\n");
        printf("░░▓▓▒▒▓▓▒▒░░░░▒▒▒▒▒▒████▓▓░░░░▒▒▒▒▒▒▒▒░░░░▒▒░░▓▓▓▓▓▓▒▒██░░░░▒▒▒▒▒▒▒▒▒▒░░░░░░░░░░░░\n");

        printf("Choose your following step: (Write 'back' to return)\n");
        printf("Login\n");
        printf("Register\n----------------------\n");


        againInput :

        char choosing[10];
        scanf("%s", choosing);

        lowercase(choosing);

        if (!strcmp(choosing, "login")){
            loginInterface(userList, doctorList, patientNumber, doctorNumber);
        }
        else if(!strcmp(choosing, "register")){
            patientNumber += 1;
            registerInterface(&userList, &doctorList, patientNumber);
        }
        else{
            printf("Invalid opeartion\n");
            goto againInput;
        }   
    }
}



int main(void){
    Patient *userList = malloc(patientNumber * sizeof(Patient));

    Doctor *doctorList = malloc(doctorNumber * sizeof(Doctor));


    firstInterface(userList, doctorList);

    


    free(userList);
    free(doctorList);


    return 0;
}
