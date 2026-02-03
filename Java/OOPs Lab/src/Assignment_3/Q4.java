package Assignment_3;

import java.util.Scanner;

abstract class Queue {
    abstract protected void push(int element);
    abstract protected int front();
    abstract protected boolean pop();
}

class LL extends Queue {
    private int value;
    private LL head, prev, tail;
    public LL(){
        head = tail = prev = null;
    }
    public LL(int value, LL head, LL tail){
        this.value = value;
        this.head = head;
        this.tail = tail;
        this.prev = null;
    }
    @Override
    public void push(int element) {
        LL new_tail = new LL(element, head, tail);
        if(head == null){
            head = tail = new_tail;
        }
        else{
            tail.prev = new_tail;
            tail = new_tail;
        }
    }
    @Override
    public int front() {
        if(head == null){
            System.out.println("Queue is empty");
            return -123456789;
        }
        return head.value;
    }
    @Override
    public boolean pop() {
        if(head == null){
            System.out.println("Queue is empty");
            return false;
        }
        head = head.prev;
        return true;
    }
}

class Arr extends Queue {
    private static final int MAX_LEN = 10000;
    private int[] queue = new int[MAX_LEN];
    private int head, tail;
    public Arr(){
        head = 0;
        tail = -1;
    }
    @Override
    public void push(int element) {
        if(head==MAX_LEN){
            System.out.println("Queue is full");
        }
        else{
            tail++;
            queue[tail] = element;
        }
    }
    @Override
    public int front() {
        if(head>tail){
            System.out.println("Queue is empty");
            return -123456789;
        }
        return queue[head];
    }
    @Override
    public boolean pop() {
        if(head>tail){
            System.out.println("Queue is empty");
            return false;
        }
        head++;
        return true;
    }
}

public class Q4 {
    public static void main(String[] args) {
        System.out.println();
        Scanner sc =  new Scanner(System.in);
        System.out.println("Choose from Options:-");
        System.out.println("1. push()");
        System.out.println("2. front()");
        System.out.println("3. pop()");
        System.out.println("Anything else to Exit");
        String option;
        System.out.println("\nUsing Linked List:-");
        LL q = new LL();
        while(true){
            System.out.print("\nChoose: ");
            option = sc.nextLine();
            System.out.println();
            if(option.equals("1")){
                System.out.print("Enter element to push: ");
                q.push(sc.nextInt()); sc.nextLine();
            }
            else if(option.equals("2")){
                System.out.println("Front element: "+q.front());
            }
            else if(option.equals("3")){
                if(q.pop()) System.out.println("Element popped");
            }
            else break;
        }
        System.out.println("\nUsing Array:-");
        Arr q2 = new Arr();
        while(true){
            System.out.print("\nChoose: ");
            option = sc.nextLine();
            System.out.println();
            if(option.equals("1")){
                System.out.print("Enter element to push: ");
                q2.push(sc.nextInt()); sc.nextLine();
            }
            else if(option.equals("2")){
                System.out.println("Front element: "+q2.front());
            }
            else if(option.equals("3")){
                if(q2.pop()) System.out.println("Element popped");
            }
            else break;
        }
    }
}
