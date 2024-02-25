#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include "courseware.c"

void * thr1(void *arg){
    printf("thread 1 - start \n");
    enroll(1,1);
    enroll(1,2);
    printf("thread 1 - finish \n");
    return NULL;
}
void * thr2(void *arg){
    printf("thread 2 - start \n");
    enroll(2,1);
    printf("thread 2 - finish \n");
    return NULL;
}
void * thr3(void *arg){
    printf("thread 3 - start \n");
    enroll(2,1);
    printf("thread 3 - finish \n");
    return NULL;
}
void populateDatabase(){
    initDatabase();
    //Create Student data-base and add data
    for(int i=0 ; i < MAX_TABLES;i++){
        Table *table = new_table();
        atomic_init(&database.tables[i],table);
    }
    char *sinput[7];
    char *cinput[7];
    sinput[0] = strdup("0;Daniel Szabo;true;0");
    sinput[1] = strdup("1;Patricio Inzaghi;false;1");
    sinput[2] = strdup("2;Weiqiang Yu;true;2");
    sinput[3] = strdup("3;Srinidhi Nagendra;true;3");
    sinput[4] = strdup("4;Mouna Safir;true;4");
    sinput[5] = strdup("5;Enrique Roman Calvo;true;5");
    sinput[6] = strdup("6;Klara Nosan;true;7");
    cinput[0] = strdup("0;placeholde;placeholde;closed;0");
    cinput[1] = strdup("1;Formal Methods for Testing;CS;open;1");
    cinput[2] = strdup("2;Quantum Computing;CS;open;2");
    cinput[3] = strdup("3;Computer-Aided Program Verification;CS;open;3");
    cinput[4] = strdup("4;Cryptography I;CS;open;3");
    cinput[5] = strdup("5;Cryptography II;CS;open;3");
    cinput[6] = strdup("6;Euskera;FL;closed;3");
    int c = 0;
    while(c < 7){
        Student *student = newStudentFromString(sinput[c]);
        if (student == NULL) {
        printf("Wrong format\n");
        }
        static char row[20];
        sprintf(row,"%d",c);// id
        // printf("storing Student %s: %s\n",row,studentToString(student));
        write(STUDENT_TABLE, row, studentToString(student));
        Course * course = newCourseFromString(cinput[c]);
        if(course == NULL){
        printf("Wrong formant\n");
        }
        // printf("storing course %s: %s\n",row,courseToString(course));
        write(COURSE_TABLE, row, courseToString(course));
        c++;
    }
    write(EROLLMENT_TABLE,"0","0:-1"); //init the table
    
    printf("db size : %d\n", atomic_load(&database.size));
    // printf("db size : %d\n", (database.size));
}


int main() {
    pthread_t t1,t2,t3;
    populateDatabase();
    
    pthread_create(&t1,NULL,thr1,NULL);
    pthread_create(&t2,NULL,thr2,NULL);
    pthread_create(&t3,NULL,thr3,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);

    Table *currentTable = getAllRows(STUDENT_TABLE);
    if(currentTable != NULL)
    for (int i = 0; i < currentTable->size; i++) {
        printf("Table: %s, Row: %s, Value: %s\n", currentTable->rows[i].table, currentTable->rows[i].row, currentTable->rows[i].value);
    }
    currentTable = getAllRows(COURSE_TABLE);
    if(currentTable != NULL)
    for (int i = 0; i < currentTable->size; i++) {
        printf("Table: %s, Row: %s, Value: %s\n", currentTable->rows[i].table, currentTable->rows[i].row, currentTable->rows[i].value);
    }
    currentTable = getAllRows(EROLLMENT_TABLE);
    if(currentTable != NULL)
    for (int i = 0; i < currentTable->size; i++) {
        printf("Table: %s, Row: %s, Value: %s\n", currentTable->rows[i].table, currentTable->rows[i].row, currentTable->rows[i].value);
    }

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
