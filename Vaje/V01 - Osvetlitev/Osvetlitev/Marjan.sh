#####################################

#./Marjan.sh {ime_datoteke} {št. testov} {0/1}
# Če imaš rešitve ("test.out") potem je 1, drugače je 0

#####################################

#!/bin/bash

# Preveri, če sta podana dva argumenta (ime programa in število testov)
if [ "$#" -ne 3 ]; then
  echo "Uporaba: $0 <ime_programa> <število_testov> <out_resitve(NE - 0, DA - 1)"
  exit 1
fi

# Argumenta
program="$1"
test_count="$2"
out_resitve="$3"

# Definicija ANSI escape sekvenc za barvanje teksta
green='\033[0;32m'
red='\033[0;31m'
reset='\033[0m'

g++ "${program}.cpp" -o ${program} -std=c++20 -pedantic -Wall

# Ime izhodne datoteke za rezultate
output_file="results.res"

# Spremenljivka za sledenje pravilnih testov
correct_tests=0

# Brisanje prejšnih rezultatov
if [ -f "results.res" ]; then
    rm results.res
fi

# Zanka za izvajanje testov
for ((i = 1; i <= test_count; i++))
do
  # Generiranje imena vhodne datoteke s vodilnimi ničlami
  input_number=$(printf "%02d" $i)
  input_file="test$input_number.in"
  output_file_rez="test$input_number.out"
  output_file_temp="test$input_number.res"
  output_file_diff="test$input_number.diff"
  rezultat=""
  razlika=0

  # Preusmeritev vhodnega testa v program in shranjevanje izhoda
  ./$program < $input_file >> $output_file_temp

  if [ $out_resitve -eq 1 ]; then
    # Primerjava izhoda programa z želenim izhodom
    diff -w $output_file_temp $output_file_rez > $output_file_diff
    if [ $? -eq 0 ]; then
      rezultat="PASSED"
      correct_tests=$((correct_tests + 1))
      echo -e "Test $i: ${green}PASSED${reset}"
      #počisti diff datoteko
      rm $output_file_diff
    else
      rezultat="FAILED"
      razlika=1
      echo -e "Test $i: ${red}FAILED${reset}"
    fi
  fi
  
  # Dodajanje rezultata programa v izhodno datoteko
  echo "Test $i:  $rezultat" >> $output_file
  cat $output_file_temp >> $output_file
  if [ $razlika -eq 1 ]; then
  	cat $output_file_diff >> $output_file
  	razlika=0
  fi
  echo "" >> $output_file
  # Počisti začasno izhodno datoteko
  rm $output_file_temp
done

# Izpiši število pravilnih testov na koncu
echo "---------------"
if [ $out_resitve -eq 1 ]; then
  echo "Rezultat: $correct_tests/$test_count"
else
  echo "Število opravljenih testov: $test_count"
fi

