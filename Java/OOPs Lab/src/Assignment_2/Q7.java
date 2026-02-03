package Assignment_2;

import java.util.Scanner;

class Date{
    private int day=0;
    private String month;
    private int year;
    public Date(String date) {
        String s = "";
        for(char c: date.toCharArray()){
            if(c=='-'){
                if(day==0){
                    day = Integer.parseInt(s);
                }
                else{
                    int m = Integer.parseInt(s);
                    switch (m) {
                        case 1-> this.month = "January";
                        case 2-> this.month = "February";
                        case 3-> this.month = "March";
                        case 4-> this.month = "April";
                        case 5-> this.month = "May";
                        case 6-> this.month = "June";
                        case 7-> this.month = "July";
                        case 8-> this.month = "August";
                        case 9-> this.month = "September";
                        case 10-> this.month = "October";
                        case 11-> this.month = "November";
                        case 12-> this.month = "December";
                    }
                }
                s = "";
            }
            else s += c;
        }
        year = Integer.parseInt(s);
    }
    public void updateDay(int day) {
        this.day = day;
    }
    public void updateMonth(String month) {
        this.month = month;
    }
    public void updateYear(int year) {
        this.year = year;
    }
    public void print(){
        System.out.print("\n"+month + " ");
        if(day<10) System.out.print("0");
        System.out.println(day + ", " + year);
    }
}
public class Q7 {
    public static void main(String[] args) {
        System.out.println();
        Scanner cin = new Scanner(System.in);
        System.out.print("Enter Date: ");
        String date = cin.nextLine();
        Date d = new Date(date);
        d.print();
    }
}
