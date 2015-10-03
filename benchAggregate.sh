#!


BENCHMARKS="./Benchmarks"
echo "Func Alg Verts Edges Expanded_Verts Paths" > Bench.dat
for file in ${BENCHMARKS}/*;
do
    FUNC=$(basename $file)
    while read line
    do
        printf "$FUNC " >> Bench.dat
        echo $line >> Bench.dat
    done < $file 
done
