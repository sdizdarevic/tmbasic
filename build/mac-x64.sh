#!/bin/bash
set -euo pipefail
scripts/depsDownload.sh
ARCH="x86_64" scripts/macSetup.sh "$@"
