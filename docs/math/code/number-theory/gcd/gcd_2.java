import java.util.Scanner;

class Main {
// --8<-- [start:core]
public int gcd(int a, int b) {
    while(b != 0) {
        int tmp = a;
        a = b;
        b = tmp % b;
    }
    return a;
}
// --8<-- [end:core]
public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int a=in.nextInt(), b=in.nextInt();
    Main solver=new Main();
    int d=solver.gcd(a,b);
    System.out.println(d);
    in.close();
}
}
