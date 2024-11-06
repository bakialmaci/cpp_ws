# Use an official Ubuntu base image
FROM ubuntu:22.04

# Set environment variables to suppress prompts during package installation
ENV DEBIAN_FRONTEND=noninteractive

# Install necessary packages and dependencies
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    cmake \
    sqlite3 \
    libsqlite3-dev \
    libssl-dev \
    wget \
    git \
    alsa-utils \
    && apt-get clean

# Set the working directory inside the container
WORKDIR /app

# Copy all project files from your host machine to the container
COPY . /app

# Ensure the config and database files are properly copied
RUN mkdir -p /app/config /app/db /app/web
COPY config /app/config
COPY db /app/db
COPY web /app/web

# Build the project using CMake
RUN rm -rf build && mkdir -p build && cd build && \
    cmake .. && \
    make

# Ensure that the executable is built and available
RUN ls -l /app/build/bin

# Expose the port that your application will run on
EXPOSE 8080

# Define the command to run your application
CMD ["./build/bin/web2os"]
