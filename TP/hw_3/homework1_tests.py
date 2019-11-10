# from task1 import group_by_f

# from task2 import has_same_ingredients  # Моя помощна функция
# from task2 import is_stronger, least_stronger, strong_relation

# from task3 import max_notes, leading

# За хората, които са си писали задачите в един файл ->
from solution import group_by_f
from solution import is_stronger#, least_stronger, strong_relation
from solution import max_notes, leading
# <--

import unittest


class TestGroupByF(unittest.TestCase):
    def test_function_with_lambda_function(self):
        true_result = group_by_f(lambda a: a % 2 == 0, [1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
        expected_result = {False: [1, 3, 5, 7, 9], True: [2, 4, 6, 8, 10]}

        self.assertEqual(true_result, expected_result)

    def test_function_with_standard_len_function(self):
        true_result = group_by_f(len, [[1], [7, 8], [1, 2, 3, 4], [4], ["random", "words"]])
        expected_result = {1: [[1], [4]], 2: [[7, 8], ['random', 'words']], 4: [[1, 2, 3, 4]]}

        self.assertEqual(true_result, expected_result)

# Аз съм си писал помощна функция
# class TestHasSameIngredients(unittest.TestCase):
#     def test_function_when_result_must_be_true(self):
#         medicine1 = ("medicine1", [("p", 5), ("q", 3)])
#         medicine2 = ("medicine2", [("p", 4), ("q", 3)])

#         self.assertTrue(has_same_ingredients(medicine1, medicine2))

#     def test_function_when_result_must_be_true_with_swapped_names(self):
#         medicine1 = ("medicine1", [("q", 5), ("p", 3)])
#         medicine2 = ("medicine2", [("p", 4), ("q", 3)])

#         self.assertTrue(has_same_ingredients(medicine1, medicine2))

#     def test_function_when_result_must_be_false(self):
#         medicine1 = ("medicine1", [("p", 5)])
#         medicine2 = ("medicine2", [("p", 4), ("q", 3)])

#         self.assertTrue(has_same_ingredients(medicine1, medicine2))


class Testis_stronger(unittest.TestCase):
    def test_function_when_medicines_are_equal_strength(self):
        medicine1 = ("medicine1", [("p", 5), ("q", 3)])
        medicine2 = ("medicine2", [("p", 4), ("q", 4)])

        self.assertFalse(is_stronger(medicine1, medicine2))

    def test_function_when_medicines_are_equal_strength1(self):
        medicine2 = ("medicine2", [("p", 4), ("q", 4)])
        medicine1 = ("medicine1", [("p", 5), ("q", 3)])

        self.assertFalse(is_stronger(medicine1, medicine2))

    def test_function_when_first_medicine_is_stronger_than_the_second(self):
        medicine1 = ("medicine1", [("p", 5), ("q", 3)])
        medicine2 = ("medicine2", [("p", 4), ("q", 3)])

        self.assertTrue(is_stronger(medicine1, medicine2))

    def test_function_when_first_medicine_is_not_stronger_than_the_second(self):
        medicine1 = ("medicine1", [("p", 5), ("q", 3)])
        medicine2 = ("medicine2", [("p", 4), ("q", 3)])

        self.assertFalse(is_stronger(medicine2, medicine1))


# class Testleast_stronger(unittest.TestCase):
#     def test_function_when_medicine_is_stronger_than_return_it(self):
#         medicine1 = ("medicine1", [("p", 5), ("q", 3)])
#         medicine2 = ("medicine2", [("p", 4), ("q", 3)])
#         medicine3 = ("medicine3", [("p", 3)])
#         medicine4 = ("medicine4", [("p", 4.5), ("q", 3), ("r", 1)])

#         expected_result = ("medicine4", [("p", 4.5), ("q", 3), ("r", 1)])

#         self.assertEqual(least_stronger(medicine2, [medicine1, medicine3, medicine4]), expected_result)

#     def test_function_when_no_medicine_is_stronger_than_return_empty_list(self):
#         medicine1 = ("medicine1", [("p", 5), ("q", 3)])
#         medicine2 = ("medicine2", [("p", 4), ("q", 3)])
#         medicine3 = ("medicine3", [("p", 3)])
#         medicine4 = ("medicine4", [("p", 4.5), ("q", 3), ("r", 1)])

#         expected_result = []

#         self.assertEqual(least_stronger(medicine1, [medicine2, medicine3, medicine4]), expected_result)


# class Teststrong_relation(unittest.TestCase):
#     def test_function_when_result_must_be_list_of_tuples(self):
#         medicine1 = ("medicine1", [("p", 5), ("q", 3)])
#         medicine2 = ("medicine2", [("p", 4), ("q", 3)])
#         medicine3 = ("medicine3", [("p", 3)])

#         expected_result = [(('medicine1', [('p', 5), ('q', 3)]), []), (('medicine2', [('p', 4), ('q', 3)]), ['medicine1']), (('medicine3', [('p', 3)]), ['medicine1', 'medicine2'])]

#         self.assertEqual(strong_relation([medicine1, medicine2, medicine3]), expected_result)


class Testmax_notes(unittest.TestCase):
    def test_function_when_result_must_be_the_max_notes(self):
        true_result = max_notes([[1, 2, 3], [2, 2, 2], [9, 7, 3]])
        expected_result = 19

        self.assertEqual(true_result, expected_result)

    def test_function_when_result_must_be_zero(self):
        true_result = max_notes([])
        expected_result = 0

        self.assertEqual(true_result, expected_result)

    def test_function_when_max_notes_are_equal_then_return_result(self):
        true_result = max_notes([[1, 2, 3], [2, 2, 2]])
        expected_result = 6

        self.assertEqual(true_result, expected_result)


class TestLeading(unittest.TestCase):
    def test_function_when_result_must_be_the_leading_note(self):
        true_result = leading([[1, 10, 2], [2, 2, 2], [9, 7, 3]])
        expected_result = 2

        self.assertEqual(true_result, expected_result)

    def test_function_when_result_must_be_the_first_leading_note(self):
        true_result = leading([[1, 2, 3], [2, 2, 2], [9, 7, 3]])
        expected_result = 0

        self.assertEqual(true_result, expected_result)


if __name__ == "__main__":
    unittest.main()
