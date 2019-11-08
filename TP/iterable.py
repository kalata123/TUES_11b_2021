import math
from time import sleep


class Itrbl():
    def __init__(self, max):
        self.max = max
        self.now = 0
        self.lst = []
        self.iterated = False
        self.indx = -1

    def __next__(self):
        if self.iterated:
            try:
                self.indx += 1
                return self.lst[self.indx]
            except IndexError:
                raise StopIteration()
        else:
            if self.now >= self.max:
                self.iterated = True
                self.now = 0
                raise StopIteration()
            else:
                sleep(1)
                self.now += 1
                self.lst.append(self.now)
                return self.now

    def __iter__(self):
        return self


def is_prime(n):
    if n == 2:
        return True
    if n % 2 == 0 or n <= 1:
        return False

    sqr = int(math.sqrt(n)) + 1

    for divisor in range(3, sqr, 2):
        if n % divisor == 0:
            return False
    return True


def fltr(generator, okay):
    for i in generator:
        if okay(i):
            yield i


def gen(i=1):
    while True:
        if is_prime(i):
            yield i
        i += 1


if __name__ == '__main__':
    for i in fltr(gen(), lambda a: a % 97 == 0):
        print(f"{i}")
