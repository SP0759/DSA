#include <stdio.h>
#include <string.h>
 
typedef struct person {
    char lastName[15];
    char firstName[15];
    char age[4];
} Person;
 
void blank100();
void tenEntry();
void printTen();
void updateRecord();
void deleteRecord();
 
int main(void) {
 
    blank100();
    tenEntry();
    printTen();
    updateRecord();
    printTen();
    deleteRecord();
    printTen();
}
 
// Creates 100 blank entries
void blank100() {
    
    FILE* wfPtr;
    if ((wfPtr = fopen("nameage.txt", "wb")) == NULL) {
        puts("Error opening nameage.txt for writing");
        return;
    }
 
    Person blankPerson = { "", "", "0" };
 
    for (int i0 = 0; i0 < 100; ++i0) {
        fwrite(&blankPerson, sizeof(Person), 1, wfPtr);
    }
    fclose(wfPtr);
}
 
// Fills ten entries
void tenEntry() {
 
    FILE* wfPtr;
    if ((wfPtr = fopen("nameage.txt", "wb")) == NULL) {
        puts("Error opening nameage.txt for writing");
        return;
    }
 
    Person p0 = { "Anderly", "Charley", "54" };
    Person p1 = { "Schultz", "Gilberto", "67" };
    Person p2 = { "Cuevas", "Abbigail", "34" };
    Person p3 = { "Rhodes", "Gregory", "83" };
    Person p4 = { "Taylor", "Giovanna", "78" };
    Person p5 = { "Glenn", "Kole", "54" };
    Person p6 = { "Reilly", "Dennis", "41" };
    Person p7 = { "Morrix", "Shannon", "27" };
    Person p8 = { "Herman", "Mekhi", "84" };
    Person p9 = { "Beltran", "Damari", "30" };
    Person p10 = { "Pawar", "Sumit", "19" };
 
    fwrite(&p0, sizeof(Person), 1, wfPtr);
    fwrite(&p1, sizeof(Person), 1, wfPtr);
    fwrite(&p2, sizeof(Person), 1, wfPtr);
    fwrite(&p3, sizeof(Person), 1, wfPtr);
    fwrite(&p4, sizeof(Person), 1, wfPtr);
    fwrite(&p5, sizeof(Person), 1, wfPtr);
    fwrite(&p6, sizeof(Person), 1, wfPtr);
    fwrite(&p7, sizeof(Person), 1, wfPtr);
    fwrite(&p8, sizeof(Person), 1, wfPtr);
    fwrite(&p9, sizeof(Person), 1, wfPtr);
    fwrite(&p10, sizeof(Person), 1, wfPtr);
 
    fclose(wfPtr);
}
 
// Prints the first ten entries
void printTen() {
 
    FILE* rfPtr;
    if ((rfPtr = fopen("nameage.txt", "rb")) == NULL) {
        puts("Error opening nameage.txt for reading");
        return;
    }
 
    Person toScreen = { "", "", "0" };
 
    for (int i0 = 0; fread(&toScreen, sizeof(Person), 1, rfPtr) && i0 < 11; ++i0) {
        printf("%s, %s, %s\n", toScreen.lastName, toScreen.firstName, toScreen.age);
    }
    puts("");
    fclose(rfPtr);
}
 
// updates one record with a new age value
void updateRecord() {
    
    FILE* rpfPtr;
    if ((rpfPtr = fopen("nameage.txt", "rb+")) == NULL) {
        puts("Error opening nameage.txt r+");
    }
 
    Person newData = { "", "", "0" };
    printf("Enter existing lastName, firstName, newAge: ");
    char line[50];
    fgets(line, 50, stdin);
    char* token = strtok(line, ", \n");
    strcpy(newData.lastName, token);
    token = strtok(NULL, ", \n");
    strcpy(newData.firstName, token);
    token = strtok(NULL, ", \n");
    strcpy(newData.age, token);
    
    Person search = { "", "", "0" };
    while (fread(&search, sizeof(Person), 1, rpfPtr) && strcmp(search.lastName, newData.lastName)) {
        
    }
    if (strcmp(search.lastName, newData.lastName) == 0) {
        fseek(rpfPtr, -1 * (int)sizeof(Person), SEEK_CUR);
        fwrite(&newData, sizeof(Person), 1, rpfPtr);
    }
    else {
        puts("Record not found.\n");
    }
 
    fclose(rpfPtr);
}
 
// deletes one record
void deleteRecord() {
    FILE* fPtr;
    if ((fPtr = fopen("nameage.txt", "rb+")) == NULL) {
        puts("Error opening nameage.txt r+");
    }
 
    Person userEntry = { "", "", "0" };
    printf("Delete existing lastName, firstName, age: ");
    char line[50];
    fgets(line, 50, stdin);
    char* token = strtok(line, ", \n");
    strcpy(userEntry.lastName, token);
    token = strtok(NULL, ", \n");
    strcpy(userEntry.firstName, token);
    token = strtok(NULL, ", \n");
    strcpy(userEntry.age, token);
 
    Person search = { "", "", "0" };
    while (fread(&search, sizeof(Person), 1, fPtr) && strcmp(search.lastName, userEntry.lastName)) {
 
    }
    if (strcmp(search.lastName, userEntry.lastName) == 0) {
        fseek(fPtr, -1 * (int)sizeof(Person), SEEK_CUR);
        Person blank = { "", "", "" };
        fwrite(&blank, sizeof(Person), 1, fPtr);
    }
    else {
        puts("Record not found.\n");
    }
 
    fclose(fPtr);
}

/*
Output:
Code:
Anderly, Charley, 54
Schultz, Gilberto, 67
Cuevas, Abbigail, 34
Rhodes, Gregory, 83
Taylor, Giovanna, 78
Glenn, Kole, 54
Reilly, Dennis, 41
Morrix, Shannon, 27
Herman, Mekhi, 84
Beltran, Damari, 30

Enter existing lastName, firstName, newAge: Rhodes, Jeff, 44
Anderly, Charley, 54
Schultz, Gilberto, 67
Cuevas, Abbigail, 34
Rhodes, Jeff, 44
Taylor, Giovanna, 78
Glenn, Kole, 54
Reilly, Dennis, 41
Morrix, Shannon, 27
Herman, Mekhi, 84
Beltran, Damari, 30

Delete existing lastName, firstName, age: Rhodes, Abe, 3
Anderly, Charley, 54
Schultz, Gilberto, 67
Cuevas, Abbigail, 34
, ,
Taylor, Giovanna, 78
Glenn, Kole, 54
Reilly, Dennis, 41
Morrix, Shannon, 27
Herman, Mekhi, 84
Beltran, Damari, 30
*/