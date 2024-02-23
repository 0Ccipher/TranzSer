#ifndef STUDENT_H
#define STUDENT_H

#include <stdbool.h>

typedef struct {
    int id;
    char *name;
    bool registered;
    char *rollNumber;
} Student;

Student *newStudent(int id, const char *name, bool registered, const char *rollNumber);
int getId(Student *student);
const char *getName(Student *student);
bool isRegistered(Student *student);
const char *getRollNumber(Student *student);
void deleteStudent(Student *student);
const char *toString(Student *student);

#endif /* STUDENT_H */
