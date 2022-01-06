def primeTable(n):
    tbl = [2]
    x = 2
    for i in range(1,n):
        while True:
            x += 1
            idx = 0
            d = tbl[idx]
            while d*d <= x and x%d != 0:
                idx += 1
                d = tbl[idx]
            if x%d != 0:
                tbl.append(x)
                break
    return tbl
import datetime
start = datetime.datetime.now()
print(primeTable(10**5)[-1])
print(datetime.datetime.now()-start)    
