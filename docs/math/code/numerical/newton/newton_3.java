import java.math.BigInteger;
import java.util.Scanner;
class Main {
// --8<-- [start:core]
public static BigInteger isqrtNewton(BigInteger n) {
  if (n.signum() == 0) return BigInteger.ZERO;
  BigInteger a = BigInteger.ONE.shiftLeft(n.bitLength() / 2);
  boolean p_dec = false;
  for (;;) {
    BigInteger b = n.divide(a).add(a).shiftRight(1);
    if (a.compareTo(b) == 0 || a.compareTo(b) < 0 && p_dec)
      break;
    p_dec = a.compareTo(b) > 0;
    a = b;
  }
  return a;
}
// --8<-- [end:core]
public static void main(String[] args){Scanner in=new Scanner(System.in);System.out.println(isqrtNewton(in.nextBigInteger()));
    in.close();}
}
