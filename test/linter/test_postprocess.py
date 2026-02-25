import unittest
from scripts.linter.postprocess import fix_full_stop, fix_quotation


class TestFixFullStop(unittest.TestCase):
    """Test cases for fix_full_stop function."""

    def test_replaces_chinese_fullstop(self):
        """Test that Chinese fullstop is replaced with middle dot."""
        content = "这是一个句子。\n"
        result = fix_full_stop(content)
        self.assertEqual(result, "这是一个句子．\n")

    def test_multiple_fullstops(self):
        """Test multiple fullstops in content."""
        content = "第一句。第二句。第三句。\n"
        result = fix_full_stop(content)
        self.assertEqual(result, "第一句．第二句．第三句．\n")

    def test_no_fullstops(self):
        """Test content without fullstops remains unchanged."""
        content = "No fullstops here\n"
        result = fix_full_stop(content)
        self.assertEqual(result, "No fullstops here\n")

    def test_empty_content(self):
        """Test empty content handling."""
        content = ""
        result = fix_full_stop(content)
        self.assertEqual(result, "")

    def test_multiline_content(self):
        """Test multiline content with fullstops."""
        content = "第一行。\n第二行。\n"
        result = fix_full_stop(content)
        self.assertEqual(result, "第一行．\n第二行．\n")

    def test_skip_block_content_not_modified(self):
        """Test that content in skip blocks is not modified.

        This tests the continue branch when line_origins[i] == -1.
        """
        content = (
            "修改这行。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "不修改这行。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "也修改这行。\n"
        )
        result = fix_full_stop(content)

        expected = (
            "修改这行．\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "不修改这行。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "也修改这行．\n"
        )
        self.assertEqual(result, expected)

    def test_nested_skip_blocks(self):
        """Test nested skip blocks preserve content."""
        content = (
            "外部。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "内部一。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "内部二。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "内部三。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "外部末。\n"
        )
        result = fix_full_stop(content)

        expected = (
            "外部．\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "内部一。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "内部二。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "内部三。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "外部末．\n"
        )
        self.assertEqual(result, expected)

    def test_mixed_content_with_skip_blocks(self):
        """Test mixed content with multiple skip blocks."""
        content = (
            "正常行一。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "跳过行。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "正常行二。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "另一跳过行。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "正常行三。\n"
        )
        result = fix_full_stop(content)

        expected = (
            "正常行一．\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "跳过行。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "正常行二．\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "另一跳过行。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "正常行三．\n"
        )
        self.assertEqual(result, expected)


class TestFixQuotation(unittest.TestCase):
    """Test cases for fix_quotation function."""

    def test_replaces_left_double_quote(self):
        """Test that left double quote is replaced with Chinese corner bracket."""
        content = '这是“引用”内容\n'
        result = fix_quotation(content)
        self.assertEqual(result, '这是「引用」内容\n')

    def test_replaces_right_double_quote(self):
        """Test that right double quote is replaced with Chinese corner bracket."""
        content = '这是“引用”内容\n'
        result = fix_quotation(content)
        self.assertEqual(result, '这是「引用」内容\n')

    def test_multiple_quotes(self):
        """Test multiple quotes in content."""
        content = '“第一”“第二”“第三”\n'
        result = fix_quotation(content)
        self.assertEqual(result, '「第一」「第二」「第三」\n')

    def test_mixed_quotes_in_sentence(self):
        """Test mixed quotes in a sentence."""
        content = '他说“你好”，然后她回答“谢谢”。\n'
        result = fix_quotation(content)
        self.assertEqual(result, '他说「你好」，然后她回答「谢谢」。\n')

    def test_no_quotes(self):
        """Test content without quotes remains unchanged."""
        content = "No quotes here\n"
        result = fix_quotation(content)
        self.assertEqual(result, "No quotes here\n")

    def test_empty_content(self):
        """Test empty content handling."""
        content = ""
        result = fix_quotation(content)
        self.assertEqual(result, "")

    def test_multiline_content(self):
        """Test multiline content with quotes."""
        content = '“第一行”\n“第二行”\n'
        result = fix_quotation(content)
        self.assertEqual(result, '「第一行」\n「第二行」\n')

    def test_quotes_in_code_block(self):
        """Test quotes in different contexts."""
        content = '文本“引用”和代码"value"\n'
        result = fix_quotation(content)
        # All quotes are replaced regardless of context
        self.assertEqual(result, '文本「引用」和代码"value"\n')

    def test_nested_quotes(self):
        """Test handling of what appears to be nested quotes."""
        content = '“外层‘内层’引用”\n'
        result = fix_quotation(content)
        self.assertEqual(result, '「外层『内层』引用」\n')

    def test_skip_block_content_not_modified(self):
        """Test that content in skip blocks is not modified.

        This tests the continue branch when line_origins[i] == -1.
        """
        content = (
            '修改这行“引用”\n'
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            '不修改这行“引用”\n'
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            '也修改这行“引用”\n'
        )
        result = fix_quotation(content)

        expected = (
            '修改这行「引用」\n'
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            '不修改这行“引用”\n'
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            '也修改这行「引用」\n'
        )
        self.assertEqual(result, expected)

    def test_nested_skip_blocks(self):
        """Test nested skip blocks preserve content."""
        content = (
            '外部“引用”\n'
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            '内部一“引用”\n'
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            '内部二“引用”\n'
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            '内部三“引用”\n'
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            '外部末“引用”\n'
        )
        result = fix_quotation(content)

        expected = (
            '外部「引用」\n'
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            '内部一“引用”\n'
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            '内部二“引用”\n'
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            '内部三“引用”\n'
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            '外部末「引用」\n'
        )
        self.assertEqual(result, expected)

    def test_mixed_content_with_skip_blocks(self):
        """Test mixed content with multiple skip blocks."""
        content = (
            '正常行一“引用”\n'
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            '跳过行“引用”\n'
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            '正常行二“引用”\n'
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            '另一跳过行“引用”\n'
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            '正常行三“引用”\n'
        )
        result = fix_quotation(content)

        expected = (
            '正常行一「引用」\n'
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            '跳过行“引用”\n'
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            '正常行二「引用」\n'
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            '另一跳过行“引用”\n'
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            '正常行三「引用」\n'
        )
        self.assertEqual(result, expected)

    def test_single_right_double_on_line_treated_as_left(self):
        content = '”\n'
        result = fix_quotation(content)
        self.assertEqual(result, '「\n')

    def test_single_right_single_on_line_treated_as_left(self):
        content = '’\n'
        result = fix_quotation(content)
        self.assertEqual(result, '『\n')

    def test_asymmetric_quotes(self):
        """Test handling of asymmetric quote usage."""
        content = '“开始但没结束\n'
        result = fix_quotation(content)
        self.assertEqual(result, '「开始但没结束\n')

    def test_multiline_quotes(self):
        """Test quotes that span multiple lines. See <https://github.com/OI-wiki/OI-wiki/blob/master/docs/lang/array.md?plain=1#L79-L80>."""
        content = '“第一行\n第二行”\n'
        result = fix_quotation(content)
        self.assertEqual(result, '「第一行\n第二行」\n')

    def test_curly_apostrophe_between_ascii_unchanged(self):
        """Curly apostrophe (’ U+2019) between ASCII letters should be left unchanged."""
        content = "don’t do it\n"
        result = fix_quotation(content)
        self.assertEqual(result, "don’t do it\n")

    def test_left_single_as_apostrophe_between_ascii(self):
        """Left single quote `‘` between ASCII letters should become a right apostrophe `’`."""
        content = "rock‘n’roll\n"
        result = fix_quotation(content)
        self.assertEqual(result, "rock’n’roll\n")

    def test_left_single_with_space_not_apostrophe(self):
        """If spaces surround the quote it should NOT be treated as an apostrophe."""
        content = "we ‘re here\n"
        result = fix_quotation(content)
        self.assertEqual(result, "we 『re here\n")

    def test_left_single_at_line_end_converted_to_right(self):
        """A left single quote at end-of-line is treated as an apostrophe and becomes `’`."""
        content = "word‘\n"
        result = fix_quotation(content)
        self.assertEqual(result, "word’\n")

    def test_apostrophe_when_only_spaces_to_right_triggers_except(self):
        """If only spaces follow the quote, index_lfirst_neq raises StopIteration and it is treated as apostrophe."""
        content = "a‘   \n"
        result = fix_quotation(content)
        self.assertEqual(result, "a’   \n")

    def test_apostrophe_after_digit(self):
        """A single quote following a digit (category 'Nd') should be treated as an apostrophe."""
        content = "version1‘s\n"
        result = fix_quotation(content)
        self.assertEqual(result, "version1’s\n")

    def test_apostrophe_after_uppercase_Lu(self):
        """An uppercase letter (category 'Lu') before a single quote should be an apostrophe."""
        content = "Φιλοσοφικό-Κοινωνιολογικό-Λεξικό-Α‘\n"
        result = fix_quotation(content)
        self.assertEqual(result, "Φιλοσοφικό-Κοινωνιολογικό-Λεξικό-Α’\n")

    def test_apostrophe_after_non_ascii_letter(self):
        """A single quote following a non-ASCII letter with category 'Ll' should be treated as an apostrophe."""
        content = "η αρχή κάθε‘ α ενεργούμε\n"
        result = fix_quotation(content)
        self.assertEqual(result, "η αρχή κάθε’ α ενεργούμε\n")

    def test_cjk_prev_char_not_apostrophe(self):
        """A single quote following a CJK character (category 'Lo') should NOT be an apostrophe."""
        content = "中‘文’\n"
        result = fix_quotation(content)
        self.assertEqual(result, "中『文』\n")

    def test_apostrophe_after_titlecase_Lt(self):
        """A titlecase letter (category 'Lt') before a single quote should be an apostrophe."""
        content = "ǅ‘emal\n"
        result = fix_quotation(content)
        self.assertEqual(result, "ǅ’emal\n")

    def test_apostrophe_after_letter_number_Nl(self):
        """A letter number (category 'Nl') before a single quote should be an apostrophe."""
        content = "Ⅻ‘section\n"
        result = fix_quotation(content)
        self.assertEqual(result, "Ⅻ’section\n")

    def test_apostrophe_after_modifier_letter_Lm(self):
        """A modifier letter (category 'Lm') before a single quote should be an apostrophe."""
        content = "tʰ‘is\n"
        result = fix_quotation(content)
        self.assertEqual(result, "tʰ’is\n")

    def test_apostrophe_after_letter_number_No(self):
        """A numeric character of other type (category 'No') before a single quote should be quote."""
        content = "௲‘s meaning is 1000\n"
        result = fix_quotation(content)
        self.assertEqual(result, "௲『s meaning is 1000\n")

    def test_leading_curly_apostrophe(self):
        """Leading curly apostrophe treated as left single quote."""
        # https://www.poetryfoundation.org/poems/42916/jabberwocky
        # In fact, `’Twas` should not be changed since it is used as a contraction of "It was", but it seems never appears in OI Wiki content, so we simply treat it as a single quote.
        content = (
            "’Twas brillig, and the slithy toves\n"
            "      Did gyre and gimble in the wabe:\n"
            "All mimsy were the borogoves,\n"
            "      And the mome raths outgrabe.\n"
            "\n"
            "“Beware the Jabberwock, my son!\n"
            "      The jaws that bite, the claws that catch!\n"
            "Beware the Jubjub bird, and shun\n"
            "      The frumious Bandersnatch!”\n"
            "\n"
            "He took his vorpal sword in hand;\n"
            "      Long time the manxome foe he sought—\n"
            "So rested he by the Tumtum tree\n"
            "      And stood awhile in thought.\n"
            "\n"
            "And, as in uffish thought he stood,\n"
            "      The Jabberwock, with eyes of flame,\n"
            "Came whiffling through the tulgey wood,\n"
            "      And burbled as it came!\n"
            "\n"
            "One, two! One, two! And through and through\n"
            "      The vorpal blade went snicker-snack!\n"
            "He left it dead, and with its head\n"
            "      He went galumphing back.\n"
            "\n"
            "“And hast thou slain the Jabberwock?\n"
            "      Come to my arms, my beamish boy!\n"
            "O frabjous day! Callooh! Callay!”\n"
            "      He chortled in his joy.\n"
            "\n"
            "’Twas brillig, and the slithy toves\n"
            "      Did gyre and gimble in the wabe:\n"
            "All mimsy were the borogoves,\n"
            "      And the mome raths outgrabe.\n"
        )
        result = fix_quotation(content)

        excepted = (
            "『Twas brillig, and the slithy toves\n"
            "      Did gyre and gimble in the wabe:\n"
            "All mimsy were the borogoves,\n"
            "      And the mome raths outgrabe.\n"
            "\n"
            "「Beware the Jabberwock, my son!\n"
            "      The jaws that bite, the claws that catch!\n"
            "Beware the Jubjub bird, and shun\n"
            "      The frumious Bandersnatch!」\n"
            "\n"
            "He took his vorpal sword in hand;\n"
            "      Long time the manxome foe he sought—\n"
            "So rested he by the Tumtum tree\n"
            "      And stood awhile in thought.\n"
            "\n"
            "And, as in uffish thought he stood,\n"
            "      The Jabberwock, with eyes of flame,\n"
            "Came whiffling through the tulgey wood,\n"
            "      And burbled as it came!\n"
            "\n"
            "One, two! One, two! And through and through\n"
            "      The vorpal blade went snicker-snack!\n"
            "He left it dead, and with its head\n"
            "      He went galumphing back.\n"
            "\n"
            "「And hast thou slain the Jabberwock?\n"
            "      Come to my arms, my beamish boy!\n"
            "O frabjous day! Callooh! Callay!」\n"
            "      He chortled in his joy.\n"
            "\n"
            "』Twas brillig, and the slithy toves\n"
            "      Did gyre and gimble in the wabe:\n"
            "All mimsy were the borogoves,\n"
            "      And the mome raths outgrabe.\n"
        )
        self.assertEqual(result, excepted)

    def test_single_quotes_after_non_alpha_ascii_not_apostrophe(self):
        """Single quotes after non-alpha ASCII letters should be treated as quotes, not apostrophes."""
        content = '“请直接打印出 ‘Hello world!’ 并返回 0”\n'
        result = fix_quotation(content)
        self.assertEqual(result, '「请直接打印出 『Hello world!』 并返回 0」\n')

    def test_single_quotes_after_non_alpha_ascii_is_apostrophe(self):
        """Single quotes after non-alpha ASCII letters should be treated as apostrophes."""
        content = '“请直接打印 ‘Hello world’”\n'
        result = fix_quotation(content)
        self.assertEqual(result, '「请直接打印 『Hello world’「\n')

    def test_deeply_nested_mixed_quotes(self):
        """Test deep nesting of mixed double/single quotes."""
        content = '“外层‘中层“内层”’结束”\n'
        result = fix_quotation(content)
        self.assertEqual(result, '「外层『中层「内层」』结束」\n')

    def test_crossed_nested_mixed_quotes(self):
        content = '“外层‘中层“错误嵌套’”结束”\n'
        result = fix_quotation(content)
        self.assertEqual(result, '「外层『中层「错误嵌套『「结束」\n')

    def test_extra_left_double_treated_as_right(self):
        """Two consecutive left double quotes: second is treated as a right quote."""
        content = '““重复”\n'
        result = fix_quotation(content)
        self.assertEqual(result, '「」重复「\n')

    def test_extra_left_single_treated_as_right(self):
        """Two consecutive left single quotes: second is treated as a right quote."""
        content = '‘‘内层’\n'
        result = fix_quotation(content)
        self.assertEqual(result, '『』内层『\n')

    def test_extra_right_double_treated_as_left(self):
        """Two consecutive right double quotes: second is treated as left quote."""
        content = '””重复“\n'
        result = fix_quotation(content)
        self.assertEqual(result, '「」重复「\n')

    def test_extra_right_single_treated_as_left(self):
        """Two consecutive right single quotes: second is treated as left quote."""
        content = '’’内层‘\n'
        result = fix_quotation(content)
        self.assertEqual(result, '『』内层『\n')


if __name__ == "__main__":
    unittest.main()
