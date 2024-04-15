#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <pthread.h>

#define SC memory_order_seq_cst

atomic_int student[3]={0,2,4};
atomic_int registered[3]={1,1,1};
atomic_int course[1]={3}; //non-zero(id) value means course exists
atomic_int courseStatus[1]={1}; // 1: course_i is open
atomic_int courseCapacity[1]={3}; // capacity
atomic_int enrollments[1]={0};// i-value= remaining capacity of course i

#define begin  __VERIFIER_Transaction_begin()
#define end __VERIFIER_Transaction_end()
#define abort __VERIFIER_Transaction_abort()

void begin;
void end;
void abort;


// Function to enroll a student in a course
void enroll(int studentID, int courseID) {
   begin;
   if(studentID < 0 || studentID >=3){
        abort;
        return;
   }
   if(courseID < 0 || courseID >=1){
        abort;
        return;
   }
 // printf("Enrolling %d in %d \n",studentID, courseID);
    for(int i=0;i<3;i++){
        atomic_load_explicit(&student[i],SC);
        atomic_load_explicit(&registered[i],SC);
    }
    atomic_load_explicit(&course[0],SC);  
    atomic_load_explicit(&courseStatus[0],SC);
    atomic_load_explicit(&courseCapacity[0],SC);

    if(atomic_load_explicit(&student[studentID],SC) == -1){
        abort; //invalid student
       // printf("Invalid Student\n");
        return;
    }
    if(atomic_load_explicit(&course[courseID],SC) == -1){
        abort; //invalid course 
       // printf("Invalid Course\n");
        return;
    }
    for(int i=0;i<1;i++){
        atomic_load_explicit(&enrollments[i],SC);
    }
    //isregistered(student) && isopen(course)
    int isregistered = atomic_load_explicit(&registered[studentID],SC);
    int isopen = atomic_load_explicit(&courseStatus[courseID],SC);
    bool flag = false;
    if(isregistered!=0 && isopen!=0){
        //if enrollments < capacity - enroll
        int enrolls = atomic_load_explicit(&enrollments[courseID] , SC);
        int capacity = atomic_load_explicit(&courseCapacity[courseID] , SC);
        if(enrolls < capacity){
            atomic_store_explicit(&enrollments[courseID],enrolls+1,SC);
           // printf("Enrolled %d in %d \n",studentID, courseID);
            flag = true;
        }
    }
    if(flag){
        for(int i=0 ; i<1; i++){
            int e = atomic_load_explicit(&enrollments[i] , SC);
            atomic_store_explicit(&enrollments[i],e,SC);
        }
    }
    end;
}

void closeCourse(int courseID) {
   begin;
   if(courseID < 0 || courseID >=1){
        abort;
        return;
   }
   for(int i=0;i<1;i++){
        atomic_load_explicit(&course[i],SC);  
        atomic_load_explicit(&courseStatus[i],SC);
        atomic_load_explicit(&courseCapacity[i],SC);
    }
    if(atomic_load_explicit(&course[courseID],SC) == -1){
        abort; //invalid course 
       // printf("Invalid Course\n");
        return;
    }
    if(atomic_load_explicit(&courseStatus[courseID],SC) == 0){
        abort;
        return;
    }
    atomic_store_explicit(&courseStatus[courseID],0,SC);
    
    for(int i=0 ; i<1; i++){
        int r1 = atomic_load_explicit(&course[i],SC);  
        int r3 = atomic_load_explicit(&courseStatus[i],SC);
        int r4 = atomic_load_explicit(&courseCapacity[i],SC);
        atomic_store_explicit(&course[i],r1,SC);
        atomic_store_explicit(&courseStatus[i],r3,SC);
        atomic_store_explicit(&courseCapacity[i],r4,SC);
    }
    end;
}

void openCourse(int courseID) {
    begin;
    if(courseID < 0 || courseID >=1){
        abort;
        return;
   }
   for(int i=0;i<1;i++){
        atomic_load_explicit(&course[i],SC);  
        atomic_load_explicit(&courseStatus[i],SC);
        atomic_load_explicit(&courseCapacity[i],SC);
    }
    if(atomic_load_explicit(&course[courseID],SC) == -1){
        abort; //invalid course 
       // printf("Invalid Course\n");
        return;
    }
    if(atomic_load_explicit(&courseStatus[courseID],SC) == 1){
        abort;
        return;
    }
    atomic_store_explicit(&courseStatus[courseID],1,SC);

    for(int i=0 ; i<1; i++){
        int r1 = atomic_load_explicit(&course[i],SC);  
        int r3 = atomic_load_explicit(&courseStatus[i],SC);
        int r4 = atomic_load_explicit(&courseCapacity[i],SC);
        atomic_store_explicit(&course[i],r1,SC);
        atomic_store_explicit(&courseStatus[i],r3,SC);
        atomic_store_explicit(&courseCapacity[i],r4,SC);
    }
    end;
}

// Function to delete a course
void deleteCourse(int courseID) {
   begin;
   if(courseID < 0 || courseID >=1){
        abort;
        return;
   }
//   printf("Deleting course %d \n",courseID);
   for(int i=0;i<1;i++){
        atomic_load_explicit(&course[i],SC);  
        atomic_load_explicit(&courseStatus[i],SC);
        atomic_load_explicit(&courseCapacity[i],SC);
    }
    if(atomic_load_explicit(&course[courseID],SC) == -1){
        abort; //invalid course 
       // printf("Invalid Course\n");
        return;
    }
    for(int i=0;i<1;i++){
        atomic_load_explicit(&enrollments[i],SC);
    }
    // delete course- set to -1 for this id
    atomic_store_explicit(&course[courseID],-1,SC);
    atomic_store_explicit(&courseStatus[courseID],-1,SC);
    atomic_store_explicit(&courseCapacity[courseID],-1,SC);
    atomic_store_explicit(&enrollments[courseID],0,SC);
   
    for(int i=0 ; i<1; i++){
        int r1 = atomic_load_explicit(&course[i],SC);  
        int r2 = atomic_load_explicit(&enrollments[i],SC);
        int r3 = atomic_load_explicit(&courseStatus[i],SC);
        int r4 = atomic_load_explicit(&courseCapacity[i],SC);
        atomic_store_explicit(&course[i],r1,SC);
        atomic_store_explicit(&enrollments[i],r2,SC);
        atomic_store_explicit(&courseStatus[i],r3,SC);
        atomic_store_explicit(&courseCapacity[i],r4,SC);
    }
    end;
}

int getAllEnrollments(){ 
   begin;
   for(int i=0 ; i<1; i++){
        atomic_load_explicit(&enrollments[i] , SC);
    }
   end;
   return 1;
}


void * thr1(void *arg){
    openCourse(0); //3
    enroll(1,0);
    deleteCourse(0);//3
    return NULL;
}
void * thr2(void *arg){
    openCourse(0); //3
    enroll(2,0); 
    deleteCourse(0); //3
    return NULL;
}
void * thr3(void *arg){
    openCourse(0);//3
    enroll(0,0);
    deleteCourse(0);//3
    getAllEnrollments();
    return NULL;
}

int main() {
    pthread_t t1,t2,t3;

    pthread_create(&t1,NULL,thr1,NULL);
    pthread_create(&t2,NULL,thr2,NULL);
    pthread_create(&t3,NULL,thr3,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
   // printf("----------------------------------------------\n");
    return 0;
}
