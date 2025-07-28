# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

**OI Wiki** is a comprehensive Chinese programming competition knowledge wiki built with MkDocs. It serves as a collaborative educational resource for competitive programming (OI/ACM-ICPC) covering algorithms, data structures, mathematics, and programming techniques.

## Architecture & Structure

### Documentation Structure
- **docs/**: Main documentation content organized by topics:
  - `basic/`: Fundamental algorithms and complexity
  - `graph/`: Graph theory and algorithms
  - `dp/`: Dynamic programming techniques
  - `ds/`: Data structures
  - `math/`: Mathematics for competitive programming
  - `string/`: String algorithms
  - `geometry/`: Computational geometry
  - `search/`: Search algorithms
  - `lang/`: Programming language tutorials (C++, Python, Java)
  - `tools/`: Development tools and environments
  - `contest/`: Competition-specific knowledge
  - `misc/`: Miscellaneous algorithms and techniques

### Build System
- **MkDocs** with custom Material theme (in `mkdocs-material/`)
- **Python dependencies**: Managed via uv (`pyproject.toml`)
- **Node.js dependencies**: Managed via Yarn (`package.json`)
- **Build pipeline**: Multi-stage process with pre/post build scripts

## Development Commands

### Local Development
```bash
# Install dependencies
uv sync --index-url https://pypi.tuna.tsinghua.edu.cn/simple/
yarn install

# Install theme and assets
./scripts/pre-build/install-theme.sh

# Start local development server
uv run mkdocs serve -v

# Build static site
uv run mkdocs build -v
```

### Code Quality & Checking
```bash
# Check documentation formatting
yarn run docs:format:check

# Format documentation
yarn run docs:format:remark

# TypeScript code formatting
yarn run scripts:format
yarn run scripts:format:check

# Run comprehensive markdown checks
node --loader ts-node/esm scripts/checker/checker.ts

# Check for problematic characters
python3 scripts/check-characters.py
```

### Production Build
```bash
# Full production build (used in CI/CD)
scripts/netlify/build.sh
```

## File Types & Conventions

### Documentation Files
- **Markdown**: `.md` files with MkDocs extensions
- **Images**: `.png`, `.svg`, `.jpg` in `images/` subdirectories
- **Code examples**: Inline code blocks and separate files in `code/` dirs
- **Configuration**: YAML frontmatter in markdown files

### Build Configuration
- **mkdocs.yml**: Main MkDocs configuration
- **pyproject.toml**: Python dependencies
- **package.json**: Node.js dependencies and scripts
- **netlify.toml**: Netlify deployment configuration

### Scripts & Automation
- **TypeScript**: Build and quality checking scripts in `scripts/`
- **Python**: Utility scripts for content validation
- **Bash**: Build and deployment scripts

## Key Development Workflows

### Content Contribution
1. Edit/add `.md` files in appropriate `docs/` subdirectories
2. Add images to corresponding `images/` directories
3. Run format checking: `yarn run docs:format:check`
4. Test locally: `uv run mkdocs serve`
5. Build and verify: `uv run mkdocs build`

### Adding New Topics
1. Create new `.md` file in appropriate directory
2. Add to `mkdocs.yml` navigation structure
3. Include code examples in `code/` subdirectory if needed
4. Add supporting images in `images/` subdirectory
5. Follow existing formatting conventions

### Code Quality Checks
- **Markdown linting**: Uses remark with custom rules
- **Character validation**: Checks for problematic Unicode characters
- **Link validation**: Verifies internal/external links
- **Math rendering**: Validates LaTeX math expressions

## Environment Setup

### Requirements
- **Python**: 3.10+ (via uv)
- **Node.js**: 20+ (via Yarn)
- **Git**: For submodule management

### Development Environment
```bash
# Clone with submodules
git clone https://github.com/OI-wiki/OI-wiki.git --depth=1
cd OI-wiki

# Install Python dependencies
uv sync

# Install Node.js dependencies
yarn install

# Install theme assets
./scripts/pre-build/install-theme.sh
```

## Common Issues & Solutions

### Build Failures
- **Missing dependencies**: Ensure both `uv sync` and `yarn install` complete successfully
- **Theme issues**: Run `./scripts/pre-build/install-theme.sh` to reinstall theme assets
- **Python version**: Use Python 3.10+ as specified in pyproject.toml

### Content Issues
- **Broken links**: Run link validation checks
- **Math rendering**: Check LaTeX syntax in mathematical content
- **Image paths**: Ensure images are in correct `images/` subdirectories

### Performance
- **Large builds**: Use incremental builds during development (`mkdocs serve`)
- **Memory issues**: Increase Node.js memory limit if needed (`NODE_OPTIONS="--max_old_space_size=3072"`)

## CI/CD Pipeline

### GitHub Actions Workflows
The project uses comprehensive GitHub Actions for continuous integration and deployment:

#### Main Build Workflow (`build.yml`)
- **Triggers**: Push to master, PR to master, manual dispatch
- **Environment**: Ubuntu-latest, Python 3.10, Node.js 20
- **Steps**:
  1. Install Python dependencies via uv
  2. Install Node.js dependencies via yarn
  3. Pre-build setup (theme installation)
  4. MkDocs build with verbose output
  5. HTML post-processing (commits info, math rendering, external links)
  6. HTML minification
  7. Redirect generation
  8. Link validation (internal links only)
  9. Deploy to gh-pages (on push events)
  10. Baidu search submission (production only)

#### Code Quality Workflows
- **Format checking** (`check-format.yml`): Markdown formatting, C++ code formatting
- **Code testing** (`test.yml`): C++ code compilation and correctness testing
- **Character validation** (`check-characters.yml`): Unicode character checks
- **Quote validation** (`check-quotes.yml`): Chinese punctuation validation
- **Script validation** (`check-scripts.yml`): TypeScript formatting and linting

#### Specialized Builds
- **PDF generation** (`build-pdf.yml`): LaTeX-based PDF builds using xelatex
- **Typst PDF** (`build-pdf-typst.yml`): Modern PDF generation with Typst
- **Author cache** (`build-authors-cache.yml`): Contributor statistics caching

#### Cross-Platform Testing
The test workflow runs C++ code validation across multiple platforms:
- Ubuntu (x86_64)
- macOS (ARM64)
- Windows (x86_64)
- Alpine Linux (x86_64)
- RISC-V Ubuntu (via Docker)

### Pre-commit Checks
Before pushing changes, ensure:
```bash
# Format checking
yarn docs:format:check -a

# Code compilation (if adding C++ examples)
python3 scripts/correctness_check.py

# Character validation
python3 scripts/check-characters.py

# Link validation (local)
node --loader ts-node/esm scripts/checker/checker.ts
```

### Deployment Strategy
- **Production**: Automatic deployment from master branch to GitHub Pages
- **Preview**: Netlify builds for PR previews
- **Mirror**: Automatic sync to Gitee (Chinese mirror)
- **CDN**: Multi-region deployment with status monitoring

### Environment Variables
Key environment variables used in CI/CD:
- `GITHUB_TOKEN`: GitHub API access
- `BAIDU_TOKEN`: Chinese search engine submission
- `NODE_OPTIONS="--max_old_space_size=3072"`: Memory optimization
- `PYTHONIOENCODING=UTF-8`: UTF-8 encoding for Python scripts

## Testing Content

### Local Testing
- Use `mkdocs serve` for live reloading during development
- Test on multiple browsers for MathJax compatibility
- Verify responsive design on mobile devices

### Link Validation
- Check internal links between documents
- Verify external links are accessible
- Test anchor links within documents

### Content Quality
- Follow established markdown formatting conventions
- Ensure mathematical notation renders correctly
- Verify code examples compile and run as expected

### Cross-Platform Compatibility
- Test C++ code examples on different compilers (GCC, Clang, MSVC)
- Validate UTF-8 encoding across platforms
- Check LaTeX math rendering in different environments