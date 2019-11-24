#!/bin/sh

CURRENT_DIR=$PWD
TARGET_DIR=$(dirname "$0")

cd $TARGET_DIR

BIN_FILE=$1

python3 -m venv env
source env/bin/activate
pip install -r requirement.txt

python3 test_suite.py $BIN_FILE

cd $CURRENT_DIR
