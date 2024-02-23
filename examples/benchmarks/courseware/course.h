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
const char *toString(Course *course);
int getId(Course *course);
const char *getName(Course *course);
const char *getDepartment(Course *course);
const char *getStatus(Course *course);
int getCapacity(Course *course);
void setStatus(Course *course, const char *status);
void deleteCourse(Course *course);

#endif /* COURSE_H */
