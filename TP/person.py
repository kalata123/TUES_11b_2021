class Address:

    def __init__(self, city=None, street=None, number=None):
        self.__city = city
        self.__street = street
        self.__number = number


class Person:

    def __init__(self):
        self.__name = ""


class Computer:

    def __init__(self, mark=None, yearOfProduct=None, cpu=None,
                 os=None, ram=None, disk=None):
        self.__mark = mark
        self.__yearOfProduct = yearOfProduct
        self.__cpu = cpu
        self.__os = os
        self.__ram = ram
        self.__disk = disk


class Markbook:
    pass


class Student(Person):

    def __init__(self, name=None, number=None):
        self.__name = name
        self.__number = number
        self.__computer = Computer()
        self.__markbook = Markbook()

    def getName(self):
        return self.__name

    def setName(self, new_name):
        self.__name = new_name

    def getNumber(self):
        return self.__number

    def setNumbe(self, new_number):
        self.__number = new_number
