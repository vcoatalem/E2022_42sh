#!/bin/sh


ORANGE='\033[0;33m'
GREEN='\033[0;32m'
ITALIC='\033[3m'
NC='\033[0m'

OUT=out
EXP_OUT=exp_out
ERR=err
EXP_ERR=exp_err
RETURN=0
EXP_RETURN=0


SETUP=$2

OUTPUT_FILE=output
EXP_OUTPUT_FILE=exp_output

CMD_FILE=cmd
TEST_DIR=tmp
BIN_FILE=$PWD/$TEST_DIR/bin

mkdir $TEST_DIR 2>/dev/null

clean_temp_files()
{
    rm -rf $CMD_FILE
    rm -rf $OUT
    rm -rf $EXP_OUT
    rm -rf $ERR
    rm -rf $EXP_ERR
    rm -rf $OUTPUT_FILE
    rm -rf $EXP_OUTPUT_FILE

}

setup()
{
    echo $1
    clean_temp_files
    if [ $SETUP -eq 0 ]; then
        cp "$1" "$BIN_FILE"

        echo "echo \"hello world!\"" >> $CMD_FILE
        echo "cat Makefile" >> $CMD_FILE
        echo "echo \"im in file\" > exp_output" >> $CMD_FILE
        echo "cat < input" >> $CMD_FILE
        echo "echo A | echo B" >> $CMD_FILE
    elif [ $SETUP -eq 1 ]; then
        echo "shopt with no argument" >> $CMD_FILE
        echo "shopt with an incorrect argument" >> $CMD_FILE
        echo "shopt with a correct argument but incorrect value" >> $CMD_FILE
        echo "shopt with a correct argument and correct value" >> $CMD_FILE
        echo "shopt piped into cat" >> $CMD_FILE
        echo "shopt piped into grep" >> $CMD_FILE
    fi
    
    echo "catch me if you can" > input
}

run_test()
{
    Q_COUNT=0
    while IFS= read -r line;
    do
        clean_temp_files
        ERROR=0
        $BIN_FILE $Q_COUNT 1> $OUT 2> $ERR; RETURN=$?
        echo $line | bash 1> $EXP_OUT 2> $EXP_ERR; EXP_RETURN=$?

        #increment q_count for next iteration
        Q_COUNT=$((Q_COUNT + 1))

        # remove all logs from output
        sed -i '/\[.*\]/d' $OUT
        
        #builtins execution do not do output comparison
        if [ $SETUP -ne 1 ]; then
            ERROR_STDOUT=$(diff $EXP_OUT $OUT)                                          
            [ "$ERROR_STDOUT" != "" ] && ERROR=1 && echo "ERROR in STDOUT: $ERROR_STDOUT"
            
            ERROR_STDERR=$(diff $EXP_ERR $ERR)                                          
            [ "$ERROR_STDERR" != "" ] && ERROR=1 && echo "ERROR in STDERR: $ERROR_STDERR"

            [ $EXP_RETURN -ne $RETURN ] && ERROR=1 && echo "ERROR in RETURN: $EXP_RETURN ? $RETURN"
        fi
        LINES_PRINTED=$(cat $OUT | wc -l)
        [ $ERROR -eq 0 ] && echo -e "$GREEN OK:  $line $ITALIC ($LINES_PRINTED lines printed) $NC" && continue
        echo "$ORANGE KO:   $line  $NC"
    done < $CMD_FILE
    clean_temp_files
}

CURRENT_DIR=$PWD


cd $TEST_DIR

setup $1

TEST=$1
run_test

cd $CURRENT_DIR
rm -rf $TEST_DIR
