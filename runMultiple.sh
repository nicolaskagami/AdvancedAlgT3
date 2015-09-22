#!/bin/bash

NUM_BATCHES=30
i=1
while [ $i -le $NUM_BATCHES ]
do
    bash buildTests.sh
    bash runTests.sh
    echo "Batch $i done"
    let "i++"
done
