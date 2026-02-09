package Assignment_5;

import java.util.*;

public class Q1 {
    public static void main(String[] args) {
        System.out.println();
        Scanner sc = new Scanner(System.in);

        ArrayList<Integer> arr = new ArrayList<>();
        System.out.print("Enter number of elements in List: ");
        int n = sc.nextInt(); sc.nextLine();
        System.out.print("Enter elements in List: ");
        for (int i = 0; i < n; i++){
            arr.add(sc.nextInt());
        }
        sc.nextLine();

        System.out.print("\nUsing for loop: ");
        for(Integer i : arr) System.out.print(i + " ");

        System.out.print("\nUsing iterator: ");
        Iterator<Integer> it = arr.iterator();
        while(it.hasNext()){
            System.out.print(it.next() + " ");
        }

        System.out.print("\nUsing ListIterator: ");
        ListIterator<Integer> itr = arr.listIterator();
        while(itr.hasNext()){
            System.out.print(itr.next() + " ");
        }
    }
}
