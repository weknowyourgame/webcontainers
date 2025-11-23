# Virtual Filesystem

A virtual filesystem implementation that runs entirely in the browser using WebAssembly. This project demonstrates how to build a filesystem in C++ and expose it to JavaScript through Emscripten.

## Overview

This project implements a simple in-memory filesystem with directory and file operations. The filesystem logic is written in C++ and compiled to WebAssembly, allowing it to run efficiently in web browsers. The user interface is a terminal-style command line that runs in the browser.

## Features

- Create directories with `mkdir`
- Create files with `touch`
- List directory contents with `ls`
- Move directories with `mv`
- Echo text with `echo`
- In-memory filesystem that persists during the browser session

## Architecture

The project consists of three main components:

1. **C++ Filesystem Core** (`fs.h`, `fs.cpp`): Implements the virtual filesystem with a tree structure of directories and files
2. **WASM Bridge** (`main.cpp`): Exposes C++ functions to JavaScript using Emscripten bindings
3. **Web Interface** (`index.html`, `app.js`): Terminal-style UI that parses commands and calls WASM functions

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

Move a directory from one location to another.

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
