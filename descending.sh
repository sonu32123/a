#!/bin/bash

# Input array
echo "Enter the elements of the array separated by spaces: "
read -a array  # Read array elements

# Get the length of the array
length=${#array[@]}

# Bubble sort in descending order
for ((i = 0; i < length; i++))
do
    for ((j = 0; j < length - i - 1; j++))
    do
        if [ ${array[j]} -lt ${array[$((j + 1))]} ]; then
            # Swap elements
            temp=${array[j]}
            array[j]=${array[$((j + 1))]}
            array[$((j + 1))]=$temp
        fi
    done
done

# Output the sorted array
echo "Array elements in descending order: ${array[@]}"
