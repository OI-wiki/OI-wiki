# OI-wiki Linter Patch System

This directory contains the linter patch system for OI-wiki, which provides preprocessing and postprocessing capabilities for Markdown files to ensure consistent formatting and style.

## Overview

The linter system consists of several components:

- **`utils.py`**: Core utilities
- **`decorators.py`**: Decorators for the linter pipeline
- **`preprocess.py`**: Preprocessing functions for fixing Markdown formatting issues
- **`postprocess.py`**: Postprocessing functions for fixing Markdown formatting issues
- **`linter_patch.py`**: Main entry point script that orchestrates the linting process

## Architecture

### Pipeline System

The linter uses a decorator-based pipeline system:

1. **`@step` decorator**: Handles skip blocks and line origin tracking
2. **`@pipeline` decorator**: Manages file I/O operations and change detection

### Skip Block System

The linter supports skip blocks to exclude certain sections from processing:

```markdown
<!-- scripts.linter.(preprocess|postprocess).function_name off -->
Content that should be skipped during linting
<!-- scripts.linter.(preprocess|postprocess).function_name on -->
```

## Components

### utils.py

Core utilities:

- **`log()`**: Debug logging function that respects `RUNNER_DEBUG` environment variable and uses GitHub Actions [workflow commands](https://docs.github.com/en/actions/reference/workflows-and-actions/workflow-commands)
- **`index_lfirst_neq()`**: Utility to find first non-equal element in an iterable

### decorators.py

Decorators:

- **`@step` decorator**: Processes content while handling skip blocks and tracking line origins
- **`@pipeline` decorator**: Wraps functions to handle file operations

### preprocess.py

Preprocessing functions:

- **`fix_details()`**: Fixes indentation issues in Markdown content
  - Corrects inconsistent indentation in nested structures
  - Preserves blank line indentation based on surrounding content
  - Uses bidirectional scanning to determine proper indentation levels

### postprocess.py

Postprocessing functions:

- **`fix_full_stop()`**: Fixes full stop issues in Markdown content

## Usage

### Command Line Interface

The main script `linter_patch.py` provides a command-line interface:

```bash
python scripts/linter_patch.py [directory] -m [mode] [-f files...]
```

**Arguments:**
- `directory`: Directory to process recursively (optional)
- `-m, --mode`: Processing mode (`pre` for preprocessing, `post` for postprocessing)
- `-f, --files`: Specific files to process (optional)

**Examples:**
```bash
# Process all Markdown files in docs directory with preprocessing
python scripts/linter_patch.py ./docs -m pre

# Process specific files
python scripts/linter_patch.py -f file1.md file2.md -m pre

# Process with postprocessing
python scripts/linter_patch.py ./docs -m post
```

### Integration

The linter can be integrated into build processes or used as a standalone tool. It respects the `.remarkignore` file to exclude certain files from processing.

## Configuration

### Environment Variables

- **`RUNNER_DEBUG`**: When set to `1`, enables detailed debug logging output. This follows GitHub Actions' default debug logging environment variable as described in the [GitHub Actions documentation](https://docs.github.com/en/actions/how-tos/monitor-workflows/enable-debug-logging).

### Files

- **`.remarkignore`**: Contains list of files to ignore during processing (one filename per line)

## Development

### Adding New Processors

1. Create a new function in the appropriate module (`preprocess.py` or `postprocess.py`)
2. Apply the `@step` decorator to handle skip blocks
3. Add the function to the appropriate mode in `linter_patch.py`

### Debugging

Enable debug mode by setting the `RUNNER_DEBUG` environment variable:

```bash
export RUNNER_DEBUG=1
python scripts/linter_patch.py ./docs -m pre
```

This will provide detailed logging about:
- File processing status
- Skip block handling
- Indentation changes
- Line-by-line processing information

The logging system uses GitHub Actions workflow commands (see [GitHub Actions workflow commands documentation](https://docs.github.com/en/actions/reference/workflows-and-actions/workflow-commands)) for structured output that integrates well with GitHub Actions CI/CD pipelines.

## Error Handling

The system includes comprehensive error handling:

- **Unclosed skip blocks**: Raises `RuntimeError` with location information
- **File I/O errors**: Handled gracefully with appropriate logging
- **Invalid arguments**: Provides helpful usage information
