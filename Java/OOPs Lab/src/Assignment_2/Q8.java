package Assignment_2;

import java.util.Scanner;
import java.util.Vector;

class Movie{
    private String title;
    private int year;
    private String rating;
    public Movie(String title, int year, String rating) {
        this.title = title;
        this.year = year;
        this.rating = rating;
    }
    public Movie(String title, int year) {
        this.title = title;
        this.year = year;
        this.rating = "";
    }
    public boolean match(String Title){
        return title.equals(Title);
    }
    public void rate(char Rating){
        if((Rating >= '1') && (Rating <= '5')) rating += Rating;
        else System.out.println("Invalid Rating");
    }
    private float getRating(){
        if(rating.isEmpty()) return 0;
        float sum = 0;
        for(char c: rating.toCharArray()){
            sum += (float)(c-'0');
        }
        return sum/rating.length();
    }
    public void Display(){
        System.out.println("Title: " + title);
        System.out.println("   Year: " + year);
        System.out.print("   Rating: ");
        if(rating.isEmpty()) System.out.println("NA");
        else System.out.println(getRating());
    }
}
public class Q8 {
    public static void main(String[] args) {
        System.out.println();
        Scanner cin = new Scanner(System.in);
        System.out.println("Choose from Options:-");
        System.out.println("1. Publish Movie");
        System.out.println("2. Show list of Movies");
        System.out.println("3. Rate Movie");
        System.out.println("4. Get Movie information");
        System.out.println("Anything else to Exit");
        String option;
        Vector<Movie> movies = new Vector<>();
        while(true){
            System.out.print("\nChoose: ");
            option = cin.nextLine();
            System.out.println();
            if(option.equals("1")){
                System.out.print("Enter Title: ");
                String Title = cin.nextLine();
                for (Movie movie : movies) {
                    if (movie.match(Title)) {
                        System.out.println("Movie with same name already exists - ");
                        System.out.print("   ");
                        movie.Display();
                        Title = "";
                        break;
                    }
                }
                if(Title.isEmpty()) continue;
                System.out.print("Enter Year: ");
                int Year = cin.nextInt(); cin.nextLine();
                System.out.print("Enter Ratings: ");
                String ratings = cin.nextLine();
                movies.add(new Movie(Title, Year, ratings));
            }
            else if(option.equals("2")){
                for(int i = 0; i < movies.size(); i++){
                    System.out.print((i+1)+". ");
                    movies.get(i).Display();
                }
            }
            else if(option.equals("3")){
                System.out.print("Enter Title: ");
                String Title = cin.nextLine();
                int i = movies.size()-1;
                for(;i>=0;i--){
                    if(movies.get(i).match(Title)) break;
                }
                if(i>=0) {
                    System.out.print("Enter Rating: ");
                    movies.get(i).rate(cin.nextLine().charAt(0));
                }
                else System.out.println("Movie does not exist.");
            }
            else if(option.equals("4")){
                System.out.print("Enter Title: ");
                String Title = cin.nextLine();
                int i = movies.size()-1;
                for(;i>=0;i--){
                    if(movies.get(i).match(Title)) break;
                }
                if(i>=0) {
                    System.out.print("   ");
                    movies.get(i).Display();
                }
                else System.out.println("Movie does not exist.");
            }
            else break;
        }
    }
}
