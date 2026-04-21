#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>


//Fix in ALL cases -> error showing if I enter incorrect username/doctorname and so on*

typedef struct Appointment Appointment;


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

    Appointment *med_history;

    int DappNumber;

    Doctor assigned_doctor;

    int isAssignedDoctor;


} Patient;

typedef struct Appointment {
    Patient patient;

    Doctor doctor;

    char service[30];

    char time[30];

    int payment;

    int status;

} Appointment;

int patientNumber = 0;
int doctorNumber = 0;
int appNumber = 0;
int WappNumber = 0;

char hospitalPassword[] = "admin";
void registerDoctor (Doctor **, Patient **);
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

void appDelete(Appointment **appList, int id) {
    for (int i = 0; i < 2; i++) {
        printf(".");
        fflush(stdout);
        sleep(1);
    }
    printf("\n");

    appNumber -= 1;
    WappNumber -= 1;

    for (int i = id; i < appNumber; i++) {
        (*appList)[i] = (*appList)[i+1];
    }

    Appointment *temp = realloc(*appList, appNumber * sizeof(Appointment));
    *appList = temp;

    printf("Appointment deleted successfully\n");
}


void patientInterface(Patient *patient, Appointment **appList){
    printf("Welcome, %s\n", (*patient).name);
   
        

    while(1){

    printf("---------------\n");
    printf("MAIN MENU\n");
    printf("---------------\n");

    printf("Patient Info (1)\nMedical History (2)\nMy Appointments(3)\nChange Personal Info(4)\nExit(5)\n");

    printf("Enter the submenu number: ");
    int subMenu;
    scanf("%d", &subMenu);

    while (subMenu <= 0){
        printf("Wrong input\n");
        printf("Enter the submenu number: ");
        scanf("%d", &subMenu);    

    }
    switch (subMenu)
    {
    case 1:
    while(1){
        printf("---------------\n");
        printf("Name: %s\n", (*patient).name);
        printf("Surname: %s\n", (*patient).surname);
        printf("Age: %d\n", (*patient).age);
        if ((*patient).gender == 1){
            printf("Gender: Male\n");
        }
        else{
            printf("Gender: Female\n");
        }
        printf("Contact info: %s\n", (*patient).contactInfo);
        printf("---------------\n");

        printf("Back to previous menu (1)\n");
        int backToPrevousMenu = 0;
        scanf("%d", &backToPrevousMenu);
        if (backToPrevousMenu){
            break;
        }

    }

        break;

    case 2: //Fix
        printf("---------------\n");
        if ((*patient).DappNumber == 0) {
            printf("Empty\n");
        }
        else{
            for (int i = 0; i < (*patient).DappNumber; i++){
                printf("---------------\n");
                printf("Appointment %d\n", i+1);
                printf("Patient name and surname: %s %s\n", (*patient).med_history[i].patient.name, ((*patient).med_history[i].patient.surname));
                printf("Doctor name and surname: %s %s\n", (*patient).med_history[i].doctor.name, (*patient).med_history[i].doctor.surname);
                printf("Service: %s\n", (*patient).med_history[i].doctor.specialisation);
                printf("Date: %s\n", (*patient).med_history[i].time);
                printf("Payment: %d\n", (*patient).med_history[i].payment);
                printf("---------------\n");
            }
        }
        break;
    case 3:
    while(1){
        printf("---------------\n");

        if(!(*patient).isAssignedDoctor){
            printf("No assigned doctor\n");
            printf("---------------\n");
        }
        else {   
            printf("About my doctor: \n");

            

            printf("Name: %s\n", (*patient).assigned_doctor.name); 
            printf("Surname: %s\n", (*patient).assigned_doctor.surname);
            printf("Specialisation: %s\n", (*patient).assigned_doctor.specialisation);
            printf("Contact Info: %s\n", (*patient).assigned_doctor.contactInfo);
            printf("Availability: %s\n", (*patient).assigned_doctor.availability);
            printf("---------------\n");
        }
        

        printf("Your appointments: \n");
        for (int i = 0; i < appNumber; i++) {
            if (!strcmp((*appList)[i].patient.name, (*patient).name)) {
                printf("Appoinment #%d\n", i + 1);
                printf("Doctor: Dr. %s %s\n",(*appList)[i].doctor.name, (*appList)[i].doctor.surname);
                printf("Service: %s\n", (*appList)[i].service);
                printf("Date: %s\n", (*appList)[i].time);
                printf("Payment: %d₼\n", (*appList)[i].payment);
                printf("---------------\n");
            }
        }

        printf("Back to previous menu (1)\n");
        int backToPrevousMenu = 0;
        scanf("%d", &backToPrevousMenu);
        if (backToPrevousMenu){
            break;
        }
    }
        break;

    
        
        
    case 4:
        while(1){
        printf("---------------\n");
        printf("Change your password (1)\n");
        printf("Change your contact info(2)\n");
        printf("Back to previous menu(3)\n");
        printf("---------------\n");

        printf("Choose one submenu: ");
        int newSubMenu;
        scanf("%d", &newSubMenu);

        if (newSubMenu == 1){
            char newPassword[30];
            while(1){
            printf("---------------\n");
            printf("Enter new password: "); 
            scanf("%s", newPassword);
            if (!strcmp(newPassword, (*patient).password)){
                printf("Same with last one!\a\n");
                printf("Try again\n");
            }
            else{
                strcpy(patient->password, newPassword);
                printf("Password was changed succesfully\n");
                break;
            }
        }
        }
        else if(newSubMenu == 2){
            char newContactInfo[15];
            while(1){
            printf("---------------\n");
            printf("Enter new number: ");
            scanf("%s", newContactInfo);
            if (!strcmp(newContactInfo, (*patient).contactInfo)){
                printf("Same with last one!\a\n");
                printf("Try again\n");
            }
            else{
                strcpy(patient->contactInfo, newContactInfo);
                printf("Contact Info was changed succesfully\n");
                break;
            }
        }
        
        }
        else if (subMenu == 3){
            break;
        }
        break;
    case 5:
        return;
        break;
    }
}
    }
    

}

void hospitalInterface(Patient **userList, Doctor **doctorList, Appointment **appList) {
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
                else if(submenu == 3) { 
                    char patientName[30];
                    char doctorName[30];
                    int patientId = 0;
                    int doctorId = 0;

                    //Should be fixed
                    int isTherePatient = 0;

                    while (!isTherePatient) {
                        printf("Enter patient's name you want to assign a doctor to: ");
                        scanf("%s", patientName);



                        for (int i = 0; i < patientNumber; i++){
                            if (!strcmp(patientName, (*userList)[i].name)){
                                printf("Patient id: %d\n", i+1);
                                printf("Name: %s\n", (*userList)[i].name);
                                printf("Surname: %s\n",(*userList)[i].surname);
                                isTherePatient = 1;

                                printf("----------------------\n");

                            }
                            
                        }

                        if (!isTherePatient){
                            printf("There is no such patient\n");
                            sleep(1);
                            printf("Do you want to exit? |YES| or |NO|");
                            char yesOrNo[4];
                            scanf("%s", yesOrNo);

                            if (!strcmp(yesOrNo,"NO")){
                                isTherePatient = 0;
                            }
                            else if (!strcmp(yesOrNo, "YES")) {
                                break;
                            }
                        }

                        if (isTherePatient) {
                            printf("Enter ID of patient you want to assign a doctor: ");
                            scanf("%d", &patientId);

                            
                            int isThereDoctor = 0;

                            printf("Enter the name of doctor that you want to assign patient in %d ID: ", patientId);
                            scanf("%s", doctorName);
                    

                            for (int i = 0; i < doctorNumber; i++){
                                if (!strcmp(doctorName, (*doctorList)[i].name)){
                                    isThereDoctor++;
                                    printf("Doctor ID: %d\n", i+1);
                                    printf("Name: %s\n", (*doctorList)[i].name);
                                    printf("Surname: %s\n", (*doctorList)[i].surname);
                                    printf("Specialisation: %s\n", (*doctorList)[i].specialisation);
                                    printf("----------------------\n");
                                }
                            }
                            if (!isThereDoctor){
                                printf("There is no such a doctor\n");
                                sleep(1);
                                printf("Do you want to exit? |YES| or |NO|");
                                char yesOrNo[4];
                                scanf("%s", yesOrNo);

                                if (!strcmp(yesOrNo,"NO")){
                                    isThereDoctor = 0;
                                }
                                else if (!strcmp(yesOrNo, "YES")) {
                                    break;
                                }
                            }

                            if (isThereDoctor) {
                                printf("Enter ID of doctor you want to choose: ");
                                scanf("%d", &doctorId);

                                (*userList)[patientId - 1].assigned_doctor = (*doctorList)[doctorId - 1];
                                (*userList)[patientId - 1].isAssignedDoctor = 1;
                                printf("Doctor assigned successfully!\n");
                            }
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
                for (int i = 0; i < 3; i++) {
                    printf(".");
                    fflush(stdout);
                    sleep(1);
                }
                printf("\n"); 
                
                for (int i = 0; i < doctorNumber; i++) {
                    printf("----------------------\n");
                    printf("Dr. %s %s\n", (*doctorList)[i].name, (*doctorList)[i].surname);
                    printf("Specialisation: %s\n", (*doctorList)[i].specialisation);
                    printf("---\nAnticipated appointments: \n");
                    for (int j = 0; j < appNumber; j++) {
                        printf("----------------------\n");
                        if (!strcmp((*appList)[j].doctor.name, (*doctorList)[i].name) && !(*appList)[j].status) {
                            printf("Appointment #%d\n", i+1);
                            printf("Patient: %s %s\n", (*appList)[j].patient.name, (*appList)[j].patient.surname);
                            printf("Service: %s\n", (*appList)[j].service);
                            printf("Date: %s\n", (*appList)[j].time);
                            printf("Payment: %d₼\n", (*appList)[j].payment);
                        }
                    }
                }

                break;
            case 4:
                registerDoctor(doctorList, userList);
                break;
        
            case 7:
                return;
                break;
        }
    }
}

void doctorInterface (Doctor *doctor, Patient **userList, Appointment **appList){
    printf("Welcome, dear Dr. %s\n", (*doctor).name);
    int menu, submenu, appid;
    while (1) {
        printf("----------------------\n");
        printf("Manage your appointments (1)\nSchedule an appointment (2)\nChange your settings (3)\nView your patients - assigned to you (4)\nExit (5)\n");
        scanf("%d", &menu);

        switch(menu) {
            case 1:
                for (int i = 0; i < 2; i++) {
                    printf(".");
                    fflush(stdout);
                    sleep(1);
                }
                printf("\n");
                
                if (WappNumber > 0) { //Fix WappNumber* It should count the number of Waiting appointmnets for EACH DOCTOR separately* (Not generally)
                    printf("Anticipated appointments\n----------------------\n");
                    for (int i = 0; i < appNumber; i++) {
                        if (!strcmp((*appList)[i].doctor.name, (*doctor).name) && (*appList)[i].status == 0) {
                            printf("Appointment #%d\n", i + 1);
                            printf("Doctor: Dr. %s\n", (*appList)[i].doctor.name);
                            printf("Patient: %s %s\n", (*appList)[i].patient.name, (*appList)[i].patient.surname);
                            printf("Service: %s\n", (*appList)[i].service);
                            printf("Date: %s\n", (*appList)[i].time);
                            printf("Payment: %d₼\n", (*appList)[i].payment);
                            printf("----------------------\n");
                        }
                    }

                    printf("Delete appointment (1)\nMark as done (2)\nChange appointment (3)\n");
                    scanf("%d", &submenu);

                    switch(submenu) {
                        case 1:
                            printf("Enter appointment id you want to delete: ");
                            scanf("%d", &appid);
                            appDelete(appList, appid-1);
                            break;

                        case 2:
                            printf("Enter appoitment id you want to mark as done: ");
                            scanf("%d", &appid);
                            (*appList)[appid - 1].status = 1;
                            WappNumber -= 1;
                            printf("----------------------\nAppointment marked as done succesfully\n");
                            //Here should be billing part*
                            (*appList)[appid - 1].patient.DappNumber++;

                            Appointment *temp = realloc((*appList)[appid - 1].patient.med_history, (*appList)[appid - 1].patient.DappNumber * sizeof(Appointment));
                            (*appList)[appid - 1].patient.med_history = temp;

                            (*appList)[appid - 1].patient.med_history[(*appList)[appid - 1].patient.DappNumber - 1] = (*appList)[appid - 1];

                            
                            break;
                        case 3:
                            printf("Enter appointment id you want to change: ");
                            scanf("%d", &appid);

                            for (int i = 0; i < 2; i++) {
                                printf(".");
                                fflush(stdout);
                                sleep(1);
                            }
                            printf("\n");
                            printf("Enter '1' if you want to change and '0' if you do not want to change\n");
                            int ch;
                            printf("Patient: %s %s | Change? ", (*appList)[appid - 1].patient.name, (*appList)[appid - 1].patient.surname);
                            scanf("%d", &ch);
                            if (ch) {
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
                                (*appList)[appid - 1].patient = (*userList)[id-1];
                                printf(".\n");
                                
                            }
                            printf("Date: %s | Change? ", (*appList)[appid - 1].time);
                            scanf("%d", &ch);
                            if (ch) {
                                getchar();
                                printf("Enter new time for the appointment: ");
                                fgets((*appList)[appid - 1].time, 30, stdin);
                                (*appList)[appid - 1].time[strcspn((*appList)[appid - 1].time, "\n")] = '\0';
                                printf(".\n");
                            }
                            printf("Payment: %d₼ | Change? ", (*appList)[appid - 1].payment);
                            scanf("%d", &ch);
                            if (ch) {
                                printf("Enter new cost of the service: ");
                                scanf("%d", &(*appList)[appid - 1].payment);
                                printf(".\n");
                            }

                            for (int i = 0; i < 3; i++) {
                                printf(".");
                                fflush(stdout);
                                sleep(1);
                            }
                            printf("\nChanges applied succesfully\n");

                            break;
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

                app.status = 0;

                appNumber += 1;
                WappNumber += 1;
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

            case 5:
                return;
                break;
        }
    }
}

void registerDoctor (Doctor **doctorList, Patient **userList){

    Doctor doctor;
    char doctorContactInfo[30];
    doctorNumber++;

    printf("Enter name: ");
    scanf("%s", doctor.name);

    printf("Enter surname: ");
    scanf("%s", doctor.surname);

    printf("Enter password: ");
    scanf("%s", doctor.password);

    printf("Enter specialisation: ");
    scanf("%s", doctor.specialisation);

    while(1){
        int sameNumberCount = 0;
    
    printf("Enter contact info: ");
    scanf("%s", doctorContactInfo);
    

    for (int i = 0; i < doctorNumber; i++){
        if (!strcmp(doctorContactInfo, (*doctorList)[i].contactInfo)){
            printf("Number already taken!\n");
            sameNumberCount++;
            break;
        }
    
        if (i == doctorNumber - 1){
            for (int j = 0; j < patientNumber; j++){
                if (!strcmp(doctorContactInfo, (*userList)[j].contactInfo)){
                printf("This number already taken!\n");
                sameNumberCount++;
                break;
                }
            }   
        }
        else if (!strcmp(doctorContactInfo, "admin")){
            printf("You are not authorized!\n");
            sameNumberCount++;
            break;
        }
        
    }
    if (sameNumberCount == 0){
        strcpy(doctor.contactInfo, doctorContactInfo);
        break;
    }

    }
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


void registerInterface(Patient **userList, Doctor **doctorList){


    Patient patient;
    int gnd;
    char patientContactInfo[15];

    patient.isAssignedDoctor = 0;
   

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

    patient.med_history = malloc(0*sizeof(Appointment));
    patient.DappNumber = 1;

    while (1){
    int sameNumberCount = 0;

    printf("Enter your contact info: ");
    scanf("%s", patientContactInfo);

    for(int i = 0; i < patientNumber; i++){
        if(!strcmp(patientContactInfo, (*userList)[i].contactInfo)){
            printf("This number already taken!\n");
            sameNumberCount++;
            break;
            
        }
        if (i == patientNumber - 1){
            for (int j = 0; j < doctorNumber; j++){
                if (!strcmp(patientContactInfo, (*doctorList)[j].contactInfo)){
                printf("This number already taken!\n");
                sameNumberCount++;
                break;
                }
            }   
        }
        else if (!strcmp(patientContactInfo, "admin")){
            printf("You are not authorized!\n");
            sameNumberCount++;
            break;
        }
        
    }
    if (sameNumberCount == 0){
        strcpy(patient.contactInfo, patientContactInfo);
        break;
    }


    }

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
            hospitalInterface(userList, doctorList, appList);
            return;
        }

        for (int i = 0; i < patientNumber; i++){
            if (!strcmp(password, (*userList)[i].password) && !strcmp(contactInfo, (*userList)[i].contactInfo)){
                logincycle = 0;
                patientInterface(&(*userList)[i], appList);
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
            registerInterface(userList, doctorList);
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
