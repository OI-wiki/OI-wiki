import java.util.Scanner;

class Main {
// --8<-- [start:core]
// Version 1
public int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Version 2
public int gcdShort(int a, int b) {
    return b == 0 ? a : gcdShort(b, a % b);
}
// --8<-- [end:core]
public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int a=in.nextInt(), b=in.nextInt();
    Main solver=new Main();
    int d=solver.gcd(a,b);
    assert d == solver.gcdShort(a,b);
    System.out.println(d);
    in.close();
}
}
