#Dunder or magic methods in Python are the methods 
#having two prefix and suffix underscores in the method name.
#Dunder here means “Double Under (Underscores)”. 
#These are commonly used for operator overloading. 
#Few examples for magic methods are:
# __init__, __add__, __len__, __repr__ etc.

# declare our own string class 
class String: 
      
    # magic method to initiate object 
    def __init__(self, string): 
        self.string = string 
          
    # print our string object 
    def __repr__(self): 
        return 'Object: {}'.format(self.string) 
  
# Driver Code 
if __name__ == '__main__': 
      
    # object creation 
    string1 = String('Hello') 
  
    # print object location 
    print(string1) 