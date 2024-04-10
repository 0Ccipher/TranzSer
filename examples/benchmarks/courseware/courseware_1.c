#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdatomic.h>

#define MAX_TABLE_SIZE 15
#define MAX_ROWS 15
#define MAX_STR_SIZE 100
#define MAX_TABLES 10

#define SC memory_order_seq_cst


typedef struct {
    char row[MAX_TABLE_SIZE][MAX_STR_SIZE];
} Table;

//Database
Table t1,t2,t3;
_Atomic(Table *) table1,table2,table3;

atomic_int a1=0;

#define STUDENT_TABLE "ST"  //table 0
#define COURSE_TABLE "CT"  // table 1
#define EROLLMENT_TABLE "ET" //table 2

#define begin  __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
#define abort __VERIFIER_Transaction_abort()

void begin;
void end;
void abort;

char sinput[7][MAX_STR_SIZE];
char cinput[7][MAX_STR_SIZE];

int getCapacity(const char* course) {
    int number = 0;
    int foundNumber = 0;

    while (*course) {
        if (*course >= '0' && *course <= '9') {
            number = number * 10 + (*course - '0');
            foundNumber = 1;
        } else if (*course==';') {
            number = 0;
            foundNumber = 0;
        }

        course++;
    }

    return number;
}
int getCourseID(const char* course) {
    int number = 0;
    int foundNumber = 0;

    while (*course) {
        if (*course >= '0' && *course <= '9') {
            number = number * 10 + (*course - '0');
            foundNumber = 1;
        } else if (*course==';' && number != 0) {
            return number;
        }

        course++;
    }

    return number;
}

bool isRegistered(const char *student){
    return (strncmp(student , "true", strlen("true")) == 0);
}

bool isOpen(const char *course){
    return (strncmp(course , "open", strlen("open")) == 0);
}
void init(){
    sprintf(t1.row[0], "%s","true;0;Daniel Szabo");
    sprintf(t1.row[1], "%s","false;1;Patricio Inzaghi");
    sprintf(t1.row[2], "%s","true;2;Weiqiang Yu;");
    sprintf(t1.row[3], "%s","true;3;Srinidhi Nagendra");
    sprintf(t1.row[4], "%s","true4;Mouna Safir");
    sprintf(t1.row[5], "%s","true;5;Enrique Roman Calvo");
    sprintf(t1.row[6], "%s","true;6;Klara Nosan");
    sprintf(t2.row[0], "%s","closed;0;placeholder;placeholder;0");
    sprintf(t2.row[1], "%s","open;1;Formal Methods for Testing;CS;1");
    sprintf(t2.row[2], "%s","open;2;Quantum Computing;CS;2");
    sprintf(t2.row[3], "%s","open;3;Computer-Aided Program Verification;CS;3");
    sprintf(t2.row[4], "%s","open;4;Cryptography I;CS;3");
    sprintf(t2.row[5], "%s","open;5;Cryptography II;CS;3");
    sprintf(t2.row[6], "%s","closed;6;Euskera;FL;3");

    sprintf(t3.row[0], "%s","0:-1");
    for(int i=7 ; i < MAX_ROWS ; i++){
        sprintf(t1.row[i], "%s","empty");
        sprintf(t2.row[i], "%s","empty");
    }
    for(int i=1 ; i < MAX_ROWS ; i++){
        sprintf(t3.row[i], "%s","empty");
    }
    table1= ATOMIC_VAR_INIT(&t1);
    table2= ATOMIC_VAR_INIT(&t2);
    table3= ATOMIC_VAR_INIT(&t3);
}

// Function to enroll a student in a course
void enroll(int studentID, int courseID) {
   begin;
    printf("Enrolling student %d in course %d\n",studentID , courseID);
    if(table1 == NULL) {
        abort;
        return;
    }
    if(table2 == NULL) {
        abort;
        return;
    }
    if(table3 == NULL) {
        abort;
        return;
    }
    if(table2 != &t2){
        abort;
        return;
    }
    if(table3 != &t3){
        abort;
        return;
    }
    if(table1 != &t1){
        abort;
        return;
    }
    Table* studentTable = table1;
    Table* ctable = table2;
    Table* etable = table3;
    printf("enroll - table2 : %p\n",table2);
    static char student[100];
    sprintf(student,"%s",studentTable->row[studentID]);
    if(strcmp(student,"empty") == 0){
        printf("Student not found\n");
        abort;
        return;
    }
    static char course[100];
    sprintf(course,"%s",ctable->row[courseID]);
    if(strcmp(course,"empty") == 0){
        printf("Course not found\n");
        abort;
        return;
    }
    static char entry[20];
    sprintf(entry,"%d:%d",courseID,studentID);
    static char cid[10];
    sprintf(cid,"%d",courseID);
    int flag = 0;
    if(isRegistered(student) && isOpen(course)){
          int totalEnrollments = 0;
          for(int i=0 ; i < MAX_ROWS ; i++){
            if(strncmp(etable->row[i],entry,strlen(entry)) ==0){
                abort;
                printf("already enrolled \n");
                return;
            }
          }
          for(int i=0 ; i < MAX_ROWS ; i++){
            if(strncmp(etable->row[i],cid,strlen(cid)) == 0)
                totalEnrollments++;
          }
          if(totalEnrollments < getCapacity(course)){
            for(int i=0 ; i < MAX_ROWS ; i++){
                if(strcmp(etable->row[i],"empty") ==0){
                    sprintf(etable->row[i], "%s" ,entry);
                    printf("Enrolled %s -> student : %s in - course : %s\n",entry,student,course);
                    flag = 1;
                    int r1 = a1;
                    break;
                }
                    
            }
          }
    }
    if(flag)
        table3=etable;
    printf("Enrolled\n");
    end;
}

// void closeCourse(int courseID) {
//    begin;
//    if(table2 == NULL) {
//         abort;
//         return;
//     }
//     static char cid[10];
//     sprintf(cid,"%d",courseID);
//     static char course[100];
//     sprintf(course,"%s",ctable->row[courseID]);
//     if(strcmp(course,"empty") == 0){
//         printf("Course not found\n");
//         abort;
//         return;
//     }
//     end;
// }

// void openCourse(int courseID) {
//    begin;
//    static char ctid[20];
//     sprintf(ctid,"%d",courseID);
//     int index = readRowFromTable(1,COURSE_TABLE , ctid);
//     if(index == -1){
//         printf("Course not found\n");
//         abort;
//         return;
//     }
//     Course *course = newCourseFromString(ctable->row[index]);
//     Course *nCourse = newCourse(course->id , course->name,course->department,"open",course->capacity);
//     if(!writetoTable(1,COURSE_TABLE ,ctid,courseToString(nCourse))){
//         printf("Write failed \n");
//         abort;
//         return;
//     }
//     end;
//     printf("Write Done\n");
// }

// Function to delete a course
void deleteCourse(int courseID) {
   begin;
   if(table2 == NULL) {
        abort;
        return;
    }
    if(table3 == NULL) {
        abort;
        return;
    }
    if(table2 != &t2){
        abort;
        return;
    }
    if(table3 != &t3){
        abort;
        return;
    }
    printf("deleted - 1 - table2 : %p\n",table2);
    Table* ctable = table2;
    Table* etable = table3;
    static char course[100];
    printf("course for id %d :: %s\n",courseID,ctable->row[courseID]);
    sprintf(course,"%s",ctable->row[courseID]);
    if(strcmp(course,"empty") == 0){
        printf("Course not found\n");
        abort;
        return;
    }
    printf("delete course start\n");
    static char cid[10];
    sprintf(cid,"%d",courseID);
    int flag1 = 0;
    int flag2 = 0;
    for(int i=0 ; i < MAX_ROWS ; i++){
        int thisid = getCourseID(ctable->row[i]);
        printf("C-ID %d\n",thisid);
        if( thisid == courseID){
            sprintf(ctable->row[i], "%s" ,"empty");
            flag1 = 1;
            printf("Course deleted \n");
            break;
        }
    }
    
    for(int i=0 ; i < MAX_ROWS ; i++){
        if(strncmp(etable->row[i],cid,strlen(cid)) == 0){
            sprintf(etable->row[i], "%s" ,"empty");
            printf("enrollment deleted \n");
            flag2 = 1;
        }
    }
    if(flag1)
        table2 = ctable;
    if(flag2)
        table3 = etable;
    printf("deleted - 2 - table2 : %p\n",table2);
    printf("delete end\n");
    end;
}

static Table * getAllEnrollments(){ 
   begin;
   printf("GetEnrollments\n");
   Table * currentTable = table3;
   end;
   return currentTable;
}
