package Assignment_3;

import java.util.Scanner;

class Person{
    private String name;
    private int age;
    public Person(String name,int age){
        this.name=name;
        this.age=age;
    }
    public void Display(){
        System.out.println("Name: "+this.name);
        System.out.println("Age: "+this.age);
    }
}

class Employee extends Person{
    private int salary;
    public Employee(String name,int age,int salary){
        super(name,age);
        this.salary=salary;
    }
    public void Display(){
        super.Display();
        System.out.println("Salary: "+this.salary);
    }
}

class Manager extends Employee{
    private String department;
    public Manager(String name,int age,int salary, String department){
        super(name,age,salary);
        this.department=department;
    }
    public void Display(){
        super.Display();
        System.out.println("Department: "+this.department);
    }
}

public class Q1 {
    public static void main(String[] args){
        System.out.println();
        Scanner sc=new Scanner(System.in);
        System.out.print("Enter Person's Name: ");
        String name=sc.nextLine();
        System.out.print("Enter Person's Age: ");
        int age=sc.nextInt(); sc.nextLine();
        Person p=new Person(name,age);
        System.out.print("Enter Employee's Salary: ");
        int salary=sc.nextInt(); sc.nextLine();
        Employee e=new Employee(name,age,salary);
        System.out.print("Enter Manager's Department: ");
        String department=sc.nextLine();
        Manager m = new Manager(name, age,  salary, department);
        System.out.println("\nPerson:-");
        p.Display();
        System.out.println("\nEmployee:-");
        e.Display();
        System.out.println("\nManager:-");
        m.Display();
    }
}
