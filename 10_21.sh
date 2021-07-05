
 j=1
 i=1
for (( i; i<9; i=i+1 ))
do   
     for (( j; j<11; j=j+1 ))
     do
          echo $i $j
          ./PPSO_17 51 200 10 $j $i 200000 >> 10D/PPSO_CEC_${j}_${i}.txt
     done
     j=1
done


