#Code from Arup Guha with some slight modifications to solve Q3 and Q4

import random

cipherQ3 = [488798928261625380184161,
          533946500611718831345802,
          411942882720703143384960,
          20068354290376977207914,
          252864055600177840617225,
          144565738643838496733483,
          98121155489099542089269,
          377474600037914621137040]

cipherQ4 = [[56495539, 72767212],
            [62083516, 76971521],
            [181398440, 263421160],
            [149867850, 72743477],
            [14826439, 190288780],
            [113953407, 197793189],
            [117331466, 185360595],
            [291767686, 140312582],
            [97578813, 288144131],
            [66782213, 277003739],
            [189849901, 192777619],
            [147582903, 21503450],
            [154299245, 242826784],
            [86211909, 200694188],
            [31309028, 293758361],
            [21217580, 3535169],
            [79019712, 49185229],
            [213930082, 159557439],
            [73624006, 229408211],
            [292736574, 18644176],
            [237123292, 168250610],
            [38995570, 306955959],
            [199390530, 176530325],
            [226189829, 196581913],
            [195038651, 170658203]]

def main():
    print("Solve 3 or 4?")
    choice = int(input())
    if choice == 3:
        Q3()

    elif choice == 4:
        Q4()

    else:
        print("No.")


def Q3():

    #Hardcode then get p and q
    n = 576025912082114341909169
    e = 395065083027011624330977

    p = getFactor(n)
    q = n // p

    #Get phi(n) and d
    mod = (p - 1) * (q - 1)
    d = modInv(e, mod)

    # Get the blocksize
    blocksize = getBlockSize(n)

    #Decrypt
    for num in cipherQ3:
        msgPart = fastmodexpo(num, d, n)
        orig = convertBack(msgPart, blocksize)
        print(orig)

def Q4():
    #Hardcode values
    Y_a = 32298658
    alpha =  52216224
    p = 310000037

    #Find X_a
    X_a = -1
    for i in range(p):
        if pow(alpha, i, p) == Y_a:
            X_a = i
            break

    if X_a == -1:
        print("Failed :(")
        return

    #Decrypt and print
    for pair in cipherQ4:
        k = pow(pair[0], X_a, p)
        kinv = modInv(k, p)

        #Block size is 6
        print(convertBack((pair[1] * kinv) % p, 6))

#THESE METHODS BELOW ARE TAKEN FROM CODE POSTED IN NOTES

# Returns the max block size for integer n.
def getBlockSize(n):

    res = 0
    mult = 1

    # If we can multiply 26 into our current size, we can add 1 to our blocksize.
    while 26*mult <= n:
        res += 1
        mult *= 26

    # Here is our result.
    return res

def convertBack(msg, blocksize):

    res = ""

    # Concatenate letters from back to front.
    for i in range(blocksize):
        let = chr(msg%26 + ord('A'))
        res = let + res
        msg = msg//26

    # Ta da!
    return res

def fastmodexpo(base,exp,mod):

    # Base case.
    if exp == 0:
        return 1

    # Speed up here with even exponent.
    if exp%2 == 0:
        tmp = fastmodexpo(base,exp//2,mod)
        return (tmp*tmp)%mod

    # Odd case, must just do the regular ways.
    return (base*fastmodexpo(base,exp-1,mod))%mod

# Returns the gcd of a and b.
def gcd(a,b):
    if b == 0:
        return a
    return gcd(b, a%b)

def EEA(a,b):

    # End of algorithm, 1*a + 0*b = a
    if b == 0:
        return [1,0,a]

    # Recursive case.
    else:

        # Next quotient and remainder.
        q = a//b
        r = a%b

        # Algorithm runs on b, r.
        rec = EEA(b,r)

        # Here is how we put the solution back together!
        return [rec[1], rec[0]-q*rec[1], rec[2]]

# Returns the modular inverse of x mod n. Returns 0 if there is no modular
# inverse.

def getFactor(n):

    a = 2
    b = 2

    while (True):

        # a steps once, b steps twice in the sequence.
        a = (a*a+1)%n
        b = (b*b+1)%n
        b = (b*b+1)%n

        # Get the difference between a,b.
        diff = a-b
        if diff < 0:
            diff += n

        # Give this a shot!
        factor = gcd(n, diff)

        # Found a factor.
        if factor > 1 and factor < n:
            return factor

        # Test failed.
        elif factor == n:
            return -1

def gcd(a,b):
    if b == 0:
        return a
    return gcd(b, a%b)

def modInv(x,n):

    # Call the Extended Euclidean.
    arr = EEA(n, x)

    # Indicates that there is no solution.
    if arr[2] != 1:
        return 0

    # Do the wrap around, if necessary.
    if arr[1] < 0:
        arr[1] += n

    # This is the modular inverse.
    return arr[1]

main()