import java.util.ArrayList;
import java.util.Scanner;
import java.util.Random;
public class testCaseGenerator {
    public static long GCD(long p, long q){
        if(q == 0){
            return p;
        }

        long r = p % q;
        return GCD(q, r);
    }
    public static long modExp(long num, long power, long mod){
        if(power == 0) return 1;
        if(power == 1) return num % mod;
        if(power % 2 == 0){
            long q = modExp(num, power/2, mod);
            return (q * q) % mod;
        }
        return (num * modExp(num, power - 1, mod)) % mod;
    }

    public static boolean isPrimitiveRoot(long p, long g){

        ArrayList<Long> factors = new ArrayList<>();

        for(int i = 2; i * i < p - 1; i++){
            if((p - 1) % i == 0){
                factors.add(Long.valueOf(i));
                factors.add(Long.valueOf(p / i));
            }
        }

        long numFactors = factors.size();

        for(int i = 0; i < numFactors; i++){
            if(modExp(g, (p - 1) / factors.get(i), p) == 1){
                return false;
            }
        }
        return true;
    }

    public static void main(String args[]){
        long p;
        int n;

        Scanner s = new Scanner(System.in);
        p = s.nextLong();
        n = s.nextInt();

        long val = 1;
        for(long i = 2; i < p - 1; i++){
            if(isPrimitiveRoot(p, i) == true){
                val = i;
                break;
            }
        }

        ArrayList<Long> relPrimes = new ArrayList<>();
        ArrayList<Long> notRelPrime = new ArrayList<>();
        for(long i = 1; i < p - 1; i++){
            if(GCD(p - 1, i) == 1){
                relPrimes.add(Long.valueOf(i));
            }
            else {
                notRelPrime.add(Long.valueOf(i));
            }
        }
        long size = relPrimes.size();
        long size2 = notRelPrime.size();

        Random rand = new Random();
        System.out.println(n);
        long[] primRoots = new long[(int)size];
        for(int i = 0; i < n; i++){
            if(rand.nextInt(2) == 1){
                primRoots[i] = modExp(val, relPrimes.get(i), p);
                System.out.println(p + " " + primRoots[i]);
            }
            else {
                long ind = rand.nextLong(size2);
                long k = notRelPrime.get((int)ind);
                System.out.println(p + " " + k);
            }
        }

        s.close();
    }
}
