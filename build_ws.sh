#!/bin/bash

# Check if the number of arguments is not equal to 1
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <workspace_path>"
    exit 1
fi

# Install submodules
echo "Installing submodules..."
git submodule update --init --recursive
echo "Submodules installed."

# Get the workspace name from the first argument
project_ws=$1

# Check if the directory exists
if [ -d "$project_ws" ]; then
    echo "Workspace '$project_ws' exists, building it..."
    # Add your build commands here, for example:
    cd "$project_ws"
    rm -rf build
    mkdir build
    cd build
    cmake ..
    make -j4
else
    echo "Workspace '$project_ws' does not exist."
fi
