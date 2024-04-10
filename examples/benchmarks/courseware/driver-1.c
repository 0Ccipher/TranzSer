#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include "courseware_1.c"



void * thr1(void *arg){
    // enroll(1,1);
    // getAllEnrollments();
    // enroll(1,2);
    return NULL;
}
void * thr2(void *arg){
    // enroll(2,1);
    // getAllEnrollments();
    deleteCourse(1);
    return NULL;
}
void * thr3(void *arg){
    enroll(2,1);
    // deleteCourse(1);
    return NULL;
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
