#!/bin/sh

setup_tmp_files()
{
    echo "catch me if you can" > input
}

clean_tmp_files()
{
    rm -rf output
    rm -rf input
}

CURRENT_DIR=$PWD
TARGET_DIR=$(dirname "$0")
cd $TARGET_DIR

BIN_FILE=$1

setup_tmp_files

python3 -m venv env

cd env
. bin/activate
cd ..

pip install -r requirement.txt

python3.7 test_suite.py $BIN_FILE

clean_tmp_files

cd $CURRENT_DIR
