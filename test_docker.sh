#!/bin/sh

set -e -x

cd "$(dirname "${0}")"

docker build . -t illixr

if [ -z "${shell}" ]
then
	cmd=/app/test.sh
else
	cmd=/bin/bash
fi

docker run -v "${PWD}:/app" -it illixr ${cmd}
