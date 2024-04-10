#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <pthread.h>

#define SC memory_order_seq_cst

atomic_int student[2]={1,2};
atomic_int registered[2]={0,1};
atomic_int course[2]={1,2}; //non-zero(id) value means course exists
atomic_int courseStatus[2]={1,1}; // 1: course_i is open
atomic_int courseCapacity[2]={1,2}; // capacity
atomic_int enrollments[2]={0,0};// i-value= remaining capacity of course i

#define begin  __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
#define abort __VERIFIER_Transaction_abort()

void begin;
void end;
void abort;


// Function to enroll a student in a course
void enroll(int studentID, int courseID) {
   begin;
    for(int i=0;i<2;i++){
        atomic_load_explicit(&student[i],SC);
        atomic_load_explicit(&registered[i],SC);
        atomic_load_explicit(&course[i],SC);  
        atomic_load_explicit(&enrollments[i],SC);
        atomic_load_explicit(&courseStatus[i],SC);
        atomic_load_explicit(&courseCapacity[i],SC);
    }
    if(atomic_load_explicit(&student[studentID],SC) == -1){
        abort; //invalid student
        printf("Invalid Student\n");
        return;
    }
    if(atomic_load_explicit(&course[courseID],SC) == -1){
        abort; //invalid course 
        printf("Invalid Course\n");
        return;
    }
    //isregistered(student) && isopen(course)
    int isregistered = atomic_load_explicit(&registered[studentID],SC);
    int isopen = atomic_load_explicit(&courseStatus[courseID],SC);
    bool flag = false;
    if(isregistered!=0 && isopen!=0){
        //if enrollments < capacity - enroll
        int enrolls = atomic_load_explicit(&enrollments[courseID] , SC);
        int capacity = atomic_load_explicit(&courseCapacity[courseID] , SC);
        printf("Current Enrolls for course %d of capacity %d: %d \n", 
                                    courseID , capacity ,enrolls);
        if(enrolls < capacity){
            atomic_store_explicit(&enrollments[courseID],enrolls+1,SC);
            printf("Enrolled %d in %d \n",studentID, courseID);
            flag = true;
        }
    }
    if(flag){
        for(int i=0 ; i < 2; i++){
            int e = atomic_load_explicit(&enrollments[i] , SC);
            atomic_store_explicit(&enrollments[i],e,SC);
        }
    }
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
   for(int i=0;i<2;i++){
        atomic_load_explicit(&course[i],SC);  
        atomic_load_explicit(&courseStatus[i],SC);
        atomic_load_explicit(&courseCapacity[i],SC);
    }
    if(atomic_load_explicit(&course[courseID],SC) == -1){
        abort; //invalid course 
        return;
    }
    for(int i=0;i<2;i++){
        atomic_load_explicit(&enrollments[i],SC);
    }
    // delete course- set to -1 for this id
    atomic_store_explicit(&course[courseID],-1,SC);
    atomic_store_explicit(&courseStatus[courseID],-1,SC);
    atomic_store_explicit(&courseCapacity[courseID],-1,SC);
    atomic_store_explicit(&enrollments[courseID],0,SC);
    printf("Deleted course %d -> new value : %d \n",
                courseID,atomic_load_explicit(&course[courseID],SC));
    for(int i=0 ; i < 2; i++){
        int r1 = atomic_load_explicit(&course[i],SC);  
        int r2 = atomic_load_explicit(&enrollments[i],SC);
        int r3 = atomic_load_explicit(&courseStatus[i],SC);
        int r4 = atomic_load_explicit(&courseCapacity[i],SC);
        atomic_store_explicit(&course[courseID],r1,SC);
        atomic_store_explicit(&enrollments[i],r2,SC);
        atomic_store_explicit(&courseStatus[courseID],r3,SC);
        atomic_store_explicit(&courseCapacity[courseID],r4,SC);
    }
    end;
}

int getAllEnrollments(){ 
   begin;
   for(int i=0 ; i < 2; i++){
        atomic_load_explicit(&enrollments[i] , SC);
    }
   end;
   return 1;
}


void * thr1(void *arg){
    enroll(0,0);
    getAllEnrollments();
    enroll(0,1);
    return NULL;
}
void * thr2(void *arg){
    enroll(1,0);
    // getAllEnrollments();
    // deleteCourse(1);
    return NULL;
}
void * thr3(void *arg){
    // enroll(1,0);
    deleteCourse(0);
    return NULL;
}

int main() {
    pthread_t t1,t2,t3;

    // pthread_create(&t1,NULL,thr1,NULL);
    pthread_create(&t2,NULL,thr2,NULL);
    pthread_create(&t3,NULL,thr3,NULL);

    // pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);

    return 0;
}
