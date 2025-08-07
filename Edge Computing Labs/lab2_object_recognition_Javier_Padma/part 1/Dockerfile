# Use an official Ubuntu base image
FROM ubuntu:latest

# Prevent interactive prompts
ARG DEBIAN_FRONTEND=noninteractive

# Install dependencies
RUN apt-get update && apt-get install -y \
	htop \
	procps \
	bash \
	&& rm -rf /var/lib/apt/lists/*

#Create a working directory
WORKDIR/data

#Default command
CMD ["/bin/bash"]
