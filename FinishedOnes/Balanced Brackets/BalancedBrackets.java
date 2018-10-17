import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class BalancedBrackets {
    
    public class Node{
        char b;
        Node n = null;
        public Node(char b){
            this.b = b;
        }
    }
    
    public class Stack{
        Node top = null;
        
        public void push(char b){
            Node n = new Node(b);
            n.n = top;
            top = n;
        }
        
        public char pop(){
            char b = 'n';
            if(top!=null){
                b = top.b;
                top = top.n;
            }
            return b;
        }
        
        public void popAll(){
            top = null;
        }
    }
    
    public void run(){
        Stack S = new Stack();
        
        Scanner in = new Scanner(System.in);
        int t = in.nextInt();
        String[] o = new String[t];
        
        for(int a0 = 0; a0 < t; a0++){
            String s = in.next();
            o[a0] = "YES";
            if(s.length()%2 !=0){
                o[a0] = "NO";
                continue;
            }
            for(int i = 0; i< s.length(); i++){
                char X = s.charAt(i);
                if(X == '(' ||X == '[' ||X == '{')
                    S.push(X);
                else if(X == ')' ||X == ']' ||X == '}'){
                    char c = S.pop();
                    if(c=='n'){
                        o[a0] = "NO";
                        break;
                    }
                    switch(c){
                        case '(' :
                            if(X != ')')
                                o[a0] = "NO";
                            break;
                        case '[' :
                            if(X != ']')
                                o[a0] = "NO";
                            break;
                        case '{' :
                        if(X != '}')
                                o[a0] = "NO";
                    }
                    if(o[a0].equals("NO"))
                        break;
                }
            }
            if(S.top !=null){
            o[a0] = "NO";
            S.popAll();
            }
        }
        
        
        for(int i = 0; i< t; i++)
            System.out.println(o[i]);
    }
    
    public static void main(String[] args) {
        new BalancedBrackets().run();
    }
}

