import unittest
import os
from unittest.mock import patch, mock_open
from scripts.linter.common import index_lfirst_neq, log, step, pipeline, TAB_LENGTH


class TestIndexLfirstNeq(unittest.TestCase):
    def test_first_element(self):
        self.assertEqual(index_lfirst_neq([2, 1, 1], 1), 0)

    def test_middle_element(self):
        self.assertEqual(index_lfirst_neq([1, 2, 1], 1), 1)

    def test_no_different_elements(self):
        with self.assertRaises(StopIteration):
            index_lfirst_neq([1, 1, 1], 1)

    def test_empty_list(self):
        with self.assertRaises(StopIteration):
            index_lfirst_neq([], 1)

    def test_tuple(self):
        self.assertEqual(index_lfirst_neq((1, 2, 1), 1), 1)


class TestLog(unittest.TestCase):
    @patch('builtins.print')
    def test_with_debug_env(self, mock_print):
        with patch.dict(os.environ, {'RUNNER_DEBUG': 'true'}):
            log("test message")
            mock_print.assert_called_once_with("::debug::test message")

    @patch('builtins.print')
    def test_without_debug_env(self, mock_print):
        with patch.dict(os.environ, {}, clear=True):
            log("test message")
            mock_print.assert_not_called()


class TestStep(unittest.TestCase):
    def test_empty_content(self):
        @step
        def dummy(content, **kwargs):
            return content
        self.assertEqual(dummy(""), "")

    def test_no_skip_blocks(self):
        @step
        def dummy(content, **kwargs):
            return content
        content = "test\ncontent"
        self.assertEqual(dummy(content), content + "\n")

    def test_with_skip_block(self):
        @step
        def dummy(content, **kwargs):
            return content
        content = (
            "before\n"
            f"<!-- {self.__module__}.dummy on -->\n"
            "skip this\n"
            f"<!-- {self.__module__}.dummy off -->\n"
            "after"
        )
        result = dummy(content)
        expected = (
            "before\n"
            "<!-- test.linter.test_common.dummy on -->\n"
            "skip this\n"
            "<!-- test.linter.test_common.dummy off -->\n"
            "after\n"
        )
        self.assertEqual(result, expected)

    def test_unclosed_skip_block(self):
        @step
        def dummy(content, **kwargs):
            return content
        content = (
            "before\n"
            f"<!-- {self.__module__}.dummy on -->\n"
            "skip this\n"
        )
        with self.assertRaises(RuntimeError):
            dummy(content)

    def test_tab_replacement(self):
        @step
        def dummy(content, **kwargs):
            return content
        content = "line\twith\ttabs\n"
        expected = "line{}with{}tabs\n".format(' '*TAB_LENGTH, ' '*TAB_LENGTH)
        result = dummy(content)
        self.assertEqual(result, expected)


class TestPipeline(unittest.TestCase):
    @patch('builtins.open', new_callable=mock_open, read_data="old content")
    def test_no_changes(self, mock_file):
        @pipeline
        def dummy(content):
            return content

        dummy("test.txt")
        mock_file().write.assert_not_called()

    @patch('builtins.open', new_callable=mock_open, read_data="old content")
    def test_with_changes(self, mock_file):
        @pipeline
        def dummy(content):
            return "new content"

        dummy("test.txt")
        mock_file().write.assert_called_once_with("new content")


if __name__ == '__main__':
    unittest.main()
