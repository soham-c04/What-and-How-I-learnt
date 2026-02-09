package Assignment_5;

import java.util.*;

public class Q3{
    public static void main(String[] args) {
        System.out.println();
        Scanner sc  = new Scanner(System.in);
        HashMap<String, Integer> count = new HashMap<>();

        while(true) {
            System.out.print("\nEnter Word: ");
            String word = sc.nextLine();
            if(count.containsKey(word)){
                int occ = count.get(word)+1;
                count.put(word, occ);
                System.out.println(word + " - " + occ);
            }
            else{
                count.put(word,1);
                System.out.println(word + " - First occurence");
            }
        }
    }
}
