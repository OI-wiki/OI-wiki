import unittest
import os
from unittest.mock import patch
from parameterized import parameterized
from scripts.linter.utils import index_lfirst_neq, log


class TestIndexLfirstNeq(unittest.TestCase):
    """Test cases for index_lfirst_neq function."""

    @parameterized.expand([
        ("first_element", [2, 1, 1], 1, 0),
        ("middle_element", [1, 2, 1], 1, 1),
        ("last_element", [1, 1, 2], 1, 2),
        ("single_element_different", [2], 1, 0),
        ("tuple_iterable", (1, 2, 1), 1, 1),
        ("string_iterable", "abc", "a", 1),
        ("none_values", [None, 1, None], None, 1),
        ("boolean_values", [True, False, True], True, 1),
    ])
    def test_successful_cases(self, name, iterable, value, expected):
        """Test successful cases for index_lfirst_neq.

        Args:
            name: Test case name for identification
            iterable: The iterable to search
            value: The value to compare against
            expected: Expected index result
        """
        result = index_lfirst_neq(iterable, value)
        self.assertEqual(result, expected, f"Failed test case: {name}")

    @parameterized.expand([
        ("no_different_elements", [1, 1, 1], 1),
        ("empty_list", [], 1),
        ("single_element_same", [1], 1),
    ])
    def test_stop_iteration_cases(self, name, iterable, value):
        """Test cases that should raise StopIteration.

        Args:
            name: Test case name for identification
            iterable: The iterable to search
            value: The value to compare against
        """
        with self.assertRaises(StopIteration):
            index_lfirst_neq(iterable, value)


class TestLog(unittest.TestCase):
    """Test cases for log function."""

    @patch('builtins.print')
    def test_with_debug_env(self, mock_print):
        """Test logging with RUNNER_DEBUG environment variable set."""
        with patch.dict(os.environ, {'RUNNER_DEBUG': '1'}):
            log("test message")
            mock_print.assert_called_once_with("::debug::test message")

    @parameterized.expand([
        ("error_type", "error message", "error", "::error::error message"),
        ("warning_type", "warning message",
         "warning", "::warning::warning message"),
        ("notice_type", "notice message", "notice", "::notice::notice message"),
        ("group_type", "group message", "group", "::group::group message"),
        ("endgroup_type", "", "endgroup", "::endgroup::"),
    ])
    @patch('builtins.print')
    def test_log_types(self, name, message, log_type, expected_output, mock_print):
        """Test logging with different types.

        Args:
            name: Test case name for identification
            message: Message to log
            log_type: Log type parameter
            expected_output: Expected print output
            mock_print: Mock print function
        """
        with patch.dict(os.environ, {'RUNNER_DEBUG': '1'}):
            log(message, type=log_type)
            mock_print.assert_called_once_with(expected_output)

    @patch('builtins.print')
    def test_without_debug_env(self, mock_print):
        """Test logging without RUNNER_DEBUG environment variable."""
        with patch.dict(os.environ, {}, clear=True):
            log("test message")
            mock_print.assert_not_called()

    @patch('builtins.print')
    def test_empty_message(self, mock_print):
        """Test logging with empty message."""
        with patch.dict(os.environ, {'RUNNER_DEBUG': '1'}):
            log("")
            mock_print.assert_called_once_with("::debug::")

    @parameterized.expand([
        ("debug_default", "test message", None, "::debug::test message"),
        ("debug_explicit", "test message", "debug", "::debug::test message"),
    ])
    @patch('builtins.print')
    def test_debug_logging(self, name, message, log_type, expected_output, mock_print):
        """Test debug logging behavior.

        Args:
            name: Test case name for identification
            message: Message to log
            log_type: Log type parameter (None for default)
            expected_output: Expected print output
            mock_print: Mock print function
        """
        with patch.dict(os.environ, {'RUNNER_DEBUG': '1'}):
            if log_type is None:
                log(message)
            else:
                log(message, type=log_type)
            mock_print.assert_called_once_with(expected_output)


if __name__ == '__main__':
    unittest.main()