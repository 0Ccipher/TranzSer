#include "student.h"
#include <stdlib.h>
#include <string.h>

Student *newStudent(int id, const char *name, bool registered, const char *rollNumber) {
    Student *student = (Student *)malloc(sizeof(Student));
    student->id = id;
    student->name = strdup(name);
    student->registered = registered;
    student->rollNumber = strdup(rollNumber);
    return student;
}

const char *toString(Student *student) {
    static char buffer[256];
    sprintf(buffer, "%d;%s;%s;%s", student->id, student->name, (student->registered?"true":"false"), student->rollNumber);
    return buffer;
}
int getId(Student *student) {
    return student->id;
}

const char *getName(Student *student) {
    return student->name;
}

bool isRegistered(Student *student) {
    return student->registered;
}

const char *getRollNumber(Student *student) {
    return student->rollNumber;
}

void deleteStudent(Student *student) {
    // free(student->name);
    // free(student->rollNumber);
    free(student);
}
