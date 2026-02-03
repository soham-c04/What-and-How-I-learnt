package Assignment_4;

import java.io.*;
import java.util.*;

public class Q4 {
    public static void main(String[] args) {
        System.out.println();
        try{
            File file = new File("/home/student/Desktop/22CS02002/OOPs Lab/src/Assignment_4/xanadu.txt");
            Scanner sc = new Scanner(file);

            int count = 0;
            while(sc.hasNextLine()) {
                for (char c : sc.nextLine().toCharArray()) {
                    if(c=='e') count++;
                }
            }
            System.out.println("Number of occurrences of 'e' in xanadu.txt is: " + count);
        }
        catch(FileNotFoundException e) {
            System.out.println("Error: File not found");
        }
    }
}