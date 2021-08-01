cd C:\Users\maxim\source\repos\Main\Debug
for /l %%x in ( 1,1, 100) do (
echo %%x
 generate_array <C:\Users\maxim\Documents\primzahlen1mio.txt  %%x 
Timeout 1
)
cd C:\Users\maxim\Documents\batch_scripts