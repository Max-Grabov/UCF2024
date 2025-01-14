from decimal import *
import math
getcontext().prec = 50;
Kb = Decimal(1.38 * 10**(-23))
h = Decimal(6.63 * 10**(-34))
q = (h / (3 * Kb))
e = Decimal(math.e)

def uZero(f):
    if((e**(q * f) - 1) == 0):
        return 99999999999999999

    return ((3 * f * f) * (e**(q * f) - 1) - (q * e**(q * f)) * f * f * f) / ((e**(q * f) - 1)**2)

def findRoot(text):
    for i in range(len(text)):
        if(text[i] == '.' or text[i] == '-'):
            continue
        for j in range(10):
            if(uZero(Decimal(text[0:i] + f"{j}" + text[i + 1:len(text)])) < 0):
                text = text[0:i] + f"{j - 1}" + text[i + 1:len(text)]
                break

    return text

text = "000000000000.0000000000000000000000000000000000000"

text = findRoot(text)

print(text)
print(uZero(Decimal(text)))
print("------------")