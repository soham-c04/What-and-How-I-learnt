package Assignment_5;

import java.util.ArrayList;
import java.util.Scanner;
import java.util.Vector;

class Stack<T>{
    private ArrayList<T> stack;
    public Stack() {
        stack = new ArrayList<>();
    }
    public void push(T item){
        stack.add(item);
    }
    public boolean isEmpty(){
        return (stack.size()==0);
    }
    public T peek(){
        if(isEmpty()){
            System.out.println("Stack is empty");
            return null;
        }
        T TOP = stack.getLast();
        return TOP;
    }
    public T pop(){
        T TOP = peek();
        if(TOP == null) return TOP;
        stack.removeLast();
        return TOP;
    }
}

public class Q7 {
    public static void main(String[] args){
        System.out.println();
        Scanner sc = new Scanner(System.in);
        Stack<String> stk = new Stack<>();
        System.out.println("Choose:-");
        System.out.println("1. push()");
        System.out.println("2. pop()");
        System.out.println("3. peek()");
        System.out.println("Anything else to exit\n");
        while(true){
            System.out.print("\nOption: ");
            String option = sc.nextLine();
            if(option.equals("1")){
                System.out.print("Item: ");
                String item = sc.nextLine();
                stk.push(item);
            }
            else if(option.equals("2")) stk.pop();
            else if(option.equals("3")) System.out.println(stk.peek());
            else break;
        }
    }
}
