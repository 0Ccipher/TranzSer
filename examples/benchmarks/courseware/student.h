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
Student *newStudentFromString(char * string);
int getsId(Student *student);
const char *getsName(Student *student);
bool isRegistered(Student *student);
const char *getRollNumber(Student *student);
void freeStudent(Student *student);
 char *studentToString(Student *student);

#endif /* STUDENT_H */
