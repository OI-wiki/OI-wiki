import unittest
from scripts.fix_details import fix_details


class TestFixDetails(unittest.TestCase):
    def test_all_blank_lines(self):
        md = "\n\n\n"
        expected = "\n\n\n"
        self.assertEqual(fix_details(md), expected)

    def test_blank_lines_with_only_tabs(self):
        md = "\t\n\t\n\t\n"
        expected = "\n\n\n"
        self.assertEqual(fix_details(md), expected)

    def test_basic_indentation(self):
        md = "    line1\n\n    line2\n"
        expected = "    line1\n    \n    line2\n"
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

    def test_skipdetails_on_off(self):
        md = (
            "  a\n"
            "<!-- preprocess.skipdetails on -->\n"
            "\n"
            "<!-- preprocess.skipdetails off -->\n"
            " b\n"
        )
        expected = (
            "  a\n"
            "<!-- preprocess.skipdetails on -->\n"
            "\n"
            "<!-- preprocess.skipdetails off -->\n"
            " b\n"
        )
        self.assertEqual(fix_details(md), expected)

    def test_skipdetails_on_off_at_start(self):
        md = (
            "<!-- preprocess.skipdetails on -->\n"
            "\n"
            "<!-- preprocess.skipdetails off -->\n"
            "  a\n"
        )
        expected = (
            "<!-- preprocess.skipdetails on -->\n"
            "\n"
            "<!-- preprocess.skipdetails off -->\n"
            "  a\n"
        )
        self.assertEqual(fix_details(md), expected)

    def test_skipdetails_on_off_at_end(self):
        md = (
            "  a\n"
            "<!-- preprocess.skipdetails on -->\n"
            "\n"
            "<!-- preprocess.skipdetails off -->\n"
        )
        expected = (
            "  a\n"
            "<!-- preprocess.skipdetails on -->\n"
            "\n"
            "<!-- preprocess.skipdetails off -->\n"
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

    def test_only_blank_lines_and_skipdetails(self):
        md = "<!-- preprocess.skipdetails on -->\n\n\n<!-- preprocess.skipdetails off -->"
        expected = "<!-- preprocess.skipdetails on -->\n\n\n<!-- preprocess.skipdetails off -->\n"
        self.assertEqual(fix_details(md), expected)

    def test_skipdetails_with_blank_lines_inside(self):
        md = (
            "  a\n"
            "<!-- preprocess.skipdetails on -->\n"
            "     \t \n"
            "   \n"
            "<!-- preprocess.skipdetails off -->\n"
            "   b\n"
        )
        expected = (
            "  a\n"
            "<!-- preprocess.skipdetails on -->\n"
            "     \t \n"
            "   \n"
            "<!-- preprocess.skipdetails off -->\n"
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

    def test_skipdetails_markers_only(self):
        md = "<!-- preprocess.skipdetails on -->\n<!-- preprocess.skipdetails off -->"
        expected = "<!-- preprocess.skipdetails on -->\n<!-- preprocess.skipdetails off -->\n"
        self.assertEqual(fix_details(md), expected)

    def test_blank_lines_and_skipdetails_at_start_end(self):
        md = "\n<!-- preprocess.skipdetails on -->\n   a\n<!-- preprocess.skipdetails off -->\n\n"
        expected = "\n<!-- preprocess.skipdetails on -->\n   a\n<!-- preprocess.skipdetails off -->\n\n"
        self.assertEqual(fix_details(md), expected)

    def test_blank_lines_and_skipdetails_in_middle(self):
        md = "a\n\n<!-- preprocess.skipdetails on -->\n   a\n<!-- preprocess.skipdetails off -->\nb\n"
        expected = "a\n\n<!-- preprocess.skipdetails on -->\n   a\n<!-- preprocess.skipdetails off -->\nb\n"
        self.assertEqual(fix_details(md), expected)

    def test_nested_skipdetails_markers(self):
        md = (
            "     a\n"
            "<!-- preprocess.skipdetails on -->\n"
            "    b\n"
            "<!-- preprocess.skipdetails on -->\n"
            "   c\n"
            "<!-- preprocess.skipdetails off -->\n"
            "  d\n"
            "<!-- preprocess.skipdetails off -->\n"
            " e\n"
        )
        expected = (
            "     a\n"
            "<!-- preprocess.skipdetails on -->\n"
            "    b\n"
            "<!-- preprocess.skipdetails on -->\n"
            "   c\n"
            "<!-- preprocess.skipdetails off -->\n"
            "  d\n"
            "<!-- preprocess.skipdetails off -->\n"
            " e\n"
        )
        self.assertEqual(fix_details(md), expected)

    def test_blank_lines_before_and_after_skipdetails(self):
        md = "\n<!-- preprocess.skipdetails on -->\n   \n<!-- preprocess.skipdetails off -->\n"
        expected = "\n<!-- preprocess.skipdetails on -->\n   \n<!-- preprocess.skipdetails off -->\n"
        self.assertEqual(fix_details(md), expected)

    def test_trailing_blank_lines(self):
        md = "  a\n\n\n"
        expected = "  a\n  \n  \n"
        self.assertEqual(fix_details(md), expected)

    def test_leading_blank_lines(self):
        md = "\n\n  a\n"
        expected = "  \n  \n  a\n"
        self.assertEqual(fix_details(md), expected)


if __name__ == "__main__":
    unittest.main()
