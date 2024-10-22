import java.util.ArrayList;
import java.util.Scanner;
class PrimRootCheck {
    public static void main(String[] args) {
        //Variable setup and setup code for algorithms
        int n;
        long p, g;
        Scanner s = new Scanner(System.in);

        n = s.nextInt();

        for(int i = 0; i < n; i++){
            p = s.nextLong();
            g = s.nextLong();

            if(isPrimitiveRoot(p, g) == true){
                System.out.println(1);
            }
            else {
                System.out.println(0);
            }
        }

        s.close();
    }

    public static boolean isPrimitiveRoot(long p, long g){
        //First we need to determine the divisors of p
        ArrayList<Long> factors = new ArrayList<>();

        //In my proof for Number 7, I showed that we only need to look at factors that are prime numbers
        //This is because that is where a non-primitive roots' cycles will first appear.
        //However, for the sake of this problem, I will check all factors since i am kinda lazy
        for(int i = 2; i * i < p - 1; i++){
            if((p - 1) % i == 0){
                //Add both the number and the value that multiplies said number to p - 1
                factors.add(Long.valueOf(i));
                factors.add(Long.valueOf(p / i));
            }
        }

        long numFactors = factors.size();

        //If we have a remainder of 1, there is a cycle therefore g is not a primitive root of p
        for(int i = 0; i < numFactors; i++){
            if(modExp(g, (p - 1) / factors.get(i), p) == 1){
                return false;
            }
        }
        return true;
    }

    //Make a fast exponentiation algorithm
    public static long modExp(long num, long power, long mod){
        if(power == 0) return 1;
        if(power == 1) return num % mod;
        if(power % 2 == 0){
            long q = modExp(num, power/2, mod);
            return (q * q) % mod;
        }
        return (num * modExp(num, power - 1, mod)) % mod;
    }
}
