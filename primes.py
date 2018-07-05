def p(k):
    for i in range(2, k):
        if k%i == 0:
            return 0
    return 1

def np1(n):
    from math import sqrt
    s = []
    x = int(sqrt(n) + 1)
    for k in range(2, x):
        if p(k) == 1:
            s += [k]
        else:
            None
    return s

def np(n):
    if p(n)==1:
        return np1(n) + [n]
    elif p(n) == 0 :
        return np1(n)

def valu(n):
    l = []
    for i in np(n):
        l += [[i, 0]]
    return l

print valu(100)

def dec(n):
    t = valu(n)
    s = np(n)
    for i in range(len(s)):
        j = s[i]
        while n%j == 0 :
            t[i][1] += 1
            j *= s[i]
    return t

print dec(100)
