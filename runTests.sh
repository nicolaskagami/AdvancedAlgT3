#!/bin/bash

GENERATION="./Generation"
BENCHMARKS="./Benchmarks"
RESULTFILE="Bench.dat"
TESTS="./Tests"
EXECDIR="./MaxFlow"
VERIF="./Verification/Verif"


for EXEC in EdmondsKarp FordFulkerson;
do
    for file in ${TESTS}/*.gr;
    do
        RESULT=$(${EXECDIR}/${EXEC} < ${file})
        ANSWER=$($VERIF < ${file})
        if [ "$RESULT" = "$ANSWER" ]
        then
            echo "OK: $EXEC: $file"
        else
            echo "Different: $EXEC: $file = $RESULT != $ANSWER"
        fi
    done
done
