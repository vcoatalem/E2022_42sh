#!/bin/sh

TEST_BIN=$1

echo $TEST_BIN

TEST_AMOUNT=4

ORANGE='\033[0;33m'
GREEN='\033[0;32m'
ITALIC='\033[3m'
NC='\033[0m'

OUTPUT_DIR=output

run_test()
{
    TEST_BIN=$1
    Q_COUNT=$2
    OUTPUT_FILE="$OUTPUT_DIR/ast_$Q_COUNT.dot"
    ERROR=0
    $TEST_BIN $Q_COUNT $OUTPUT_FILE | sed '/[LL PARSER]/d' 2> /dev/null; RETURN=$?
    [ $RETURN -ne 0 ] && ERROR=1
    [ $ERROR -eq 0 ] && echo -e "$GREEN TEST #$Q_COUNT: OK ! $NC"
    [ $ERROR -eq 1 ] && echo -e "$ORANGE TEST #$Q_COUNT: KO ! $NC"
}

mkdir $OUTPUT_DIR 2>/dev/null

TEST=$1

for i in $(seq 0 1 $TEST_AMOUNT); do
    run_test $TEST $i
done

exit 0
