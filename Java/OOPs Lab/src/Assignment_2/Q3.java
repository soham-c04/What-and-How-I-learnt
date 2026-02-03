package Assignment_2;

import java.util.Scanner;

class BankAccount {
    private int AccountNumber;
    private String AccountName;
    private float AccountBalance;
    public BankAccount(int accountNumber, String accountName, float accountBalance) {
        AccountNumber = accountNumber;
        AccountName = accountName;
        AccountBalance = accountBalance;
    }
    public void Deposit(float amount) {
        AccountBalance = AccountBalance + amount;
    }
    public void Withdraw(float amount) {
        AccountBalance = AccountBalance - amount;
    }
    public float CheckBalance() {
        System.out.println("\nAccount Balance: " + AccountBalance);
        return AccountBalance;
    }
}

public class Q3 {
    public static void main(String[] args) {
        System.out.println();
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter Account Number: ");
        int a = sc.nextInt();
        System.out.print("\nEnter Account Name: ");
        String b = sc.next();
        System.out.print("\nEnter Account Balance: ");
        int c = sc.nextInt();
        BankAccount B = new BankAccount(a, b, c);
        B.CheckBalance();
        System.out.println("\nChoose 1 to Deposit, 2  to Withdraw and 3 to Check Balance, Anything else to Exit: ");
        while(true) {
            System.out.print("\nEnter Choice: ");
            int d = sc.nextInt();
            if(d == 1) {
                System.out.print("\nEnter Amount to Deposit: ");
                float amount = sc.nextFloat();
                B.Deposit(amount);
            }
            else if(d == 2) {
                System.out.print("\nEnter Amount to Withdraw: ");
                float amount = sc.nextFloat();
                B.Withdraw(amount);
            }
            else if(d == 3) {
                float amount =  B.CheckBalance();
                if(amount <= 0) break;
            }
            else break;
        }
    }
}
