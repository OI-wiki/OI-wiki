import unittest
from scripts.linter.preprocess import fix_details
from scripts.linter.common import TAB_LENGTH


class TestFixDetails(unittest.TestCase):
    def test_empty(self):
        md = ""
        expected = ""
        self.assertEqual(fix_details(md), expected)

    def test_all_blank_lines(self):
        md = "\n\n\n"
        expected = "\n\n\n"
        self.assertEqual(fix_details(md), expected)

    def test_blank_lines_with_only_tabs(self):
        md = "\t\n\t\n\t\n"
        expected = md.replace('\t', ' '*TAB_LENGTH)
        self.assertEqual(fix_details(md), expected)

    def test_basic_indentation(self):
        md = "    line1\n\n    line2\n"
        expected = "    line1\n    \n    line2\n"
        self.assertEqual(fix_details(md), expected)

    def test_basic_indentation_with_rspace(self):
        md = "    line1  \n\n    line2 \n"
        expected = "    line1  \n    \n    line2 \n"
        self.assertEqual(fix_details(md), expected)

    def test_blank_lines_alignment(self):
        md = "  a\n\n  b\n"
        expected = "  a\n  \n  b\n"
        self.assertEqual(fix_details(md), expected)

    def test_multiple_blank_lines(self):
        md = "  a\n\n\n  b\n"
        expected = "  a\n  \n  \n  b\n"
        self.assertEqual(fix_details(md), expected)

    def test_no_blank_lines(self):
        md = "a\nb\nc"
        expected = "a\nb\nc\n"
        self.assertEqual(fix_details(md), expected)

    def test_skipmark_on_off(self):
        md = (
            "  a\n"
            "<!-- scripts.linter.preprocess.fix_details on -->\n"
            "\n"
            "<!-- scripts.linter.preprocess.fix_details off -->\n"
            " b\n"
        )
        expected = (
            "  a\n"
            "<!-- scripts.linter.preprocess.fix_details on -->\n"
            "\n"
            "<!-- scripts.linter.preprocess.fix_details off -->\n"
            " b\n"
        )
        self.assertEqual(fix_details(md), expected)

    def test_skipmark_on_off_at_start(self):
        md = (
            "<!-- scripts.linter.preprocess.fix_details on -->\n"
            "\n"
            "<!-- scripts.linter.preprocess.fix_details off -->\n"
            "  a\n"
        )
        expected = (
            "<!-- scripts.linter.preprocess.fix_details on -->\n"
            "\n"
            "<!-- scripts.linter.preprocess.fix_details off -->\n"
            "  a\n"
        )
        self.assertEqual(fix_details(md), expected)

    def test_skipmark_on_off_at_end(self):
        md = (
            "  a\n"
            "<!-- scripts.linter.preprocess.fix_details on -->\n"
            "\n"
            "<!-- scripts.linter.preprocess.fix_details off -->\n"
        )
        expected = (
            "  a\n"
            "<!-- scripts.linter.preprocess.fix_details on -->\n"
            "\n"
            "<!-- scripts.linter.preprocess.fix_details off -->\n"
        )
        self.assertEqual(fix_details(md), expected)

    def test_blank_line_at_start(self):
        md = "\n  a\n"
        expected = "  \n  a\n"
        self.assertEqual(fix_details(md), expected)

    def test_blank_line_at_end(self):
        md = "  a\n\n"
        expected = "  a\n  \n"
        self.assertEqual(fix_details(md), expected)

    def test_blank_lines_before_and_after_content(self):
        md = "\n  a\n\n"
        expected = "  \n  a\n  \n"
        self.assertEqual(fix_details(md), expected)

    def test_mixed_indentation(self):
        md = "    a\n  \n      b\n"
        expected = "    a\n    \n      b\n"
        self.assertEqual(fix_details(md), expected)

    def test_blank_lines_between_different_indents(self):
        md = "  a\n\n    b\n"
        expected = "  a\n  \n    b\n"
        self.assertEqual(fix_details(md), expected)

    def test_blank_lines_between_no_indent(self):
        md = "a\n\nb\n"
        expected = "a\n\nb\n"
        self.assertEqual(fix_details(md), expected)

    def test_only_blank_lines_and_skipmark(self):
        md = "<!-- scripts.linter.preprocess.fix_details on -->\n\n\n<!-- scripts.linter.preprocess.fix_details off -->"
        expected = "<!-- scripts.linter.preprocess.fix_details on -->\n\n\n<!-- scripts.linter.preprocess.fix_details off -->\n"
        self.assertEqual(fix_details(md), expected)

    def test_skipmark_with_blank_lines_inside(self):
        md = (
            "  a\n"
            "<!-- scripts.linter.preprocess.fix_details on -->\n"
            "     \t \n"
            "   \n"
            "<!-- scripts.linter.preprocess.fix_details off -->\n"
            "   b\n"
        )
        expected = (
            "  a\n"
            "<!-- scripts.linter.preprocess.fix_details on -->\n"
            "     \t \n"
            "   \n"
            "<!-- scripts.linter.preprocess.fix_details off -->\n"
            "   b\n"
        )
        self.assertEqual(fix_details(md), expected)

    def test_blank_lines_with_tabs(self):
        md = "\tline1\n\n\tline2\n"
        expected = "  line1\n  \n  line2\n"
        self.assertEqual(fix_details(md), expected)

    def test_blank_lines_mixed_spaces_and_tabs(self):
        md = "  a\n\t\n    b\n"
        expected = "  a\n  \n    b\n"
        self.assertEqual(fix_details(md), expected)

    def test_blank_lines_between_lines_with_increasing_indent(self):
        md = "a\n\n  b\n\n    c\n"
        expected = "a\n\n  b\n  \n    c\n"
        self.assertEqual(fix_details(md), expected)

    def test_blank_lines_between_lines_with_decreasing_indent(self):
        md = "      a\n\n    b\n\n  c\n"
        expected = "      a\n    \n    b\n  \n  c\n"
        self.assertEqual(fix_details(md), expected)

    def test_blank_lines_with_mixed_spaces_tabs_and_content(self):
        md = " a\n\t\n    b\n\t\n      c\n"
        expected = " a\n \n    b\n    \n      c\n"
        self.assertEqual(fix_details(md), expected)

    def test_skipmark_markers_only(self):
        md = "<!-- scripts.linter.preprocess.fix_details on -->\n<!-- scripts.linter.preprocess.fix_details off -->"
        expected = "<!-- scripts.linter.preprocess.fix_details on -->\n<!-- scripts.linter.preprocess.fix_details off -->\n"
        self.assertEqual(fix_details(md), expected)

    def test_blank_lines_and_skipmark_at_start_end(self):
        md = "\n<!-- scripts.linter.preprocess.fix_details on -->\n   a\n<!-- scripts.linter.preprocess.fix_details off -->\n\n"
        expected = "\n<!-- scripts.linter.preprocess.fix_details on -->\n   a\n<!-- scripts.linter.preprocess.fix_details off -->\n\n"
        self.assertEqual(fix_details(md), expected)

    def test_blank_lines_and_skipmark_in_middle(self):
        md = "a\n\n<!-- scripts.linter.preprocess.fix_details on -->\n   a\n<!-- scripts.linter.preprocess.fix_details off -->\nb\n"
        expected = "a\n\n<!-- scripts.linter.preprocess.fix_details on -->\n   a\n<!-- scripts.linter.preprocess.fix_details off -->\nb\n"
        self.assertEqual(fix_details(md), expected)

    def test_nested_skipmark_markers(self):
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

    def test_blank_lines_before_and_after_skipmark(self):
        md = "\n<!-- scripts.linter.preprocess.fix_details on -->\n   \n<!-- scripts.linter.preprocess.fix_details off -->\n"
        expected = "\n<!-- scripts.linter.preprocess.fix_details on -->\n   \n<!-- scripts.linter.preprocess.fix_details off -->\n"
        self.assertEqual(fix_details(md), expected)

    def test_trailing_blank_lines(self):
        md = "  a\n\n\n"
        expected = "  a\n  \n  \n"
        self.assertEqual(fix_details(md), expected)

    def test_leading_blank_lines(self):
        md = "\n\n  a\n"
        expected = "  \n  \n  a\n"
        self.assertEqual(fix_details(md), expected)

    def test_missing_skipmark_on(self):
        md = "\n   \n<!-- scripts.linter.preprocess.fix_details off -->\n"
        with self.assertRaises(RuntimeError):
            fix_details(md)

    def test_missing_skipmark_off(self):
        md = "\n<!-- scripts.linter.preprocess.fix_details on -->\n   \n"
        with self.assertRaises(RuntimeError):
            fix_details(md)


if __name__ == "__main__":
    unittest.main()
