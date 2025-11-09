#!/bin/sh

echo "Enter a number:"
read num1
echo "Enter a second number:"
read num2
echo "Enter your choice (1:Add, 2:Subtract, 3:Multiply, 4:Divide):"
read choice

case $choice in
  1) echo "Addition of 2 numbers is: $(echo "$num1 + $num2" | bc)" ;;
  2) echo "Subtraction of 2 numbers is: $(echo "$num1 - $num2" | bc)" ;;
  3) echo "Multiplication of 2 numbers is: $(echo "$num1 * $num2" | bc)" ;;
  4) echo "Division of 2 numbers is: $(echo "scale=2; $num1 / $num2" | bc)" ;;
  *) echo "Invalid choice" ;;
esac

echo "Do you want to create a file directory (y/n)?"
read ch1

if [ "$ch1" = "y" ]; then
  echo "Enter name of directory:"
  read filedir
  mkdir "$filedir"
fi

echo "Do you want to create a subdirectory (y/n)?"
read ch2

if [ "$ch2" = "y" ]; then
  echo "Enter name of subdirectory:"
  read subfiledir
  cd "$filedir" || exit
  mkdir "$subfiledir"
fi

echo "Do you want to create a new file (y/n)?"
read ch3

if [ "$ch3" = "y" ]; then
  echo "Enter name of file:"
  read filename
  cd "$filedir/$subfiledir" || exit
  echo "Enter content (Press Ctrl+D to save):"
  cat > "$filename"
fi

echo "Do you want to create a renamed copy of the file (y/n)?"
read ch4

if [ "$ch4" = "y" ]; then
  echo "Enter name for the copy of file:"
  read filename2
  cd "$filedir/$subfiledir" || exit
  cp "$filename" "$filename2"
fi

echo "Do you want to change the permissions of the file (y/n)?"
read ch5

if [ "$ch5" = "y" ]; then
  cd "$filedir/$subfiledir" || exit
  chmod 744 "$filename"
fi

echo "List of files with their permissions:"
ls -l "$filedir/$subfiledir"
