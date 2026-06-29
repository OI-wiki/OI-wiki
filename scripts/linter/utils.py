import os

from typing import Iterable

TAB_LENGTH = 2


def index_lfirst_neq(l: Iterable, value):
    """
    Find the index of the first element in an iterable that is not equal to the given value.

    Args:
        l: The iterable to search
        value: The value to compare against

    Returns:
        int: The index of the first non-equal element

    Raises:
        StopIteration: If no non-equal element is found
    """
    return next(idx for idx, v in enumerate(l) if v != value)


def log(msg, type='debug'):
    """
    Log a message with optional type prefix for GitHub Actions compatibility.

    This function uses GitHub Actions workflow commands for structured logging output.
    The 'type' parameter corresponds to GitHub Actions workflow command types such as:
    - 'debug': Debug messages
    - 'group': Start a collapsible group
    - 'endgroup': End a collapsible group
    - 'error': Error messages
    - 'warning': Warning messages
    - 'notice': Notice messages

    See GitHub Actions workflow commands documentation for more details:
    https://docs.github.com/en/actions/reference/workflows-and-actions/workflow-commands

    Args:
        msg: The message to log
        type: The log type corresponding to GitHub Actions workflow command types
    """
    if type != 'debug' or os.environ.get('RUNNER_DEBUG'):
        print(f"::{type}::{msg}")


class Grouping:
    """Context manager for emitting GitHub Actions foldable groups.

    Use this as a convenience to wrap sections of output in a collapsible
    group for GitHub Actions logs:

        with Grouping('Run linter checks'):
            ...

    By default the group start/end commands are emitted only when the
    ``RUNNER_DEBUG`` environment variable is set. Pass ``enable_only_debug=False``
    to always emit groups regardless of ``RUNNER_DEBUG``.
    """

    def __init__(self, title, enable_only_debug=True) -> None:
        self.__title = title
        self.__enable_only_debug = enable_only_debug

    def __enter__(self):
        if not self.__enable_only_debug or os.environ.get('RUNNER_DEBUG'):
            log(self.__title, 'group')
        return self

    def __exit__(self, exc_type, exc, tb):
        if not self.__enable_only_debug or os.environ.get('RUNNER_DEBUG'):
            log('', 'endgroup')
        return False
