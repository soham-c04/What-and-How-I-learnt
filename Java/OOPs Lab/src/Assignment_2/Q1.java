package Assignment_2;

import java.util.Scanner;

class NumberHolder {
    public int anInt;
    public float aFloat;
    public NumberHolder(int a, float b) {
        anInt = a;
        aFloat = b;
    }
    public void Display(){
        System.out.print("Attribute Values : ");
        System.out.print(anInt + " ");
        System.out.println(aFloat);
    }
}

public class Q1 {
    public static void main(String[] args) {
        System.out.println();
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter 2 integers : ");
        int a = sc.nextInt(), b = sc.nextInt();
        NumberHolder nh = new NumberHolder(a, b);
        nh.Display();
        System.out.print("Enter 2 integers : ");
        a =  sc.nextInt(); b =  sc.nextInt();
        NumberHolder nh2 = new NumberHolder(a, b);
        nh2.Display();
    }
}
