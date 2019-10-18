try:
   fob = open("test", "w")
   fob.write("This is my test file for exception handling!!")
except IOError:
   print "Error: can\'t find the file or read data"
else:
   print "Write operation is performed successfully on the file"
   fob.close()