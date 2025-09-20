import unittest
from parameterized import parameterized
from scripts.linter.postprocess import fix_full_stop
from scripts.linter.utils import TAB_LENGTH


class TestConstants:
    """Constants used across test cases."""

    CODEBLOCK_ALL_LANG = [
        "tex",
        "text",
        "plain",
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


class TestFixFullStopBasic(unittest.TestCase):
    """Basic test cases for fix_full_stop function."""

    def setUp(self):
        """Set up test fixtures."""
        self.constants = TestConstants()

    def test_empty_content(self):
        """Test with empty content."""
        result = fix_full_stop("")
        self.assertEqual(result, "")

    def test_single_line_no_changes(self):
        """Test with single line that needs no changes."""
        content = "This is a normal line"
        expected = "This is a normal line\n"
        self.assertEqual(fix_full_stop(content), expected)

    def test_multiline_content(self):
        """Test punctuation replacement in multiline content."""
        content = "Line 1 with $x$, punctuation.\nLine 2 with $y$. punctuation。\nLine 3 with no changes."
        expected = "Line 1 with $x$, punctuation.\nLine 2 with $y$. punctuation．\nLine 3 with no changes.\n"
        self.assertEqual(fix_full_stop(content), expected)

    def test_no_inline_math_no_changes(self):
        """Test that content without inline math is not affected by punctuation rules."""
        content = "This is normal text, with punctuation. It should not change!"
        expected = "This is normal text, with punctuation. It should not change!\n"
        self.assertEqual(fix_full_stop(content), expected)

    def test_no_trailing_newline_input(self):
        """Test with input that has no trailing newline."""
        content = "Line。punctuation"
        expected = "Line．punctuation\n"
        self.assertEqual(fix_full_stop(content), expected)

    def test_period_replacement_chinese_to_fullwidth(self):
        """Test replacement of Chinese period with fullwidth period."""
        content = "This is a sentence。 Another sentence。"
        result = fix_full_stop(content)
        expected = "This is a sentence． Another sentence．\n"
        self.assertEqual(result, expected)

    def test_mixed_punctuation_replacements(self):
        """Test both inline math punctuation and period replacements."""
        content = "Formula $x$, is correct。 Another formula $y$ . is also correct。"
        result = fix_full_stop(content)
        expected = "Formula $x$, is correct． Another formula $y$ . is also correct．\n"
        self.assertEqual(result, expected)

    def test_unicode_punctuation_mixed(self):
        """Test with mixed Unicode punctuation."""
        content = "Mixed punctuation: $x$, Chinese period。 English period. $y$;"
        result = fix_full_stop(content)
        expected = "Mixed punctuation: $x$, Chinese period． English period. $y$;\n"
        self.assertEqual(result, expected)


class TestFixFullStopMathBlock(unittest.TestCase):
    def test_simple(self):
        content = (
            r"$$"+'\n'
            r"\$foo\$,\$bar\$。\$baz\$."+'\n'
            r"$$"+'\n'
            r"\$foo\$,\$bar\$。\$baz\$."+'\n'
        )
        expected = (
            r"$$"+'\n'
            r"\$foo\$,\$bar\$．\$baz\$."+'\n'
            r"$$"+'\n'
            r"\$foo\$,\$bar\$．\$baz\$."+'\n'
        )
        result = fix_full_stop(content)
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
            r"\$foo\$,\$bar\$．\$baz\$."+'\n'
        )
        result = fix_full_stop(content)
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
            r"\$foo\$,\$bar\$．\$baz\$."+'\n'
        )
        result = fix_full_stop(content)
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
            r"\$foo\$,\$bar\$．\$baz\$."+'\n'
            r"$$"+'\n'
        )
        result = fix_full_stop(content)
        self.assertEqual(result, expected)


class TestFixFullStopCodeBlock(unittest.TestCase):
    @parameterized.expand(TestConstants.CODEBLOCK_ALL_LANG)
    def test_simple(self, lang):
        content = (
            f"```{lang}\n"
            "$foo$,$bar$。$baz$.\n"
            "```\n"
        )
        expected = (
            f"```{lang}\n"
            "$foo$,$bar$．$baz$.\n"
            "```\n"
        )

        result = fix_full_stop(content)
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
            "$foo$,$bar$．$baz$.\n"
        )

        result = fix_full_stop(content)
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
        expected = (
            f"```{lang}\n"
            "```\n"
            f"```{lang}\n"
            "$foo$,$bar$．$baz$.\n"
            "```\n"
        )

        result = fix_full_stop(content)
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
            "$foo$,$bar$．$baz$.\n"
        )

        result = fix_full_stop(content)
        self.assertEqual(result, expected)


class TestFixFullStopMathCodeBlock(unittest.TestCase):
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
        expected = (
            r"$$"+'\n'
            r"\$foo\$,\$bar\$．\$baz\$."+'\n'
            r"$$"+'\n'
            f"```{lang}\n"
            "$foo$,$bar$．$baz$.\n"
            "```\n"
        )

        result = fix_full_stop(content)
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
        expected = (
            r"$$"+'\n'
            r"$$"+'\n'
            f"```{lang}\n"
            "$foo$,$bar$．$baz$.\n"
            "```\n"
            r"$$"+'\n'
            r"$$"+'\n'
            f"```{lang}\n"
            "$foo$,$bar$．$baz$.\n"
            "```\n"
        )

        result = fix_full_stop(content)
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
            r"\$foo\$,\$bar\$．\$baz\$."+'\n'
            r"$$"+'\n'
            f"```{lang}\n"
            "```\n"
            r"$$"+'\n'
            r"\$foo\$,\$bar\$．\$baz\$."+'\n'
            r"$$"+'\n'
        )
        result = fix_full_stop(content)
        self.assertEqual(result, expected)


class TestFixFullStopSkipBlocks(unittest.TestCase):
    """Test cases for skip block handling."""

    def setUp(self):
        """Set up test fixtures."""
        self.constants = TestConstants()
        self.SKIP_BLOCK_ON = "<!-- scripts.linter.postprocess.fix_full_stop off -->"
        self.SKIP_BLOCK_OFF = "<!-- scripts.linter.postprocess.fix_full_stop on -->"

    def test_skip_blocks_preserved(self):
        """Test that skip blocks are preserved unchanged."""
        md = (
            "$foo$,$bar$。$baz$.\n"
            f"{self.SKIP_BLOCK_ON}\n"
            "$foo$,$bar$。$baz$.\n"
            f"{self.SKIP_BLOCK_OFF}\n"
            "$foo$,$bar$。$baz$.\n"
        )
        expected = (
            "$foo$,$bar$．$baz$.\n"
            f"{self.SKIP_BLOCK_ON}\n"
            "$foo$,$bar$。$baz$.\n"
            f"{self.SKIP_BLOCK_OFF}\n"
            "$foo$,$bar$．$baz$.\n"
        )
        self.assertEqual(fix_full_stop(md), expected)

    def test_multiple_skip_blocks(self):
        """Test multiple skip blocks in the same content."""
        md = (
            "$foo$,$bar$。$baz$.\n"
            f"{self.SKIP_BLOCK_ON}\n"
            "$foo$,$bar$。$baz$.\n"
            f"{self.SKIP_BLOCK_OFF}\n"
            "$foo$,$bar$。$baz$.\n"
            f"{self.SKIP_BLOCK_ON}\n"
            "$foo$,$bar$。$baz$.\n"
            f"{self.SKIP_BLOCK_OFF}\n"
            "$foo$,$bar$。$baz$.\n"
        )
        expected = (
            "$foo$,$bar$．$baz$.\n"
            f"{self.SKIP_BLOCK_ON}\n"
            "$foo$,$bar$。$baz$.\n"
            f"{self.SKIP_BLOCK_OFF}\n"
            "$foo$,$bar$．$baz$.\n"
            f"{self.SKIP_BLOCK_ON}\n"
            "$foo$,$bar$。$baz$.\n"
            f"{self.SKIP_BLOCK_OFF}\n"
            "$foo$,$bar$．$baz$.\n"
        )
        self.assertEqual(fix_full_stop(md), expected)

    def test_skip_block_at_beginning(self):
        """Test skip block at the beginning of content."""
        md = (
            f"{self.SKIP_BLOCK_ON}\n"
            "$foo$,$bar$。$baz$.\n"
            f"{self.SKIP_BLOCK_OFF}\n"
            "$foo$,$bar$。$baz$.\n"
        )
        expected = (
            f"{self.SKIP_BLOCK_ON}\n"
            "$foo$,$bar$。$baz$.\n"
            f"{self.SKIP_BLOCK_OFF}\n"
            "$foo$,$bar$．$baz$.\n"
        )
        self.assertEqual(fix_full_stop(md), expected)

    def test_skip_block_at_end(self):
        """Test skip block at the end of content."""
        md = (
            "$foo$,$bar$。$baz$.\n"
            f"{self.SKIP_BLOCK_ON}\n"
            "$foo$,$bar$。$baz$.\n"
            f"{self.SKIP_BLOCK_OFF}\n"
        )
        expected = (
            "$foo$,$bar$．$baz$.\n"
            f"{self.SKIP_BLOCK_ON}\n"
            "$foo$,$bar$。$baz$.\n"
            f"{self.SKIP_BLOCK_OFF}\n"
        )
        self.assertEqual(fix_full_stop(md), expected)


if __name__ == "__main__":
    unittest.main()
