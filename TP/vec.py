import copy

v = 2
v2 = copy.deepcopy(v)
v3 = copy.copy(v)
print(v == v2)
print(v is v2)
print(v == v3)
print(v is v3)
