echo "Enter a number: "
read number

sum=0

while [ $number -gt 0 ]
do
    digit=$(( number % 10 ))   
    sum=$(( sum + digit ))     
    number=$(( number / 10 ))  
done

echo "The sum of the digits is: $sum"


# open command prompt
# sudo apt update
# sudo apt install nano
# nano --version
# nano sum.sh
# write code
# ctrl O - enter - ctrl x
# chmod +x sum.sh
# ./sum.sh
