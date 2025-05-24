#!/bin/bash

# Configuration
BUILD_DIR="build"
RESULTS_DIR="results"
PLOTS_DIR="plots"
VENV_DIR="venv"
BINARY_NAME="SortTester"

# Exit on error
set -e

function setup_build() {
    echo "Setting up build environment..."
    if [ ! -d "$BUILD_DIR" ]; then
        mkdir -p "$BUILD_DIR"
    fi

    cd "$BUILD_DIR"
    cmake .. || { echo "CMake configuration failed"; exit 1; }
    make -j$(nproc) || { echo "Build failed"; exit 1; }
    cd ..
}

function run_tests() {
    echo "Running $BINARY_NAME..."
    cd build
    if [ -f $BINARY_NAME ]; then
        time "./$BINARY_NAME" || { echo "Tests failed"; exit 1; }
    else
        echo "Error: Binary $BINARY_NAME not found in $BUILD_DIR/"
        exit 1
    fi
    cd ..
}

function check_results() {
    echo -e "\nTest results:"
    if [ -d "$RESULTS_DIR" ]; then
        find "$RESULTS_DIR" -type f | while read -r file; do
            echo "- ${file#./}"
        done
    else
        echo "Warning: No results directory found"
    fi
}

function setup_python() {
    echo -e "\nSetting up Python environment..."
    if [ ! -d "$VENV_DIR" ]; then
        python3 -m venv "$VENV_DIR"
    fi

    source "$VENV_DIR"/bin/activate
    pip install --upgrade pip > /dev/null
    pip install -r requirements.txt > /dev/null 2>&1
}

function generate_plots() {
    echo "Generating visualization plots..."
    python3 plots.py
    
    echo -e "\nGenerated plots:"
    ls -lh "$PLOTS_DIR" 2>/dev/null || echo "No plots directory found"
    deactivate
}

# Main execution
setup_build
run_tests
check_results
setup_python
generate_plots

echo -e "\nAll tasks completed successfully"