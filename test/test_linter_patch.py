"""Integration tests for linter_patch module."""

import os
import tempfile
import unittest

from scripts.linter_patch import apply_preprocess, apply_postprocess


class TestFileOperations(unittest.TestCase):
    """Test file operations and integration scenarios."""

    def setUp(self):
        """Set up test fixtures."""
        self.temp_dir = tempfile.TemporaryDirectory()
        self.temp_path = self.temp_dir.name

    def tearDown(self):
        """Clean up test fixtures."""
        self.temp_dir.cleanup()

    def _create_test_file(self, filename, content):
        """Helper to create a test file and return its path."""
        filepath = os.path.join(self.temp_path, filename)
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(content)
        return filepath

    def _read_file(self, filepath):
        """Helper to read file content."""
        with open(filepath, 'r', encoding='utf-8') as f:
            return f.read()

    def test_preprocess_applies_indentation_fixes(self):
        """Test preprocessing applies indentation fixes correctly."""
        content = "    line1\n\n    line2\n"
        expected = "    line1\n    \n    line2\n"

        filepath = self._create_test_file("test.md", content)
        apply_preprocess(filepath)

        self.assertEqual(self._read_file(filepath), expected)

    def test_postprocess_applies_fullstop_fixes(self):
        """Test postprocessing replaces fullstop correctly."""
        content = "这是一个句子。\n"
        expected = "这是一个句子．\n"

        filepath = self._create_test_file("test.md", content)
        apply_postprocess(filepath)

        self.assertEqual(self._read_file(filepath), expected)

    def test_file_unchanged_when_no_fixes_needed(self):
        """Test that file content remains unchanged when no fixes needed."""
        content = "simple content without issues\n"

        filepath = self._create_test_file("test.md", content)
        apply_postprocess(filepath)

        self.assertEqual(self._read_file(filepath), content)

    def test_file_not_found_raises_error(self):
        """Test error handling for non-existent file."""
        non_existent = os.path.join(self.temp_path, "nonexistent.md")

        with self.assertRaises(FileNotFoundError):
            apply_preprocess(non_existent)

    def test_empty_file_handling(self):
        """Test processing with empty file."""
        filepath = self._create_test_file("empty.md", "")
        apply_preprocess(filepath)

        self.assertEqual(self._read_file(filepath), "")

    def test_skip_blocks_preserved(self):
        """Test that skip blocks are preserved during processing."""
        content = (
            "  a\n"
            "<!-- scripts.linter.preprocess.fix_details off -->\n"
            "  \n"
            "<!-- scripts.linter.preprocess.fix_details on -->\n"
            "  b\n"
        )

        filepath = self._create_test_file("test.md", content)
        apply_preprocess(filepath)

        result = self._read_file(filepath)
        self.assertIn("scripts.linter.preprocess.fix_details off", result)
        self.assertIn("scripts.linter.preprocess.fix_details on", result)

    def test_unicode_content(self):
        """Test processing with unicode content."""
        content = "    中文内容\n\n    更多中文\n"
        expected = "    中文内容\n    \n    更多中文\n"

        filepath = self._create_test_file("test.md", content)
        apply_preprocess(filepath)

        self.assertEqual(self._read_file(filepath), expected)


if __name__ == "__main__":
    unittest.main()