package Assignment_3;

import java.util.Scanner;

class Asset{
    private String descriptor;
    private String date;
    private int current_value;
    protected Asset(String descriptor, String date, int current_value){
        this.descriptor = descriptor;
        this.date = date;
        this.current_value = current_value;
    }
    protected void displayDetails(){
        System.out.println("Asset descriptor: " + descriptor);
        System.out.println("Asset date: " + date);
        System.out.println("Asset current_value: " + current_value);
    }
}

class Stock extends Asset{
    private int num_shares;
    private int share_price;
    private static final String asset_type = "stock";
    public Stock(String descriptor, String date, int current_value, int num_shares, int share_price){
        super(descriptor, date, current_value);
        this.num_shares = num_shares;
        this.share_price = share_price;
    }
    public void displayDetails(){
        super.displayDetails();
        System.out.println("Asset num_shares: " + num_shares);
        System.out.println("Asset share price: " + share_price);
        System.out.println("Asset asset type: " + asset_type);
    }
}

class Bond extends Asset{
    private int interest_rate;
    private static final String asset_type = "bond";
    public Bond(String descriptor, String date, int current_value, int interest_rate){
        super(descriptor, date, current_value);
        this.interest_rate = interest_rate;
    }
    public void displayDetails(){
        super.displayDetails();
        System.out.println("Interest rate: " + interest_rate);
        System.out.println("Asset type: " + asset_type);
    }
}

class Savings extends Asset{
    private int interest_rate;
    private static final String asset_type = "savings";
    public Savings(String descriptor, String date, int current_value, int interest_rate){
        super(descriptor, date, current_value);
        this.interest_rate = interest_rate;
    }
    public void displayDetails(){
        super.displayDetails();
        System.out.println("Interest rate: " + interest_rate);
        System.out.println("Asset type: " + asset_type);
    }
}

public class Q2 {
    public static void main(String[] args){
        System.out.println();
        Scanner sc=new Scanner(System.in);
        System.out.print("Enter descriptor: ");
        String descriptor=sc.nextLine();
        System.out.print("Enter date: ");
        String date=sc.nextLine();
        System.out.print("Enter current value: ");
        int current_value=sc.nextInt(); sc.nextLine();

        System.out.print("Enter number of Stock shares: ");
        int num_shares=sc.nextInt(); sc.nextLine();
        System.out.print("Enter Stock share price: ");
        int share_price=sc.nextInt(); sc.nextLine();
        Stock s =  new Stock(descriptor, date, current_value, num_shares, share_price);
        System.out.print("Enter Bond interest rate: ");
        int interest_rate=sc.nextInt(); sc.nextLine();
        Bond b = new Bond(descriptor, date, current_value, interest_rate);
        System.out.print("Enter Savings interest rate: ");
        int interest_rate2=sc.nextInt(); sc.nextLine();
        Savings sv = new Savings(descriptor, date, current_value, interest_rate2);
        System.out.println("\nStock Class:-");
        s.displayDetails();
        System.out.println("\nBond Class:-");
        b.displayDetails();
        System.out.println("\nSavings Class:-");
        sv.displayDetails();
    }
}
