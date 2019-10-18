class Building:

    def __init__(self, floors=100, eggs=2):
        self.floors = floors
        self.eggs = eggs

    def drop(self):
        for i in range(0, self.floors, 14):
            pass
