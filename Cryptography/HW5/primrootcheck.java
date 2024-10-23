import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Scanner;
class PrimRootCheck {
    public static void main(String[] args) {
        //Variable setup and setup code for algorithms
        int n;
        BigInteger p = new BigInteger("0");
        BigInteger g = new BigInteger("0");
        Scanner s = new Scanner(System.in);

        n = s.nextInt();

        for(int i = 0; i < n; i++){
            p = s.nextBigInteger();
            g = s.nextBigInteger();

            if(isPrimitiveRoot(p, g) == true){
                System.out.println(1);
            }
            else {
                System.out.println(0);
            }
        }

        s.close();
    }

    public static boolean isPrimitiveRoot(BigInteger p, BigInteger g){
        //First we need to determine the divisors of p
        ArrayList<BigInteger> factors = new ArrayList<>();

        BigInteger check = p.subtract(BigInteger.ONE);
        //In my proof for Number 7, I showed that we only need to look at factors that are prime numbers
        //This is because that is where a non-primitive roots' cycles will first appear.
        //However, for the sake of this problem, I will check all factors since i am kinda lazy
        BigInteger i = BigInteger.TWO;
        while(true){
            if(i.multiply(i).compareTo(check) == 1){
                break;
            }

            if(check.mod(i).equals(BigInteger.ZERO)){
                //Add both the number and the value that multiplies said number to p - 1
                factors.add(i);
                factors.add(check.divide(i));
            }

            i = i.add(BigInteger.ONE);
        }

        long numFactors = factors.size();

        //If we have a remainder of 1, there is a cycle therefore g is not a primitive root of p
        for(int j = 0; j < numFactors; j++){
            if(modExp(g, check.divide(factors.get(j)), p).equals(BigInteger.ONE)){
                return false;
            }
        }
        return true;
    }

    //Make a fast exponentiation algorithm
    public static BigInteger modExp(BigInteger num, BigInteger power, BigInteger mod){
        if(power.equals(BigInteger.ZERO)) return BigInteger.ONE;
        if(power.equals(BigInteger.ONE)) return num.mod(mod);
        if(power.mod(BigInteger.TWO).equals(BigInteger.ZERO)){
            BigInteger q = modExp(num, power.divide(BigInteger.TWO), mod);
            return (q.multiply(q)).mod(mod);
        }
        return (num.multiply(modExp(num, power.subtract(BigInteger.ONE), mod)).mod(mod));
    }
}
