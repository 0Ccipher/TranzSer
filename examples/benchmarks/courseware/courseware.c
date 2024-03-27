#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdatomic.h>
#include "student.h"
#include "student.c"
#include "course.h"
#include "course.c"
#include "db.c"

#define STUDENT_TABLE "ST"  //table 0
#define COURSE_TABLE "CT"  // table 1
#define EROLLMENT_TABLE "ET" //table 2

#define begin  __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
#define abort __VERIFIER_Transaction_abort()

void begin;
void end;
void abort;

// Function to enroll a student in a course
void enroll(int studentID, int courseID) {
   begin;
    printf("Enrolling student %d in course %d\n",studentID , courseID);
    static char stid[20];
    sprintf(stid,"%d",studentID);
    int index = readRowFromTable(0,STUDENT_TABLE , stid);
    if(index == -1){
        printf("Student not found\n");
        abort;
        return;
    }
    Student *student = newStudentFromString(database[0]->row[index]);
    printf("Student extracted : %s \n" , studentToString(student));
    static char ctid[20];
    sprintf(ctid,"%d",courseID);
    index = readRowFromTable(1,COURSE_TABLE , ctid);
    if(index == -1){
        printf("Course not found\n");
        abort;
        return;
    }
    Course *course = newCourseFromString(database[1]->row[index]);
    printf("Course extracted : %s \n" , courseToString(course));
    // printf("Student %s in course %s\n",studentToString(student) , courseToString(course));
    static char entry[20];
    sprintf(entry,"%d:%d",courseID,studentID);
    if(isRegistered(student) && strcmp(getStatus(course),"open") == 0){
          int totalEnrollments = countIfIDStartsWith(2,EROLLMENT_TABLE,ctid);
          if(totalEnrollments == -1){
            abort;
            return;
          }
          printf("Current Enrollments : %d\n",totalEnrollments);
          if(totalEnrollments < course->capacity){
            if(!writetoTable(2,EROLLMENT_TABLE,entry,entry)){
                abort;
                return;
            } //row and value as entry
            printf("Enrolled \n");
          }
    }
    end;
}

void closeCourse(int courseID) {
   begin;
   static char ctid[20];
    sprintf(ctid,"%d",courseID);
    int index = readRowFromTable(1,COURSE_TABLE , ctid);
    if(index == -1){
        printf("Course not found\n");
        abort;
        return;
    }
    Course *course = newCourseFromString(database[1]->row[index]);
    Course *nCourse = newCourse(course->id , course->name,course->department,"closed",course->capacity);
    if(!writetoTable(1,COURSE_TABLE ,ctid,courseToString(nCourse))){
        abort;
        return;
    }
    end;
}

void openCourse(int courseID) {
   begin;
   static char ctid[20];
    sprintf(ctid,"%d",courseID);
    int index = readRowFromTable(1,COURSE_TABLE , ctid);
    if(index == -1){
        printf("Course not found\n");
        abort;
        return;
    }
    Course *course = newCourseFromString(database[1]->row[index]);
    Course *nCourse = newCourse(course->id , course->name,course->department,"open",course->capacity);
    if(!writetoTable(1,COURSE_TABLE ,ctid,courseToString(nCourse))){
        printf("Write failed \n");
        abort;
        return;
    }
    end;
    printf("Write Done\n");
}

// Function to delete a course
void deleteCourse(int courseID) {
   begin;
    printf("delete course start\n");
    static char ctid[20];
    sprintf(ctid,"%d",courseID);
    int index = readRowFromTable(1,COURSE_TABLE , ctid);
    if(index == -1){
        printf("Course not found\n");
        abort;
        return;
    }
    int flag = deleteRowFromTable(1,COURSE_TABLE , ctid);
    if(flag == -1 || flag == 0){
        abort;
        return;
    }
    while(true){
      printf("delete course-enrollments start\n");
      flag = deleteRowFromTable(2,EROLLMENT_TABLE,ctid);
      if(flag == -1){
        abort;
        return;
      }
      if( flag == 0) break;
    }
    printf("delete end\n");
    end;
}

static Table * getAllEnrollments(){ 
   begin;
   printf("GetEnrollments\n");
   Table * currentTable = getAllRows(2);
   if(currentTable==NULL){
    abort;
    return NULL;
   }
    // for (int i = 0; i < currentTable->size; i++) {
    //     printf("Row: %s\n", currentTable->row[i]);
    // }
   end;
   return currentTable;
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