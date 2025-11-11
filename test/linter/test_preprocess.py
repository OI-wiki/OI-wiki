import unittest
from parameterized import parameterized
from scripts.linter.preprocess import fix_details, fix_punctuations
from scripts.linter.utils import TAB_LENGTH


class TestConstants:
    """Constants used across test cases."""

    # Punctuation mappings
    PUNCTUATION_MAPPING = {
        ('。', '．'),
        (',', '，'),
        ('.', '．'),
        (';', '；'),
        (':', '：'),
        ('!', '！'),
        ('?', '？')
    }

    CODEBLOCK_SKIP_LANG = [
        "tex",
        "text",
        "plain"
    ]
    CODEBLOCK_CONTINUE_LANG = [
        "bash",
        "bat",
        "c",
        "console",
        "cpp",
        "doscon",
        "haskell",
        "java",
        "JSON",
        "json",
        "LaTeX",
        "latex",
        "markdown",
        "nasm",
        "pascal",
        "powershell",
        "ps1con",
        "pycon",
        "python",
        "Rust",
        "rust",
        "sh",
        "shell",
        "vim",
        "XML",
    ]
    CODEBLOCK_ALL_LANG = [*CODEBLOCK_SKIP_LANG, *CODEBLOCK_CONTINUE_LANG]

    # Common test patterns
    SIMPLE_MATH_FORMULA = "$x + y$"
    COMPLEX_MATH_FORMULA = r"$\sum_{i=1}^{n} x_i$"
    INTEGRAL_FORMULA = r"$\int_0^1 f(x)dx$"
    FRACTION_FORMULA = r"$\frac{a}{b}$"
    MATRIX_FORMULA = r"$\begin{pmatrix} a & b \\ c & d \end{pmatrix}$"

    # Performance test parameters
    LARGE_INPUT_SIZE = 3000


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
        ("unclosed_skip_block", "\n<!-- scripts.linter.preprocess.fix_details off -->\n   \n",
         "unclosed skip block"),
        ("unopened_skip_block", "\n   \n<!-- scripts.linter.preprocess.fix_details on -->\n",
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
            "<!-- scripts.linter.preprocess.fix_details off -->\n"
            "     \t \n"
            "   \n"
            "<!-- scripts.linter.preprocess.fix_details on -->\n"
            " b\n"
        )
        expected = (
            "  a\n"
            "<!-- scripts.linter.preprocess.fix_details off -->\n"
            "     \t \n"
            "   \n"
            "<!-- scripts.linter.preprocess.fix_details on -->\n"
            " b\n"
        )
        self.assertEqual(fix_details(md), expected)

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
        expected = (
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


class TestFixPunctuationsBasic(unittest.TestCase):
    """Basic test cases for fix_punctuations function."""

    def setUp(self):
        """Set up test fixtures."""
        self.constants = TestConstants()

    def test_empty_content(self):
        """Test with empty content."""
        result = fix_punctuations("")
        self.assertEqual(result, "")

    def test_single_line_no_changes(self):
        """Test with single line that needs no changes."""
        content = "This is a normal line"
        expected = "This is a normal line\n"
        self.assertEqual(fix_punctuations(content), expected)

    def test_multiline_content(self):
        """Test punctuation replacement in multiline content."""
        content = "Line 1 with $x$, punctuation.\nLine 2 with $y$. punctuation。\nLine 3 with no changes."
        expected = "Line 1 with $x$，punctuation.\nLine 2 with $y$．punctuation。\nLine 3 with no changes.\n"
        self.assertEqual(fix_punctuations(content), expected)

    def test_no_inline_math_no_changes(self):
        """Test that content without inline math is not affected by punctuation rules."""
        content = "This is normal text, with punctuation. It should not change!"
        expected = "This is normal text, with punctuation. It should not change!\n"
        self.assertEqual(fix_punctuations(content), expected)

    def test_no_trailing_newline_input(self):
        """Test with input that has no trailing newline."""
        content = "Line with $x$, punctuation"
        expected = "Line with $x$，punctuation\n"
        self.assertEqual(fix_punctuations(content), expected)


class TestFixPunctuationsInlineMath(unittest.TestCase):
    """Test cases for inline math punctuation replacement."""

    def setUp(self):
        """Set up test fixtures."""
        self.constants = TestConstants()

    @parameterized.expand(TestConstants.PUNCTUATION_MAPPING)
    def test_all_punctuation_types_coverage(self, english_punct, chinese_punct):
        """Test that all punctuation types are covered."""

        content = f"Formula {self.constants.SIMPLE_MATH_FORMULA}{english_punct} is correct"
        expected = f"Formula {self.constants.SIMPLE_MATH_FORMULA}{chinese_punct}is correct\n"
        result = fix_punctuations(content)
        self.assertEqual(
            result, expected, f"Failed to convert {english_punct} to {chinese_punct}")

    @parameterized.expand(TestConstants.PUNCTUATION_MAPPING)
    def test_all_punctuation_types_coverage_no_trailing_space(self, english_punct, chinese_punct):
        """Test that all punctuation types are covered."""

        content = f"Formula {self.constants.SIMPLE_MATH_FORMULA}{english_punct}is correct"
        expected = f"Formula {self.constants.SIMPLE_MATH_FORMULA}{chinese_punct}is correct\n"
        result = fix_punctuations(content)
        self.assertEqual(
            result, expected, f"Failed to convert {english_punct} to {chinese_punct}")

    @parameterized.expand(TestConstants.PUNCTUATION_MAPPING)
    def test_all_punctuation_keep_trailing_space_of_the_line(self, english_punct, chinese_punct):
        """Test that all punctuation types are covered."""

        content = f"Formula {self.constants.SIMPLE_MATH_FORMULA}{english_punct}  \n"
        expected = f"Formula {self.constants.SIMPLE_MATH_FORMULA}{chinese_punct}  \n"
        result = fix_punctuations(content)
        self.assertEqual(
            result, expected, f"Failed to convert {english_punct} to {chinese_punct}")

    def test_multiple_inline_math_punctuations(self):
        """Test multiple punctuation replacements in one line."""
        content = "Formulas $a$, $b$. and $c$; are correct"
        result = fix_punctuations(content)
        expected = "Formulas $a$，$b$．and $c$；are correct\n"
        self.assertEqual(result, expected)

    def test_complex_inline_math_formulas(self):
        """Test punctuation replacement with complex inline math formulas."""
        content = "The formula $\\sum_{i=1}^{n} x_i$, is the sum. Another $\\int_0^1 f(x)dx$ . is an integral."
        result = fix_punctuations(content)
        expected = "The formula $\\sum_{i=1}^{n} x_i$，is the sum. Another $\\int_0^1 f(x)dx$ . is an integral.\n"
        self.assertEqual(result, expected)

    def test_all_punctuation_types_in_one_line(self):
        """Test all punctuation types in a single line."""
        content = "Test $a$, $b$. $c$; $d$: $e$! $f$?"
        result = fix_punctuations(content)
        expected = "Test $a$，$b$．$c$；$d$：$e$！$f$？\n"
        self.assertEqual(result, expected)

    def test_punctuation_at_end_of_line(self):
        """Test punctuation at the end of lines."""
        content = "Line ending with $x$,\nLine ending with $y$.\nLine ending with $z$;"
        result = fix_punctuations(content)
        expected = "Line ending with $x$，\nLine ending with $y$．\nLine ending with $z$；\n"
        self.assertEqual(result, expected)

    def test_consecutive_inline_math_formulas(self):
        """Test consecutive inline math formulas with punctuation."""
        content = "Formulas $a$, $b$. $c$; are consecutive"
        result = fix_punctuations(content)
        expected = "Formulas $a$，$b$．$c$；are consecutive\n"
        self.assertEqual(result, expected)

    def test_inline_math_with_special_characters(self):
        """Test inline math with special characters and punctuation."""
        content = "Formula $x^2 + y^2 = z^2$, is Pythagorean theorem."
        result = fix_punctuations(content)
        expected = "Formula $x^2 + y^2 = z^2$，is Pythagorean theorem.\n"
        self.assertEqual(result, expected)


class TestFixPunctuationsBlockMath(unittest.TestCase):
    """Test cases for block math punctuation replacement."""

    def setUp(self):
        """Set up test fixtures."""
        self.constants = TestConstants()

    @parameterized.expand(TestConstants.PUNCTUATION_MAPPING)
    def test_all_punctuation_types_coverage(self, english_punct, chinese_punct):
        """Test that all punctuation types are covered."""

        content = f"Formula ${self.constants.SIMPLE_MATH_FORMULA}${english_punct} is correct"
        expected = f"Formula ${self.constants.SIMPLE_MATH_FORMULA}${chinese_punct}is correct\n"
        result = fix_punctuations(content)
        self.assertEqual(
            result, expected, f"Failed to convert {english_punct} to {chinese_punct}")

    @parameterized.expand(TestConstants.PUNCTUATION_MAPPING)
    def test_all_punctuation_types_coverage_no_trailing_space(self, english_punct, chinese_punct):
        """Test that all punctuation types are covered."""

        content = f"Formula ${self.constants.SIMPLE_MATH_FORMULA}${english_punct}is correct"
        expected = f"Formula ${self.constants.SIMPLE_MATH_FORMULA}${chinese_punct}is correct\n"
        result = fix_punctuations(content)
        self.assertEqual(
            result, expected, f"Failed to convert {english_punct} to {chinese_punct}")

    @parameterized.expand(TestConstants.PUNCTUATION_MAPPING)
    def test_all_punctuation_keep_trailing_space_of_the_line(self, english_punct, chinese_punct):
        """Test that all punctuation types are covered."""

        content = f"Formula ${self.constants.SIMPLE_MATH_FORMULA}${english_punct}  \n"
        expected = f"Formula ${self.constants.SIMPLE_MATH_FORMULA}${chinese_punct}  \n"
        result = fix_punctuations(content)
        self.assertEqual(
            result, expected, f"Failed to convert {english_punct} to {chinese_punct}")

    def test_all_punctuation_types_empty_math_in_one_line(self):
        """Test all punctuation types in a single line."""
        content = "Test $$, $$. $$; $$: $$! $$?"
        result = fix_punctuations(content)
        expected = "Test $$, $$．$$; $$：$$! $$？\n"
        self.assertEqual(result, expected)

    def test_all_punctuation_types_in_one_line(self):
        """Test all punctuation types in a single line."""
        content = "Test $$a$$, $$b$$. $$c$$; $$d$$: $$e$$! $$f$$?"
        result = fix_punctuations(content)
        expected = "Test $$a$$，$$b$$．$$c$$；$$d$$：$$e$$！$$f$$？\n"
        self.assertEqual(result, expected)

    def test_punctuation_at_end_of_line(self):
        """Test punctuation at the end of lines."""
        content = "Line ending with $$x$$,\nLine ending with $$y$$.\nLine ending with $$z$$;"
        result = fix_punctuations(content)
        expected = "Line ending with $$x$$，\nLine ending with $$y$$．\nLine ending with $$z$$；\n"
        self.assertEqual(result, expected)

    def test_inline_math_in_the_middle(self):
        """Test inline math in the middle."""
        content = "Formulas $$a$$, $b$. $$c$$; are consecutive"
        result = fix_punctuations(content)
        expected = "Formulas $$a$$，$b$．$$c$$；are consecutive\n"
        self.assertEqual(result, expected)

    def test_block_math_in_the_middle(self):
        """Test block math in the middle."""
        content = "Formulas $a$, $$b$$. $c$; are consecutive"
        result = fix_punctuations(content)
        expected = "Formulas $a$，$$b$$．$c$；are consecutive\n"
        self.assertEqual(result, expected)

    def test_block_math_with_special_characters(self):
        """Test block math with special characters and punctuation."""
        content = "Formula $$x^2 + y^2 = z^2$$, is Pythagorean theorem."
        result = fix_punctuations(content)
        expected = "Formula $$x^2 + y^2 = z^2$$，is Pythagorean theorem.\n"
        self.assertEqual(result, expected)


class TestFixPunctuationsMathBlock(unittest.TestCase):
    def test_simple(self):
        content = (
            r"$$"+'\n'
            r"\$foo\$,\$bar\$。\$baz\$."+'\n'
            r"$$"+'\n'
            r"\$foo\$,\$bar\$。\$baz\$."+'\n'
        )
        expected = (
            r"$$"+'\n'
            r"\$foo\$,\$bar\$。\$baz\$."+'\n'
            r"$$"+'\n'
            r"\$foo\$，\$bar\$．\$baz\$．"+'\n'
        )
        result = fix_punctuations(content)
        self.assertEqual(result, expected)

    def test_empty_math_block(self):
        content = (
            r"$$"+'\n'
            r"$$"+'\n'
            r"\$foo\$,\$bar\$。\$baz\$."+'\n'
        )
        expected = (
            r"$$"+'\n'
            r"$$"+'\n'
            r"\$foo\$，\$bar\$．\$baz\$．"+'\n'
        )
        result = fix_punctuations(content)
        self.assertEqual(result, expected)

    def test_nested_empty_math_blocks_changed(self):
        content = (
            r"$$"+'\n'
            r"$$"+'\n'
            r"$$"+'\n'
            r"$$"+'\n'
            r"\$foo\$,\$bar\$。\$baz\$."+'\n'
        )
        expected = (
            r"$$"+'\n'
            r"$$"+'\n'
            r"$$"+'\n'
            r"$$"+'\n'
            r"\$foo\$，\$bar\$．\$baz\$．"+'\n'
        )
        result = fix_punctuations(content)
        self.assertEqual(result, expected)

    def test_nested_empty_math_blocks(self):
        content = (
            r"$$"+'\n'
            r"$$"+'\n'
            r"$$"+'\n'
            r"\$foo\$,\$bar\$。\$baz\$."+'\n'
            r"$$"+'\n'
        )
        expected = (
            r"$$"+'\n'
            r"$$"+'\n'
            r"$$"+'\n'
            r"\$foo\$,\$bar\$。\$baz\$."+'\n'
            r"$$"+'\n'
        )
        result = fix_punctuations(content)
        self.assertEqual(result, expected)


class TestFixPunctuationsCodeBlock(unittest.TestCase):
    def setUp(self):
        self.skip_lang = TestConstants.CODEBLOCK_SKIP_LANG

    @parameterized.expand(TestConstants.CODEBLOCK_ALL_LANG)
    def test_simple(self, lang):
        content = (
            f"```{lang}\n"
            "$foo$,$bar$。$baz$.\n"
            "```\n"
        )
        changed = (
            f"```{lang}\n"
            "$foo$，$bar$．$baz$．\n"
            "```\n"
        )
        expected = content if lang in self.skip_lang else changed

        result = fix_punctuations(content)
        self.assertEqual(result, expected)

    @parameterized.expand(TestConstants.CODEBLOCK_ALL_LANG)
    def test_empty_codeblock(self, lang):
        content = (
            f"```{lang}\n"
            "```\n"
            "$foo$,$bar$。$baz$.\n"
        )
        expected = (
            f"```{lang}\n"
            "```\n"
            "$foo$，$bar$．$baz$．\n"
        )

        result = fix_punctuations(content)
        self.assertEqual(result, expected)

    @parameterized.expand(TestConstants.CODEBLOCK_ALL_LANG)
    def test_nested_empty_codeblocks(self, lang):
        content = (
            f"```{lang}\n"
            "```\n"
            f"```{lang}\n"
            "$foo$,$bar$。$baz$.\n"
            "```\n"
        )
        changed = (
            f"```{lang}\n"
            "```\n"
            f"```{lang}\n"
            "$foo$，$bar$．$baz$．\n"
            "```\n"
        )
        expected = content if lang in self.skip_lang else changed

        result = fix_punctuations(content)
        self.assertEqual(result, expected)

    @parameterized.expand(TestConstants.CODEBLOCK_ALL_LANG)
    def test_nested_empty_codeblocks_changed(self, lang):
        content = (
            f"```{lang}\n"
            "```\n"
            f"```{lang}\n"
            "```\n"
            "$foo$,$bar$。$baz$.\n"
        )
        expected = (
            f"```{lang}\n"
            "```\n"
            f"```{lang}\n"
            "```\n"
            "$foo$，$bar$．$baz$．\n"
        )

        result = fix_punctuations(content)
        self.assertEqual(result, expected)


class TestFixPunctuationsMathCodeBlock(unittest.TestCase):
    def setUp(self):
        self.skip_lang = TestConstants.CODEBLOCK_SKIP_LANG

    @parameterized.expand(TestConstants.CODEBLOCK_ALL_LANG)
    def test_simple(self, lang):
        content = (
            r"$$"+'\n'
            r"\$foo\$,\$bar\$。\$baz\$."+'\n'
            r"$$"+'\n'
            f"```{lang}\n"
            "$foo$,$bar$。$baz$.\n"
            "```\n"
        )
        changed = (
            r"$$"+'\n'
            r"\$foo\$,\$bar\$。\$baz\$."+'\n'
            r"$$"+'\n'
            f"```{lang}\n"
            "$foo$，$bar$．$baz$．\n"
            "```\n"
        )
        expected = content if lang in self.skip_lang else changed

        result = fix_punctuations(content)
        self.assertEqual(result, expected)

    @parameterized.expand(TestConstants.CODEBLOCK_ALL_LANG)
    def test_empty_math_block(self, lang):
        content = (
            r"$$"+'\n'
            r"$$"+'\n'
            f"```{lang}\n"
            "$foo$,$bar$。$baz$.\n"
            "```\n"
            r"$$"+'\n'
            r"$$"+'\n'
            f"```{lang}\n"
            "$foo$,$bar$。$baz$.\n"
            "```\n"
        )
        changed = (
            r"$$"+'\n'
            r"$$"+'\n'
            f"```{lang}\n"
            "$foo$，$bar$．$baz$．\n"
            "```\n"
            r"$$"+'\n'
            r"$$"+'\n'
            f"```{lang}\n"
            "$foo$，$bar$．$baz$．\n"
            "```\n"
        )
        expected = content if lang in self.skip_lang else changed

        result = fix_punctuations(content)
        self.assertEqual(result, expected)

    @parameterized.expand(TestConstants.CODEBLOCK_ALL_LANG)
    def test_empty_code_block(self, lang):
        content = (
            f"```{lang}\n"
            "```\n"
            r"$$"+'\n'
            r"\$foo\$,\$bar\$。\$baz\$."+'\n'
            r"$$"+'\n'
            f"```{lang}\n"
            "```\n"
            r"$$"+'\n'
            r"\$foo\$,\$bar\$。\$baz\$."+'\n'
            r"$$"+'\n'
        )
        expected = (
            f"```{lang}\n"
            "```\n"
            r"$$"+'\n'
            r"\$foo\$,\$bar\$。\$baz\$."+'\n'
            r"$$"+'\n'
            f"```{lang}\n"
            "```\n"
            r"$$"+'\n'
            r"\$foo\$,\$bar\$。\$baz\$."+'\n'
            r"$$"+'\n'
        )
        result = fix_punctuations(content)
        self.assertEqual(result, expected)


class TestFixPunctuationsEdgeCases(unittest.TestCase):
    """Test cases for edge cases and special scenarios."""

    def setUp(self):
        """Set up test fixtures."""
        self.constants = TestConstants()

    @parameterized.expand([
        ("empty_math", "Empty math $$, and $$. should be identified as a block math mark",
         "Empty math $$, and $$．should be identified as a block math mark\n"),
        ("nested_dollars", "Text with $nested$dollar$signs$, should be processed",
         "Text with $nested$dollar$signs$，should be processed\n"),
        ("single_dollar", "Text with $single dollar, should not be processed",
         "Text with $single dollar, should not be processed\n"),
        ("unmatched_dollars", "Text with $unmatched, should not be processed",
         "Text with $unmatched, should not be processed\n"),
    ])
    def test_edge_cases_inline_math(self, name, input_text, expected):
        """Test edge cases with inline math formulas."""
        result = fix_punctuations(input_text)
        self.assertEqual(result, expected, f"Failed test case: {name}")

    def test_very_long_math_formula(self):
        """Test with very long mathematical expression."""
        long_formula = r"$\sum_{i=1}^{n} \sum_{j=1}^{m} \sum_{k=1}^{p} x_{i,j,k} \cdot y_{i,j,k} \cdot z_{i,j,k}$"
        content = f"Long formula {long_formula}, is complex"
        result = fix_punctuations(content)
        expected = f"Long formula {long_formula}，is complex\n"
        self.assertEqual(result, expected)

    def test_math_with_special_characters(self):
        """Test math formulas with special characters."""
        content = r"Formula $\alpha + \beta = \gamma$, is Greek"
        result = fix_punctuations(content)
        expected = r"Formula $\alpha + \beta = \gamma$，is Greek"+"\n"
        self.assertEqual(result, expected)

    def test_math_with_unicode(self):
        """Test math formulas with Unicode characters."""
        content = r"Formula $\forall x \in \mathbb{R}$, is universal"
        result = fix_punctuations(content)
        expected = r"Formula $\forall x \in \mathbb{R}$，is universal"+"\n"
        self.assertEqual(result, expected)

    def test_multiple_consecutive_punctuation(self):
        """Test multiple consecutive punctuation marks."""
        content = "Formula $x$,;:!? is complex"
        result = fix_punctuations(content)
        expected = "Formula $x$，;:!? is complex\n"
        self.assertEqual(result, expected)

    def test_punctuation_at_very_end(self):
        """Test punctuation at the very end of content."""
        content = "Formula $x$,"
        result = fix_punctuations(content)
        expected = "Formula $x$，\n"
        self.assertEqual(result, expected)

    def test_only_whitespace_content(self):
        """Test content with only whitespace."""
        content = "   \t  \n  \t  "
        result = fix_punctuations(content)
        expected = "   {}  \n  {}  \n".format(' '*TAB_LENGTH, ' '*TAB_LENGTH)
        self.assertEqual(result, expected)

    def test_mixed_newline_types(self):
        """Test content with mixed newline types (CRLF and LF)."""
        content = "Line 1 with $x$, punctuation.\r\nLine 2 with $y$. punctuation。\r\n"
        result = fix_punctuations(content)
        expected = "Line 1 with $x$，punctuation.\nLine 2 with $y$．punctuation。\n"
        self.assertEqual(result, expected)

    @parameterized.expand([
        ("no_space_after_comma", "Formula $x$,is correct", "Formula $x$，is correct\n"),
        ("no_space_after_period", "Formula $x$.is correct", "Formula $x$．is correct\n"),
        ("no_space_after_semicolon", "Formula $x$;is correct",
         "Formula $x$；is correct\n"),
        ("no_space_after_colon", "Formula $x$:is correct", "Formula $x$：is correct\n"),
        ("no_space_after_exclamation",
         "Formula $x$!is correct", "Formula $x$！is correct\n"),
        ("no_space_after_question", "Formula $x$?is correct",
         "Formula $x$？is correct\n"),
    ])
    def test_punctuation_without_spaces(self, name, input_text, expected):
        """Test punctuation replacement without spaces after punctuation."""
        result = fix_punctuations(input_text)
        self.assertEqual(result, expected, f"Failed test case: {name}")


class TestFixPunctuationsParameterized(unittest.TestCase):
    """Test cases using parameterized tests for comprehensive coverage."""

    @parameterized.expand([
        ("sum_formula", r"The formula $\sum_{i=1}^{n} x_i$, is the sum",
         r"The formula $\sum_{i=1}^{n} x_i$，is the sum"+'\n'),
        ("integral_formula", r"Another $\int_0^1 f(x)dx$. is an integral",
         r"Another $\int_0^1 f(x)dx$．is an integral"+'\n'),
        ("fraction_formula", r"Fraction $\frac{a}{b}$, is correct",
         r"Fraction $\frac{a}{b}$，is correct"+'\n'),
        ("matrix_formula", r"Matrix $\begin{pmatrix} a & b \\ c & d \end{pmatrix}$; is square",
         r"Matrix $\begin{pmatrix} a & b \\ c & d \end{pmatrix}$；is square"+'\n'),
    ])
    def test_complex_math_formulas(self, name, input_text, expected):
        """Test punctuation replacement with complex mathematical expressions."""
        result = fix_punctuations(input_text)
        self.assertEqual(result, expected, f"Failed test case: {name}")

    @parameterized.expand([
        ("whitespace_only_lines", "   \nLine with $x$, punctuation.\n   \n",
         "   \nLine with $x$，punctuation.\n   \n"),
        ("no_trailing_newline", "Line with $x$, punctuation",
         "Line with $x$，punctuation\n"),
        ("multiple_spaces_after_punct", "Formula $x$,   is correct",
         "Formula $x$，  is correct\n"),
        ("tabs_after_punct", "Formula $x$,\tis correct",
         f"Formula $x$，{' '*(TAB_LENGTH-1)}is correct\n"),
    ])
    def test_whitespace_handling(self, name, input_text, expected):
        """Test various whitespace scenarios."""
        result = fix_punctuations(input_text)
        self.assertEqual(result, expected, f"Failed test case: {name}")


class TestFixPunctuationsPerformance(unittest.TestCase):
    """Test cases for performance and large input handling."""

    def setUp(self):
        """Set up test fixtures."""
        self.constants = TestConstants()

    def test_performance_large_input(self):
        """Test performance with large input containing many math formulas."""
        # Create a large input with many inline math formulas
        lines = []
        for i in range(self.constants.LARGE_INPUT_SIZE):
            lines.append(
                f"Formula $x_{i}$, is correct. Another $y_{i}$; is also correct.")

        content = "\n".join(lines)
        result = fix_punctuations(content)

        # Verify the result has the expected structure
        self.assertTrue(result.endswith('\n'))
        self.assertEqual(result.count('，'), self.constants.LARGE_INPUT_SIZE)
        self.assertEqual(result.count('；'), self.constants.LARGE_INPUT_SIZE)
        self.assertIn("$x_0$，", result)
        self.assertIn("$y_0$；", result)
        self.assertIn(f"$x_{self.constants.LARGE_INPUT_SIZE-1}$，", result)
        self.assertIn(f"$y_{self.constants.LARGE_INPUT_SIZE-1}$；", result)

    def test_performance_very_large_input(self):
        """Test performance with very large input (10x larger)."""
        very_large_size = self.constants.LARGE_INPUT_SIZE * 10
        lines = []
        for i in range(very_large_size):
            lines.append(f"Formula $x_{i}$, is correct.")

        content = "\n".join(lines)
        result = fix_punctuations(content)

        # Verify the result has the expected structure
        self.assertTrue(result.endswith('\n'))
        self.assertEqual(result.count('，'), very_large_size)
        self.assertIn("$x_0$，", result)
        self.assertIn(f"$x_{very_large_size-1}$，", result)

    def test_performance_complex_math_formulas(self):
        """Test performance with complex math formulas."""
        lines = []
        for i in range(100):
            lines.append(
                f"Complex formula {self.constants.COMPLEX_MATH_FORMULA}, is sum {i}.")
            lines.append(
                f"Integral {self.constants.INTEGRAL_FORMULA}; is integral {i}.")
            lines.append(
                f"Fraction {self.constants.FRACTION_FORMULA}: is fraction {i}.")

        content = "\n".join(lines)
        result = fix_punctuations(content)

        # Verify the result has the expected structure
        self.assertTrue(result.endswith('\n'))
        self.assertEqual(result.count('，'), 100)  # Complex formulas
        self.assertEqual(result.count('；'), 100)  # Integral formulas
        self.assertEqual(result.count('：'), 100)  # Fraction formulas

    def test_performance_mixed_content(self):
        """Test performance with mixed content types."""
        lines = []
        for i in range(500):
            # Mix of different content types
            lines.append(f"Simple text line {i}.")
            lines.append(f"Formula $x_{i}$, is correct.")
            lines.append("")  # Empty line
            lines.append("   ")  # Whitespace line

        content = "\n".join(lines)
        result = fix_punctuations(content)

        # Verify the result has the expected structure
        self.assertTrue(result.endswith('\n'))
        self.assertEqual(result.count('，'), 500)  # Math formulas


class TestFixPunctuationsSkipBlocks(unittest.TestCase):
    """Test cases for skip block handling."""

    def setUp(self):
        """Set up test fixtures."""
        self.constants = TestConstants()
        self.SKIP_BLOCK_ON = "<!-- scripts.linter.preprocess.fix_punctuations off -->"
        self.SKIP_BLOCK_OFF = "<!-- scripts.linter.preprocess.fix_punctuations on -->"

    def test_skip_blocks_preserved(self):
        """Test that skip blocks are preserved unchanged."""
        md = (
            f"{self.constants.COMPLEX_MATH_FORMULA}, is the sum\n"
            f"{self.SKIP_BLOCK_ON}\n"
            f"{self.constants.INTEGRAL_FORMULA}. is an integral\n"
            f"{self.constants.FRACTION_FORMULA}, is correct\n"
            f"{self.SKIP_BLOCK_OFF}\n"
            f"{self.constants.MATRIX_FORMULA}; is square\n"
        )
        expected = (
            f"{self.constants.COMPLEX_MATH_FORMULA}，is the sum\n"
            f"{self.SKIP_BLOCK_ON}\n"
            f"{self.constants.INTEGRAL_FORMULA}. is an integral\n"
            f"{self.constants.FRACTION_FORMULA}, is correct\n"
            f"{self.SKIP_BLOCK_OFF}\n"
            f"{self.constants.MATRIX_FORMULA}；is square\n"
        )
        self.assertEqual(fix_punctuations(md), expected)

    def test_multiple_skip_blocks(self):
        """Test multiple skip blocks in the same content."""
        md = (
            f"Before first block: {self.constants.SIMPLE_MATH_FORMULA}, is simple\n"
            f"{self.SKIP_BLOCK_ON}\n"
            f"Skipped: {self.constants.SIMPLE_MATH_FORMULA}, should not change\n"
            f"{self.SKIP_BLOCK_OFF}\n"
            f"Between blocks: {self.constants.SIMPLE_MATH_FORMULA}, is processed\n"
            f"{self.SKIP_BLOCK_ON}\n"
            f"Also skipped: {self.constants.SIMPLE_MATH_FORMULA}, should not change\n"
            f"{self.SKIP_BLOCK_OFF}\n"
            f"After second block: {self.constants.SIMPLE_MATH_FORMULA}, is processed\n"
        )
        expected = (
            f"Before first block: {self.constants.SIMPLE_MATH_FORMULA}，is simple\n"
            f"{self.SKIP_BLOCK_ON}\n"
            f"Skipped: {self.constants.SIMPLE_MATH_FORMULA}, should not change\n"
            f"{self.SKIP_BLOCK_OFF}\n"
            f"Between blocks: {self.constants.SIMPLE_MATH_FORMULA}，is processed\n"
            f"{self.SKIP_BLOCK_ON}\n"
            f"Also skipped: {self.constants.SIMPLE_MATH_FORMULA}, should not change\n"
            f"{self.SKIP_BLOCK_OFF}\n"
            f"After second block: {self.constants.SIMPLE_MATH_FORMULA}，is processed\n"
        )
        self.assertEqual(fix_punctuations(md), expected)

    def test_skip_block_at_beginning(self):
        """Test skip block at the beginning of content."""
        md = (
            f"{self.SKIP_BLOCK_ON}\n"
            f"Skipped: {self.constants.SIMPLE_MATH_FORMULA}, should not change\n"
            f"{self.SKIP_BLOCK_OFF}\n"
            f"Processed: {self.constants.SIMPLE_MATH_FORMULA}, should change\n"
        )
        expected = (
            f"{self.SKIP_BLOCK_ON}\n"
            f"Skipped: {self.constants.SIMPLE_MATH_FORMULA}, should not change\n"
            f"{self.SKIP_BLOCK_OFF}\n"
            f"Processed: {self.constants.SIMPLE_MATH_FORMULA}，should change\n"
        )
        self.assertEqual(fix_punctuations(md), expected)

    def test_skip_block_at_end(self):
        """Test skip block at the end of content."""
        md = (
            f"Processed: {self.constants.SIMPLE_MATH_FORMULA}, should change\n"
            f"{self.SKIP_BLOCK_ON}\n"
            f"Skipped: {self.constants.SIMPLE_MATH_FORMULA}, should not change\n"
            f"{self.SKIP_BLOCK_OFF}\n"
        )
        expected = (
            f"Processed: {self.constants.SIMPLE_MATH_FORMULA}，should change\n"
            f"{self.SKIP_BLOCK_ON}\n"
            f"Skipped: {self.constants.SIMPLE_MATH_FORMULA}, should not change\n"
            f"{self.SKIP_BLOCK_OFF}\n"
        )
        self.assertEqual(fix_punctuations(md), expected)


class TestFixPunctuationsSummary(unittest.TestCase):
    """Summary and integration tests for the fix_punctuations function."""

    def setUp(self):
        """Set up test fixtures."""
        self.constants = TestConstants()
        self.SKIP_BLOCK_ON = "<!-- scripts.linter.preprocess.fix_punctuations off -->"
        self.SKIP_BLOCK_OFF = "<!-- scripts.linter.preprocess.fix_punctuations on -->"

    def test_comprehensive_integration(self):
        """Test comprehensive integration of all punctuation fixes."""
        # Create a comprehensive test case that covers all major scenarios
        content = (
            "Document with various punctuation scenarios:\n"
            f"1. Simple math: {self.constants.SIMPLE_MATH_FORMULA}, is basic\n"
            f"2. Complex math: {self.constants.COMPLEX_MATH_FORMULA}, is advanced\n"
            f"3. Mixed content: Formula {self.constants.SIMPLE_MATH_FORMULA}, is correct。\n"
            f"4. Multiple punctuation: Test {self.constants.SIMPLE_MATH_FORMULA}, {self.constants.SIMPLE_MATH_FORMULA}. {self.constants.SIMPLE_MATH_FORMULA}; {self.constants.SIMPLE_MATH_FORMULA}: {self.constants.SIMPLE_MATH_FORMULA}! {self.constants.SIMPLE_MATH_FORMULA}?\n"
            f"5. Skip block test:\n"
            f"{self.SKIP_BLOCK_ON}\n"
            f"Skipped: {self.constants.SIMPLE_MATH_FORMULA}, should not change\n"
            f"{self.SKIP_BLOCK_OFF}\n"
            f"6. After skip: {self.constants.SIMPLE_MATH_FORMULA}, is processed\n"
        )

        expected = (
            "Document with various punctuation scenarios:\n"
            f"1. Simple math: {self.constants.SIMPLE_MATH_FORMULA}，is basic\n"
            f"2. Complex math: {self.constants.COMPLEX_MATH_FORMULA}，is advanced\n"
            f"3. Mixed content: Formula {self.constants.SIMPLE_MATH_FORMULA}，is correct。\n"
            f"4. Multiple punctuation: Test {self.constants.SIMPLE_MATH_FORMULA}，{self.constants.SIMPLE_MATH_FORMULA}．{self.constants.SIMPLE_MATH_FORMULA}；{self.constants.SIMPLE_MATH_FORMULA}：{self.constants.SIMPLE_MATH_FORMULA}！{self.constants.SIMPLE_MATH_FORMULA}？\n"
            f"5. Skip block test:\n"
            f"{self.SKIP_BLOCK_ON}\n"
            f"Skipped: {self.constants.SIMPLE_MATH_FORMULA}, should not change\n"
            f"{self.SKIP_BLOCK_OFF}\n"
            f"6. After skip: {self.constants.SIMPLE_MATH_FORMULA}，is processed\n"
        )

        result = fix_punctuations(content)
        self.assertEqual(result, expected)


if __name__ == "__main__":
    unittest.main()
