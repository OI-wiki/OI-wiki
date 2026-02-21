"""Unit tests for the decorators module."""

import unittest
from scripts.linter.decorators import step
from scripts.linter.utils import TAB_LENGTH


class TestStep(unittest.TestCase):
    """Test cases for step decorator."""

    def setUp(self):
        """Set up test fixtures."""
        @step
        def dummy(content, **kwargs):
            return content
        self.dummy_func = dummy

    def test_empty_content(self):
        """Test with empty content."""
        self.assertEqual(self.dummy_func(""), "")

    def test_content_gets_trailing_newline(self):
        """Test that content without trailing newline gets one added."""
        self.assertEqual(self.dummy_func("test"), "test\n")

    def test_multiline_content(self):
        """Test multiline content processing."""
        content = "line1\nline2\nline3"
        self.assertEqual(self.dummy_func(content), content + "\n")

    def test_tabs_replaced_with_spaces(self):
        """Test tab replacement with spaces."""
        content = "line\twith\ttabs\n"
        expected = "line{}with{}tabs\n".format(' '*TAB_LENGTH, ' '*TAB_LENGTH)
        self.assertEqual(self.dummy_func(content), expected)

    def test_single_skip_block(self):
        """Test with single skip block."""
        content = (
            "before\n"
            f"<!-- {self.__module__}.dummy off -->\n"
            "skip this\n"
            f"<!-- {self.__module__}.dummy on -->\n"
            "after"
        )
        result = self.dummy_func(content)
        expected = (
            "before\n"
            f"<!-- {self.__module__}.dummy off -->\n"
            "skip this\n"
            f"<!-- {self.__module__}.dummy on -->\n"
            "after\n"
        )
        self.assertEqual(result, expected)

    def test_nested_skip_blocks(self):
        """Test with nested skip blocks."""
        content = (
            "before\n"
            f"<!-- {self.__module__}.dummy off -->\n"
            "outer\n"
            f"<!-- {self.__module__}.dummy off -->\n"
            "inner\n"
            f"<!-- {self.__module__}.dummy on -->\n"
            "outer again\n"
            f"<!-- {self.__module__}.dummy on -->\n"
            "after"
        )
        result = self.dummy_func(content)
        expected = (
            "before\n"
            f"<!-- {self.__module__}.dummy off -->\n"
            "outer\n"
            f"<!-- {self.__module__}.dummy off -->\n"
            "inner\n"
            f"<!-- {self.__module__}.dummy on -->\n"
            "outer again\n"
            f"<!-- {self.__module__}.dummy on -->\n"
            "after\n"
        )
        self.assertEqual(result, expected)

    def test_tabs_in_skip_blocks_preserved(self):
        """Test that tabs in skip blocks are preserved."""
        content = (
            "before\n"
            "<!-- test.linter.test_decorators.dummy off -->\n"
            "line\twith\ttabs\n"
            "<!-- test.linter.test_decorators.dummy on -->\n"
            "after"
        )
        result = self.dummy_func(content)
        expected = (
            "before\n"
            "<!-- test.linter.test_decorators.dummy off -->\n"
            "line\twith\ttabs\n"
            "<!-- test.linter.test_decorators.dummy on -->\n"
            "after\n"
        )
        self.assertEqual(result, expected)

    def test_unclosed_skip_block_raises_error(self):
        """Test error handling for unclosed skip block."""
        content = "before\n<!-- test.linter.test_decorators.dummy off -->\nskip\n"
        with self.assertRaises(RuntimeError) as context:
            self.dummy_func(content)
        expected_message = "unclosed skip block for tag 'test.linter.test_decorators.dummy' starting at line 2. Please ensure all skip blocks are properly closed with '<!-- test.linter.test_decorators.dummy on -->'"
        self.assertEqual(str(context.exception), expected_message)

    def test_unopened_skip_block_raises_error(self):
        """Test error handling for unopened skip block."""
        content = "before\n<!-- test.linter.test_decorators.dummy on -->\nafter"
        with self.assertRaises(RuntimeError) as context:
            self.dummy_func(content)
        expected_message = "unopened skip block for tag 'test.linter.test_decorators.dummy' ending at line 2. Please ensure all skip blocks are properly opened with '<!-- test.linter.test_decorators.dummy off -->'"
        self.assertEqual(str(context.exception), expected_message)

    def test_content_modification_preserved(self):
        """Test that content modifications are preserved."""
        @step
        def modifier(content, **kwargs):
            return content.replace("old", "new")

        result = modifier("old content")
        self.assertEqual(result, "new content\n")

    def test_skip_block_content_not_modified(self):
        """Test that skip blocks are preserved during content modification."""
        @step
        def modifier(content, **kwargs):
            return content.replace("old", "new")

        content = (
            "old content\n"
            f"<!-- {self.__module__}.modifier off -->\n"
            "old in skip\n"
            f"<!-- {self.__module__}.modifier on -->\n"
            "old after"
        )
        result = modifier(content)
        expected = (
            "new content\n"
            f"<!-- {self.__module__}.modifier off -->\n"
            "old in skip\n"
            f"<!-- {self.__module__}.modifier on -->\n"
            "new after\n"
        )
        self.assertEqual(result, expected)


if __name__ == '__main__':
    unittest.main()