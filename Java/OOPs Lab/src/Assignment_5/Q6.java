package Assignment_5;

import java.util.*;

public class Q6 {
    public static void main(String[] args) {
        System.out.println();
        Scanner sc = new Scanner(System.in);
        Set<Integer> liked = new LinkedHashSet<Integer>();
        while(true){
            System.out.print("\nEnter post ID (-1 to exit): ");
            int id = sc.nextInt();
            if(id==-1) break;
            liked.add(id);
        }
        System.out.print("\nFinal order: ");
        for(Integer id: liked) System.out.print(id + " ");
    }
}
