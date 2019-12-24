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
        lst = '\n  -------------\n' +\
            '3 | {a3} | {b3} | {c3} |\n'.format(
                    a3=self.board["A3"],
                    b3=self.board["B3"],
                    c3=self.board["C3"]) +\
            '  -------------\n' +\
            '2 | {a2} | {b2} | {c2} |\n'.format(
                    a2=self.board["A2"],
                    b2=self.board["B2"],
                    c2=self.board["C2"]) +\
            '  -------------\n' +\
            '1 | {a1} | {b1} | {c1} |\n'.format(
                    a1=self.board["A1"],
                    b1=self.board["B1"],
                    c1=self.board["C1"]) +\
            '  -------------\n' +\
            '    A   B   C  \n'
        return lst

    def __which_col(self):
        for i in ["A", "B", "C"]:
            if (
                self.board[i + "1"] ==
                self.board[i + "2"] ==
                self.board[i + "3"] and
                self.board[i + "1"] != " "
            ):
                return i
        return None

    def __which_row(self):
        for i in [1, 2, 3]:
            if (
                self.board["A" + str(i)] ==
                self.board["B" + str(i)] ==
                self.board["C" + str(i)] and
                self.board["A" + str(i)] != " "
            ):
                return i
        return None

    def __which_dia(self):
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

    def __check_draw(self):
        return " " in self.board.values()

    def game_status(self):
        c = self.__which_col()  # returns the letter of winner's col
        r = self.__which_row()  # returns number of winner's row
        d = self.__which_dia()  # returns 1 or 3 - depends on the dia
        if r:
            return "{} wins!".format(self.board["A" + str(r)])
        elif c:
            return "{} wins!".format(self.board[c + "1"])
        elif d:
            return "{} wins!".format(self.board["A" + str(d)])
        elif self.__check_draw():  # if it's draw
            return "Draw!"
        else:
            return "Game in progress."

    def __setitem__(self, other, val):

        if other not in self.board.keys():  # Wrong Key
            raise InvalidKey()
        elif val not in ("O", "X"):  # Wrong Value
            raise InvalidValue()
        elif self.board[other] != " ":  # Place taken
            raise InvalidMove()
        elif val != self.on_turn and self.on_turn != "":  # Not your turn
            raise NotYourTurn()
        else:
            self.board[other] = val
            self.on_turn = str(set(("O", "X")).difference((val,)))\
                .replace("{", "").replace("}", "").replace("'", "")
