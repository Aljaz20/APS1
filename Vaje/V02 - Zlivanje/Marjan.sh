#####################################
			VERSION=1.2
#####################################

#./Marjan.sh {ime_datoteke} {št. testov}

#####################################

#!/bin/bash

# Preveri, če sta podana dva argumenta (ime programa in število testov)
if [ "$#" -ne 2 ]; then
  echo "Uporaba: $0 <ime_programa> <število_testov>"
  exit 1
fi

# Definicija ANSI escape sekvenc za barvanje teksta - bold
green='\e[1;92m'
red='\e[1;91m'
blue='\e[1;94m'
purple='\e[1;95m'
yellow='\e[1;93m'
white='\e[1;97m'
reset='\e[0m'

# Čas za timeout
to=2.0


echo -e "${yellow}---------------------------------------------"
echo "		VERSION == ${VERSION}"
echo -e "---------------------------------------------${reset}"

echo -e "${white}Timelimit = ${to}s${reset}"
echo ""

# Argumenti
program="$1"
test_count="$2"

g++ "${program}.cpp" -o ${program} -std=c++20 -pedantic -Wall

# Spremenljivka za sledenje pravilnih testov
correct_tests=0

# Spremenljivka za teste brez rešitev
done_tests=0

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
  
  if [ -f $output_file_temp ]; then
    rm $output_file_temp
  fi
  if [ -f $output_file_diff ]; then
    rm $output_file_diff
  fi
  
  # Uporaba timeout za omejitev časovnega limita na 2 sekundi
  timeout $to ./$program < $input_file > $output_file_temp

  # Preveri, ali je program presegel časovni limit
  if [ $? -eq 124 ]; then
    echo -e "Test $input_number: ${purple}Timeout${reset}"
  else
	if [ -f $output_file_rez ]; then
		# Primerjaj izhod programa s pričakovanim izhodom
		cmp -s $output_file_temp $output_file_rez
      if [ $? -eq 0 ]; then
        correct_tests=$((correct_tests + 1))
        echo -e "Test $input_number: ${green}PASSED${reset}"
      else
        echo -e "Test $input_number: ${red}FAILED${reset}"
      fi
    else
       echo -e "Test $input_number: ${blue}DONE${reset}"
       done_tests=$((done_tests + 1))
	fi
  fi
  
  # Počisti začasno izhodno datoteko
  rm $output_file_temp
done

# Izpiši število pravilnih testov na koncu
echo -e "${white}---------------"
if [ $((test_count -  done_tests)) -ne 0 ]; then
  echo "Rezultat: $correct_tests/$((test_count - done_tests))"
fi
if [ $done_tests -ne 0 ]; then
  echo "Ostali opravljeni testi : $done_tests"
fi

echo -e ${reset}

rm "${program}"
