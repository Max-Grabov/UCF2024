def modExp(num, power, mod):
    res = 1
    while (power > 0):

        #If our power is odd, (last bit is off), multiply our value by our num (removing 1 power)
        if ((power & 1) != 0):
            res = (res * num) % mod

        #Our power is even, do a shift to divide by 2
        power = power >> 1

        #Perform the squaring
        num = (num * num) % mod

    #Return our value
    return res % mod

def isPrimitiveRoot(p, g, factors):

    #For every possible value of a factor that is valuable, perform realtive prime test, up to sqrt(p-1)
    #If we include 1 every value would fail since a^(p-1)/1 is equivalent to 1 via fermat's theorem
    for i in range(2, p):
        if(i * i > p - 1):
            break

        # Append both i and (p - 1) / i since they are factors
        if((p - 1) % i) == 0:
            factors.append(i)
            factors.append(int((p - 1) / i))

    numFactors = len(factors)

    #if any of these factors have a modExp of 1, g is not primitive
    for i in range(0, numFactors):
        if(modExp(g, int((p - 1) / factors[i]), p) == 1):
            return False

    return True


n = 0
p = g = 0

factors = []

n = int(input())

#Do the input gathering and use functions
for i in range(0, n):
    inpt = input().split(" ")

    p = int(inpt[0])
    g = int(inpt[1])

    factors = []
    if(isPrimitiveRoot(p, g, factors) == True):
        print(1)

    else:
        print(0)



