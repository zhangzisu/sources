import java.util.*;
import java.math.BigInteger;

class Main {
    private static final BigInteger _1 = new BigInteger("1");

    public static void main(String args[]) {
        Scanner cin = new Scanner(System.in);
        int x = cin.nextInt();

        for (; x > 0; x--) {
            BigInteger n = new BigInteger(cin.next());
            BigInteger p = new BigInteger(cin.next());
            BigInteger m = n;
            BigInteger ans = _1;
            while (m.compareTo(p) >= 0) {
                BigInteger rest = m.mod(p);
                m = m.divide(p);
                ans = ans.multiply(rest.add(_1));
            }
            ans = ans.multiply(m.add(_1));
            System.out.println(n.add(_1).subtract(ans));
        }

        cin.close();
    }
}