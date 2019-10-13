import unittest
import accumulate


class SolutionTest(unittest.TestCase):

    def test_accumulate_left(self):
        res = accumulate.accumulate_left(lambda a, b: a / b, 64, [2, 4, 8])
        self.assertEqual(1.0, res)

    # def test_accumulate_right(self):
    #     res = accumulate.accumulate_right(lambda a, b: a / b, 8, [16, 32, 64])
    #     self.assertEqual(4.0, res)


if __name__ == "__main__":
    unittest.main()
