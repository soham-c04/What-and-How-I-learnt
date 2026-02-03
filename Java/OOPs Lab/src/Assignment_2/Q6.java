package Assignment_2;

import java.util.*;

import static java.util.Collections.reverse;

class Expression{
    private String infix;
    private float value;
    public Expression(String expr){
        infix = expr;
    }
    public void print(){
        System.out.println("Infix = " + infix);
    }
    private static int precedence(char op){
        switch(op){
            case '+', '-':
                return 1;
            case '*', '/':
                return 2;
        }
        return 0;
    }
    private String getPostfix(){
        Stack<Character> stk = new Stack<>();
        Stack<Float> val = new Stack<>();
        String postfix = "";
        for(char c : infix.toCharArray()){
            if(c>='0' && c<='9'){
                postfix += c;
                val.push((float)(c-'0'));
            }
            else {
                while((!stk.isEmpty()) && (precedence(c) <= precedence(stk.peek()))){
                    char ch = stk.pop();
                    postfix += ch;
                    float b = val.pop(), a = val.pop();
                    if(ch=='-') val.push(a-b);
                    else if(ch=='*') val.push(a*b);
                    else if(ch=='/') val.push(a/b);
                    else if(ch=='+') val.push(a+b);
                }
                stk.push(c);
            }
        }
        while(!stk.isEmpty()){
            char ch = stk.pop();
            postfix += ch;
            float b = val.pop(), a = val.pop();
            if(ch=='-') val.push(a-b);
            else if(ch=='*') val.push(a*b);
            else if(ch=='/') val.push(a/b);
            else if(ch=='+') val.push(a+b);
        }
        value = val.pop();
        return postfix;
    }
    private String getPrefix(){
        infix = new StringBuilder(infix).reverse().toString();
        String prefix = new StringBuilder(getPostfix()).reverse().toString();
        infix = new StringBuilder(infix).reverse().toString();
        return prefix;
    }
    public void printPost(){ System.out.println("Postfix = " + getPostfix()); }
    public void printPre(){
        System.out.println("Prefix = " + getPrefix());
    }
    public float eval(){
        getPostfix();
        return value;
    }
}

public class Q6 {
    public static void main(String[] args){
        System.out.println();
        Scanner cin = new Scanner(System.in);
        System.out.print("Enter expression: ");
        String expr = cin.nextLine();
        Expression x =  new Expression(expr);
        x.print();
        x.printPost();
        x.printPre();
        System.out.print("x = " + x.eval());
    }
}
