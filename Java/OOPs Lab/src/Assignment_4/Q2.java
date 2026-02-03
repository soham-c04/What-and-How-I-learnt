package Assignment_4;

import java.io.*;
import java.util.*;

public class Q2 {
    public static void main(String[] args) {
        try{
            File file = new File("/home/student/Desktop/22CS02002/OOPs Lab/src/Assignment_4/file.txt");
            Scanner sc = new Scanner(file);

            ArrayList<int[]> list =  new ArrayList<>();
            while(sc.hasNextLine()) {
                String[] nums = sc.nextLine().split(",\\s");
                int x = 0, y = 0;
                try {
                    x = Integer.parseInt(nums[0]);
                }
                catch(NumberFormatException e){
                    throw new NumberFormatException(nums[0]);
                }

                try {
                    y = Integer.parseInt(nums[1]);
                }
                catch(NumberFormatException e){
                    throw new NumberFormatException(nums[1]);
                }
                list.add(new int[]{x,y});
            }

            Collections.sort(list, (a, b) -> {
                if (a[0] != b[0])
                    return Integer.compare(a[0], b[0]);
                else
                    return Integer.compare(a[1], b[1]);
            });

            for(int[] pair:list){
                System.out.println(pair[0]+" "+pair[1]);
            }
        }
        catch(FileNotFoundException e) {
            System.out.println("Error: File not found");
        }
        catch(ArrayIndexOutOfBoundsException e){
            System.out.println("Error: Less than 2 columns.");
        }
        catch (NumberFormatException e) {
            System.out.println("Error: Not an integer. Given: " + e.getMessage());
        }
    }
}