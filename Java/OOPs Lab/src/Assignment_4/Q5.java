package Assignment_4;

import java.util.InputMismatchException;
import java.util.Scanner;

class ATMAccount{
    private String AccountNo;
    private int balance;

    public ATMAccount(String AccountNo, int balance) {
        this.AccountNo = AccountNo;
        this.balance = balance;
    }

    public void deposit(int amount){
        this.balance += amount;
    }

    public void withdraw(int amount){
        if(this.balance < amount) throw new IllegalArgumentException("You have only " + balance + ". You tried to withdraw " + amount);
        this.balance -= amount;
    }

    public float calculateInstallment(int months){
        if(months == 0) throw new ArithmeticException();
        float installment = this.balance / (float) months;
        return installment;
    }

    public void showBalance(){
        System.out.println("Your Balance is: " + this.balance);
    }
}

public class Q5 {
    public static void main(String[] args){
        System.out.println();
        Scanner sc = new Scanner(System.in);
        ATMAccount atm = new ATMAccount("12345", 0);

        System.out.println("Account Manager\nChoose from Options:-");
        System.out.println("1. Deposit");
        System.out.println("2. Withdraw");
        System.out.println("3. Calculate Installment");
        System.out.println("Anything else to Exit");

        while(true) {
            System.out.print("\nChoose: ");
            String option = sc.nextLine();
            System.out.println();

            try {
                if(option.equals("1")) {
                    System.out.print("Enter Deposit Amount: ");
                    int amount = sc.nextInt();
                    sc.nextLine();
                    atm.deposit(amount);
                }
                else if(option.equals("2")) {
                    System.out.print("Enter Withdraw Amount: ");
                    int amount = sc.nextInt();
                    sc.nextLine();
                    atm.withdraw(amount);
                }
                else if(option.equals("3")) {
                    System.out.print("Enter Months for installment: ");
                    int months = sc.nextInt();
                    sc.nextLine();
                    System.out.println("Installment: " + atm.calculateInstallment(months));
                }
                else break;
            }
            catch (InputMismatchException e){
                System.out.println("Error: Input Not an integer.");
                sc.nextLine();
            }
            catch (IllegalArgumentException e) {
                System.out.println("Error: " + e.getMessage());
            }
            catch (ArithmeticException e){
                System.out.println("Error: Can't divide by zero");
            }
            finally{
                atm.showBalance();
            }
        }
    }
}
