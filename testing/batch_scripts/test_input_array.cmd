cd C:\Users\maxim\source\repos\Main\Debug
for /l %%x in ( 1,1, 100) do (
echo %%x
 generate_array %%x 
Timeout 1
)
cd C:\Users\maxim\Documents\batch_scripts
