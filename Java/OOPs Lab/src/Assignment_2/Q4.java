package Assignment_2;

import java.util.Scanner;

class Student{
    private int Marks;
    public void SetMarks(int marks){
        Marks = marks;
    }
    public int GetMarks(){
        return Marks;
    }
}

public class Q4 {
    public static void main(String[] args) {
        System.out.println();
        Scanner sc = new Scanner(System.in);
        /*
        No, it is not possible to directly access Marks from main() because they are in separate classes and
        Marks is a private variable.
         */
        System.out.print("Enter Marks: ");
        int a =  sc.nextInt();
        Student s = new Student();
        s.SetMarks(a);
        System.out.println("Your marks are: " + s.GetMarks());
    }
}
