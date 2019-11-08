def group_by_f(func, lst):
    dct = {}
    for i in range(len(lst)):
        if func(lst[i]) in dct.keys()= func(lst[j]):
        dct[func(lst[i])].append(lst[i])
    return dct
dct = group_by_f(lambda a: a % 2 == 0, [1,2,3,4,5,6,7,8,9,10])
print(dct)
