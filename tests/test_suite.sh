#!/bin/sh

clean_tmp_files()
{
    rm outut
    rm input
}

CURRENT_DIR=$PWD
TARGET_DIR=$(dirname "$0")
echo $TARGET_DIR

cd $TARGET_DIR

BIN_FILE=$1

python3 -m venv env

cd env
. bin/activate
cd ..

pip install -r requirement.txt

python3.7 test_suite.py $BIN_FILE

clean_tmp_files

cd $CURRENT_DIR
