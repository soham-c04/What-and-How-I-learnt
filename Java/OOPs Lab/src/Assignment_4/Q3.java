package Assignment_4;

import java.util.*;

import static java.lang.System.exit;

class RetValTest {
    public static String sEmail = "";

    public static void extractEmail(String sentence) {
        try {
            if(sentence==null || sentence.isEmpty()) throw new ArrayIndexOutOfBoundsException("Supplied String empty.");

            String[] tokens = sentence.split(" ");
            for (String token : tokens) {
                if (token.endsWith("@iitbbs.ac.in")) {
                    sEmail = token;
                    return;
                }
            }
            throw new IllegalArgumentException("no iitbbs email found");
        }
        catch(ArrayIndexOutOfBoundsException e){
            System.out.println("Error: " + e.getMessage());
            exit(1);
        }
        catch(IllegalArgumentException e){
            System.out.println("Error: " + e.getMessage());
            exit(2);
        }
    }
}

public class Q3 {
    public static void main(String[] args) {
        RetValTest.extractEmail("My email is xyz23@iitbbs.ac.in");
        System.out.println("Success: "+RetValTest.sEmail);
    }
}
