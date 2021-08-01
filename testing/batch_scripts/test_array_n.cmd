cd C:\Users\maxim\source\repos\Main\Debug
for /l %%x in ( 1,1, 100) do (
echo %%x

generate_array %%x>input.txt

Main<input.txt >out1.txt
BruteForce<input.txt>out2.txt
FC out1.txt out2.txt > 0  && Echo Same ||  goto :myBreak


TIMEOUT /t 1
)

Main<input.txt 
BruteForce<input.txt
cd C:\Users\maxim\Documents\batch_scripts
PAUSE