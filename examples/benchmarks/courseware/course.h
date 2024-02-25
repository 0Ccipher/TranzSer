#ifndef COURSE_H
#define COURSE_H

typedef struct {
    int id;
    char *name;
    char *department;
    char *status;
    int capacity;
} Course;

Course *newCourse(int id, const char *name, const char *department, const char *status, int capacity);
Course *newCourseFromString(char * string);
char *courseToString(Course *course);
int getcId(Course *course);
const char *getcName(Course *course);
const char *getDepartment(Course *course);
const char *getStatus(Course *course);
int getCapacity(Course *course);
void setStatus(Course *course, const char *status);
void freeCourse(Course *course);

#endif /* COURSE_H */
