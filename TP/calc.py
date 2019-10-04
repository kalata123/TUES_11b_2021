class Calculator:
    # def __init__(self, a, b):
    #     self.a = a
    #     self.b = b

    def multiply(self, a, b=1):
        if b:
            self.last = a * b
        else:
            self.last *= a
        return self.last

    def divide(self, a, b=1):
        if b:
            self.last = a / b
        else:
            self.last /= a
        return self.last

    def substract(self, a, b=0):
        if b:
            self.last = a - b
        else:
            self.last -= a
        return self.last

    def sum(self, a, b=0):
        if b:
            self.last = a + b
        else:
            self.last += a
        return self.last

    def lastValue(self):
        if self.last:
            return self.last
        else:
            return None


if __name__ == "__main__":
    a = int(input("a:"))
    b = int(input("b:"))
    calc = Calculator()

    print(f"""Multi = {calc.multiply(a, b)}, Div = {calc.divide(a, b)},
Subs = {calc.substract(a, b)}, Sum = {calc.sum(a)}, {calc.lastValue()}""")
