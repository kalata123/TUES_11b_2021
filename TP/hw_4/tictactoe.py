class Board:

    def __init__(self):
        self.board = {}


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

    def checkHor(self, letter):
        import pdb
        pdb.set_trace()
        return self.board[letter + "1"] ==\
               self.board[letter + "2"] ==\
               self.board[letter + "3"] and\
               self.board[letter + "1"] != " "and\
               self.board[letter + "1"] is not None,\
               self.board[letter + "1"]

    def checkWinner(self):
        for j in ["A", "B", "C"]:
            hor, w = self.checkHor(j)
            if hor:
                return w
        pass

    def __setitem__(self, other, val):
        self.board[other.upper()] = val
        if (len(self.board.keys()) == 9):
            a = self.checkWinner()
            if a:
                print("Congrats {}".format(a))


if __name__ == "__main__":
    brd = Board()
    for j in ["A", "B", "C"]:
        for i in range(1, 4):
            brd[j+str(i)] = " "
    brd["A1"] = "X"
    brd["A2"] = "X"
    brd["A3"] = "X"
    print(brd)
    brd["C1"] = "O"
