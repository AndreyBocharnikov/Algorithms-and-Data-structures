import java.math.BigInteger; 
import java.util.Scanner;

public class Main
{
	public static void main(String[] args) {
	    Scanner in = new Scanner(System.in);
        int n = in.nextInt();
	    for (int i = 0; i < n; i++) {
	        Long x = in.nextLong();
	        BigInteger a = new BigInteger(x.toString());
	        if (a.isProbablePrime(10)) {
	            System.out.println("YES");  
	        } else {
	            System.out.println("NO"); 
	        }
	    } 
	}
}
