class Student:    
    def __init__(self, name, number):
        self.__name = name
        self.__number = number
        self.__grades = {}

    def addMark(self, subject, mark):
        if subject not in self.__grades:
            self.__grades[subject] = list([])
            
        self.__grades[subject].append(mark)

    def getAverage(self, subject):
        print(self.__grades[subject])
        return sum(self.__grades[subject]) / len(self.__grades[subject])
        
    def getName(self) :
        return self.__name
        
    def getNumber(self): 
        return self.__number
        
student = Student("Stoyan Hristov", 22)
student.addMark("TP", 2)
student.addMark("TP", 4)
print("Average mark:", student.getAverage("TP"),"\n")
