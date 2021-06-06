
 j=27
   for (( j; j<31; j=j+1 ))
   do
        echo $j
        ./PPSO 30 500 100 $j 1000000 >> CEC_2017/100D/PPSO_CEC_${j}.txt
   done