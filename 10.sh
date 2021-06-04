
 j=1
   for (( j; j<31; j=j+1 ))
   do
        echo $j
        ./PPSO 1 200 10 $j 100000 >> CEC_2017/10D/PPSO_CEC_${j}.txt
   done