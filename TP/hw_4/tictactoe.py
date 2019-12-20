class Board:

    def __init__(self):
        # self.board = []
        self.board = {}

    def __setitem__(self, other, val):
        self.board[other.upper()] = val

    def __str__(self):
        lst = "  -------------\n"
        for i in [1, 2, 3]:
            lst += "{i} | {a} | {b} | {c} |\n".format(
                    i=i,
                    a=self.board["A" + str(i)],
                    b=self.board["B" + str(i)],
                    c=self.board["C" + str(i)])
            lst += "  -------------\n"
        lst += "    A   b   C"
        return lst


if __name__ == "__main__":
    brd = Board()
    for j in ["A", "B", "C"]:
        for i in range(1, 4):
            brd[j+str(i)] = " "
    brd["A1"] = "X"
    brd["C1"] = "O"
    print(brd)
