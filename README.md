# WebContainers

<img width="965" height="669" alt="Screenshot from 2025-11-23 14-40-51" src="https://github.com/user-attachments/assets/ea314318-2959-4592-9204-19345f182c93" />

A WebAssembly-based filesystem implementation for WebContainer-like environments. This project builds the core virtual filesystem infrastructure needed to run development tools and code execution directly in the browser.

## Overview

This project implements an in-memory filesystem with directory and file operations, compiled to WebAssembly to power browser-native development environments. It provides the foundational filesystem layer that WebContainer environments depend on to manage files, directories, and project structures entirely on the client side.

The filesystem is exposed through a terminal-style interface, allowing developers to navigate, create, and manipulate file systems in the browser without any backend server involvement.

## Features

- Create and manage directories with `mkdir`
- Create and organize files with `touch`
- Browse filesystem contents with `ls`
- Move directories and files with `mv`
- Echo and output text with `echo`
- In-memory filesystem persisting across browser sessions
- Terminal-style command interface for filesystem operations

## Architecture

The project consists of three main components:

1. **C++ Filesystem Core** (`fs.h`, `fs.cpp`): Implements the virtual filesystem as a tree structure with directories and files, handling all core filesystem operations
2. **WASM Bridge** (`main.cpp`): Exposes C++ functions to JavaScript using Emscripten bindings, enabling seamless JS-to-WebAssembly communication
3. **Web Interface** (`index.html`, `app.js`): Terminal-style UI that parses user commands and invokes WASM functions

## Building

### Prerequisites

- Emscripten SDK (emsdk)
- A C++ compiler (via Emscripten)

### Build Steps

1. Activate the Emscripten environment:
   ```bash
   source emsdk/emsdk_env.sh
   ```

2. Compile the C++ code to WebAssembly:
   ```bash
   chmod +x build.sh
   ./build.sh
   ```
   This generates `main.js` and `main.wasm` files.

3. Start a local web server (required for WASM):
   ```bash
   python3 -m http.server 8000
   ```

4. Open `http://localhost:8000/index.html` in your browser.

## Usage

The interface provides a terminal-style command line. Available commands:

### mkdir
Create a new directory.
```
mkdir /home/test
```

### touch
Create one or more files in a directory.
```
touch /home/test file1.txt file2.txt
```

### ls
List the contents of a directory.
```
ls /home/test
```

### mv
Move a directory or file from one location to another.
```
mv /home/test /tmp/test
```

### echo
Echo text to the output.
```
echo Hello World
```

## License

MIT
