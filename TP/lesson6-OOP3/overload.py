"""
 Desc:
  Python program to demonstrate method overloading in Python
"""


class Heap:
    def create(self, name=None):
        if name is not None:
            print('Hello ' + name)
        else:
            print('Hello ')


heap = Heap()
heap.create()
heap.create(" test parameter")
