#!/bin/sh

TEST_BIN=$1
AST_FILE_BASENAME=$2

echo $TEST_BIN

TEST_AMOUNT=8

ORANGE='\033[0;33m'
GREEN='\033[0;32m'
ITALIC='\033[3m'
NC='\033[0m'

OUTPUT_DIR=output
ERR_DIR=err

run_test()
{
    TEST_BIN=$1
    Q_COUNT=$2
    OUTPUT_FILE="$OUTPUT_DIR/"$AST_FILE_BASENAME"_$Q_COUNT.dot"
    ERROR=0
    $TEST_BIN $Q_COUNT $OUTPUT_FILE 1>/dev/null 2> $ERR_DIR; RETURN=$?
    [ $RETURN -ne 0 ] && ERROR=1
    [ $ERROR -eq 0 ] && echo -e  "$GREEN TEST #$Q_COUNT: $(cat $ERR_DIR) : OK ! $NC"
    [ $ERROR -eq 1 ] && echo -e "$ORANGE TEST #$Q_COUNT: $(cat $ERR_DIR) : KO ! $NC"
    rm $ERR_DIR
}

mkdir $OUTPUT_DIR 2>/dev/null

TEST=$1

for i in $(seq 0 1 $TEST_AMOUNT); do
    run_test $TEST $i
done

exit 0
