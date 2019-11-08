from collections import defaultdict
``

def group_by_f(func, lst):
    dct = defaultdict(list)
    for i in range(len(lst)):
        dct[func(lst[i])].append(lst[i])
    return dct


if __name__ == '__main__':
    a = [[1], [7, 8], [1, 2, 3, 4], [4], ["random", "words"]]
    dct = group_by_f(len, a)
    print(dct.keys())
    print(dct.values())
    print(dct)
