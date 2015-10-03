#!/bin/bash

GENERATION="./Generation"
TESTS="./Tests"

i=0
NUM_TESTS=5
while [ $i -lt $NUM_TESTS ]
do
    i=$(printf %02d $((10#$i + 1)))
    R=$(bc <<< "scale=0;2^$i+1")
    C=$(bc <<< "scale=0;2^$i")
    N=$(bc <<< "scale=0;$R*$C")
    CAPACITY=$(bc <<< "scale=0;2*$N")
    DEGREE=$(bc <<< "scale=0;2^($i-4) +2")
    $GENERATION/Gen 1 $R $C $CAPACITY $TESTS/mesh_${i}.gr  
    if [ "$?" = "255" ]
    then
        echo -e "\tMesh: i: ${i} Degree: $DEGREE"
    fi
    $GENERATION/Gen 2 $R $C $CAPACITY $TESTS/randomlvl_${i}.gr  
    if [ "$?" = "255" ]
    then
        echo -e "\tRandom Level: i: ${i} Degree: $DEGREE"
    fi
    $GENERATION/Gen 3 $R $C $CAPACITY $TESTS/randomlvl2_${i}.gr  
    if [ "$?" = "255" ]
    then
        echo -e "\tRandom Level 2: i: ${i} Degree: $DEGREE"
    fi
    $GENERATION/Gen 4 $N $DEGREE 1 $TESTS/matching_${i}.gr  
    if [ "$?" = "255" ]
    then
        echo -e "\tMatching: i: ${i} Degree: $DEGREE"
    fi
    $GENERATION/Gen 5 $R $DEGREE $CAPACITY $TESTS/squareMesh_${i}.gr  
    if [ "$?" = "255" ]
    then
        echo -e "\tSquare Mesh: i: ${i} Degree: $DEGREE"
    fi
    $GENERATION/Gen 6 $R $C $DEGREE $TESTS/basicLine_${i}.gr  
    if [ "$?" = "255" ]
    then
        echo -e "\tBasic Line: i: ${i} Degree: $DEGREE"
    fi
    $GENERATION/Gen 7 $R $C $DEGREE $TESTS/expLine_${i}.gr  
    if [ "$?" = "255" ]
    then
        echo -e "\tExp Line: i: ${i} Degree: $DEGREE"
    fi
    $GENERATION/Gen 8 $R $C $DEGREE $TESTS/dExpLine_${i}.gr  
    if [ "$?" = "255" ]
    then
        echo -e "\tDexp Line: i: ${i} Degree: $DEGREE"
    fi
    $GENERATION/Gen 9 $N 1 1 $TESTS/dinicBad_${i}.gr  
    if [ "$?" = "255" ]
    then
        echo -e "\tDinic Bad: i: ${i} Degree: $DEGREE"
    fi
    $GENERATION/Gen 10 $N 2 2 $TESTS/goldBad_${i}.gr  
    if [ "$?" = "255" ]
    then
        echo -e "\tGold Bad: i: ${i} Degree: $DEGREE"
    fi
done
