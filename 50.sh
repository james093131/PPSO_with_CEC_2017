
 j=1
   for (( j; j<31; j=j+1 ))
   do
        echo $j
        ./PPSO 30 300 50 $j 500000 >> CEC_2017/50D/PPSO_CEC_${j}.txt
   done