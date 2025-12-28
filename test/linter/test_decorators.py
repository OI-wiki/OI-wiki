import unittest
from parameterized import parameterized
from scripts.linter.decorators import step
from scripts.linter.utils import TAB_LENGTH


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
            f"<!-- {self.__module__}.dummy off -->\n"
            "skip this\n"
            f"<!-- {self.__module__}.dummy on -->\n"
            "after"
        )
        result = self.dummy_func(content)
        expected = (
            "before\n"
            "<!-- test.linter.test_decorators.dummy off -->\n"
            "skip this\n"
            "<!-- test.linter.test_decorators.dummy on -->\n"
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
            "<!-- test.linter.test_decorators.dummy off -->\n"
            "outer\n"
            "<!-- test.linter.test_decorators.dummy off -->\n"
            "inner\n"
            "<!-- test.linter.test_decorators.dummy on -->\n"
            "outer again\n"
            "<!-- test.linter.test_decorators.dummy on -->\n"
            "after\n"
        )
        self.assertEqual(result, expected)

    @parameterized.expand([
        ("unclosed_skip_block", "before\n<!-- test.linter.test_decorators.dummy off -->\nskip this\n",
         "unclosed skip block"),
        ("unopened_skip_block", "before\n<!-- test.linter.test_decorators.dummy on -->\nafter",
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
            "<!-- test.linter.test_decorators.dummy off -->\n"
            "line\twith\ttabs\n"
            "<!-- test.linter.test_decorators.dummy on -->\n"
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
            f"<!-- {self.__module__}.dummy_modify off -->\n"
            "old in skip\n"
            f"<!-- {self.__module__}.dummy_modify on -->\n"
            "old after"
        )
        result = dummy_modify(content)
        expected = (
            "new content\n"
            "<!-- test.linter.test_decorators.dummy_modify off -->\n"
            "old in skip\n"
            "<!-- test.linter.test_decorators.dummy_modify on -->\n"
            "new after\n"
        )
        self.assertEqual(result, expected)


if __name__ == '__main__':
    unittest.main()