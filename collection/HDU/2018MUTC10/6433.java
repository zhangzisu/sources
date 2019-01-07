import java.util.Scanner;
import java.math.BigInteger;

class Main {
    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        int t = cin.nextInt();
        while (t-- > 0) {
            BigInteger b = new BigInteger("1");
            int n = cin.nextInt();
            while (n-- > 0)
                b = b.multiply(new BigInteger("2"));
            System.out.println(b);
        }
    }
}