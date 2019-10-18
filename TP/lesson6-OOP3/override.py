"""
 Desc:
  Python program to demonstrate overriding
  using the super() method
"""


class base(object):
    def base_func(self):
        print('Method of base class')


class child(base):
    def base_func(self):
        print('Method of child class')
        super(child, self).base_func()


class next_child(child):
    def base_func(self):
        print('Method of next_child class')
        super(next_child, self).base_func()


obj = next_child()
obj.base_func()
