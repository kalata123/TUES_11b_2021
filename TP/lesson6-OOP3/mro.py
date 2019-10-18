"""
 Desc:
  Python program to demonstrate how MRO(Method Resolution Order )
  resolves a method or an attribute
"""


class Heap:
    def create(self):
        print(" Creating Heap")


class Node(Heap):
    def create(self):
        print(" Creating Node")


node = Node()
node.create()
