package Assignment_5;

import java.util.*;

class Hospital{
    public int appointmentID;
    public String patient_name;
    public int appointment_time;

    public Hospital(int appointmentID, String patient_name, int appointment_time){
        this.appointmentID = appointmentID;
        this.patient_name = patient_name;
        this.appointment_time = appointment_time;   // I am assuming 24 hour format
    }

    public void print(){
        System.out.println(appointmentID + " | " + patient_name + " | " + appointment_time);
    }
}

public class Q5 {
    public static void main(String[] args){
        System.out.println();
        List<Hospital> hospitals = new ArrayList<>();
        hospitals.add(new Hospital(1, "goku", 1623));
        hospitals.add(new Hospital(2, "sasuke", 2250));
        hospitals.add(new Hospital(3, "hori chie", 1265));
        hospitals.add(new Hospital(4, "jiraya", 1256));
        hospitals.add(new Hospital(5, "frieren", 2156));

        hospitals.sort(new Comparator<Hospital>() {
            public int compare(Hospital a, Hospital b) {
                return Integer.compare(a.appointment_time, b.appointment_time);
            }
        });

        System.out.println("Sorted by appointment_time:-");
        for(Hospital h: hospitals){
            h.print();
        }

        Collections.sort(hospitals, (a, b) -> {
            return a.patient_name.compareTo(b.patient_name);
        });

        System.out.println("\nSorted by patient_name:-");
        for(Hospital h: hospitals){
            h.print();
        }
    }
}
