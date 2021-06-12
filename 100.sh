
 j=1
   for (( j; j<31; j=j+1 ))
   do
        echo $j
     mkdir /home/ailab/Downloads/PPSO_with_CEC_2017/Record_RESULT/100D/$j
     ./PPSO 1 500 100 $j 1000000 0.3 >> CEC_2017/100D/PPSO_CEC_${j}.txt
   done