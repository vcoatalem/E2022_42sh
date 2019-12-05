#!/bin/sh

TEST_AMOUNT=30

ORANGE='\033[0;33m'
GREEN='\033[0;32m'
ITALIC='\033[3m'
NC='\033[0m'

OUT=out
ERR=err

clean_temp_files()
{
    rm -rf $OUT
    rm -rf $ERR
}

run_test()
{
    TEST_BIN=$1
    Q_COUNT=$2
    clean_temp_files
    ERROR=0
    $TEST_BIN $Q_COUNT 1> $OUT 2> $ERR; RETURN=$?
    [ $RETURN -ne 0 ] && ERROR=1
    [ $ERROR -eq 0 ] && echo -e "$GREEN OK:  $(cat "$OUT")  $NC"
    [ $ERROR -eq 1 ] && cat "$ERR" && echo -e "$ORANGE KO ! $(cat "$OUT") $NC"
    clean_temp_files
}

CURRENT_DIR=$PWD

TEST_DIR=tmp/
mkdir $TEST_DIR 2>/dev/null
cd $TEST_DIR

TEST=$1

for i in $(seq 0 1 $TEST_AMOUNT); do
    run_test $TEST $i
done

cd $CURRENT_DIR
rm -rf $TEST_DIR
