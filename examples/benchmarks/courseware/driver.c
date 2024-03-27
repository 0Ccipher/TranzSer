#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include "courseware.c"

char sinput[7][MAX_STR_SIZE];
char cinput[7][MAX_STR_SIZE];


void * thr1(void *arg){
    printf("thread 1 - start \n");
    enroll(1,1);
    getAllEnrollments();
    enroll(1,2);
    printf("thread 1 - finish \n");
    return NULL;
}
void * thr2(void *arg){
    printf("thread 2 - start \n");
    enroll(2,1);
    getAllEnrollments();
    deleteCourse(2);
    printf("thread 2 - finish \n");
    return NULL;
}
void * thr3(void *arg){
    printf("thread 3 - start \n");
    enroll(2,1);
    // deleteCourse(1);
    printf("thread 3 - finish \n");
    return NULL;
}

void init(){
    sprintf(t[0].row[0], "%s","0;Daniel Szabo;true;0");
    sprintf(t[0].row[1], "%s","1;Patricio Inzaghi;false;1");
    sprintf(t[0].row[2], "%s","2;Weiqiang Yu;true;2");
    sprintf(t[0].row[3], "%s","3;Srinidhi Nagendra;true;3");
    sprintf(t[0].row[4], "%s","4;Mouna Safir;true;4");
    sprintf(t[0].row[5], "%s","5;Enrique Roman Calvo;true;5");
    sprintf(t[0].row[6], "%s","6;Klara Nosan;true;7");
    sprintf(t[1].row[0], "%s","0;placeholde;placeholde;closed;0");
    sprintf(t[1].row[1], "%s","1;Formal Methods for Testing;CS;open;1");
    sprintf(t[1].row[2], "%s","2;Quantum Computing;CS;open;2");
    sprintf(t[1].row[3], "%s","3;Computer-Aided Program Verification;CS;open;3");
    sprintf(t[1].row[4], "%s","4;Cryptography I;CS;open;3");
    sprintf(t[1].row[5], "%s","5;Cryptography II;CS;open;3");
    sprintf(t[1].row[6], "%s","6;Euskera;FL;closed;3");

    sprintf(t[2].row[0], "%s","0:-1");
    for(int i=7 ; i < MAX_ROWS ; i++){
        sprintf(t[0].row[i], "%s","empty");
        sprintf(t[1].row[i], "%s","empty");
    }
    for(int i=1 ; i < MAX_ROWS ; i++){
        sprintf(t[2].row[i], "%s","empty");
    }
    database[0]= ATOMIC_VAR_INIT(&t[0]);
    database[1]= ATOMIC_VAR_INIT(&t[1]);
    database[2]= ATOMIC_VAR_INIT(&t[2]);
}


int main() {
    pthread_t t1,t2,t3;

    __VERIFIER_Transaction_begin();
        init();
    __VERIFIER_Transaction_end();

    pthread_create(&t1,NULL,thr1,NULL);
    pthread_create(&t2,NULL,thr2,NULL);
    pthread_create(&t3,NULL,thr3,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);

    printf("\n---------------------------------______________ --------------------\n");
    return 0;
}


// int main() {
//     pthread_t t1,t2,t3;
//     initDatabase();
//     populateDatabase();
//     write(EROLLMENT_TABLE,"0","0:0"); //init the table
//     char *sinput[3];
//     char *cinput[3];
//     sinput[0] = strdup("1;John Doe;true;A12345");
//     sinput[1] = strdup("2;Bob Doe;false;B00042");
//     sinput[2] = strdup("3;Alice Doe;true;B00042");
//     cinput[0] = strdup("1;Math;Mathematics;open;50");
//     cinput[1] = strdup("2;Physics;Science;close;40");
//     cinput[2] = strdup("3;Formal Methods;CSE;open;40");

//     int c = 0;
//     while(c < 3){
//         Student *student = newStudentFromString(sinput[c]);
//         if (student == NULL) {
//         printf("Wrong format\n");
//         }
//         static char row[20];
//         sprintf(row,"%d",c+1);// id
//         printf("storing Student %s: %s\n",row,studentToString(student));
//         write(STUDENT_TABLE, row, studentToString(student));
//         Course * course = newCourseFromString(cinput[c]);
//         if(course == NULL){
//         printf("Wrong formant\n");
//         }
//         printf("storing course %s: %s\n",row,courseToString(course));
//         write(COURSE_TABLE, row, courseToString(course));
//         c++;
//     }

//     pthread_create(&t1,NULL,thr1,NULL);
//     pthread_create(&t2,NULL,thr2,NULL);
//     pthread_create(&t3,NULL,thr3,NULL);

//     pthread_join(t1,NULL);
//     pthread_join(t2,NULL);
//     pthread_join(t3,NULL);

//     Table *currentTable = getAllRows(STUDENT_TABLE);
//     if(currentTable != NULL)
//     for (int i = 0; i < currentTable->size; i++) {
//         printf("Table: %s, Row: %s, Value: %s\n", currentTable->rows[i].table, currentTable->rows[i].row, currentTable->rows[i].value);
//     }
//     currentTable = getAllRows(COURSE_TABLE);
//     if(currentTable != NULL)
//     for (int i = 0; i < currentTable->size; i++) {
//         printf("Table: %s, Row: %s, Value: %s\n", currentTable->rows[i].table, currentTable->rows[i].row, currentTable->rows[i].value);
//     }
//     currentTable = getAllRows(EROLLMENT_TABLE);
//     if(currentTable != NULL)
//     for (int i = 0; i < currentTable->size; i++) {
//         printf("Table: %s, Row: %s, Value: %s\n", currentTable->rows[i].table, currentTable->rows[i].row, currentTable->rows[i].value);
//     }

//     printf("\n---------------------------------______________ --------------------\n");
//     return 0;
// }
