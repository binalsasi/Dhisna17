import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class LargestRectangle {
    
    public class Stack{
        int top = 0;
        int[] h;
        int maxA = 0;
        int min = 1000001;
        Stack next = null;
        
        public Stack(int c){
            h = new int[c+1];
        }
        
        public void push(int i){
            if(min>i) min = i;
            h[++top] = i;
            if(maxA < top*min) maxA = top*min;
        }
        
        public int pop(){
            if(top!=0)
             return h[top--];
            min = 1000001;
            return 0;
        }
    }

    public void run(){
        Scanner s = new Scanner(System.in);
        int n = s.nextInt();
        Stack a = new Stack(n), b = new Stack(n);
        a.next = b; b.next = a;
        Stack cur = a;
        for(int i = 0; i< n; i++)
            a.push(s.nextInt());
        
        int t = 0;
        while(n!=0){
            t = cur.pop();
            if(t!=0){
                if(cur.top!=0)
                    cur.next.push(t);
            }else{
                n--;
                cur = cur.next;
            }
        }
        
        System.out.println((a.maxA > b.maxA ? a.maxA : b.maxA));
    }
    
    public static void main(String[] args) {
        new LargestRectangle().run();
    }
}
