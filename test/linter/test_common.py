import unittest
import os
from unittest.mock import patch, mock_open
from parameterized import parameterized
from scripts.linter.common import index_lfirst_neq, log, step, pipeline, TAB_LENGTH


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


class TestStepBasic(unittest.TestCase):
    """Basic test cases for step decorator."""

    def setUp(self):
        """Set up test fixtures."""
        @step
        def dummy(content, **kwargs):
            return content
        self.dummy_func = dummy

    def test_empty_content(self):
        """Test with empty content."""
        self.assertEqual(self.dummy_func(""), "")

    def test_no_skip_blocks(self):
        """Test content without skip blocks."""
        content = "test\ncontent"
        self.assertEqual(self.dummy_func(content), content + "\n")

    def test_single_line_content(self):
        """Test single line content."""
        content = "single line"
        self.assertEqual(self.dummy_func(content), content + "\n")

    def test_multiline_content(self):
        """Test multiline content."""
        content = "line1\nline2\nline3"
        self.assertEqual(self.dummy_func(content), content + "\n")


class TestStepSkipBlocks(unittest.TestCase):
    """Test cases for skip block handling in step decorator."""

    def setUp(self):
        """Set up test fixtures."""
        @step
        def dummy(content, **kwargs):
            return content
        self.dummy_func = dummy

    def test_single_skip_block(self):
        """Test with single skip block."""
        content = (
            "before\n"
            f"<!-- {self.__module__}.dummy on -->\n"
            "skip this\n"
            f"<!-- {self.__module__}.dummy off -->\n"
            "after"
        )
        result = self.dummy_func(content)
        expected = (
            "before\n"
            "<!-- test.linter.test_common.dummy on -->\n"
            "skip this\n"
            "<!-- test.linter.test_common.dummy off -->\n"
            "after\n"
        )
        self.assertEqual(result, expected)

    def test_nested_skip_blocks(self):
        """Test with nested skip blocks."""
        content = (
            "before\n"
            f"<!-- {self.__module__}.dummy on -->\n"
            "outer\n"
            f"<!-- {self.__module__}.dummy on -->\n"
            "inner\n"
            f"<!-- {self.__module__}.dummy off -->\n"
            "outer again\n"
            f"<!-- {self.__module__}.dummy off -->\n"
            "after"
        )
        result = self.dummy_func(content)
        expected = (
            "before\n"
            "<!-- test.linter.test_common.dummy on -->\n"
            "outer\n"
            "<!-- test.linter.test_common.dummy on -->\n"
            "inner\n"
            "<!-- test.linter.test_common.dummy off -->\n"
            "outer again\n"
            "<!-- test.linter.test_common.dummy off -->\n"
            "after\n"
        )
        self.assertEqual(result, expected)

    def test_global_skip_blocks(self):
        """Test global skip blocks (scripts.linter.*)."""
        content = (
            "before\n"
            "<!-- scripts.linter.* on -->\n"
            "skip this\n"
            "<!-- scripts.linter.* off -->\n"
            "after"
        )
        result = self.dummy_func(content)
        expected = (
            "before\n"
            "<!-- scripts.linter.* on -->\n"
            "skip this\n"
            "<!-- scripts.linter.* off -->\n"
            "after\n"
        )
        self.assertEqual(result, expected)

    @parameterized.expand([
        ("unclosed_skip_block", "before\n<!-- test.linter.test_common.dummy on -->\nskip this\n",
         "unclosed skip block"),
        ("unopened_skip_block", "before\n<!-- test.linter.test_common.dummy off -->\nafter",
         "unopened skip block"),
    ])
    def test_skip_block_error_handling(self, name, content, expected_error):
        """Test error handling for malformed skip blocks.

        Args:
            name: Test case name for identification
            content: Content with malformed skip blocks
            expected_error: Expected error message fragment
        """
        with self.assertRaises(RuntimeError) as context:
            self.dummy_func(content)
        self.assertIn(expected_error, str(context.exception),
                      f"Failed test case: {name}")


class TestStepTabHandling(unittest.TestCase):
    """Test cases for tab handling in step decorator."""

    def setUp(self):
        """Set up test fixtures."""
        @step
        def dummy(content, **kwargs):
            return content
        self.dummy_func = dummy

    def test_tab_replacement(self):
        """Test tab replacement with spaces."""
        content = "line\twith\ttabs\n"
        expected = "line{}with{}tabs\n".format(' '*TAB_LENGTH, ' '*TAB_LENGTH)
        result = self.dummy_func(content)
        self.assertEqual(result, expected)

    def test_mixed_tabs_and_spaces(self):
        """Test mixed tabs and spaces."""
        content = "  line\twith\tmixed\n"
        expected = "  line{}with{}mixed\n".format(
            ' '*TAB_LENGTH, ' '*TAB_LENGTH)
        result = self.dummy_func(content)
        self.assertEqual(result, expected)

    def test_tabs_in_skip_blocks(self):
        """Test that tabs in skip blocks are preserved."""
        content = (
            "before\n"
            "<!-- test.linter.test_common.dummy on -->\n"
            "line\twith\ttabs\n"
            "<!-- test.linter.test_common.dummy off -->\n"
            "after"
        )
        result = self.dummy_func(content)
        self.assertIn("line\twith\ttabs", result)


class TestStepParameterHandling(unittest.TestCase):
    """Test cases for parameter handling in step decorator."""

    def setUp(self):
        """Set up test fixtures."""
        @step
        def dummy(content, **kwargs):
            return content
        self.dummy_func = dummy

    def test_content_modification(self):
        """Test that content modifications are preserved."""
        @step
        def dummy_modify(content, **kwargs):
            return content.replace("old", "new")
        content = "old content"
        result = dummy_modify(content)
        self.assertEqual(result, "new content\n")

    def test_skip_block_preservation(self):
        """Test that skip blocks are preserved during content modification."""
        @step
        def dummy_modify(content, **kwargs):
            return content.replace("old", "new")
        content = (
            "old content\n"
            f"<!-- {self.__module__}.dummy_modify on -->\n"
            "old in skip\n"
            f"<!-- {self.__module__}.dummy_modify off -->\n"
            "old after"
        )
        result = dummy_modify(content)
        expected = (
            "new content\n"
            "<!-- test.linter.test_common.dummy_modify on -->\n"
            "old in skip\n"
            "<!-- test.linter.test_common.dummy_modify off -->\n"
            "new after\n"
        )
        self.assertEqual(result, expected)


if __name__ == '__main__':
    unittest.main()
