import unittest
from parameterized import parameterized
from scripts.linter.preprocess import fix_details
from scripts.linter.utils import TAB_LENGTH


class TestFixDetailsBasic(unittest.TestCase):
    """Basic test cases for fix_details function."""

    def setUp(self):
        """Set up test fixtures."""
        self.sample_content = "    line1\n\n    line2\n"
        self.expected_basic = "    line1\n    \n    line2\n"

    def tearDown(self):
        """Clean up test fixtures."""
        pass

    def test_empty_content(self):
        """Test with empty content."""
        self.assertEqual(fix_details(""), "")

    def test_single_line(self):
        """Test with single line content."""
        self.assertEqual(fix_details("  line"), "  line\n")

    def test_basic_indentation_fix(self):
        """Test basic indentation correction."""
        self.assertEqual(fix_details(self.sample_content), self.expected_basic)

    @parameterized.expand([
        ("blank_line_alignment", "  a\n\n  b\n", "  a\n  \n  b\n"),
        ("multiple_blank_lines", "  a\n\n\n  b\n", "  a\n  \n  \n  b\n"),
        ("mixed_indentation_levels", "    a\n  \n      b\n", "    a\n    \n      b\n"),
        ("no_indent_content", "a\n\nb\n", "a\n\nb\n"),
    ])
    def test_indentation_scenarios(self, name, input_text, expected):
        """Test various indentation scenarios.

        Args:
            name: Test case name for identification
            input_text: Input markdown content
            expected: Expected output after indentation fix
        """
        result = fix_details(input_text)
        self.assertEqual(result, expected, f"Failed test case: {name}")

    def test_blank_lines_at_boundaries(self):
        """Test blank lines at start and end."""
        md = "\n  a\n\n"
        expected = "  \n  a\n  \n"
        self.assertEqual(fix_details(md), expected)

    def test_no_indent_content(self):
        """Test content with no indentation."""
        md = "a\n\nb\n"
        expected = "a\n\nb\n"
        self.assertEqual(fix_details(md), expected)

    def test_tab_handling(self):
        """Test tab replacement with spaces."""
        md = "\tline1\n\n\tline2\n"
        expected = "  line1\n  \n  line2\n"
        self.assertEqual(fix_details(md), expected)

    def test_mixed_spaces_and_tabs(self):
        """Test mixed spaces and tabs."""
        md = "  a\n\t\n    b\n"
        expected = "  a\n  \n    b\n"
        self.assertEqual(fix_details(md), expected)

    @parameterized.expand([
        ("unclosed_skip_block", "\n<!-- scripts.linter.preprocess.fix_details on -->\n   \n",
         "unclosed skip block"),
        ("unopened_skip_block", "\n   \n<!-- scripts.linter.preprocess.fix_details off -->\n",
         "unopened skip block"),
    ])
    def test_skip_block_error_handling(self, name, input_text, expected_error):
        """Test error handling for malformed skip blocks.

        Args:
            name: Test case name for identification
            input_text: Input markdown with malformed skip blocks
            expected_error: Expected error message fragment
        """
        with self.assertRaises(RuntimeError) as context:
            fix_details(input_text)
        self.assertIn(expected_error, str(context.exception),
                      f"Failed test case: {name}")


class TestFixDetailsTabHandling(unittest.TestCase):
    """Test cases for tab handling in fix_details function."""

    @parameterized.expand([
        ("basic_tab_replacement", "\tline1\n\n\tline2\n", "  line1\n  \n  line2\n"),
        ("mixed_spaces_tabs", "  a\n\t\n    b\n", "  a\n  \n    b\n"),
        ("tabs_with_content", "\tcontent\n\n\tmore content\n",
         "  content\n  \n  more content\n"),
        ("multiple_tabs", "\t\tline\n\n\t\tline\n", "    line\n    \n    line\n"),
    ])
    def test_tab_scenarios(self, name, input_text, expected):
        """Test various tab handling scenarios.

        Args:
            name: Test case name for identification
            input_text: Input markdown content with tabs
            expected: Expected output after tab replacement
        """
        result = fix_details(input_text)
        self.assertEqual(result, expected, f"Failed test case: {name}")

    def test_tab_length_constant(self):
        """Test that TAB_LENGTH constant is used correctly."""
        # Verify that tabs are replaced with exactly TAB_LENGTH spaces
        content = "\tline\n"
        result = fix_details(content)
        expected = " " * TAB_LENGTH + "line\n"
        self.assertEqual(result, expected)


class TestFixDetailsSkipBlocks(unittest.TestCase):
    """Test cases for skip block handling in fix_details function."""

    def test_skip_blocks_preserved(self):
        """Test that skip blocks are preserved unchanged."""
        md = (
            "  a\n"
            "<!-- scripts.linter.preprocess.fix_details on -->\n"
            "     \t \n"
            "   \n"
            "<!-- scripts.linter.preprocess.fix_details off -->\n"
            " b\n"
        )
        expected = (
            "  a\n"
            "<!-- scripts.linter.preprocess.fix_details on -->\n"
            "     \t \n"
            "   \n"
            "<!-- scripts.linter.preprocess.fix_details off -->\n"
            " b\n"
        )
        self.assertEqual(fix_details(md), expected)

    def test_nested_skip_blocks(self):
        """Test nested skip blocks."""
        md = (
            "     a\n"
            "<!-- scripts.linter.preprocess.fix_details on -->\n"
            "    b\n"
            "<!-- scripts.linter.preprocess.fix_details on -->\n"
            "   c\n"
            "<!-- scripts.linter.preprocess.fix_details off -->\n"
            "  d\n"
            "<!-- scripts.linter.preprocess.fix_details off -->\n"
            " e\n"
        )
        expected = (
            "     a\n"
            "<!-- scripts.linter.preprocess.fix_details on -->\n"
            "    b\n"
            "<!-- scripts.linter.preprocess.fix_details on -->\n"
            "   c\n"
            "<!-- scripts.linter.preprocess.fix_details off -->\n"
            "  d\n"
            "<!-- scripts.linter.preprocess.fix_details off -->\n"
            " e\n"
        )
        self.assertEqual(fix_details(md), expected)

    def test_global_skip_blocks(self):
        """Test global skip blocks (scripts.linter.*)."""
        md = (
            "  a\n"
            "<!-- scripts.linter.* on -->\n"
            "     \t \n"
            "   \n"
            "<!-- scripts.linter.* off -->\n"
            " b\n"
        )
        expected = (
            "  a\n"
            "<!-- scripts.linter.* on -->\n"
            "     \t \n"
            "   \n"
            "<!-- scripts.linter.* off -->\n"
            " b\n"
        )
        self.assertEqual(fix_details(md), expected)


class TestFixDetailsComplexScenarios(unittest.TestCase):
    """Test complex real-world scenarios for fix_details function."""

    def test_complex_indentation_scenario(self):
        """Test complex real-world indentation scenario."""
        md = (
            "# Title\n"
            "\n"
            "    Some indented content\n"
            "\n"
            "        More indented content\n"
            "\n"
            "    Back to less indented\n"
            "\n"
            "Normal content\n"
        )
        expected = (
            "# Title\n"
            "\n"
            "    Some indented content\n"
            "    \n"
            "        More indented content\n"
            "    \n"
            "    Back to less indented\n"
            "\n"
            "Normal content\n"
        )
        self.assertEqual(fix_details(md), expected)

    def test_whitespace_only_lines(self):
        """Test lines with only whitespace characters."""
        md = "  a\n   \n  b\n"
        expected = "  a\n  \n  b\n"
        self.assertEqual(fix_details(md), expected)

    def test_mixed_line_endings(self):
        """Test content with mixed line endings."""
        md = "  line1\r\n  \n  line2\r\n"
        result = fix_details(md)
        # Should handle mixed line endings gracefully
        self.assertIsInstance(result, str)
        self.assertTrue(result.endswith('\n'))

    def test_very_deep_indentation(self):
        """Test very deep indentation levels."""
        deep_content = "        " * 10 + \
            "deep content\n\n        " * 10 + "more deep content\n"
        result = fix_details(deep_content)
        self.assertIsInstance(result, str)
        self.assertTrue(result.endswith('\n'))
        self.assertIn("deep content", result)

    def test_performance_large_input(self):
        """Test performance with large input."""
        lines = []
        for i in range(1000):
            indent = "    " * (i % 5)  # Vary indentation
            lines.append(f"{indent}line {i}")
            if i % 10 == 0:  # Add blank lines occasionally
                lines.append("")

        content = "\n".join(lines)
        result = fix_details(content)

        # Verify the result has the expected structure
        self.assertTrue(result.endswith('\n'))
        self.assertIn("line 0", result)
        self.assertIn("line 999", result)


class TestFixDetailsEdgeCases(unittest.TestCase):
    """Test edge cases and boundary conditions for fix_details function."""

    def test_empty_lines_only(self):
        """Test content with only empty lines."""
        md = "\n\n\n"
        expected = "\n\n\n"
        self.assertEqual(fix_details(md), expected)

    def test_single_character_lines(self):
        """Test lines with single characters."""
        md = "a\n\nb\n"
        expected = "a\n\nb\n"
        self.assertEqual(fix_details(md), expected)

    def test_very_long_lines(self):
        """Test very long lines."""
        long_line = "    " + "x" * 10000
        md = f"{long_line}\n\n{long_line}\n"
        result = fix_details(md)
        self.assertIsInstance(result, str)
        self.assertTrue(result.endswith('\n'))

    def test_unicode_content(self):
        """Test content with unicode characters."""
        md = "    中文内容\n\n    更多中文\n"
        expected = "    中文内容\n    \n    更多中文\n"
        self.assertEqual(fix_details(md), expected)

    def test_special_characters(self):
        """Test content with special characters."""
        md = "    $math$ content\n\n    @special chars\n"
        expected = "    $math$ content\n    \n    @special chars\n"
        self.assertEqual(fix_details(md), expected)


if __name__ == "__main__":
    unittest.main()
