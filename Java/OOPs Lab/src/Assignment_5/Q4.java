package Assignment_5;

import java.util.*;

class Employee{
    public String name;
    public String department;
    public Employee(String name, String department){
        this.name = name;
        this.department = department;
    }
}

public class Q4{
    public static void main(String[] args){
        List<Employee> arr_e =  new ArrayList<Employee>();
        arr_e.add(new Employee("emp1","cse"));
        arr_e.add(new Employee("emp2","ee"));
        arr_e.add(new Employee("emp3","ece"));
        arr_e.add(new Employee("emp4","cse"));
        arr_e.add(new Employee("emp5","cse"));

        Map<String, List<Employee>> group = new HashMap<>();
        for(Employee e:arr_e){
            group.putIfAbsent(e.department, new ArrayList<>());
            group.get(e.department).add(e);
        }

        for(String department:group.keySet()){
            System.out.print(department + ": ");
            for(Employee e:group.get(department)){
                System.out.print(e.name + " ");
            }
            System.out.println();
        }
    }
}
