#!/bin/bash

for ((a=9003; a <= 9004 ; a++))
do
   python server.py $a &
   python client.py localhost $a A5.sh -mode CUI >> results/out1_$a.txt &	
   python client.py localhost $a A5.sh -mode CUI >> results/out2_$a.txt &

wait

done
