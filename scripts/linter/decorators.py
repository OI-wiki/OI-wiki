import random

from functools import wraps
from scripts.linter.utils import TAB_LENGTH, index_lfirst_neq, log


def step(func):
    """
    Decorator that processes Markdown content while handling skip blocks.

    Skip blocks allow certain sections to be excluded from processing using HTML comments:
    <!-- scripts.linter.(preprocess|postprocess).function_name off -->
    Content to skip
    <!-- scripts.linter.(preprocess|postprocess).function_name on -->

    Args:
        func: The function to wrap

    Returns:
        The wrapped function that handles skip blocks and line origin tracking
    """
    tag = f"{func.__module__}.{func.__name__}"
    skip_tag_begin = f'<!-- {tag} off -->'
    skip_tag_end = f'<!-- {tag} on -->'
    skip_placeholder = f'<!-- {tag} block {random.randint(0, 2147483647)} -->'

    @wraps(func)
    def inner(md_content: str, **kwargs):
        # Handle empty content
        if not len(md_content):
            log("Empty content provided, returning empty string")
            return ''

        lines = md_content.splitlines()
        removed_blocks = []  # Store skipped content blocks
        line_origins = []    # Track original line numbers
        processed_lines = []  # Store processed content

        skip_counter = 0
        last_skip_index = -1
        current_skip_block = []
        current_skip_block_indent = 0

        log(f"Processing {len(lines)} lines with skip tag '{tag}'")

        # First pass: identify skip blocks and process non-skipped content
        for index, line in enumerate(lines):
            stripped = line.strip()
            if stripped == skip_tag_begin:
                last_skip_index = index
                if skip_counter == 0:
                    current_skip_block_indent = index_lfirst_neq(line, ' ')
                skip_counter += 1
                log(f"line {index+1}: skip begin, level = {skip_counter}")

            if skip_counter == 0:
                # Process line: replace tabs with spaces
                processed_lines.append(line.replace('\t', ' '*TAB_LENGTH))
                line_origins.append(index)
            elif skip_counter > 0:
                # Add to skip block
                current_skip_block.append(line)
            else:
                raise RuntimeError(
                    f"unopened skip block for tag '{tag}' ending at line {last_skip_index+1}. Please ensure all skip blocks are properly opened with '{skip_tag_begin}'"
                )

            if stripped == skip_tag_end:
                last_skip_index = index
                skip_counter -= 1
                log(f"line {index+1}: skip end, level = {skip_counter}")
                if skip_counter == 0:
                    # End of skip block, store it and add placeholder
                    removed_blocks.append(current_skip_block)
                    current_skip_block = []
                    processed_lines.append(
                        ' '*current_skip_block_indent+skip_placeholder)
                    line_origins.append(-1)  # Mark as placeholder

        # Validate skip block structure
        if skip_counter > 0:
            raise RuntimeError(
                f"unclosed skip block for tag '{tag}' starting at line {last_skip_index + 1}. Please ensure all skip blocks are properly closed with '{skip_tag_end}'"
            )
        elif skip_counter < 0:
            raise RuntimeError(
                f"unopened skip block for tag '{tag}' ending at line {last_skip_index + 1}. Please ensure all skip blocks are properly opened with '{skip_tag_begin}'"
            )
        processed_content = '\n'.join(processed_lines)+'\n'

        assert line_origins

        log(f"Processed content: {len(processed_lines)} lines, {len(removed_blocks)} skip blocks")

        # Apply the actual processing function
        log(f"Starting {func.__name__} processing")
        result: str = func(processed_content,
                           line_origins=line_origins, **kwargs)
        log(f"Completed {func.__name__} processing")

        # If no skip blocks, return result directly
        if not removed_blocks:
            log("No skip blocks to restore")
            return result

        # Second pass: restore skip blocks
        log(f"Restoring {len(removed_blocks)} skip blocks")
        processed_lines = []
        lines = result.splitlines()
        current_block_index = 0

        for index, line in enumerate(lines):
            if line.strip() == skip_placeholder:
                # Replace placeholder with original skip block content
                processed_lines.extend(removed_blocks[current_block_index])
                current_block_index += 1
                log(f"Restored skip block {current_block_index}")
            else:
                processed_lines.append(line)

        final_result = '\n'.join(processed_lines)+'\n'
        log(f"Final result: {len(processed_lines)} lines")
        return final_result

    return inner


def pipeline(func):
    """
    Decorator that wraps functions to handle file operations.

    This decorator:
    - Opens and reads the file
    - Applies the processing function
    - Writes back only if content changed
    - Provides logging for file operations

    Args:
        func: The function to wrap (should take md_content as first argument)

    Returns:
        The wrapped function that operates on file paths
    """
    @wraps(func)
    def inner(file: str):
        log(file, type='group')

        old, new = '', ''
        try:
            # Read file content
            with open(file, 'r', encoding='utf-8') as f:
                old = f.read()
                log(f"Read {len(old)} characters from {file}")

            # Apply processing
            new = func(old)
            log(f"Processing completed, result length: {len(new)} characters")

            # Write back if changed
            if old != new:
                with open(file, 'w', encoding='utf-8') as f:
                    f.write(new)
                    log(f"File modified: wrote {len(new)} characters to {file}")
            else:
                log("No changes detected, file not modified")

        except Exception as e:
            log(f"Error processing {file}: {str(e)}", type='error')
            raise

        log('', type='endgroup')

    return inner
