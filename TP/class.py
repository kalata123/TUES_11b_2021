class A:
    def a(self):
        pass


class Human:
    what = 'Human'

    def __init__(self, a):
        pass
    pass


class Student(Human):
    pass


if __name__ == '__main__':
    z = Student(2)
    print(z.what)
