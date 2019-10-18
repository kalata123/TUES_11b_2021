"""
 Desc:
  Python program to demonstrate how differs overloading from Java/C++
  a method or an attribute
"""


class Heap:
    def create(self):
        print(" Creating Heap")

    def create(self, param):
        print(" Creating Node with param",  param)


heap = Heap()
heap.create()  # error!
heap.create(" test parameter")
