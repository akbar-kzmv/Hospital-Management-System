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

    float doctorBalance;

    int appNumberDoc;
        

} Doctor;



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

typedef struct Feedback {
    Patient patient;

    char text[300];

} Feedback;

typedef struct Appointment {
    Patient patient;

    Doctor doctor;

    char service[30];

    char time[30];

    int payment;

    int status;

    int payed;

} Appointment;

int patientNumber = 0;
int doctorNumber = 0;
int appNumber = 0;
int WappNumber = 0;
int fedNumber = 0;

float hospitalIncome = 0;

char hospitalPassword[] = "admin";
void registerDoctor (Doctor **, Patient **);
void firstInterface(Patient **userList, Doctor **doctorList, Appointment **appList, Feedback **fedList);

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


void patientInterface(Patient *patient, Appointment **appList, Feedback **fedList, Doctor **doctorList){
    printf("Welcome, %s\n", (*patient).name);

    while(1){

    printf("---------------\n");
    printf("MAIN MENU\n");
    printf("---------------\n");

    printf("Patient Info (1)\nMedical History (2)\nMy Appointments (3)\nChange Personal Info (4)\nWrite a report (5)\nPay the service (6)\nExit (7)\n");

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
        if ((*patient).gender == 1) {
            printf("Gender: Male\n");
        }
        else {
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
                printf("Patient name and surname: %s %s\n", ((*patient).med_history[i]).patient.name, ((*patient).med_history[i].patient.surname));
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
            if ((!strcmp((*appList)[i].patient.name, (*patient).name)) && (*appList)[i].status == 0) {
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
        printf("Change your contact info (2)\n");
        printf("Back to previous menu (3)\n");
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
        Feedback feedback;
        getchar();
        printf("We value your feedback! Write your thoughts, advices or complaints: ");
        fgets(feedback.text, 300, stdin);
        feedback.text[strcspn(feedback.text, "\n")] = '\0';
        feedback.patient = (*patient);
        
        fedNumber++;

        Feedback *temp = realloc((*fedList), fedNumber * sizeof(Feedback));
        (*fedList) = temp;
        (*fedList)[fedNumber - 1] = feedback;
        
        break;
    case 6:
        for (int i = 0; i < (*patient).DappNumber; i++){
            if ((*patient).med_history[i].payed == 0) {
                printf("---------------\n");
                printf("Appointment ID %d\n", i + 1);
                printf("Name/Surname: %s %s\n", (*patient).name, (*patient).surname);
                printf("Doctor: Dr. %s %s\n", (*patient).med_history[i].doctor.name, (*patient).med_history[i].doctor.surname);
                printf("Service: %s\n", (*patient).med_history[i].doctor.specialisation);
                printf("Date: %s\n",(*patient).med_history[i].time);
                printf("Payment: %d₼\n", (*patient).med_history[i].payment);            
            }          
        }
        printf("Choose ID of appointment you want to pay: "); 
        int payID;
        scanf("%d", &payID);

        printf("---------------\n");
        for (int i = 0; i < 2; i++) {
            printf(".");
            fflush(stdout);
            sleep(1);
        }
        printf("\n");
         
        (*patient).med_history[payID - 1].payed = 1;

        for (int i = 0; i < doctorNumber; i++){
            if (!strcmp((*doctorList)[i].contactInfo, (*patient).med_history[payID - 1].doctor.contactInfo)){
                (*doctorList)[i].doctorBalance += ((*patient).med_history[payID - 1].payment)*0.8;
                (*patient).med_history[payID - 1].doctor.doctorBalance = (*doctorList)[i].doctorBalance;
                break;
            }
        }

        hospitalIncome += ((*patient).med_history[payID - 1].payment)*0.2;
        printf("Payment successful\n");
               
        break;
    case 7:
        return;
        break;
    }
}
    }
    

}

void userReport(Patient **userList){

    while (1){
    printf("---------------\n");
    printf("\tPATIENT REPORT PAGE\t\n");
    printf("---------------\n");

    printf("Total number of patients: %d\n", patientNumber);
    printf("---------------\n");
    printf("Age Distribution:\n");
    int ageBelow18 = 0;  //Teenagers
    int ageBetween18And35 = 0;
    int ageBetween35And60 = 0;
    int ageAbove60 = 0; //Retired 

    for (int i = 0; i <patientNumber; i++){
        if ((*userList)[i].age < 18){
            ageBelow18 ++;
        }
        else if((*userList)[i].age >= 18 && (*userList)[i].age < 35){
            ageBetween18And35++;
        }
        else if((*userList)[i].age >= 35 && (*userList)[i].age < 60){
            ageBetween35And60++;
        }
        else if((*userList)[i].age > 60){
            ageAbove60++;
        }
    }
    printf("Teen patients [0 - 18): %.2f%%\n", 100*(ageBelow18/(float)patientNumber));
    printf("Patients aged [18 - 35): %.2f%%\n", 100*(ageBetween18And35/(float)patientNumber));
    printf("Patients aged [35 - 60): %.2f%%\n", 100*(ageBetween35And60/(float)patientNumber));
    printf("Retitred patients [age > 60]: %.2f%%\n", 100*(ageAbove60/(float)patientNumber));
    printf("---------------\n");

    printf("Gender distribution: \n");
    int numberOfMalePatients = 0;
    int numberOfFemalePatients = 0;

    for (int i = 0; i < patientNumber; i++){
        if ((*userList)[i].gender == 1){
            numberOfMalePatients++;
        }
        else{
            numberOfFemalePatients++;
        }
    }

    printf("Male Patients: %.2f%%\n", 100*(numberOfMalePatients/(float)patientNumber));
    printf("Female Patients: %.2f%%\n", 100*(numberOfFemalePatients/(float)patientNumber));

    printf("---------------\n");

    
    
    printf("Back to previous menu (1)\n");
    int backToPreviousMenu = 0;
    scanf("%d",&backToPreviousMenu);
    if (backToPreviousMenu){
        break;
    }
    }

    
    
}

void doctorReport(Patient **userList, Doctor **doctorList) {
    printf("Doctor statictics Report: \n");
    printf("Total number of doctors: %d\n", doctorNumber);
    printf("Number of patients per doctor: \n");
    for (int i = 0; i < doctorNumber; i++) {
        int patientsPerDoc = 0;
        printf("Dr. %s %s: ", (*doctorList)[i].name, (*doctorList)[i].surname);
        for (int j = 0; j < patientNumber; j++) {
            if ((*userList)[j].assigned_doctor.contactInfo == (*doctorList)[i].contactInfo) {
                patientsPerDoc += 1;
            }
        }
        printf("%d\n", patientsPerDoc);

    }

    if (appNumber > 0) {
        printf("The busiest doctor: ");
        int maxApp = 0;
        Doctor busyDoc;
        for (int i = 0; i < appNumber; i++) {
            if ((*doctorList)[i].appNumberDoc > maxApp) {
                maxApp = (*doctorList)[i].appNumberDoc;
                busyDoc = (*doctorList)[i];
            }

        }
        printf("Dr. %s %s\n", busyDoc.name, busyDoc.surname);
    }

}

void revenueReport(Doctor **doctorList){
    printf("Hospital Income: %g₼\n", hospitalIncome);
    printf("Income of doctors: \n");
    for (int i = 0; i < doctorNumber; i++){
        printf("Dr. %s %s: %g₼\n", (*doctorList)[i].name, (*doctorList)[i].surname, (*doctorList)[i].doctorBalance);
        
    }
}
void hospitalInterface(Patient **userList, Doctor **doctorList, Appointment **appList, Feedback **fedList) {
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
        printf("Manage patients (1)\nManage doctors (2)\nManage appointments (3)\nRegister a doctor (4)\nView feedbacks (5)\nManage payments (6)\nGenerate reports (7)\nExit (8)\n");
        do {
            scanf("%d", &menu);
            if (menu < 1 || menu > 8) printf("Invalid number! Choose again!\n");
        } while(menu > 8 || menu < 1);

        switch (menu) {
            case 1:
                for (int i = 0; i < 2; i++) {
                    printf(".");
                    fflush(stdout);
                    sleep(1);
                }
                printf("\n----------------------\nView patients (1)\nDelete patient (2)\nAssign Doctor (3)\nBack (4)\n"); //Exit (4)
                scanf("%d", &submenu);

                if (submenu == 1) {
                    if (patientNumber > 0) {
                        int back;
                        while(1) {
                            printf("+-----------+------------+------------+------------+------------+---------------+------------------+\n");
                            printf(" %-10s | %-10s | %-10s | %-10s | %-10s | %-13s | %-16s |\n", "Id", "Name", "Surname", "Age", "Gender", "Contact Info", "Assigned doctor");
                            printf("+-----------+------------+------------+------------+------------+---------------+------------------+\n");
                            for (int i = 0; i < patientNumber; i++) {
                                char gnder[10];
                                char doc_name[22];
                                if ((*userList)[i].gender == 1) strcpy(gnder, "Male");
                                else if ((*userList)[i].gender == 0) strcpy(gnder, "Female");

                                if ((*userList)[i].isAssignedDoctor) { //Fix (No doctor assigned) to show
                                    strcpy(doc_name, (*userList)[i].assigned_doctor.name);
                                }
                                else strcpy(doc_name, "No doctor assigned\n");

                                printf(" %-10d | %-10s | %-10s | %-10d | %-10s | %-13s | %-16s\n", i+1, (*userList)[i].name, (*userList)[i].surname, (*userList)[i].age, gnder, (*userList)[i].contactInfo, doc_name);
                                
                                
                            }
                            printf("Back (1)\n");
                            do {
                                scanf("%d", &back);
                            } while(back != 1);

                            break;
                        }
                    }
                    else {
                        printf("No patients found!\n");
                    }
                }
                else if (submenu == 2) {
                    int delete = 1, delid;
                    char delname[30];
                    while(delete) {
                        printf("Enter the name of patient you want to delete: ");
                        scanf("%s", delname);
                        int patientexist = 0;

                        for (int i = 0; i < patientNumber; i++) {
                            if (!strcmp((*userList)[i].name, delname)) {
                                patientexist = 1;
                                break;
                            }
                        }
                        
                        
                        if (patientexist) {
                            printf("+-----------+------------+------------+------------+------------+---------------+------------------+\n");
                            printf(" %-10s | %-10s | %-10s | %-10s | %-10s | %-13s | %-16s |\n", "Id", "Name", "Surname", "Age", "Gender", "Contact Info", "Assigned doctor");
                            printf("+-----------+------------+------------+------------+------------+---------------+------------------+\n");
                            for (int i = 0; i < patientNumber; i++) {
                                if (!strcmp((*userList)[i].name, delname)) {
                                    char gnder[10];
                                    char doc_name[22];
                                    if ((*userList)[i].gender == 1) strcpy(gnder, "Male");
                                    else if ((*userList)[i].gender == 0) strcpy(gnder, "Female");

                                    if ((*userList)[i].isAssignedDoctor) {
                                        strcpy(doc_name, (*userList)[i].assigned_doctor.name);
                                    }
                                    else strcpy(doc_name, "No doctor assigned\n");

                                    printf(" %-10d | %-10s | %-10s | %-10d | %-10s | %-13s | %-16s\n", i+1, (*userList)[i].name, (*userList)[i].surname, (*userList)[i].age, gnder, (*userList)[i].contactInfo, doc_name);
                                }
                            }
                        
                            printf("Enter the exact id of patient you want to delete: ");
                            scanf("%d", &delid);
                            userDelete(userList, delid - 1);
                            delete = 0;
                        } else {
                            printf("There is no such patient\n");
                            int delexit;
                            printf("Do you want to exit? (1 - Yes | 0 - No): ");
                            scanf("%d", &delexit);
                            if (delexit) delete = 0;
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

                        printf("+-----------+------------+------------+------------+------------+---------------+------------------+\n");
                        printf(" %-10s | %-10s | %-10s | %-10s | %-10s | %-13s | %-16s |\n", "Id", "Name", "Surname", "Age", "Gender", "Contact Info", "Assigned doctor");
                        printf("+-----------+------------+------------+------------+------------+---------------+------------------+\n");
                        for (int i = 0; i < patientNumber; i++){
                            if (!strcmp(patientName, (*userList)[i].name)){
                                char gnder[10];
                                char doc_name[22];
                                if ((*userList)[i].gender == 1) strcpy(gnder, "Male");
                                else if ((*userList)[i].gender == 0) strcpy(gnder, "Female");

                                if ((*userList)[i].isAssignedDoctor) {
                                    strcpy(doc_name, (*userList)[i].assigned_doctor.name);
                                }
                                else strcpy(doc_name, "No doctor assigned\n");

                                printf(" %-10d | %-10s | %-10s | %-10d | %-10s | %-13s | %-16s\n", i+1, (*userList)[i].name, (*userList)[i].surname, (*userList)[i].age, gnder, (*userList)[i].contactInfo, doc_name);
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
                                }
                            }

                            if (isThereDoctor) {
                                printf("+-----------+------------+------------+----------------+------------+------------------+------------------+\n");
                                printf(" %-10s | %-10s | %-10s | %-16s | %-13s | %-10s | %-13s | %-10s |\n", "Id", "Name", "Surname", "Specialisation", "Contact Info", "Password", "Availability", "Income");
                                printf("+-----------+------------+------------+----------------+------------+------------------+------------------+\n");
                                for (int i = 0; i < doctorNumber; i++){
                                    if (!strcmp(doctorName, (*doctorList)[i].name)){
                                        printf(" %-10d | %-10s | %-10s | %-16s | %-13s | %-10s | %-13s | %-10f |\n", i+1, (*doctorList)[i].name, (*doctorList)[i].surname, (*doctorList)[i].specialisation, (*doctorList)[i].contactInfo, (*doctorList)[i].password, (*doctorList)[i].availability, (*doctorList)[i].doctorBalance);
                                    }
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
                else if (submenu == 4) {
                    break;
                }
                break;
            case 2:
                for (int i = 0; i < 2; i++) {
                    printf(".");
                    fflush(stdout);
                    sleep(1);
                }
                printf("\n----------------------\nView doctors (1)\nDelete doctor (2)\nExit (3)\n");
                scanf("%d", &submenu);

                if (submenu == 1) {
                    int back;
                    while(1) {
                        printf("+-----------+------------+------------+------------------+---------------+------------+---------------+------------+\n");
                        printf(" %-10s | %-10s | %-10s | %-16s | %-13s | %-10s | %-13s | %-10s |\n", "Id", "Name", "Surname", "Specialisation", "Contact Info", "Password", "Availability", "Income");
                        printf("+-----------+------------+------------+------------------+---------------+------------+---------------+------------+\n");
                        for (int i = 0; i < doctorNumber; i++) {
                            printf(" %-10d | %-10s | %-10s | %-16s | %-13s | %-10s | %-13s | %-10f |\n", i+1, (*doctorList)[i].name, (*doctorList)[i].surname, (*doctorList)[i].specialisation, (*doctorList)[i].contactInfo, (*doctorList)[i].password, (*doctorList)[i].availability, (*doctorList)[i].doctorBalance);
                        }

                        printf("Back (1)\n");
                            do {
                                scanf("%d", &back);
                            } while(back != 1);

                            break;
                    }
                }
                else if (submenu == 2) {
                    int delete = 1, delid;
                    char delname[30];
                    while(delete) {
                        printf("Enter the name of doctor you want to delete: ");
                        scanf("%s", delname);
                        int doctorexist = 0;

                        for (int i = 0; i < doctorNumber; i++) {
                            if (!strcmp((*doctorList)[i].name, delname)) {
                                doctorexist = 1;
                                break;
                            }
                        }
                        
                        if (doctorexist) {
                            printf("+-----------+------------+------------+----------------+------------+------------------+------------------+\n");
                            printf(" %-10s | %-10s | %-10s | %-16s | %-13s | %-10s | %-13s | %-10s |\n", "Id", "Name", "Surname", "Specialisation", "Contact Info", "Password", "Availability", "Income");
                            printf("+-----------+------------+------------+----------------+------------+------------------+------------------+\n");
                            for (int i = 0; i < doctorNumber; i++) {
                                if (!strcmp((*doctorList)[i].name, delname)) {
                                    printf(" %-10d | %-10s | %-10s | %-10s | %-10s | %-13s | %-16s | %-10f |\n", i+1, (*doctorList)[i].name, (*doctorList)[i].surname, (*doctorList)[i].specialisation, (*doctorList)[i].contactInfo, (*doctorList)[i].password, (*doctorList)[i].availability, (*doctorList)[i].doctorBalance);
                                }
                            }
                        
                            printf("Enter the exact id of doctor you want to delete: ");
                            scanf("%d", &delid);
                            doctorDelete(doctorList, delid - 1);
                            delete = 0;
                        } else {
                            printf("There is no such doctor\n");
                            int delexit;
                            printf("Do you want to exit? (1 - Yes | 0 - No): ");
                            scanf("%d", &delexit);
                            if (delexit) delete = 0;
                        }
                    }
                }
                else if (submenu == 3) {
                    break;
                }
                break;

            case 3:
                for (int i = 0; i < 3; i++) {
                    printf(".");
                    fflush(stdout);
                    sleep(1);
                }
                printf("\n"); 
                
                if (appNumber > 0) {
    
                    printf("+-----------+-------------------------+------------+----------------------+\n");
                    printf(" %-10s | %-23s | %-10s | %-20s |\n", "Id", "Patient's Fullname", "Service", "Date");
                    printf("+-----------+-------------------------+------------+----------------------+\n");
                    for (int i = 0; i < doctorNumber; i++) {
                        printf("Dr. %s %s\n", (*doctorList)[i].name, (*doctorList)[i].surname);
                        printf("Specialisation: %s\n", (*doctorList)[i].specialisation);
                        printf("Anticipated appointments: \n");
                        for (int j = 0; j < appNumber; j++) {
                            if (!strcmp((*appList)[j].doctor.name, (*doctorList)[i].name) && !(*appList)[j].status) {
                                printf("+-----------+-------------------------+------------+----------------------+\n");
                                printf(" %-10d | %-10s %-12s | %-10s | %-20s |\n", j+1, (*appList)[j].patient.name, (*appList)[j].patient.surname, (*appList)[j].service, (*appList)[j].time);
                                printf("+-----------+-------------------------+------------+----------------------+\n");
                            }
                        }
                        printf("\n");
                    }
                }
                else {
                    printf("No scheduled appointments\n");
                }
                
                break;
            case 4:
                registerDoctor(doctorList, userList);
                break;
                
            case 5:
                printf("Reports: \n");

                for (int i = 0; i < fedNumber; i++) {
                    printf("%s | %s %s\n\n", (*fedList)[i].text, (*fedList)[i].patient.name, (*fedList)[i].patient.surname);
                }
                
                break;
            case 7:
                while (1){
                    int choose;
                    printf("Report sections: \n");
                    printf("----------------------\n");
                    printf("Patient Report (1)\n");
                    printf("Doctor Report (2)\n");
                    printf("Revenue Report (3)\n");

                    scanf("%d", &choose);
                    
                    if (choose == 1){
                        userReport(userList);
                        
                    }
                    else if(choose == 2){
                        doctorReport(userList, doctorList);
                    }
                    else if(choose == 3){
                        revenueReport(doctorList);
                    }
                    printf("----------------------\n");              

                    printf("Back to previous menu (4)\n");
                    int backToPreviousMenu;
                    scanf("%d", &backToPreviousMenu);
                    if (backToPreviousMenu == 4){
                        break;
                    }
                }
                
                break;
            case 8:
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
        printf("Manage your appointments (1)\nSchedule an appointment (2)\nChange your settings (3)\nView your patients - assigned to you (4)\nShow Balance (5)\nExit (6)\n");
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

                    printf("Delete appointment (1)\nMark as done (2)\nChange appointment (3)\n"); //Exit(4)
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

                            int patientID = -1;

                            for (int i = 0; i < patientNumber; i++) {
                                if (!strcmp((*userList)[i].contactInfo, (*appList)[appid - 1].patient.contactInfo)) {
                                    patientID = i;
                                    break;
                                }
                            }

                            if (patientID == -1) {
                                for (int i = 0; i < patientNumber; i++) {
                                    if (!strcmp((*userList)[i].name, (*appList)[appid - 1].patient.name) &&
                                        !strcmp((*userList)[i].surname, (*appList)[appid - 1].patient.surname)) {
                                        patientID = i;
                                        break;
                                    }
                                }
                            }

                            if (patientID != -1) {
                                (*appList)[appid - 1].status = 1;
                                WappNumber -= 1;

                                (*userList)[patientID].DappNumber++;

                                Appointment *temp = realloc((*userList)[patientID].med_history,
                                                            (*userList)[patientID].DappNumber * sizeof(Appointment));

                                if (temp == NULL) {
                                    printf("Memory allocation failed\n");
                                    (*userList)[patientID].DappNumber--;
                                    break;
                                }

                                (*userList)[patientID].med_history = temp;
                                (*userList)[patientID].med_history[(*userList)[patientID].DappNumber - 1] = (*appList)[appid - 1];

                                printf("----------------------\nAppointment marked as done succesfully\n");
                            }
                            else {
                                printf("Patient not found. Appointment was not added to medical history.\n");
                            }

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
            while(1){
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
                app.payed = 0;

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
                (*doctor).appNumberDoc += 1;

                printf("\nAppointment scheduled successfully\n");

                for (int i = 0; i < 2; i++) {
                    printf(".");
                    fflush(stdout);
                    sleep(1);
                }
                printf("Back to previous page (1)\n");
                int backToPreviousPage;
                scanf("%d", &backToPreviousPage);
                if (backToPreviousPage){
                    break;                    
                }
            }
                

                break;
            case 3:
                while(1){
                    printf("----------------------\n");
                    int ch;
                    printf("Enter '1' if you want to change setting & '0' if you do not want to change\n");
                    printf("Name: %s | Change? ", (*doctor).name);
                    scanf("%d", &ch);
                    if (ch) {
                        printf("Enter new name: ");
                        scanf("%s", (*doctor).name);
                    }
                    
                    printf("Surname: %s | Change? ", (*doctor).surname);
                    scanf("%d", &ch);
                    if (ch) {
                        printf("Enter new surname: ");
                        scanf("%s", (*doctor).surname);
                    }

                    printf("Password: %s", (*doctor).password);
                    scanf("%d", &ch);
                    if (ch) {
                        printf("Enter new surname: ");
                        scanf("%s", (*doctor).password);
                    }

                    printf("Specialisation: %s", (*doctor).specialisation);
                    scanf("%d", &ch);
                    if (ch) {
                        printf("Enter new specialisation: ");
                        scanf("%s", (*doctor).specialisation);
                    }

                    printf("Contact Info: %s", (*doctor).contactInfo);
                    scanf("%d", &ch);
                    if (ch) {
                        printf("Enter new contact info: ");
                        scanf("%s", (*doctor).contactInfo);
                    }

                    printf("Availability: %s", (*doctor).availability);
                    scanf("%d", &ch);
                    if (ch) {
                        printf("Enter new availability time: ");
                        getchar();
                        fgets((*doctor).availability, 30, stdin);
                        (*doctor).availability[strcspn((*doctor).availability, "\n")] = '\0';
                    }
                    printf("----------------------\n");

                    printf("Back to previous page (1)\n");
                    int backToPreviousPage;
                    scanf("%d", &backToPreviousPage);
                    if (backToPreviousPage){
                        break;                    
                    }
                }
                break;                
            case 4:
                while(1){
                    printf("----------------------\n");
                    printf("Assigned Patients\n");
                    int assignedUserId = 0;
                    for (int i = 0; i < patientNumber; i++){
                        if (!strcmp((*userList)[i].assigned_doctor.name, (*doctor).name)){
                            assignedUserId++;
                            printf("Assigned user %d\n", assignedUserId);
                            printf("Patient Name/Surname: %s %s\n",(*userList)[i].name, (*userList)[i].surname);
                            if ((*userList)[i].gender == 1){
                                printf("Gender: Male\n");
                            }
                            else{
                                printf("Gender: Male\n");
                            }
                            
                            printf("Age: %d\n", (*userList)[i].age);
                            printf("Contact info: %s\n", (*userList)[i].contactInfo);
                            printf("----------------------\n");
                        }
                    }

                    printf("Back to previous page (1)\n");
                    int backToPreviousPage;
                    scanf("%d", &backToPreviousPage);
                    if (backToPreviousPage){
                        break;                    
                    }
                }
                break;
            case 5:
                printf("Current Balance: %g\n", (*doctor).doctorBalance);
                break;
            case 6:
                return;
                break;

        }
    }
}

void registerDoctor (Doctor **doctorList, Patient **userList){

    Doctor doctor;
    doctor.doctorBalance = 0;
    doctor.appNumberDoc = 0;
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

    patient.DappNumber = 0;
    patient.med_history = NULL;

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


void loginInterface(Patient **userList, Doctor **doctorList, Appointment **appList, Feedback **fedList) {
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
            hospitalInterface(userList, doctorList, appList, fedList);
            return;
        }

        for (int i = 0; i < patientNumber; i++){
            if (!strcmp(password, (*userList)[i].password) && !strcmp(contactInfo, (*userList)[i].contactInfo)){
                logincycle = 0;
                patientInterface(&(*userList)[i], appList, fedList, doctorList);
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





void firstInterface(Patient **userList, Doctor **doctorList, Appointment **appList, Feedback **fedList){
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
            loginInterface(userList, doctorList, appList, fedList);
        }
        else if(!strcmp(choosing, "register")){
            patientNumber += 1;
            registerInterface(userList, doctorList);
        }
        else if(!strcmp(choosing, "exit")){
            break;
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

    Feedback *fedList = malloc(fedNumber * sizeof(Feedback));

    firstInterface(&userList, &doctorList, &appList, &fedList);

    



    free(userList);
    free(doctorList);


    return 0;
}
