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
    char surn
