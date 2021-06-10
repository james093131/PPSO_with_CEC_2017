
 j=1
   for (( j; j<2; j=j+1 ))
   do
        echo $j
     #    ./PPSO 30 300 50 $j 500000 >> CEC_2017/50D/PPSO_CEC_${j}.txt
     mkdir /home/ailab/Downloads/PPSO_with_CEC_2017/Record_RESULT/50D/$j
     ./PPSO 1 300 50 $j 500000 0.0 >> CEC_2017/50D/PPSO_CEC_${j}.txt
   done