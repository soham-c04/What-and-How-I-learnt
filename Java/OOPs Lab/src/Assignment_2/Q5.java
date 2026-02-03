package Assignment_2;

import java.util.Scanner;

class Interest{
    private static double RateOfInterest = 10;
    private double Balance;
    public Interest(double principal){
        Balance = principal;
    }
    private static double SimpleInterest(float time){
        double interest = time * RateOfInterest/100;
        return interest;
    }
    private static double CompoundInterest(int time){
        double interest = Math.pow(1+RateOfInterest/100,time);
        return interest;
    }
//    public void Deposit(float amount) {
//        Balance += amount;
//    }
//    public void Withdraw(float amount) {
//        Balance += amount;
//    }
    public double withSimpleInterest(float time){
        return Balance*SimpleInterest(time);
    }
    public double withCompoundInterest(int time){
        return Balance*CompoundInterest(time);
    }
}

public class Q5 {
    public static void main(String[] args) {
        System.out.println();
        Scanner sc = new Scanner(System.in);
        System.out.print("\nEnter Account Balance (principal): ");
        double a = sc.nextInt();
        Interest B = new Interest(a);
        System.out.print("\nEnter Account-2 Balance (principal): ");
        double b = sc.nextInt();
        Interest C = new Interest(b);
        System.out.print("Enter time (in years): ");
        int t = sc.nextInt();

        System.out.println("Account-1:\nSimpleInterest after " + t + " years is = " + B.withSimpleInterest(t));
        System.out.println("CompoundInterest after " + t + " years is = " + B.withCompoundInterest(t));

        System.out.println("\nAccount-2:\nSimpleInterest after " + t + " years is = " + C.withSimpleInterest(t));
        System.out.println("CompoundInterest after " + t + " years is = " + C.withCompoundInterest(t));
    }
}
