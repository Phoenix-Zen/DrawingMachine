def dicoIte(v, l):
    ind_d = 0
    ind_f = len(l)-1
    while ind_d <= ind_f:
        ind_c = (ind_d +ind_f)//2
        if l[ind_c] == v:
            return ind_c
        if l[ind_c] < v:
            ind_d = ind_c+1
        if l[ind_c] > v:
            ind_d = ind_c-1
def ficoRec(v, l):
    ind_m = (len(l)-1)//2
    if l[ind_m] == v:
        return ind_m
    elif l[ind_m] > v:
        return ficoRec(v, l[:ind_m])
    else:
        return ind_m+ficoRec(v, l[ind_m:])
print(dicoIte(5, [2,3,4,5,6]))
print(ficoRec(5, [2,3,4,5,6]))
print(ficoRec(25, [1,2,6,10,12,13,18,25,29,35]))