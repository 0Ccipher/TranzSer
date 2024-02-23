package benchmarks.courseware;

import database.TRUtility;

public class Course {

    private int id;
    private String name;
    private String departement;
    private String status;
    private int capacity;

    public Course(int id, String name, String departement, String status, int capacity) {
        this.id = id;
        this.name = name;
        this.departement = departement;
        this.status = status;
        this.capacity = capacity;
    }

    @Override
    public String toString() {
        return id + ";" + name + ";" + departement + ";" + status + ";" + capacity;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public String getDepartement() {
        return departement;
    }

    public String getStatus() {
        return status;
    }

    public int getCapacity() {
        return capacity;
    }

    public void setStatus(String status) {
        this.status = status;
    }
}
