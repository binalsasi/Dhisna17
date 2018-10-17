import java.util.*;

public class HighFalls {
    public class Node{
        int p;
        boolean alive = true;
        Node n;
        public Node(int p, boolean a){
            this.p = p;
            alive = a;
        }
    }
    
    public class Stack{
        Node top = null;
        
        public boolean push(int i){
            Node n = null;
            if(top != null &&top.p < i)
                n = new Node(i, false);
            else
                n = new Node(i, true);
            n.n = top;
            top = n;
            return top.alive;
        }
        
        public void nPush(int i){
            Node n = new Node(i, true);
            n.n = top;
            top = n;
        }
        
        public Node pop(){
            Node n = null;
            n = top;
            top = top.n;
            return n;
        }
    }
    
    public void run(){
        Scanner sc = new Scanner(System.in);
        int num = sc.nextInt();
        int days = 0;
        boolean death = false, pop = true;
        Stack a = new Stack(), b = new Stack();
        
        for(int i = 0; i< num; i++){
            if(a.push(sc.nextInt())){
                death = true;
            }
        }
        
        days++;
        
        int buffer = 0;
        while(death){
            death = false;
            if(pop){
                if(a.top!=null){
                    while(a.top!=null){
                        Node d = a.pop();
                        if(d.alive){
                            if(d.p >= buffer){
                                if(buffer!=0)
                                     b.nPush(buffer);
                            }
                            else
                                death = true;
                                buffer = d.p;
                        }
                    }
                    b.nPush(buffer);
                }
                pop = false;
            }
            else{
                while(b.top!=null){
                    if(a.push(b.pop().p))
                        death = true;
                }
                pop = true;
            }
            days++;
        }
        
        System.out.println(days);
    }
    public static void main(String[] args) {
        new HighFalls().run();
    }
}
