
./PPSO_17 1 300 50 1 0 500000 >> 17_RESULT/50D/PPSO_CEC_1.txt
 i=3
for (( i; i<31; i=i+1 ))
do   
     
     echo $i 
     ./PPSO_17 51 300 50 $i 0 500000 >> 17_RESULT/50D/PPSO_CEC_${i}.txt

done




