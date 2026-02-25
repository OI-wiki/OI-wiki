"""Unit tests for the utils module."""

import os
import unittest
from unittest.mock import patch
from scripts.linter.utils import index_lfirst_neq, log
from scripts.linter.utils import Grouping
from unittest.mock import call


class TestIndexLfirstNeq(unittest.TestCase):
    """Test cases for index_lfirst_neq function."""

    def test_finds_first_different_element(self):
        """Test finding the first element not equal to value."""
        cases = [
            ("first", [2, 1, 1], 1, 0),
            ("middle", [1, 2, 1], 1, 1),
            ("last", [1, 1, 2], 1, 2),
            ("single_different", [2], 1, 0),
            ("string", "abc", "a", 1),
        ]
        for name, iterable, value, expected in cases:
            with self.subTest(name=name):
                self.assertEqual(index_lfirst_neq(iterable, value), expected)

    def test_raises_stop_iteration_when_not_found(self):
        """Test StopIteration raised when no different element found."""
        cases = [
            ("all_same", [1, 1, 1], 1),
            ("empty", [], 1),
            ("single_same", [1], 1),
        ]
        for name, iterable, value in cases:
            with self.subTest(name=name):
                with self.assertRaises(StopIteration):
                    index_lfirst_neq(iterable, value)


class TestLog(unittest.TestCase):
    """Test cases for log function."""

    @patch('builtins.print')
    def test_logs_when_runner_debug_set(self, mock_print):
        """Test logging when RUNNER_DEBUG environment variable is set."""
        with patch.dict(os.environ, {'RUNNER_DEBUG': '1'}):
            log("test message")
            mock_print.assert_called_once_with("::debug::test message")

    @patch('builtins.print')
    def test_silent_when_runner_debug_not_set(self, mock_print):
        """Test no logging when RUNNER_DEBUG is not set."""
        with patch.dict(os.environ, {}, clear=True):
            log("test message")
            mock_print.assert_not_called()

    @patch('builtins.print')
    def test_non_debug_types_print_without_runner_debug(self, mock_print):
        """Non-debug log types should print even if RUNNER_DEBUG is not set."""
        cases = [
            ("error", "error message", "::error::error message"),
            ("warning", "warning message", "::warning::warning message"),
            ("group", "group message", "::group::group message"),
            ("endgroup", "", "::endgroup::"),
        ]
        with patch.dict(os.environ, {}, clear=True):
            for log_type, message, expected in cases:
                with self.subTest(log_type=log_type):
                    mock_print.reset_mock()
                    log(message, type=log_type)
                    mock_print.assert_called_once_with(expected)

    @patch('builtins.print')
    def test_log_types(self, mock_print):
        """Test logging with different log types."""
        cases = [
            ("error", "error message", "error", "::error::error message"),
            ("warning", "warning message", "warning", "::warning::warning message"),
            ("group", "group message", "group", "::group::group message"),
            ("endgroup", "", "endgroup", "::endgroup::"),
        ]
        for name, message, log_type, expected in cases:
            with self.subTest(name=name):
                mock_print.reset_mock()
                with patch.dict(os.environ, {'RUNNER_DEBUG': '1'}):
                    log(message, type=log_type)
                    mock_print.assert_called_once_with(expected)


class TestGrouping(unittest.TestCase):
    """Test cases for the Grouping context manager."""

    @patch('builtins.print')
    def test_grouping_with_runner_debug(self, mock_print):
        """When RUNNER_DEBUG is set, group and endgroup should be printed."""
        with patch.dict(os.environ, {'RUNNER_DEBUG': '1'}):
            with Grouping('mygroup'):
                pass

        self.assertEqual(mock_print.call_args_list,
                         [call('::group::mygroup'), call('::endgroup::')])

    @patch('builtins.print')
    def test_grouping_without_runner_debug_disabled(self, mock_print):
        """When RUNNER_DEBUG is not set and enable_only_debug=True, nothing prints."""
        with patch.dict(os.environ, {}, clear=True):
            with Grouping('mygroup'):
                pass

        mock_print.assert_not_called()

    @patch('builtins.print')
    def test_grouping_force_enabled(self, mock_print):
        """When enable_only_debug=False, group commands are always printed."""
        with patch.dict(os.environ, {}, clear=True):
            with Grouping('forced', enable_only_debug=False):
                pass

        self.assertEqual(mock_print.call_args_list,
                         [call('::group::forced'), call('::endgroup::')])

    def test_grouping_does_not_suppress_exceptions(self):
        """Exceptions inside the context should propagate (exit returns False)."""
        with patch.dict(os.environ, {}, clear=True):
            with self.assertRaises(ValueError):
                with Grouping('forced', enable_only_debug=False):
                    raise ValueError('boom')


if __name__ == '__main__':
    unittest.main()
