# OS Portfolio

This repository contains a set of operating systems assignments implemented mainly in C++, with supporting Python scripts for plotting and a LaTeX report source.

## Repository Layout

- `The-Shell/` - custom shell implementation
- `task2/` - multithreaded word count
- `paging/` - aging page replacement simulation
- `deadlock/` - deadlock detection
- `scheduling/` - CPU scheduling comparison and chart generation
- `filesystem/` - file size histogram and chart generation
- `chat/` - TCP chat system with client and server programs
- `passwords/` - password hashing and verification demo
- `REPORT/latex/TKH_School_of_Computing_Template/` - LaTeX source for the written report
- `venv/` - Python virtual environment used by the plotting scripts
- `setup.sh` - helper script for installing system dependencies in a Linux-based environment

## Requirements

- A C++17-capable compiler
- `g++`
- Python 3
- `matplotlib` for the plotting scripts used by `scheduling/` and `filesystem/`
- OpenSSL development libraries for `passwords/`
- A LaTeX toolchain if you want to build the report (`pdflatex` and `bibtex`)

The repository was developed in a Linux/Codespaces-style environment. If you are using the provided shell environment, `setup.sh` installs the core system packages used by the projects.

## Quick Start

1. Install the required build tools and libraries for your platform.
2. If you want to use the provided Python environment, activate it from the repository root:

	```bash
	source venv/bin/activate
	```

3. Build and run the project you need using the instructions below.

## Projects

### Task 1: Shell

```bash
cd The-Shell
./run.sh main.cpp
```

If you want to compile manually:

```bash
g++ -std=c++17 -w main.cpp -o main
./main
```

The shell also supports file-driven execution when you pass an input file.

### Task 2: Multithreaded Word Count

```bash
cd task2
g++ -std=c++17 -w main.cpp -o main
./main <text_file> <N_threads>
```

The repository includes `test.txt` as a sample input.

### Task 3: Aging Page Replacement

```bash
cd paging
g++ -std=c++17 -w main.cpp -o main
./main <reference_file> [max_frames]
```

### Task 4: Deadlock Detection

```bash
cd deadlock
g++ -std=c++17 -w main.cpp -o main
./main
```

Update `input.txt` before running if you want to test different input data.

### Task 5: CPU Scheduling

```bash
cd scheduling
g++ -std=c++17 -w main.cpp -o main
./main
```

The program reads `processes.txt`, writes `results.csv`, and generates a chart through `plot.py`.

### Task 6: File Size Histogram

```bash
cd filesystem
g++ -std=c++17 -w main.cpp -o main
./main <directory> <bin_width>
```

The program writes `output.csv` and generates a histogram chart through `plot.py`.

### Task 7: Chat System

Compile the server and client separately:

```bash
cd chat
g++ server.cpp -o server -pthread
g++ client.cpp -o client -pthread
```

Run the server first, then start one or more clients in separate terminals:

```bash
./server
./client
```

### Task 8: Password Hashing

```bash
cd passwords
g++ main.cpp -o main -lssl -lcrypto
./main
```

Make sure OpenSSL is installed before compiling this project.

## Report Source

The written report is stored under `REPORT/latex/TKH_School_of_Computing_Template/`.

To build it:

```bash
cd REPORT/latex/TKH_School_of_Computing_Template
pdflatex main.tex
bibtex main
pdflatex main.tex
pdflatex main.tex
```

## Generated Files

Several projects create output files when they run, including CSV summaries and chart images. These are kept in their respective folders for convenience and can be regenerated at any time.