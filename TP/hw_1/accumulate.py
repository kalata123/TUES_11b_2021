import pdb


def accumulate_left(func, a, b):
    pdb.set_trace()
    if b == []:
        return 1
    else:
        return a/accumulate_left(func, a, b[:-1])
