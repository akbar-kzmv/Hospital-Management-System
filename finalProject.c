#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

//Fix Doctor Login*
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

typedef struct Appointment {
    Patient patient;

    Doctor doctor;

    char service[30];

    char time[30];

    int payment;

} Appointment;

int patientNumber = 0;
int doctorNumber = 0;
int appNumber = 0;

char hospitalPassword[] = "admin";
void registerDoctor (Doctor **);
void firstInterface(Patient **userList, Doctor **doctorList, Appointment **appList);

void userDelete(Patient **userList, int id) {
    for (int i = 0; i < 2; i++) {
        printf(".");
        fflush(stdout);
        sleep(1);
    }
    printf("\n");

    patientNumber -= 1;

    for (int i = id; i < patientNumber; i++) {
        (*userList)[i] = (*userList)[i+1];
    }

    Patient *temp = realloc(*userList, patientNumber * sizeof(Patient));
    *userList = temp;

    printf("Patient deleted successfully\n");
}

void doctorDelete(Doctor **doctorList, int id) {
    for (int i = 0; i < 2; i++) {
        printf(".");
        fflush(stdout);
        sleep(1);
    }
    printf("\n");

    doctorNumber -= 1;

    for (int i = id; i < doctorNumber; i++) {
        (*doctorList)[i] = (*doctorList)[i+1];
    }

    Doctor *temp = realloc(*doctorList, doctorNumber * sizeof(Doctor));
    *doctorList = temp;

    printf("Doctor deleted successfully\n");
}

void patientInterface(Patient *patient){
    printf("Welcome, %s\n", (*patient).name);
}

void hospitalInterface(Patient **userList, Doctor **doctorList) {
    int menu;
    int submenu; 

    while(1) {
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
                printf("\n----------------------\nView patients (1)\nDelete patient (2)\nAssign Doctor(3)\n");
                scanf("%d", &submenu);

                if (submenu == 1) {
                    for (int i = 0; i < patientNumber; i++) {
                        printf("Patient #%d\n", i+1);
                        printf("Name: %s\n", (*userList)[i].name);
                        printf("Surname: %s\n", (*userList)[i].surname);
                        printf("Age: %d\n", (*userList)[i].age);
                        if ((*userList)[i].gender == 1) {
                            printf("Gender: Male\n");
                        }
                        else if ((*userList)[i].gender == 2) {
                            printf("Gender: Female\n");
                        }
                        printf("Contact info: %s\n", (*userList)[i].contactInfo);
                        printf("Password: %s\n", (*userList)[i].password);
                        if ((*userList)[i].assigned_doctor.name) { //Fix (No doctor assigned) to show
                            printf("Assigned doctor: Dr. %s\n", (*userList)[i].assigned_doctor.name);
                        }
                        else printf("No doctor assigned\n"); 
                        //Medical history remains*
                        printf("----------------------\n");
                    }
                }
                else if (submenu == 2) {
                    int delete = 1, delid;
                    char delname[30];
                    while(delete) {
                        printf("Enter the name of patient you want to delete: ");
                        scanf("%s", delname);
                        
                        if (patientNumber > 0) {
                            for (int i = 0; i < patientNumber; i++) {
                                if (!strcmp((*userList)[i].name, delname)) {
                                    printf("Patient id: %d\n", i+1);
                                    printf("Patient name: %s\n", (*userList)[i].name);
                                    printf("Patient surname: %s\n", (*userList)[i].surname);
                                    printf("----------------------\n");
                                }
                            }
                        
                            printf("Enter the exact id of patient you want to delete: ");
                            scanf("%d", &delid);
                            userDelete(userList, delid - 1);
                            delete = 0;
                        } else {
                            printf("There is no patient(s) to delete\n");
                            delete = 0;
                        }
                    }
                }
                else if(submenu == 3){ //Fix (if I entered wrong patient/doctor name/id)
                    char patientName[30];
                    char doctorName[30];

                    printf("Enter patient's name you want to assign a doctor to: ");
                    scanf("%s", patientName);

                    int patientId = 0;
                    int doctorId = 0;


                    for (int i = 0; i < patientNumber; i++){
                        if (!strcmp(patientName, (*userList)[i].name)){
                            printf("Patient id: %d\n", i+1);
                            printf("Name: %s\n", (*userList)[i].name);
                            printf("Surname: %s\n",(*userList)[i].surname);

                            printf("----------------------\n");

                        }
                        printf("Enter ID of patient you want to assign a doctor: ");
                        scanf("%d", &patientId);


                        printf("Enter the name of doctor that you want to assign patient in %d ID: ", patientId);
                        scanf("%s", doctorName);


                        for (int i = 0; i < doctorNumber; i++){
                            if (!strcmp(doctorName, (*doctorList)[i].name)){
                                printf("Doctor ID: %d\n", i+1);
                                printf("Name: %s\n", (*doctorList)[i].name);
                                printf("Surname: %s\n", (*doctorList)[i].surname);
                                printf("Specialisation: %s\n", (*doctorList)[i].specialisation);
                                printf("----------------------\n");
                            }

                            printf("Enter ID of doctor you want to choose: ");
                            scanf("%d", &doctorId);

                            (*userList)[patientId - 1].assigned_doctor = (*doctorList)[doctorId - 1];

                            printf("Doctor assigned successfully!\n");
                        }
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
                        printf("Name: %s\n", (*doctorList)[i].name);
                        printf("Surname: %s\n", (*doctorList)[i].surname);
                        printf("Specialisation: %s\n", (*doctorList)[i].specialisation);
                        printf("Availability: %s\n", (*doctorList)[i].availability);
                        printf("Contact Info: %s\n", (*doctorList)[i].contactInfo);
                        printf("Password: %s\n", (*doctorList)[i].password);
                        printf("----------------------\n");
                    }
                }
                else if (submenu == 2) {
                    int delete = 1, delid;
                    char delname[30];
                    while(delete) {
                        printf("Enter the name of doctor you want to delete: ");
                        scanf("%s", delname);
                        
                        if (doctorNumber > 0) {
                            for (int i = 0; i < doctorNumber; i++) {
                                if (!strcmp((*doctorList)[i].name, delname)) {
                                    printf("Doctor id: %d\n", i+1);
                                    printf("Doctor name: %s\n", (*doctorList)[i].name);
                                    printf("Doctor surname: %s\n", (*doctorList)[i].surname);
                                    printf("Doctor specialisation: %s\n", (*doctorList)[i].specialisation);
                                    printf("----------------------\n");
                                }
                            }
                        
                            printf("Enter the exact id of doctor you want to delete: ");
                            scanf("%d", &delid);
                            doctorDelete(doctorList, delid - 1);
                            delete = 0;
                        } else {
                            printf("There is no doctor(s) to delete\n");
                            delete = 0;
                        }
                    }
                }
                break;

            case 3:
                
            case 4:
                registerDoctor(doctorList);
                break;
        
            case 7:
                return;
                break;
        }
    }
}

void doctorInterface (Doctor *doctor, Patient **userList, Appointment **appList){
    printf("Welcome, dear Dr. %s\n", (*doctor).name);
    int menu, submenu;
    while (1) {
        printf("\n----------------------\n");
        printf("Manage your appointments (1)\nSchedule an appointment (2)\nChange your settings (3)\nExit (4)\n");
        scanf("%d", &menu);

        switch(menu) {
            case 1:
                for (int i = 0; i < 2; i++) {
                    printf(".");
                    fflush(stdout);
                    sleep(1);
                }
                printf("\n");
                
                if (appNumber > 0) {
                    for (int i = 0; i < appNumber; i++) {
                        if (!strcmp((*appList)[i].doctor.name, (*doctor).name)) {
                            printf("Appointment #%d\n", i + 1);
                            printf("Doctor: Dr. %s\n", (*appList)[i].doctor.name);
                            printf("Patient: %s\n", (*appList)[i].patient.name);
                            printf("Service: %s\n", (*appList)[i].service);
                            printf("Payment: %d₼\n", (*appList)[i].payment);
                            printf("----------------------\n");
                        }
                    }
                } else printf("No scheduled appointments\n");

                break;
            case 2:
                char name[30];
                int id;
                printf("Enter the name of patient you want to make an appointment with: ");
                scanf("%s", name);

                for (int i = 0; i < patientNumber; i++) {
                    if (!strcmp(name, (*userList)[i].name)) {
                        printf("Patient id: %d\n", i+1);
                        printf("Patient name: %s\n",  (*userList)[i].name);
                        printf("Patient surname: %s\n", (*userList)[i].surname);
                        printf("----------------------\n");
                    }
                }

                printf("Enter the exact id of patient: ");
                scanf("%d", &id);
                getchar();

                Appointment app;
                app.patient = (*userList)[id-1];
                app.doctor = (*doctor);
                strcpy(app.service, (*doctor).specialisation);
                
                printf("Enter the date/time of appointment: ");
                fgets(app.time, 30, stdin);
                app.time[strcspn(app.time, "\n")] = '\0';

                printf("Enter the cost of the service: ");
                scanf("%d", &app.payment);

                appNumber += 1;
                Appointment *temp = realloc((*appList), appNumber * sizeof(Appointment));
                *appList = temp;
                (*appList)[appNumber - 1] = app;

                for (int i = 0; i < 2; i++) {
                    printf(".");
                    fflush(stdout);
                    sleep(1);
                }

                printf("\nAppointment scheduled successfully\n");

                for (int i = 0; i < 2; i++) {
                    printf(".");
                    fflush(stdout);
                    sleep(1);
                }


                break;

            case 4:
                return;
                break;
        }
    }
}

void registerDoctor (Doctor **doctorList){

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

    return;   

}


void lowercase (char *word){
    while(*word){
        *word = tolower(*word);
        
        word++;
    }
} //We do not use this function anywhere (except firstInterface). Can be fixed!


void registerInterface(Patient **userList){


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


void loginInterface(Patient **userList, Doctor **doctorList, Appointment **appList) {
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
            if (!strcmp(password, (*userList)[i].password) && !strcmp(contactInfo, (*userList)[i].contactInfo)){
                logincycle = 0;
                patientInterface(&(*userList)[i]);
                return;
            }
        }

        for(int i = 0; i < doctorNumber; i++){
            if (!strcmp(password, (*doctorList)[i].password) && !strcmp(contactInfo, (*doctorList)[i].contactInfo)){
                logincycle = 0;
                doctorInterface(&(*doctorList)[i], userList, appList);
                return;
            }
        }
        printf("Wrong credentials! Try again!\n");
    }
    
}





void firstInterface(Patient **userList, Doctor **doctorList, Appointment **appList){
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
            loginInterface(userList, doctorList, appList);
        }
        else if(!strcmp(choosing, "register")){
            patientNumber += 1;
            registerInterface(userList);
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

    Appointment *appList = malloc(appNumber * sizeof(Appointment));


    firstInterface(&userList, &doctorList, &appList);

    free(userList);
    free(doctorList);


    return 0;
}
