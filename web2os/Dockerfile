# Step 1: Use an official Ubuntu base image
FROM ubuntu:22.04

# Step 2: Set environment variables to suppress prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Step 3: Install necessary packages and dependencies
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    cmake \
    sqlite3 \
    libsqlite3-dev \
    libssl-dev \
    wget \
    git \
    && apt-get clean

# Step 4: Set the working directory inside the container
WORKDIR /app

# Step 5: Copy all project files from your host machine to the container
COPY . /app

# Step 6: Copy the config.json file into the container
COPY config/config.json /app/config/config.json

# Step 7: Build the project using CMake
RUN mkdir -p build && cd build && \
    cmake .. && \
    make

# Step 8: Expose the port that your application will run on
EXPOSE 8080

# Step 9: Define the command to run your application
CMD ["./build/bin/web2os"]
