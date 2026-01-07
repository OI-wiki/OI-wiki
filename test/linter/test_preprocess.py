"""Unit tests for the preprocess module."""

import unittest
from scripts.linter.preprocess import fix_details


class TestFixDetails(unittest.TestCase):
    """Test cases for fix_details function."""

    def test_empty_content(self):
        """Test with empty content."""
        self.assertEqual(fix_details(""), "")

    def test_single_line_gets_trailing_newline(self):
        """Test that single line gets trailing newline."""
        self.assertEqual(fix_details("  line"), "  line\n")

    def test_indentation_scenarios(self):
        """Test various indentation scenarios."""
        cases = [
            ("basic", "    line1\n\n    line2\n", "    line1\n    \n    line2\n"),
            ("multiple_blanks", "  a\n\n\n  b\n", "  a\n  \n  \n  b\n"),
            ("mixed_indent", "    a\n  \n      b\n", "    a\n    \n      b\n"),
            ("no_indent", "a\n\nb\n", "a\n\nb\n"),
            ("boundaries", "\n  a\n\n", "  \n  a\n  \n"),
        ]
        for name, input_text, expected in cases:
            with self.subTest(name=name):
                self.assertEqual(fix_details(input_text), expected)

    def test_tab_handling(self):
        """Test tab replacement with spaces."""
        cases = [
            ("basic_tab", "\tline1\n\n\tline2\n", "  line1\n  \n  line2\n"),
            ("mixed", "  a\n\t\n    b\n", "  a\n  \n    b\n"),
            ("multiple", "\t\tline\n\n\t\tline\n", "    line\n    \n    line\n"),
        ]
        for name, input_text, expected in cases:
            with self.subTest(name=name):
                self.assertEqual(fix_details(input_text), expected)

    def test_skip_blocks_preserved(self):
        """Test that skip blocks are preserved unchanged."""
        md = (
            "  a\n"
            "<!-- scripts.linter.preprocess.fix_details off -->\n"
            "     \t \n"
            "   \n"
            "<!-- scripts.linter.preprocess.fix_details on -->\n"
            " b\n"
        )
        result = fix_details(md)
        self.assertIn("     \t ", result)  # Tab preserved in skip block

    def test_nested_skip_blocks(self):
        """Test nested skip blocks."""
        md = (
            "     a\n"
            "<!-- scripts.linter.preprocess.fix_details off -->\n"
            "    b\n"
            "<!-- scripts.linter.preprocess.fix_details off -->\n"
            "   c\n"
            "<!-- scripts.linter.preprocess.fix_details on -->\n"
            "  d\n"
            "<!-- scripts.linter.preprocess.fix_details on -->\n"
            " e\n"
        )
        result = fix_details(md)
        self.assertIn("   c", result)  # Content in nested skip block preserved

    def test_unclosed_skip_block_raises_error(self):
        """Test error handling for unclosed skip block."""
        content = "\n<!-- scripts.linter.preprocess.fix_details off -->\n   \n"
        with self.assertRaises(RuntimeError) as context:
            fix_details(content)
        self.assertIn("unclosed skip block", str(context.exception))

    def test_unopened_skip_block_raises_error(self):
        """Test error handling for unopened skip block."""
        content = "\n   \n<!-- scripts.linter.preprocess.fix_details on -->\n"
        with self.assertRaises(RuntimeError) as context:
            fix_details(content)
        self.assertIn("unopened skip block", str(context.exception))

    def test_complex_real_world_scenario(self):
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

    def test_unicode_content(self):
        """Test content with unicode characters."""
        md = "    中文内容\n\n    更多中文\n"
        expected = "    中文内容\n    \n    更多中文\n"
        self.assertEqual(fix_details(md), expected)

    def test_whitespace_only_lines(self):
        """Test lines with only whitespace characters."""
        md = "  a\n   \n  b\n"
        expected = "  a\n  \n  b\n"
        self.assertEqual(fix_details(md), expected)

    def test_empty_lines_only(self):
        """Test content with only empty lines."""
        self.assertEqual(fix_details("\n\n\n"), "\n\n\n")


if __name__ == "__main__":
    unittest.main()