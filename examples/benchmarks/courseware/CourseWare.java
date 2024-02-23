package benchmarks.courseware;

import benchmarks.BenchmarkModule;
import database.AbortDatabaseException;

import java.util.ArrayList;
import java.util.HashMap;

public class CourseWare {

    public static final String STUDENT = "STUDENT";
    public static final String COURSE = "COURSE";
    public static final String ENROLLMENTS = "ENROLLMENTS";
    private static CourseWare courseWareInstance;

    public static CourseWare getInstance() {
        if(courseWareInstance == null){
            courseWareInstance = new CourseWare();
        }
        return courseWareInstance;
    }

    
    public void enroll(int studentID, int courseID){
        try {
            db.begin();
            var stString = db.readRow(STUDENT, studentID + "");
            if(stString == null) db.abort();

            var student = new Student(stString);

            var cString = db.readRow(COURSE, courseID + "");
            if(cString == null) db.abort();
            var course = new Course(cString);


            if(!student.isRegistered() && course.getStatus().equals("open")){

                var enrollments = db.readIfIDStartsWith(ENROLLMENTS, courseID+ "");
                if(enrollments.size() < course.getCapacity()){
                    enrollments.add(studentID+"");

                    db.insertRow(ENROLLMENTS, courseID+":"+studentID);
                }
            }

            db.commit();
        } catch (Exception ignored) {

        }
    }

    public ArrayList<String> getEnrollments(){
        db.begin();

        var enrollments = db.readAllIDs(ENROLLMENTS);

        db.commit();
        return enrollments;
    }

    public void closeCourse(int courseID){
        db.begin();
        modifyCourseStatusBody(courseID, "close");
        db.commit();
    }

    protected void modifyCourseStatusBody(int courseID, String label){

        var courseSt = db.readRow(COURSE, courseID+"");

        if(courseSt != null){
            var course = new Course(courseSt);
            course.setStatus(label);
            db.writeRow(COURSE, courseID+"", course.toString());
        }
    }

    public void openCourse(int courseID){
        db.begin();
        modifyCourseStatusBody(courseID, "open");
        db.commit();
    }


    public void deleteCourse(int courseID){
        db.begin();

        modifyCourseStatusBody(courseID, "close");

        db.deleteRow(COURSE, courseID+"");

        var enrollments = db.readAllIDs(ENROLLMENTS);
        for(var e: enrollments){
            if(e.startsWith(courseID+"")){
                db.deleteRow(ENROLLMENTS, e.toString());
            }
        }

        db.commit();
    }
}
