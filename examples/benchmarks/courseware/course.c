#include "course.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Course *newCourse(int id, const char *name, const char *department, const char *status, int capacity) {
    Course *course = (Course *)malloc(sizeof(Course));
    course->id = id;
    course->name = strdup(name);
    course->department = strdup(department);
    course->status = strdup(status);
    course->capacity = capacity;
    return course;
}

Course *newCourseFromString(char *string){
    Course *course = (Course *)malloc(sizeof(Course));
    printf("extracting course %s\n",string);
    char *token = strtok(string, ";");
    if (token == NULL) {
        printf("Wrong format\n");
        return NULL;
    }
    course->id = atoi(token);
    token = strtok(NULL, ";");
    if (token == NULL) {
        printf("Wrong format\n");
        return NULL;
    }
    course->name = strdup(token);
    token = strtok(NULL, ";");
    if (token == NULL) {
        printf("Wrong format\n");
        return NULL;
    }
    course->department = strdup(token);
    token = strtok(NULL, ";");
    if (token == NULL) {
        printf("Wrong format\n");
        return NULL;
    }
    course->status = strdup(token);
    token = strtok(NULL, ";");
    if (token == NULL) {
        printf("Wrong format\n");
        return NULL;
    }
    course->capacity = atoi(token);
    return course;
}

char *courseToString(Course *course) {
    static char buffer[256];
    sprintf(buffer, "%d;%s;%s;%s;%d", course->id, course->name, course->department, course->status, course->capacity);
    return buffer;
}

int getcId(Course *course) {
    return course->id;
}

const char *getcName(Course *course) {
    return course->name;
}

const char *getDepartment(Course *course) {
    return course->department;
}

const char *getStatus(Course *course) {
    return course->status;
}

int getCapacity(Course *course) {
    return course->capacity;
}

void setStatus(Course *course, const char *status) {
//     free(course->status);
    course->status = strdup(status);
}

void freeCourse(Course *course) {
//     free(course->name);
//     free(course->department);
//     free(course->status);
    free(course);
}
