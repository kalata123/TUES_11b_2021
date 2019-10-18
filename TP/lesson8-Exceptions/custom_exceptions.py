#define Python user-defined exceptions
class Error(Exception):
   """Base class for other exceptions"""
   pass
 
class InputTooSmallError(Error):
   """Raised when the entered alpahbet is smaller than the actual one"""
   pass
 
class InputTooLargeError(Error):
   """Raised when the entered alpahbet is larger than the actual one"""
   pass

#our main program
#user guesses an alphabet until he/she gets it right
 
#you need to guess this alphabet
alphabet = 'm'
 
while True:
   try:
       apb =  raw_input("Enter an alphabet: ")
       if apb < alphabet:
           raise InputTooSmallError
       elif apb > alphabet:
           raise InputTooLargeError
       break
   except InputTooSmallError:
       print("The entered alphabet is too small, try again!")
       print('')
   except InputTooLargeError:
       print("The entered alphabet is too large, try again!")
       print('')
 
print("Congratulations! You guessed it correctly.")