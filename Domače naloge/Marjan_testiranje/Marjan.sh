#####################################
			VERSION="Testiranje"
#####################################

#./Marjan.sh {ime_datoteke} {ime_datoteke2} {število testov}

#####################################

#!/bin/bash

# Definicija ANSI escape sekvenc za barvanje teksta - bold
green='\e[1;92m'
red='\e[1;91m'
blue='\e[1;94m'
purple='\e[1;95m'
yellow='\e[1;93m'
white='\e[1;97m'
reset='\e[0m'

# Preveri, če je podanih dovolj argumentov (ime programa)
if [ "$#" -lt 2 ]; then
  echo "Uporaba: $0 <ime_programa1> <ime_programa2> <št. testov>"
  exit 1
fi

# Argumenti
program="$1"
program2="$2"
test_num="$3"

# Čas za timeout
to=2.0

echo -e "${yellow}---------------------------------------------"
echo "		VERSION == ${VERSION}"
echo -e "---------------------------------------------${reset}"

echo -e "${white}Timelimit = ${to}s${reset}"
echo -e "${white}Število testov = ${test_num}${reset}"
echo ""

g++ "${program}.cpp" -o ${program} -std=c++20 -pedantic -Wall
g++ "${program2}.cpp" -o ${program2} -std=c++20 -pedantic -Wall
g++ generator.cpp -o generator -std=c++20 -pedantic -Wall
# Vsi testi
test_count=0

# napačni testi
wrong_tests=0



# funkcija ob koncu izvajanja
izpisi_rezultate() {
	# Izpiši število pravilnih testov na koncu
	echo -e "${white}---------------"
	echo "Število testov: $test_count"
	
	echo -e ${reset}
	rm "${program}"
	rm "${program2}"
	rm generator
	exit 1
}

# Prekinitev programa
trap izpisi_rezultate SIGINT

# Testiranje
testing() {
	echo ""
	echo -e "${blue}Testiranje programa ${program} in ${program2}...${reset}"
	for ((i = 1; i <= test_num; i++))
	do
	  # na vsake 100 testov izpiši i
	  if [ $((test_count % 100)) -eq 0 ]; then
	  	echo -e "${white}Test $test_count${reset}"
	  fi
	  ./generator > test0.in

	  input_file="test0.in"
	  output_file_rez="test0.out"
	  output_file_temp="test0.res"
	  output_file_diff="test0.diff"
	  
	  if [ -f $output_file_temp ]; then
		rm $output_file_temp
	  fi
	  if [ -f $output_file_rez ]; then
	  	rm $output_file_rez
	  fi
	  
	  # Uporaba timeout za omejitev časovnega limita na 2 sekundi
	  timeout $to ./$program < $input_file > $output_file_rez 2> /dev/null
	  timeout $to ./$program2 < $input_file > $output_file_temp 2> /dev/null	  

	  
	  diff -w $output_file_temp $output_file_rez > $output_file_diff
		rezultat=$?
		if [ $rezultat -ne 0 ]; then
		  # rename input file
			preimenuj=$((preimenuj + 1))
			mv $input_file "test${preimenuj}.in"
			echo -e "Test $preimenuj: ${red}WRONG ANSWER${reset}"
		else
			rm $input_file
			rm $output_file_rez
	  	    rm $output_file_temp	
		fi

	  rm $output_file_diff	  
	  
	  test_count=$((test_count + 1))
	done
}

testing
izpisi_rezultate
