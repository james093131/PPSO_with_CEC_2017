
 j=1
   for (( j; j<31; j=j+1 ))
   do
        echo $j
        mkdir /home/ailab/Downloads/PPSO_with_CEC_2017/Record_RESULT/10D/$j
        ./PPSO 1 200 10 $j 100000 0.3 >> CEC_2017/10D/PPSO_CEC_${j}.txt
   done