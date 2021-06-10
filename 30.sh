
 j=1
   for (( j; j<31; j=j+1 ))
   do
        echo $j
        mkdir /home/ailab/Downloads/PPSO_with_CEC_2017/Record_RESULT/30D/$j
        ./PPSO 1 200 30 $j 300000 0.3 >> CEC_2017/30D/PPSO_CEC_${j}.txt
   done