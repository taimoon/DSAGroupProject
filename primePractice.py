def isprime_navie(x): #navie approach if genuinely do it
    for i in range(2,x-1):
        if (x % i) == 0:
            return False
    return True
def isprime(x): #answer given online
    import math
    for i in range(2,int(math.sqrt(x))+1):
        if (x % i) == 0:
            return False
    return True
def isprime2(x):#another uncommon given online
    i = 2
    while i*i < x+1:
        if (x%i) == 0:
            return False
        i=i+1
    return True
def nextprime(x):
    x = x+1
    while isprime2(x) == False:
        x=x+1
    return x
def primePos(n):
    x = 2
    for i in range(1, n):
        x = nextprime(x)
    return x
import datetime
start = datetime.datetime.now()
print(primePos(10**5))
print(datetime.datetime.now()-start)   
