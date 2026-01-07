import unittest
from scripts.linter.postprocess import fix_full_stop


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


if __name__ == "__main__":
    unittest.main()
