echo "Hello, World!"
ls -la
echo "Enter your name:"
read name
echo "Hello, $name!"

cat file.txt


touch newfile.txt


if [ -f "file.txt" ]; then
  echo "File exists."
else
  echo "File does not exist."
fi


for i in 1 2 3 4 5; do
  echo "Number $i"
done


count=1
while [ $count -le 5 ]; do
  echo "Count: $count"
  count=$((count + 1))
done



a=5
b=10
if (( a < b )); then
  echo "$a is less than $b"
fi



while true; do
  read -p "Enter a number (0 to exit): " num
  if (( num == 0 )); then
    break
  fi
  echo "You entered: $num"
done



grep "Hello" file.txt



sed 's/old-text/new-text/g' file.txt

