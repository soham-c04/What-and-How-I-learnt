package Assignment_5;

import java.util.*;

public class Q2{
    public static <T> void PrintArray(T[] arr){
        for(T a:arr){
            System.out.print(a + " ");
        }
        System.out.println();
    }

    public static void main(String[] args){
        System.out.println();
        Integer[] a = {3,1,2};
        String[] b = {"goku", "sasuke", "jiraya"};
        PrintArray(a);
        PrintArray(b);
    }
}
