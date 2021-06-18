
 j=1
   for (( j; j<11; j=j+1 ))
   do
        echo $j
        ./PPSO 30 200 10 $j 200000 >> CEC_2021/10D/PPSO_CEC_${j}.txt
   done