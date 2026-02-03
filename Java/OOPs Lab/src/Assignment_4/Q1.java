package Assignment_4;

import java.util.Scanner;

public class Q1 {
    public static void main(String[] args){
        try{
            int num = Integer.parseInt(args[0]);
            if(num<=0) throw new IllegalArgumentException("Factorial for only natural numbers.");
            long fact = 1;
            for(int i=2;i<=num;i++){
                fact = fact*i;
            }
            System.out.println("Factorial is: " + fact);
        }
        catch(ArrayIndexOutOfBoundsException e){
            System.out.println("Error: No argument given.");
        }
        catch(NumberFormatException e){
            System.out.println("Error: Not an integer.");
        }
        catch (IllegalArgumentException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
