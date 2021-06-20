
j=1
i=1
for (( i; i<9; i=i+1 ))
do   
     for (( j; j<11; j=j+1 ))
     do
          echo $i $j
        ./PPSO 30 300 20 $j $i 1000000 >> CEC_2021/20D/PPSO_CEC_${j}.txt
     done
     j=1
done

