#!/bin/bash
set -euxo pipefail

export IMAGE_NAME="tmbasic-linux-x64"
export HOST_UID=$(id -u "$USER")
export HOST_GID=$(id -g "$USER")
export BASE_IMAGE_NAME="alpine:3.12"

cat docker/Dockerfile.build-linux | envsubst | docker build -t $IMAGE_NAME docker -f-

pushd ..
docker run --rm --tty --interactive --volume "$PWD:/code" --workdir /code --name $IMAGE_NAME $IMAGE_NAME
popd
