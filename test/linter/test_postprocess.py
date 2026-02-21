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
        
        # Lines outside skip block should be modified
        self.assertIn("修改这行．", result)
        self.assertIn("也修改这行．", result)
        # Line inside skip block should NOT be modified
        self.assertIn("不修改这行。", result)

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
        
        # Only outer lines should be modified
        self.assertIn("外部．", result)
        self.assertIn("外部末．", result)
        # All inner lines should be preserved
        self.assertIn("内部一。", result)
        self.assertIn("内部二。", result)
        self.assertIn("内部三。", result)

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
        
        # Normal lines should be modified
        self.assertIn("正常行一．", result)
        self.assertIn("正常行二．", result)
        self.assertIn("正常行三．", result)
        # Skip block lines should be preserved
        self.assertIn("跳过行。", result)
        self.assertIn("另一跳过行。", result)


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
        
        # Lines outside skip block should be modified
        self.assertIn("修改这行「引用」", result)
        self.assertIn("也修改这行「引用」", result)
        # Line inside skip block should NOT be modified
        self.assertIn('不修改这行“引用”', result)

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
        
        # Only outer lines should be modified
        self.assertIn("外部「引用」", result)
        self.assertIn("外部末「引用」", result)
        # All inner lines should be preserved
        self.assertIn('内部一“引用”', result)
        self.assertIn('内部二“引用”', result)
        self.assertIn('内部三“引用”', result)

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
        
        # Normal lines should be modified
        self.assertIn("正常行一「引用」", result)
        self.assertIn("正常行二「引用」", result)
        self.assertIn("正常行三「引用」", result)
        # Skip block lines should be preserved
        self.assertIn('跳过行“引用”', result)
        self.assertIn('另一跳过行“引用”', result)

    def test_single_quote_on_line(self):
        """Test a single quote character on a line."""
        content = '”\n'
        result = fix_quotation(content)
        # Both left and right quote replacements apply
        self.assertEqual(result, '」\n')

    def test_asymmetric_quotes(self):
        """Test handling of asymmetric quote usage."""
        content = '“开始但没结束\n'
        result = fix_quotation(content)
        self.assertEqual(result, '「开始但没结束\n')


if __name__ == "__main__":
    unittest.main()
