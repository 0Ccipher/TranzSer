#include "student.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

bool strtobool(const char *str) {
    return strcmp(str, "true") == 0;
}

Student *newStudent(int id, const char *name, bool registered, const char *rollNumber) {
    Student *student = (Student *)malloc(sizeof(Student));
    student->id = id;
    student->name = strdup(name);
    student->registered = registered;
    student->rollNumber = strdup(rollNumber);
    return student;
}

Student *newStudentFromString(char *string){
    Student *student = (Student *)malloc(sizeof(Student));
    // printf("extracting Student %s\n",string);
    char *token = strtok(string, ";");
    if (token == NULL) {
        printf("Wrong format\n");
        return NULL;
    }
    student->id = atoi(token);
    token = strtok(NULL, ";");
    if (token == NULL) {
        printf("Wrong format\n");
        return NULL;
    }
    student->name = strdup(token);
    token = strtok(NULL, ";");
    if (token == NULL) {
        printf("Wrong format\n");
        return NULL;
    }
    student->registered = strtobool(token);
    token = strtok(NULL, ";");
    if (token == NULL) {
        printf("Wrong format\n");
        return NULL;
    }
    student->rollNumber = strdup(token);
    return student;
}

char *studentToString(Student *student) {
    static char buffer[256];
    sprintf(buffer, "%d;%s;%s;%s", student->id, student->name, (student->registered?"true":"false"), student->rollNumber);
    return buffer;
}

int getsId(Student *student) {
    return student->id;
}

const char *getsName(Student *student) {
    return student->name;
}

bool isRegistered(Student *student) {
    return student->registered;
}

const char *getRollNumber(Student *student) {
    return student->rollNumber;
}

void freeStudent(Student *student) {
    // free(student->name);
    // free(student->rollNumber);
    free(student);
}
