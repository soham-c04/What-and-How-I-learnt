package Assignment_3;

import java.util.Scanner;
import java.util.Vector;

class Room{
    private int ID;
    protected Room(int ID){
        this.ID = ID;
    }
    public int getID(){
        return ID;
    }
}

class Office extends Room{
    public Office(int ID){
        super(ID);
    }
}

class ClassRoom extends Room{
    int size;
    public ClassRoom(int ID, int size){
        super(ID);
        this.size = size;
    }
    public int getSize(){
        return size;
    }
}

class Department{
    private String name;
    private Vector<Office> offices;
    Department(String name){
        this.name = name;
        offices = new Vector<Office>();
    }
    public void addOffice(Office office){
        offices.add(office);
    }
    public String getName(){
        return name;
    }
}

class person{
    private String id;
    protected person(String id){
        this.id = id;
    }
    public String getID(){
        return id;
    }
}

class Professor extends person{
    private String type;
    private Department department;
    Professor(String id, String type, Department department){
        super(id);
        if(type.equals("Full") || type.equals("Associate") || type.equals("Assistant")) this.type = type;
        else System.out.println("Professor of Invalid type");
        this.department = department;
    }
    public String getType(){
        return type;
    }
    public Department getDepartment(){
        return department;
    }
}

class Staff extends person{
    private Office office;
    Staff(String id, Office office){
        super(id);
        this.office = office;
    }
    public Office  getOffice(){
        return office;
    }
}

public class Q5 {
    public static void main(String[] args) {

        System.out.println();
        Scanner cin = new Scanner(System.in);

        Vector<Department> departments = new Vector<>();
        Vector<Office> allOffices = new Vector<>();
        Vector<Professor> professors = new Vector<>();
        Vector<Staff> staffMembers = new Vector<>();

        System.out.println("\nChoose from Options:-");
        System.out.println("1. Add Department");
        System.out.println("2. Add Office to Department");
        System.out.println("3. Add Professor");
        System.out.println("4. Add Staff");
        System.out.println("5. Show All Data");
        System.out.println("Anything else to Exit");

        while (true) {
            System.out.print("\nChoose: ");
            String option = cin.nextLine();
            System.out.println();

            if (option.equals("1")) {
                System.out.print("Enter Department Name: ");
                String name = cin.nextLine();
                departments.add(new Department(name));
                System.out.println("Department added.");
            }

            else if (option.equals("2")) {
                if (departments.isEmpty()) {
                    System.out.println("No departments available.");
                    continue;
                }

                for (int i = 0; i < departments.size(); i++) {
                    System.out.println((i + 1) + ". " + departments.get(i).getName());
                }

                System.out.print("Choose Department: ");
                int d = cin.nextInt() - 1;
                cin.nextLine();

                System.out.print("Enter Office ID: ");
                int id = cin.nextInt();
                cin.nextLine();

                Office office = new Office(id);
                departments.get(d).addOffice(office);
                allOffices.add(office);

                System.out.println("Office added.");
            }

            else if (option.equals("3")) {
                if (departments.isEmpty()) {
                    System.out.println("No departments available.");
                    continue;
                }

                System.out.print("Enter Professor ID: ");
                String id = cin.nextLine();

                System.out.print("Enter Type (Full / Associate / Assistant): ");
                String type = cin.nextLine();

                for (int i = 0; i < departments.size(); i++) {
                    System.out.println((i + 1) + ". " + departments.get(i).getName());
                }

                System.out.print("Choose Department: ");
                int d = cin.nextInt() - 1;
                cin.nextLine();

                professors.add(new Professor(id, type, departments.get(d)));
                System.out.println("Professor added.");
            }

            else if (option.equals("4")) {
                if (allOffices.isEmpty()) {
                    System.out.println("No offices available.");
                    continue;
                }

                System.out.print("Enter Staff ID: ");
                String id = cin.nextLine();

                for (int i = 0; i < allOffices.size(); i++) {
                    System.out.println((i + 1) + ". Office ID: " + allOffices.get(i).getID());
                }

                System.out.print("Choose Office: ");
                int o = cin.nextInt() - 1;
                cin.nextLine();

                staffMembers.add(new Staff(id, allOffices.get(o)));
                System.out.println("Staff added.");
            }

            else if (option.equals("5")) {
                System.out.println("\nDepartments:");
                for (Department d : departments)
                    System.out.println("- " + d.getName());

                System.out.println("\nProfessors:");
                for (Professor p : professors)
                    System.out.println("- " + p.getID() +
                            " (" + p.getType() + ", " +
                            p.getDepartment().getName() + ")");

                System.out.println("\nStaff:");
                for (Staff s : staffMembers)
                    System.out.println("- " + s.getID() +
                            " (Office " + s.getOffice().getID() + ")");
            }

            else break;
        }
    }
}
