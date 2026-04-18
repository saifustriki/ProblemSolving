# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

A C benchmarking simulator comparing 5 sorting algorithms (selection, bubble, insertion, Shell, quicksort) across varying input sizes (up to 10M+ elements). Measures execution time for three input cases: random, sorted, and reverse-sorted arrays.

Deliverable: source code + `rapport.md` (max 10 pages, later converted to PDF) covering algorithm analysis, code, machine specs, and generated curves.

## Build & Run

Once a Makefile exists:
```bash
make          # build
make run      # run benchmarks
make clean    # clean binaries
```

Manual compile:
```bash
gcc -O2 -o sort_bench main.c sorting.c -lm
./sort_bench
```

## Architecture

The project is C-only. Expected structure once implemented:

- `main.c` — benchmark loop: iterate over N values, fill arrays (random/sorted/reversed), time each algorithm, print/export results
- `sorting.c` / `sorting.h` — implementations of all 5 sort algorithms
- `rapport.md` — written report (French), includes code snippets, timing curves, and machine configuration

## Key Implementation Notes

- Use `clock()` or `gettimeofday()` / `clock_gettime(CLOCK_MONOTONIC)` for timing (prefer `clock_gettime` for better resolution at large N)
- Each sort must operate on a **fresh copy** of the input array to avoid measuring already-sorted data for subsequent algorithms
- For N up to 10M+, O(n²) algorithms (bubble, selection, insertion) will be very slow — consider skipping them past a threshold or running with a timeout
- Shell sort gap sequence matters for performance; document the chosen sequence in the report
- Output format: CSV or space-separated rows `N,algo,case,time_ms` makes curve generation easy (e.g., with gnuplot or Python matplotlib)
