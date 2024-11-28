n = int(input())
winState = 0
loseState = 0
drawState = 0
for i in range(31) :
    if(n < pow(2, i)) : 
        break
    numN = (n // pow(2, i) + 1) // 2
    numM = 0 
    for j in range(i + 1, 31): 
        numM += (n // pow(2, j) + 1) // 2 
    if i % 2 == 1: 
        winState += numN * numN + 2 * numN * numM
    if i % 2 == 0: 
        loseState += numN * numN
        drawState += 2 * numN * numM

print(winState)
print(drawState)
print(loseState)
    


def bruteForce(n): 
    def rec(dp, x, y) : 
        if x % 2 == 1 and y % 2 == 1 : return 0 
        if (x, y) in dp :
            return 2
        dp[(x, y)] = 1
        isDraw = False
        if x % 2 == 0 : 
            ret = rec(dp, x // 2, y + x // 2)
            if ret == 0:
               return 1
            elif ret == 2 : 
               isDraw = True
        if y % 2 == 0 : 
            ret = rec(dp, x + y // 2, y // 2)
            if ret == 0: 
                return 1
            elif ret == 2 : 
                isDraw = True
        
        if isDraw :  
            return 2
        return 0 
    ret = {}
    for x in range(1, n + 1) : 
        for y in range(1, n + 1) :
            dp = {}
            s = rec(dp, x, y)
            if s not in ret: 
              ret[s] = 1
            else : 
              ret[s] += 1 
    print(ret[0], ret[2], ret[1])

#bruteForce(n)
