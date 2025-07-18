#!/bin/sh

docker build --platform=linux/amd64 -t ubuntu22-x86_64 .
docker build --platform=linux/arm64 -t ubuntu22-arm64 .
