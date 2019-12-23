class InvalidMove(BaseException):
    def __str__(self):
        return "Place is already taken. Try again!"


class InvalidValue(BaseException):
    def __str__(self):
        return "You can use only O and X. Try again!"


class InvalidKey(BaseException):
    def __str__(self):
        return "No such coordinates. Try again!"


class NotYourTurn(BaseException):
    def __str__(self):
        return "Not your turn."


class TicTacToeBoard:

    def __init__(self):
        self.first_move = 1
        self.on_turn = ""
        self.next_on_turn = ""
        self.board = {}
        for j in ["A", "B", "C"]:
            for i in range(1, 4):
                self.board[j+str(i)] = " "

    def __str__(self):
        lst = "\n  -------------\n"
        for i in [3, 2, 1]:
            lst += "{i} | {a} | {b} | {c} |\n".format(
                    i=i,
                    a=self.board["A" + str(i)],
                    b=self.board["B" + str(i)],
                    c=self.board["C" + str(i)])
            lst += "  -------------\n"
        lst += "    A   B   C  \n"
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
        if (
            self.board["A1"] ==
            self.board["B2"] ==
            self.board["C3"] and
            self.board["A1"] != " "
        ):
            return 1

        if (
            self.board["A1"] ==
            self.board["B2"] ==
            self.board["C3"] and
            self.board["A1"] != " "
        ):
            return 3

    def check_draw(self):
        return False if " " in self.board.values() else True

    def game_status(self):
        c = self.check_cols()  # returns the letter of winner's col
        r = self.check_rows()  # returns number of winner's row
        d = self.check_dia()  # returns 1 or 3, depending on the direction of d
        if r:
            return "{} wins!".format(self.board["A" + str(r)])
        elif c:
            return "{} wins!".format(self.board[c + "1"])
        elif d:
            return "{} wins!".format(self.board["A" + str(d)])
        elif self.check_draw():  # if it's draw
            return "Draw!"
        else:
            return "Game in progress."

    def __setitem__(self, other, val):
        if self.board[other.upper()] != " ":  # Place taken
            raise InvalidMove()
        elif other.upper() not in self.board.keys():  # Wrong Key
            raise InvalidKey()
        elif val not in ("O", "X"):  # Wrong Value
            raise InvalidValue()
        elif val == self.next_on_turn and not self.first_move:  # Not your turn
            raise NotYourTurn()
        elif self.first_move:
            self.board[other.upper()] = val
            self.first_move = 0
            self.next_on_turn = val
        else:
            self.board[other.upper()] = val
            self.on_turn = self.next_on_turn
            self.next_on_turn = val


if __name__ == "__main__":
    brd = TicTacToeBoard()
    brd["A1"] = 'X'
    brd["A2"] = 'O'
    brd["B1"] = 'X'
    brd["A3"] = 'O'
    brd["C1"] = 'X'
    print(brd.game_status())
    print(brd)
