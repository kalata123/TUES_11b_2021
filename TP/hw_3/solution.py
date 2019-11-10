import pdb
from collections import defaultdict


def group_by_f(func, lst):
    dct = defaultdict(list)
    for i in range(len(lst)):
        dct[func(lst[i])].append(lst[i])
    return dct


def max_notes(lst):
    tmp = 0
    for i in range(len(lst)):
        for _ in range(len(lst[i])):
            tmp = sum(lst[i]) if tmp < sum(lst[i]) else tmp
    return tmp


def leading(lst):
    tmp = 0
    for i in range(len(lst)):
        tmp = i if lst[tmp][-1] < lst[i][-1] else tmp
    return tmp


def is_stronger(a, b):
    if set(a[1]) == set(b[1]):
        return False

    if len(set(a[1])) < len(set(b[1])):
        return False

    A = sorted(a[1], key=lambda x: x[0])
    B = sorted(b[1], key=lambda x: x[0])

    for i in range(len(set(b[1]))):
        # if they have the same ingredients, but A has less power
        if A[i][0] == B[i][0]:
            if A[i][1] < B[i][1]:
                return False
    return True


def least_stronger(a, lst):
    return "sap"


def strong_relation(lst):
    a = []
    for i in range(len(lst)):
        a.append((lst[i], []))
        for j in range(len(lst)):
            if is_stronger(lst[j], lst[i]):
                a[i][1].append(lst[j][0])
    return a


if __name__ == '__main__':
    pass
