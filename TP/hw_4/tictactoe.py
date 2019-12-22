class TicTacToeBoard:

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

    def check_cols(self):
        for i in ["A", "B", "C"]:
            if (
                self.board[i + "1"] ==
                self.board[i + "2"] ==
                self.board[i + "3"] and
                self.board[i + "1"] != " "
            ):
                return i
        return None

    def check_rows(self):
        for i in [1, 2, 3]:
            if (
                self.board["A" + str(i)] ==
                self.board["B" + str(i)] ==
                self.board["C" + str(i)] and
                self.board["A" + str(i)] != " "
            ):
                return i
        return None

    def check_dia(self):
        pass

    def game_status(self):
        c = self.check_cols()  # returns the letter of winner's col
        r = self.check_rows()  # returns number of winner's row
        d = self.check_dia()  # returns 1 or 3, depending on the direction of d
        if r:
            print("{} wins!".format(self.board["A" + str(r)]))
        elif c:
            print("{} wins!".format(self.board[c + "1"]))
        elif d:
            print("{} wins!".format(self.board["A" + str(d)]))
        elif 0:  # if it's draw
            pass
        else:
            print("Game in progress.")
        pass

    def __setitem__(self, other, val):
        self.board[other.upper()] = val


if __name__ == "__main__":
    brd = TicTacToeBoard()
    for j in ["A", "B", "C"]:
        for i in range(1, 4):
            brd[j+str(i)] = " "
    brd["A1"] = "X"
    brd["B1"] = "X"
    brd["C1"] = "X"
    brd["C2"] = "O"
    brd.game_status()
    brd["A3"] = "X"
    brd.game_status()
    print(brd)
