#!/bin/bash

PROJECT_DIR=$(dirname "$(realpath "$0")")/..
VENV_PATH=${PROJECT_DIR}/analysis/venv/bin/activate

source "$VENV_PATH" && \
python ${PROJECT_DIR}/analysis/parse_res.py && \
python ${PROJECT_DIR}/analysis/graph.py
