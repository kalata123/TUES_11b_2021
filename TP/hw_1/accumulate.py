def accumulate_left(func, a, b):
    return accumulate_left(func, func(a, b[0]), b[1:]) if b else a


def accumulate_right(func, a, b):
    return func(b[0], accumulate_right(func, a, b[1:])) if b else a
