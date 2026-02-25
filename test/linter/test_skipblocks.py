"""Tests for mixed skip blocks across different linter functions."""

import unittest
from scripts.linter.preprocess import fix_details
from scripts.linter.postprocess import fix_full_stop, fix_quotation


class TestMixedSkipBlocks(unittest.TestCase):
    """Test cases for content with multiple different skip block types."""

    def test_multiple_skip_block_types_in_sequence(self):
        """Test different skip block types in sequence."""
        content = (
            "正常行。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "跳过句号。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "正常行“引用”。\n"
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "跳过引用“文本”。\n"
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "结束。\n"
        )

        # Apply fix_full_stop
        result = fix_full_stop(content)
        expected_fullstop = (
            "正常行．\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "跳过句号。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "正常行“引用”．\n"
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "跳过引用“文本”．\n"
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "结束．\n"
        )
        self.assertEqual(result, expected_fullstop)

        # Apply fix_quotation
        result = fix_quotation(content)
        expected_quotation = (
            "正常行。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "跳过句号。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "正常行「引用」。\n"
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "跳过引用“文本”。\n"
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "结束。\n"
        )
        self.assertEqual(result, expected_quotation)

    def test_interleaved_skip_blocks(self):
        """Test skip blocks for different functions interleaved."""
        content = (
            "开始。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "句号跳过。引用“正常”。\n"
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "句号跳过。引用“跳过”。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "句号正常。引用“跳过”。\n"
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "句号正常。引用“正常”。\n"
        )

        # Apply fix_full_stop
        result = fix_full_stop(content)
        expected_fullstop = (
            "开始．\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "句号跳过。引用“正常”。\n"
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "句号跳过。引用“跳过”。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "句号正常．引用“跳过”．\n"
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "句号正常．引用“正常”．\n"
        )
        self.assertEqual(result, expected_fullstop)

        # Apply fix_quotation
        result = fix_quotation(content)
        expected_quotation = (
            "开始。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "句号跳过。引用「正常」。\n"
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "句号跳过。引用“跳过”。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "句号正常。引用“跳过”。\n"
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "句号正常。引用「正常」。\n"
        )
        self.assertEqual(result, expected_quotation)

    def test_nested_different_skip_block_types(self):
        """Test one skip block type nested inside another."""
        content = (
            "外部。引用“正常”。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "句号跳过。引用“正常”。\n"
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "句号跳过。引用“跳过”。\n"
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "句号跳过。引用“正常”。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "外部。引用“正常”。\n"
        )

        # Apply fix_full_stop
        result = fix_full_stop(content)
        expected_fullstop = (
            "外部．引用“正常”．\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "句号跳过。引用“正常”。\n"
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "句号跳过。引用“跳过”。\n"
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "句号跳过。引用“正常”。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "外部．引用“正常”．\n"
        )
        self.assertEqual(result, expected_fullstop)

        # Apply fix_quotation
        result = fix_quotation(content)
        expected_quotation = (
            "外部。引用「正常」。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "句号跳过。引用「正常」。\n"
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "句号跳过。引用“跳过”。\n"
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "句号跳过。引用「正常」。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "外部。引用「正常」。\n"
        )
        self.assertEqual(result, expected_quotation)

    def test_all_three_skip_block_types(self):
        """Test preprocess and postprocess skip blocks together."""
        content = (
            "    正常缩进\n"
            "\n"
            "    句号。引用“文本”。\n"
            "<!-- scripts.linter.preprocess.fix_details off -->\n"
            "    \t\n"
            "<!-- scripts.linter.preprocess.fix_details on -->\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "    句号。引用“文本”。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "    句号。引用“文本”。\n"
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "    结束\n"
        )

        # Apply fix_details
        result = fix_details(content)
        expected_details = (
            "    正常缩进\n"
            "    \n"
            "    句号。引用“文本”。\n"
            "<!-- scripts.linter.preprocess.fix_details off -->\n"
            "    \t\n"
            "<!-- scripts.linter.preprocess.fix_details on -->\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "    句号。引用“文本”。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "    句号。引用“文本”。\n"
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "    结束\n"
        )
        self.assertEqual(result, expected_details)

        # Apply fix_full_stop
        result = fix_full_stop(content)
        expected_fullstop = (
            "    正常缩进\n"
            "\n"
            "    句号．引用“文本”．\n"
            "<!-- scripts.linter.preprocess.fix_details off -->\n"
            "      \n"
            "<!-- scripts.linter.preprocess.fix_details on -->\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "    句号。引用“文本”。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "    句号．引用“文本”．\n"
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "    结束\n"
        )
        self.assertEqual(result, expected_fullstop)

        # Apply fix_quotation
        result = fix_quotation(content)
        expected_quotation = (
            "    正常缩进\n"
            "\n"
            "    句号。引用「文本」。\n"
            "<!-- scripts.linter.preprocess.fix_details off -->\n"
            "      \n"
            "<!-- scripts.linter.preprocess.fix_details on -->\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "    句号。引用「文本」。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "    句号。引用“文本”。\n"
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "    结束\n"
        )
        self.assertEqual(result, expected_quotation)

    def test_single_quotes_with_skip_blocks(self):
        """Test single quote handling with skip blocks."""
        content = (
            "外层‘内层’引用。\n"
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "保留‘单引号’原样。\n"
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "转换‘单引号’正常。\n"
        )

        result = fix_quotation(content)
        expected = (
            "外层『内层』引用。\n"
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "保留‘单引号’原样。\n"
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "转换『单引号』正常。\n"
        )
        self.assertEqual(result, expected)

    def test_mixed_quotes_with_skip_blocks(self):
        """Test both single and double quotes with skip blocks."""
        content = (
            "双引号“测试”和单引号‘测试’。\n"
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "跳过“双引号”和‘单引号’。\n"
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "正常“双引号”和‘单引号’。\n"
        )

        result = fix_quotation(content)
        expected = (
            "双引号「测试」和单引号『测试』。\n"
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "跳过“双引号”和‘单引号’。\n"
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "正常「双引号」和『单引号』。\n"
        )
        self.assertEqual(result, expected)

    def test_adjacent_different_skip_blocks(self):
        """Test adjacent skip blocks of different types."""
        content = (
            "正常。引用“测试”。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "结束。引用“测试”。\n"
        )

        # Apply fix_full_stop
        result = fix_full_stop(content)
        expected_fullstop = (
            "正常．引用“测试”．\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "结束．引用“测试”．\n"
        )
        self.assertEqual(result, expected_fullstop)

        # Apply fix_quotation
        result = fix_quotation(content)
        expected_quotation = (
            "正常。引用「测试」。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "结束。引用「测试」。\n"
        )
        self.assertEqual(result, expected_quotation)

    def test_complex_real_world_markdown(self):
        """Test complex real-world scenario with multiple skip block types."""
        content = (
            "    ```\n"
            "\n"
            "    代码示例\n"
            "\n"
            "    正文。包含“引用”内容。\n"
            "\n"
            "    <!-- scripts.linter.preprocess.fix_details off -->\n"
            "\t保留制表符\n"
            "    <!-- scripts.linter.preprocess.fix_details on -->\n"
            "\n"
            "    <!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "    保留句号。但转换引号“测试”。\n"
            "    <!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "\n"
            "    <!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "    转换句号。但保留引号“测试”。\n"
            "    <!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "\n"
            "    结尾。引用“结束”。\n"
            "    ```\n"
        )

        # Apply fix_details
        result = fix_details(content)
        expected_details = (
            "    ```\n"
            "    \n"
            "    代码示例\n"
            "    \n"
            "    正文。包含“引用”内容。\n"
            "    \n"
            "    <!-- scripts.linter.preprocess.fix_details off -->\n"
            "\t保留制表符\n"
            "    <!-- scripts.linter.preprocess.fix_details on -->\n"
            "    \n"
            "    <!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "    保留句号。但转换引号“测试”。\n"
            "    <!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "    \n"
            "    <!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "    转换句号。但保留引号“测试”。\n"
            "    <!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "    \n"
            "    结尾。引用“结束”。\n"
            "    ```\n"
        )
        self.assertEqual(result, expected_details)

        # Apply fix_full_stop
        result = fix_full_stop(content)
        expected_fullstop = (
            "    ```\n"
            "\n"
            "    代码示例\n"
            "\n"
            "    正文．包含“引用”内容．\n"
            "\n"
            "    <!-- scripts.linter.preprocess.fix_details off -->\n"
            "  保留制表符\n"
            "    <!-- scripts.linter.preprocess.fix_details on -->\n"
            "\n"
            "    <!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "    保留句号。但转换引号“测试”。\n"
            "    <!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "\n"
            "    <!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "    转换句号．但保留引号“测试”．\n"
            "    <!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "\n"
            "    结尾．引用“结束”．\n"
            "    ```\n"
        )
        self.assertEqual(result, expected_fullstop)

        # Apply fix_quotation
        result = fix_quotation(content)
        expected_quotation = (
            "    ```\n"
            "\n"
            "    代码示例\n"
            "\n"
            "    正文。包含「引用」内容。\n"
            "\n"
            "    <!-- scripts.linter.preprocess.fix_details off -->\n"
            "  保留制表符\n"
            "    <!-- scripts.linter.preprocess.fix_details on -->\n"
            "\n"
            "    <!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "    保留句号。但转换引号「测试」。\n"
            "    <!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "\n"
            "    <!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "    转换句号。但保留引号“测试”。\n"
            "    <!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "\n"
            "    结尾。引用「结束」。\n"
            "    ```\n"
        )
        self.assertEqual(result, expected_quotation)

    def test_empty_skip_blocks_different_types(self):
        """Test empty skip blocks of different types."""
        content = (
            "开始。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "中间。\n"
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "结束。\n"
        )

        # Apply fix_full_stop
        result = fix_full_stop(content)
        expected_fullstop = (
            "开始．\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "中间．\n"
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "结束．\n"
        )
        self.assertEqual(result, expected_fullstop)

        # Apply fix_quotation
        result = fix_quotation(content)
        expected_quotation = content  # No quotes to change
        self.assertEqual(result, expected_quotation)

    def test_same_content_multiple_skip_types(self):
        """Test same content line affected by different skip blocks."""
        content = (
            "行一。引用“测试”。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "行二。引用“测试”。\n"
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "行三。引用“测试”。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "行四。引用“测试”。\n"
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "行五。引用“测试”。\n"
        )

        # Apply fix_full_stop
        result = fix_full_stop(content)
        expected_fullstop = (
            "行一．引用“测试”．\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "行二。引用“测试”。\n"
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "行三。引用“测试”。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "行四．引用“测试”．\n"
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "行五．引用“测试”．\n"
        )
        self.assertEqual(result, expected_fullstop)

        # Apply fix_quotation
        result = fix_quotation(content)
        expected_quotation = (
            "行一。引用「测试」。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "行二。引用「测试」。\n"
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "行三。引用“测试”。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "行四。引用“测试”。\n"
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "行五。引用「测试」。\n"
        )
        self.assertEqual(result, expected_quotation)

    def test_deeply_nested_multiple_types_skip_blocks(self):
        """Test deep nesting of multiple different skip block types."""
        content = (
            "外层“起始”。\n"
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "外层跳过引号“保持”。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "内层跳过句号并保持引号“内跳过”。\n"
            "<!-- scripts.linter.preprocess.fix_details off -->\n"
            "\n"
            "    \t内更深预处理“跳过”。\t\n"
            "<!-- scripts.linter.preprocess.fix_details on -->\n"
            "内层句号恢复。引号“内恢复”。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "外层句号恢复。引号“外恢复”。\n"
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "结尾“结束”。\n"
        )

        # Apply fix_details (preprocess) — ensure preprocess off region preserves its whitespace
        result = fix_details(content)
        expected_details = (
            "外层“起始”。\n"
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "外层跳过引号“保持”。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "内层跳过句号并保持引号“内跳过”。\n"
            "<!-- scripts.linter.preprocess.fix_details off -->\n"
            "\n"
            "    \t内更深预处理“跳过”。\t\n"
            "<!-- scripts.linter.preprocess.fix_details on -->\n"
            "内层句号恢复。引号“内恢复”。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "外层句号恢复。引号“外恢复”。\n"
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "结尾“结束”。\n"
        )
        self.assertEqual(result, expected_details)

        # Apply fix_full_stop — expect exact full output
        result = fix_full_stop(content)
        expected_fullstop = (
            "外层“起始”．\n"
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "外层跳过引号“保持”．\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "内层跳过句号并保持引号“内跳过”。\n"
            "<!-- scripts.linter.preprocess.fix_details off -->\n"
            "\n"
            "    \t内更深预处理“跳过”。\t\n"
            "<!-- scripts.linter.preprocess.fix_details on -->\n"
            "内层句号恢复。引号“内恢复”。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "外层句号恢复．引号“外恢复”．\n"
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "结尾“结束”．\n"
        )
        self.assertEqual(result, expected_fullstop)

        # Apply fix_quotation — expect exact full output
        result = fix_quotation(content)
        expected_quotation = (
            "外层「起始」。\n"
            "<!-- scripts.linter.postprocess.fix_quotation off -->\n"
            "外层跳过引号“保持”。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop off -->\n"
            "内层跳过句号并保持引号“内跳过”。\n"
            "<!-- scripts.linter.preprocess.fix_details off -->\n"
            "\n"
            "    \t内更深预处理“跳过”。\t\n"
            "<!-- scripts.linter.preprocess.fix_details on -->\n"
            "内层句号恢复。引号“内恢复”。\n"
            "<!-- scripts.linter.postprocess.fix_full_stop on -->\n"
            "外层句号恢复。引号“外恢复”。\n"
            "<!-- scripts.linter.postprocess.fix_quotation on -->\n"
            "结尾「结束」。\n"
        )
        self.assertEqual(result, expected_quotation)


if __name__ == "__main__":
    unittest.main()
