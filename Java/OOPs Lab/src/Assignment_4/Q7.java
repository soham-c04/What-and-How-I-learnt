package Assignment_4;

import java.time.LocalDate;
import java.util.*;

class Person {
    private static int nextPersonId = 1;
    private int personId;
    private String name;
    private int age;
    private boolean loggedIn;

    public Person(String name, int age) {
        this.personId = nextPersonId++;
        this.name = name;
        this.age = age;
        this.loggedIn = false;
    }

    public boolean login() {
        this.loggedIn = true;
        System.out.println(name + " logged in.");
        return true;
    }

    public void logout() {
        this.loggedIn = false;
        System.out.println(name + " logged out.");
    }

    public int getPersonId() { return personId; }
    public String getName() { return name; }
    public int getAge() { return age; }
}

class Patient extends Person {      // Inheritance from Person
    private static int nextPatientId = 1;
    private int patientId;
    private String disease;

    // Aggregation - HAS-A set of appointments
    private List<Appointment> appointmentsList;
    // Association - Uniquely associated to a ward
    private Ward ward;

    public Patient(int age, String disease) {
        super("Patient#" + nextPatientId, age);
        this.patientId = nextPatientId++;
        this.disease = disease;
        this.appointmentsList = new ArrayList<>();
        this.ward = null;
    }

    public void bookAppointment(LocalDate date, String time) {
        Appointment appt = new Appointment(date, time, this);
        appointmentsList.add(appt);
        System.out.println("Patient " + patientId + " booked appointment on " + date + " at " + time);
    }

    public void admitToWard(Ward w) {
        if (w.addPatient(this)) {
            this.ward = w;
            System.out.println("Patient " + patientId + " admitted to Ward " + w.getWardNo());
        } else {
            System.out.println("Admission failed for patient " + patientId + ". Ward full.");
        }
    }

    public void dischargeFromWard() {
        if (ward != null) {
            ward.releasePatient(this);
            System.out.println("Patient " + patientId + " discharged from Ward " + ward.getWardNo());
            this.ward = null;
        } else {
            System.out.println("Patient " + patientId + " is not in any ward");
        }
    }

    public int getPatientId() { return patientId; }
    public String getDisease() { return disease; }
    public List<Appointment> getAppointments() { return appointmentsList; }
    public Ward getWard() { return ward; }
}

class Doctor extends Person {       // Inheritance from Person
    private static int nextDoctorId = 1;
    private int doctorId;
    private String specialization;

    public Doctor(String name, int age, String specialization) {
        super(name, age);
        this.doctorId = nextDoctorId++;
        this.specialization = specialization;
    }

    public void prescribeMedicine(MedicalRecord record, Medicine m) {
        record.useMedicine(m);
        System.out.println("Doctor prescribed " + m.getName() + " for record " + record.getRecordId());
    }

    public int getDoctorId() { return doctorId; }
    public String getSpecialization() { return specialization; }
}

class Ward {
    private int wardNo;
    private String type;
    private int capacity;

    // Aggregation - Contains some Patients
    private List<Patient> patients;

    public Ward(int wardNo, String type, int capacity) {
        this.wardNo = wardNo;
        this.type = type;
        this.capacity = capacity;
        this.patients = new ArrayList<>();
    }

    public boolean addPatient(Patient p) {
        if (patients.size() >= capacity) return false;
        patients.add(p);
        System.out.println("Added patient " + p.getPatientId() + " to ward " + wardNo);
        return true;
    }

    public void releasePatient(Patient p) {
        if (patients.remove(p)) {
            System.out.println("Released patient " + p.getPatientId() + " from ward " + wardNo);
        } else {
            System.out.println("Patient " + p.getPatientId() + " not found in ward " + wardNo);
        }
    }

    public int getPatientCount() {
        return patients.size();
    }

    public int getWardNo() { return wardNo; }
    public String getType() { return type; }
    public int getCapacity() { return capacity; }
    public List<Patient> getPatients() { return patients; }
}

class Appointment {
    private static int nextAppointmentId = 1;
    private int appointmentId;
    private LocalDate date;
    private String time;
    private boolean confirmed;
    private boolean cancelled;

    // Association - Uniquely linked to 1 patient
    private Patient patient;
    // Composition - Set of Medical Records
    private List<MedicalRecord> records;

    public Appointment(LocalDate date, String time, Patient patient) {
        this.appointmentId = nextAppointmentId++;
        this.date = date;
        this.time = time;
        this.patient = patient;
        this.records = new ArrayList<>();
        this.confirmed = false;
        this.cancelled = false;
    }

    public void confirm() {
        if (!cancelled) {
            confirmed = true;
            System.out.println("Appointment " + appointmentId + " confirmed.");
        } else {
            System.out.println("Cannot confirm cancelled appointment " + appointmentId);
        }
    }

    public void cancel() {
        if (!confirmed) {
            cancelled = true;
            System.out.println("Appointment " + appointmentId + " cancelled.");
        } else {
            System.out.println("Cannot cancel confirmed appointment " + appointmentId);
        }
    }

    public void addRecord(MedicalRecord mr) {
        records.add(mr);
        System.out.println("Medical record " + mr.getRecordId() + " added to appointment " + appointmentId);
    }

    // Dependency - Uses Billing Function
    public Billing generateBill() {
        double total = 0.0;
        for (MedicalRecord mr : records) {
            total += mr.getTotalMedicineCost();
        }
        Billing bill = new Billing(total);
        System.out.println("Generated bill for appointment " + appointmentId + " with amount " + total);
        return bill;
    }

    public int getAppointmentId() { return appointmentId; }
    public LocalDate getDate() { return date; }
    public String getTime() { return time; }
    public Patient getPatient() { return patient; }
    public List<MedicalRecord> getRecords() { return records; }
}

class MedicalRecord {
    private static int nextRecordId = 1;
    private int recordId;
    private String diagnosis;

    // Composition - has a set of medicines
    private List<Medicine> medicines;

    public MedicalRecord(String diagnosis) {
        this.recordId = nextRecordId++;
        this.diagnosis = diagnosis;
        this.medicines = new ArrayList<>();
    }

    public void updateRecord(String newDiagnosis) {
        this.diagnosis = newDiagnosis;
        System.out.println("Record " + recordId + " updated. New diagnosis: " + diagnosis);
    }

    public void useMedicine(Medicine m) {
        medicines.add(m);
        System.out.println("Medicine " + m.getName() + " added to record " + recordId);
    }

    public double getTotalMedicineCost() {
        double sum = 0.0;
        for (Medicine m : medicines) sum += m.getPrice();   // Usage Dependency
        return sum;
    }

    public int getRecordId() { return recordId; }
    public String getDiagnosis() { return diagnosis; }
    public List<Medicine> getMedicines() { return medicines; }
}

class Medicine {
    private static int nextMedId = 1;
    private int medicineId;
    private String name;
    private double price;

    public Medicine(String name, double price) {
        this.medicineId = nextMedId++;
        this.name = name;
        this.price = price;
    }

    public double getPrice() { return price; }
    public String getName() { return name; }
    public int getMedicineId() { return medicineId; }
}

class Billing {
    private static int nextBillId = 1;
    private int billId;
    private double amount;

    public Billing(double amount) {
        this.billId = nextBillId++;
        this.amount = amount;
    }

    public double generateBill() {
        System.out.println("Billing generated: id=" + billId + ", amount=" + amount);
        return amount;
    }

    public int getBillId() { return billId; }
    public double getAmount() { return amount; }
}

public class Q7 {
    public static void main(String[] args) {
        Doctor dr = new Doctor("Dr. Strange", 45, "Cardiology");
        dr.login();

        Ward wardA = new Ward(1, "General", 2);

        Patient p1 = new Patient(30, "Flu");
        Patient p2 = new Patient(40, "Fracture");

        p1.bookAppointment(LocalDate.now().plusDays(1), "10:00");
        p2.bookAppointment(LocalDate.now().plusDays(1), "11:00");

        Appointment appt1 = p1.getAppointments().get(0);
        MedicalRecord mr1 = new MedicalRecord("Influenza - mild");
        appt1.addRecord(mr1);

        Medicine med1 = new Medicine("Paracetamol", 10.0);
        Medicine med2 = new Medicine("Cough Syrup", 50.0);

        dr.prescribeMedicine(mr1, med1);
        dr.prescribeMedicine(mr1, med2);

        p1.admitToWard(wardA);

        Billing bill = appt1.generateBill();
        System.out.println("Generated bill id " + bill.getBillId() + " amount: " + bill.getAmount());

        p1.dischargeFromWard();

        dr.logout();
    }
}