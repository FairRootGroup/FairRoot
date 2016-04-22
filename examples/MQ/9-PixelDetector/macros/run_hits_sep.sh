for (( i=0 ; i<$1 ; i++ ))
do
    cp pixel_TGeant3.digi.root pixel_f${i}_TGeant3.digi.root
    rm -f hits_f${i}.dat
done

for (( i=0 ; i<$1 ; i++ ))
do
    echo -n "DATE MARKER" &>> hits_f${i}.dat
    date &>> hits_f${i}.dat
    root -l -q 'run_hits_sep.C('$i')' &>> hits_f${i}.dat &
done

echo "$1 root jobs created"