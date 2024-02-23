#include <stdio.h>
#include "student.h"
#include "student.c"
int main() {
    // Create instances of Student
    Student *student1 = newStudent(1, "Alice", true, "A001");
    Student *student2 = newStudent(2, "Bob", false, "B002");

    // Print student information
    printf("Student 1:\n");
    printf("ID: %d\n", getId(student1));
    printf("Name: %s\n", getName(student1));
    printf("Registered: %s\n", isRegistered(student1) ? "true" : "false");
    printf("Roll Number: %s\n\n", getRollNumber(student1));

    printf("Student 2: %s\n",toString(student2));

    // Free memory
    deleteStudent(student1);
    deleteStudent(student2);

    return 0;
}

// #include <stdio.h>
// #include "course.h"
// #include "course.c"

// int main() {
//     // Create instances of Course
//     Course *course1 = newCourse(1, "Math", "Mathematics", "Active", 50);
//     Course *course2 = newCourse(2, "Physics", "Science", "Inactive", 40);

//     // Print course information
//     printf("Course 1: %s\n", toString(course1));
//     printf("Course 2: %s\n", toString(course2));

//     // Change status of course1
//     setStatus(course1, "Inactive");
//     printf("Updated Course 1 status: %s\n", getStatus(course1));

//     // Free memory
//     deleteCourse(course1);
//     deleteCourse(course2);

//     return 0;
// }
