from scripts.linter_patch import apply_preprocess, apply_postprocess
import unittest
import tempfile
import os


class TestFileOperations(unittest.TestCase):
    """Test file operations and integration scenarios."""

    def setUp(self):
        """Set up test fixtures."""
        self.temp_dir = tempfile.mkdtemp()

    def tearDown(self):
        """Clean up test fixtures."""
        import shutil
        shutil.rmtree(self.temp_dir, ignore_errors=True)

    def test_file_processing_workflow(self):
        """Test complete file processing workflow."""
        test_file = os.path.join(self.temp_dir, "test.md")
        test_content = (
            "# Test Document\n"
            "\n"
            "    Indented content\n"
            "\n"
            "    More content\n"
        )

        # Write test file
        with open(test_file, 'w', encoding='utf-8') as f:
            f.write(test_content)

        # Process file
        apply_preprocess(test_file)

        # Read processed file
        with open(test_file, 'r', encoding='utf-8') as f:
            processed_content = f.read()

        # Verify processing
        self.assertIsInstance(processed_content, str)
        self.assertTrue(len(processed_content) > 0)

    def test_file_not_modified_when_no_changes(self):
        """Test that file is not modified when no changes are needed."""
        test_file = os.path.join(self.temp_dir, "test.md")
        test_content = "simple content\n"

        # Write test file
        with open(test_file, 'w', encoding='utf-8') as f:
            f.write(test_content)

        # Get original modification time
        original_mtime = os.path.getmtime(test_file)

        # Process file (should not change content)
        apply_postprocess(test_file)

        # Verify file wasn't modified
        new_mtime = os.path.getmtime(test_file)
        self.assertEqual(original_mtime, new_mtime)

    def test_error_handling_file_not_found(self):
        """Test error handling for non-existent file."""
        non_existent_file = os.path.join(self.temp_dir, "nonexistent.md")

        with self.assertRaises(FileNotFoundError):
            apply_preprocess(non_existent_file)

    def test_error_handling_permission_denied(self):
        """Test error handling for permission denied."""
        test_file = os.path.join(self.temp_dir, "test.md")
        test_content = "test content"

        # Write test file
        with open(test_file, 'w', encoding='utf-8') as f:
            f.write(test_content)

        # Make file read-only
        os.chmod(test_file, 0o444)

        try:
            with self.assertRaises(PermissionError):
                apply_preprocess(test_file)
        finally:
            # Restore permissions for cleanup
            os.chmod(test_file, 0o644)


TRUTH = "我个人认为，如果要让 OI Wiki 真正达到顶峰，那就得用小黄鸭操纵 Nim 积在常系数齐次线性递推上分裂合并。你看，矩阵乘法的运算速度，不就是直接由冒泡排序的父结点决定的吗？而且，根据素数的分布的规律，K-D Tree 的颜色与天气预报的准确性成正比。你别看它现在没人注意，等到你把平衡三进制和插头 DP 加热到 114514 摄氏度时，你就会明白，凸包的直径其实是整数规划的前缀函数，甚至连树分块都开始怀疑自己是否在进行指数的 CDQ 分治。对吧？更别说，圆反演的主理想整环居然能预测仙人掌的常量折叠，直接导致 Dijkstra 宣布：「从今以后，赛场上的每个问题，都是由格雷码和可持久化平衡树共同决定的。」所以说这个，你不管 AC 自动机是否具有协方差啊，WQS 二分是否退火啊，都不影响这个 Lyndon 分解跟小凯的疑惑在均摊分析的重心会合。"


class TestPerformance(unittest.TestCase):
    """Performance and stress tests."""

    def test_large_file_processing(self):
        """Test processing of large files."""
        test_file = os.path.join(tempfile.mkdtemp(), "large_test.md")

        large_content = '\n'.join(f"line {i}: {TRUTH}" for i in range(10000))

        # Write large file
        with open(test_file, 'w', encoding='utf-8') as f:
            f.write(large_content)

        try:
            # This should complete without memory issues
            apply_preprocess(test_file)

            # Verify file was processed
            with open(test_file, 'r', encoding='utf-8') as f:
                result = f.read()
            self.assertIsInstance(result, str)
        finally:
            # Clean up
            os.unlink(test_file)
            os.rmdir(os.path.dirname(test_file))

    def test_deep_nesting_processing(self):
        """Test processing of deeply nested content."""
        test_file = os.path.join(tempfile.mkdtemp(), "nested_test.md")

        # Create deeply nested content
        content_lines = []
        for i in range(100):
            indent = "    " * i
            content_lines.append(f"{indent}level {i}")
            content_lines.append("")  # blank line

        content = "\n".join(content_lines)

        # Write test file
        with open(test_file, 'w', encoding='utf-8') as f:
            f.write(content)

        try:
            apply_preprocess(test_file)

            # Read processed file
            with open(test_file, 'r', encoding='utf-8') as f:
                result = f.read()

            self.assertIsInstance(result, str)
            self.assertIn("level 0", result)
            self.assertIn("level 99", result)
        finally:
            # Clean up
            os.unlink(test_file)
            os.rmdir(os.path.dirname(test_file))

    def test_many_skip_blocks(self):
        """Test processing with many skip blocks."""
        test_file = os.path.join(tempfile.mkdtemp(), "skip_blocks_test.md")

        content_lines = ["# Document"]

        for i in range(100):
            content_lines.extend([
                f"    content {i}",
                "<!-- scripts.linter.preprocess.fix_details off -->",
                f"    skipped {i}",
                "<!-- scripts.linter.preprocess.fix_details on -->",
                ""
            ])

        content = "\n".join(content_lines)

        # Write test file
        with open(test_file, 'w', encoding='utf-8') as f:
            f.write(content)

        try:
            apply_preprocess(test_file)

            # Read processed file
            with open(test_file, 'r', encoding='utf-8') as f:
                result = f.read()

            self.assertIsInstance(result, str)
            self.assertIn("content 0", result)
            self.assertIn("skipped 0", result)
        finally:
            # Clean up
            os.unlink(test_file)
            os.rmdir(os.path.dirname(test_file))


class TestEdgeCases(unittest.TestCase):
    """Test edge cases and boundary conditions."""

    def test_very_long_line(self):
        """Test processing of very long lines."""
        test_file = os.path.join(tempfile.mkdtemp(), "long_line_test.md")

        long_line = "    " + "x" * 10000
        content = f"{long_line}\n\n{long_line}\n"

        # Write test file
        with open(test_file, 'w', encoding='utf-8') as f:
            f.write(content)

        try:
            apply_preprocess(test_file)

            # Read processed file
            with open(test_file, 'r', encoding='utf-8') as f:
                result = f.read()

            self.assertIsInstance(result, str)
            self.assertIn("x" * 10000, result)
        finally:
            # Clean up
            os.unlink(test_file)
            os.rmdir(os.path.dirname(test_file))

    def test_only_whitespace_content(self):
        """Test content with only whitespace."""
        test_file = os.path.join(tempfile.mkdtemp(), "whitespace_test.md")

        content = "   \n\t\n   \n"

        # Write test file
        with open(test_file, 'w', encoding='utf-8') as f:
            f.write(content)

        try:
            apply_preprocess(test_file)

            # Read processed file
            with open(test_file, 'r', encoding='utf-8') as f:
                result = f.read()

            self.assertIsInstance(result, str)
        finally:
            # Clean up
            os.unlink(test_file)
            os.rmdir(os.path.dirname(test_file))

    def test_mixed_line_endings(self):
        """Test content with mixed line endings."""
        test_file = os.path.join(tempfile.mkdtemp(), "line_endings_test.md")

        content = "  line1\r\n  \n  line2\r\n"

        # Write test file
        with open(test_file, 'w', encoding='utf-8') as f:
            f.write(content)

        try:
            apply_preprocess(test_file)

            # Read processed file
            with open(test_file, 'r', encoding='utf-8') as f:
                result = f.read()

            self.assertIsInstance(result, str)
        finally:
            # Clean up
            os.unlink(test_file)
            os.rmdir(os.path.dirname(test_file))

    def test_unicode_edge_cases(self):
        """Test unicode edge cases."""
        test_file = os.path.join(tempfile.mkdtemp(), "unicode_test.md")

        content = (
            "    normal content\n"
            "    \n"
            "    \u200b\u200c\u200d invisible chars\n"  # Zero-width characters
            "    \n"
            "    \u202e RTL override\n"  # Right-to-left override
        )

        # Write test file
        with open(test_file, 'w', encoding='utf-8') as f:
            f.write(content)

        try:
            apply_preprocess(test_file)

            # Read processed file
            with open(test_file, 'r', encoding='utf-8') as f:
                result = f.read()

            self.assertIsInstance(result, str)
            self.assertIn("invisible chars", result)
        finally:
            # Clean up
            os.unlink(test_file)
            os.rmdir(os.path.dirname(test_file))


class TestApplyPreprocess(unittest.TestCase):
    """Test cases for apply_preprocess function directly."""

    def test_basic_preprocessing(self):
        """Test basic preprocessing functionality."""
        test_file = os.path.join(tempfile.mkdtemp(), "basic_test.md")

        content = "  line1\n\n  line2\n"

        # Write test file
        with open(test_file, 'w', encoding='utf-8') as f:
            f.write(content)

        try:
            apply_preprocess(test_file)

            # Read processed file
            with open(test_file, 'r', encoding='utf-8') as f:
                result = f.read()

            # Should add newline at end and potentially fix indentation
            self.assertTrue(result.endswith('\n'))
        finally:
            # Clean up
            os.unlink(test_file)
            os.rmdir(os.path.dirname(test_file))

    def test_empty_content(self):
        """Test preprocessing with empty content."""
        test_file = os.path.join(tempfile.mkdtemp(), "empty_test.md")

        # Write empty file
        with open(test_file, 'w', encoding='utf-8') as f:
            f.write("")

        try:
            apply_preprocess(test_file)

            # Read processed file
            with open(test_file, 'r', encoding='utf-8') as f:
                result = f.read()

            self.assertEqual(result, "")
        finally:
            # Clean up
            os.unlink(test_file)
            os.rmdir(os.path.dirname(test_file))

    def test_content_with_skip_blocks(self):
        """Test preprocessing preserves skip blocks."""
        test_file = os.path.join(tempfile.mkdtemp(), "skip_test.md")

        content = (
            "  a\n"
            "<!-- scripts.linter.preprocess.fix_details off -->\n"
            "\n"
            "<!-- scripts.linter.preprocess.fix_details on -->\n"
            " b\n"
        )

        # Write test file
        with open(test_file, 'w', encoding='utf-8') as f:
            f.write(content)

        try:
            apply_preprocess(test_file)

            # Read processed file
            with open(test_file, 'r', encoding='utf-8') as f:
                result = f.read()

            self.assertIn(
                "<!-- scripts.linter.preprocess.fix_details off -->", result)
            self.assertIn(
                "<!-- scripts.linter.preprocess.fix_details on -->", result)
        finally:
            # Clean up
            os.unlink(test_file)
            os.rmdir(os.path.dirname(test_file))


if __name__ == "__main__":
    unittest.main()