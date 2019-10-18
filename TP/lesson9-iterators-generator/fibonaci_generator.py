# Demonstrate Python Generator Function

def fibonacci(xterms):
    # first two terms
    x1 = 0
    x2 = 1
    count = 0

    if xterms <= 0:
       print("Please provide a +ve integer")
    elif xterms == 1:
       print("Fibonacci seq upto",xterms,":")
       print(x1)
    else:
       while count < xterms:
           xth = x1 + x2
           x1 = x2
           x2 = xth
           count += 1
           yield xth

fib = fibonacci(5)

print(next(fib))
print(next(fib))
print(next(fib))
print(next(fib))
print(next(fib))
print(next(fib))