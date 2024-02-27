#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdatomic.h>
#include "student.h"
#include "student.c"
#include "course.h"
#include "course.c"
#include "database_atomic.c"

#define STUDENT_TABLE "ST"  //table 0
#define COURSE_TABLE "CT"  // table 1
#define EROLLMENT_TABLE "ET" //table 2

void __VERIFIER_Transaction_begin(){};
void __VERIFIER_Transaction_end(){};

// Function to enroll a student in a course
void enroll(int studentID, int courseID) {
    __VERIFIER_Transaction_begin();
    printf("Enrolling student %d in course %d\n",studentID , courseID);
    static char stid[20];
    sprintf(stid,"%d",studentID);
    char * ststr = readRowFromTable(0,STUDENT_TABLE , stid);
    if(ststr == NULL){
        printf("Student not found\n");
        return;
    }
    Student *student = newStudentFromString(ststr);
    static char ctid[20];
    sprintf(ctid,"%d",courseID);
    char * ctstr = readRowFromTable(1,COURSE_TABLE , ctid);
    if(ctstr == NULL){
        printf("Course not found\n");
        return;
    }
    Course *course = newCourseFromString(ctstr);
    // printf("Student %s in course %s\n",studentToString(student) , courseToString(course));
    static char entry[20];
    sprintf(entry,"%d:%d",courseID,studentID);
    if(isRegistered(student) && strcmp(getStatus(course),"open") == 0){
          int totalEnrollments = countIfIDStartsWith(2,EROLLMENT_TABLE,ctid);
          printf("Current Enrollments : %d\n",totalEnrollments);
          if(totalEnrollments < course->capacity){
                writetoTable(2,EROLLMENT_TABLE,entry,entry); //row and value as entry
                printf("Enrolled \n");
          }
    }
    __VERIFIER_Transaction_end();
}

// Function to close a course row is id
void closeCourse(char * row) {
    __VERIFIER_Transaction_begin();
    writetoTable(1,COURSE_TABLE ,row,"closed");
    __VERIFIER_Transaction_end();
}

// Function to open a course
void openCourse(char * row) {
    __VERIFIER_Transaction_begin();
    writetoTable(1,COURSE_TABLE ,row,"open");
    __VERIFIER_Transaction_end();
}

// Function to delete a course
void deleteCourse(int courseID) {
    __VERIFIER_Transaction_begin();
    static char ctid[20];
    sprintf(ctid,"%d",courseID);
    char * ctstr = readRowFromTable(1,COURSE_TABLE , ctid);
    if(ctstr == NULL){
      printf("course not found");
      return;
    }
    deleteRowFromTable(1,COURSE_TABLE , ctid);
    bool flag = true;
    while(flag){
      flag = deleteRowFromTable(2,EROLLMENT_TABLE,ctid);
    }
    __VERIFIER_Transaction_end();
}

static Table * getAllEnrollments(){ 
    __VERIFIER_Transaction_begin();
   Table * t =  getAllRows(2);
   __VERIFIER_Transaction_end();
   return t;
}


// int main() {
//       pthread_t t1,t2,t3;
//       initDatabase();
//       write(EROLLMENT_TABLE,"0","0:0"); //init the table
//       char *sinput[3];
//       char *cinput[3];
//       // strcpy(input[0],"1;John Doe;true;A12345");
//       sinput[0] = strdup("1;John Doe;true;A12345");
//       // strcpy(input[1],"2;Bob Doe;false;B00042");
//       sinput[1] = strdup("2;Bob Doe;false;B00042");
//       sinput[2] = strdup("3;Alice Doe;true;B00042");
//       cinput[0] = strdup("1;Math;Mathematics;open;50");
//       cinput[1] = strdup("2;Physics;Science;close;40");
//       cinput[2] = strdup("3;Formal Methods;CSE;open;40");
//       int c = 0;
//       while(c < 3){
//             Student *student = newStudentFromString(sinput[c]);
//             if (student == NULL) {
//             printf("Wrong format\n");
//             }
//             static char row[20];
//             sprintf(row,"%d",c+1);// id
//             printf("storing Student %s: %s\n",row,studentToString(student));
//             write(STUDENT_TABLE, row, studentToString(student));
//             Course * course = newCourseFromString(cinput[c]);
//             if(course == NULL){
//             printf("Wrong formant\n");
//             }
//             printf("storing course %s: %s\n",row,courseToString(course));
//             write(COURSE_TABLE, row, courseToString(course));
//             c++;
//       }
//       enroll(1,1);
//       enroll(1,2);
//       enroll(1,3);
//       enroll(2,1);
//       enroll(2,2);
//       enroll(2,3);
//       enroll(3,1);
//       enroll(3,2);
//       enroll(3,3);

//       Table *currentTable = getAllRows(STUDENT_TABLE);
//       if(currentTable != NULL)
//       for (int i = 0; i < currentTable->size; i++) {
//             printf("Table: %s, Row: %s, Value: %s\n", currentTable->rows[i].table, currentTable->rows[i].row, currentTable->rows[i].value);
//       }
//       currentTable = getAllRows(COURSE_TABLE);
//       if(currentTable != NULL)
//       for (int i = 0; i < currentTable->size; i++) {
//             printf("Table: %s, Row: %s, Value: %s\n", currentTable->rows[i].table, currentTable->rows[i].row, currentTable->rows[i].value);
//       }
//       currentTable = getAllRows(EROLLMENT_TABLE);
//       if(currentTable != NULL)
//       for (int i = 0; i < currentTable->size; i++) {
//             printf("Table: %s, Row: %s, Value: %s\n", currentTable->rows[i].table, currentTable->rows[i].row, currentTable->rows[i].value);
//       }

//       return 0;
// }

// int main() {
//     initDatabase();

//     char *sinput[2];
//     char *cinput[2];
//     // strcpy(input[0],"1;John Doe;true;A12345");
//     sinput[0] = strdup("1;John Doe;true;A12345");
//     // strcpy(input[1],"2;Bob Doe;false;B00042");
//     sinput[1] = strdup("2;Bob Doe;false;B00042");
//     cinput[0] = strdup("1;Math;Mathematics;open;50");
//     cinput[1] = strdup("2;Physics;Science;close;40");
//     int c = 0;
//     while(c < 2){
//         Student *student = newStudentFromString(sinput[c]);
//         if (student == NULL) {
//             printf("Wrong format\n");
//         }
//         static char row[20];
//         sprintf(row,"%d",c+1);// id
//         printf("storing Student %s: %s\n",row,studentToString(student));
//         write(STUDENT_TABLE, row, studentToString(student));
//         Course * course = newCourseFromString(cinput[c]);
//         if(course == NULL){
//             printf("Wrong formant\n");
//         }
//         printf("storing course %s: %s\n",row,courseToString(course));
//         write(COURSE_TABLE, row, courseToString(course));
//         c++;
//     }

//     printf("fetched - %s\n", read(STUDENT_TABLE, "1"));
//     Student *student = newStudentFromString(read(STUDENT_TABLE, "1"));
//     printf("Reading student : %s \n", studentToString(student));

//     printf("fetched - %s\n", read(COURSE_TABLE, "1"));
//      Course * course = newCourseFromString(read(COURSE_TABLE, "1"));
//     printf("Reading course : %s \n", courseToString(course));

//     printf("fetched - %s\n", read(STUDENT_TABLE, "2"));
//     student = newStudentFromString(read(STUDENT_TABLE, "2"));
//     printf("Reading student : %s \n", studentToString(student));

//     printf("fetched - %s\n", read(COURSE_TABLE, "2"));
//     course = newCourseFromString(read(COURSE_TABLE, "2"));
//     printf("Reading course : %s \n", courseToString(course));

//     deleteRow(STUDENT_TABLE,"1");
//     Table *currentTable = getAllRows(STUDENT_TABLE);
//     if(currentTable != NULL)
//     for (int i = 0; i < currentTable->size; i++) {
//         printf("Table: %s, Row: %s, Value: %s\n", currentTable->rows[i].table, currentTable->rows[i].row, currentTable->rows[i].value);
//     }
//     return 0;
// }