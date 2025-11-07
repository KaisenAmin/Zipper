```markdown
# Zipper (C++ + PowerShell)

A tiny CLI tool to **zip** and **unzip** files on Windows by calling PowerShell’s
`Compress-Archive` and `Expand-Archive` from C++.

## Features
- `--zip` / `--unzip`
- Multiple inputs via `--path`
- Output target with `--dest`
- Simple error handling with `std::invalid_argument`

## Build
```bash
g++ -std=c++17 -O2 -o zipper main.cpp
# or use MSVC / CMake as you prefer
```

## Usage

```bash
# Create a zip
zipper --zip   --path src include assets  --dest out.zip

# Extract a zip
zipper --unzip --path out.zip            --dest extracted\
```

> Requires Windows 10+ with PowerShell available on PATH. Uses `system()` to invoke commands.

