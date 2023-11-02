#####################################
			VERSION=1.5
#####################################

#./Marjan.sh {ime_datoteke} {dodatni_parametri}

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
if [ "$#" -eq 0 ]; then
  echo "Uporaba: $0 <ime_programa> <dodatni_parametri>"
  echo "Dodatni parametri: T={} - timeoutlimit, M={} - measuretime, R={} - range of tests (1- || -4 || 2-5)"
  exit 1
fi

# Argumenti
program="$1"
shift 1

# Čas za timeout
to=2.0

# Izpiši čas
M_time=0
total_time=0

# Testno območje
testi_zacetek=-1
testi_konec=-1
range="ALL"

# Preglej dodatne parametre
while [ $# -gt 0 ]; do
  case "$1" in
    T=*) # Če argument ustreza "T=2" (nastavitev timeout)
      to="${1#T=}"
      ;;
    M=*) # Če argument ustreza "M=1" (nastavitev izpisa posameznih časov)
      M_time="${1#M=}"
      if [ "$M_time" -ne 0 ] && [ "$M_time" -ne 1 ]; then
        echo "Napačna vrednost M. Mora biti 0 ali 1."
        exit 1
      fi 
      ;;
    R=*) # Če argument ustreza "R=1-2" (nastavitev range)
      range="${1#R=}"
      # Preverite, ali obstaja začetek in konec obsega
      if [[ "$range" =~ ^[0-9]+-?[0-9]*$ ]]; then
		testi_zacetek="${range%%-*}"
		testi_konec="${range#*-}"
		if [ -z "$testi_konec" ]; then
			testi_konec=-1
		fi
      elif [[ "$range" =~ ^-[0-9]+$ ]]; then
        testi_konec="${range#-}"
      else
        echo "Napačen format obsega R: $range"
        exit 1
      fi
      ;;
    *)
      # Neveljaven parameter
      echo "Neveljaven parameter: $1"
      exit 1
      ;;
  esac
  shift
done

echo -e "${yellow}---------------------------------------------"
echo "		VERSION == ${VERSION}"
echo -e "---------------------------------------------${reset}"

echo -e "${white}Timelimit = ${to}s${reset}"
echo -e "${white}Measure time = ${M_time}${reset}"
echo -e "${white}Test range = ${range}${reset}"
echo ""

g++ "${program}.cpp" -o ${program} -std=c++20 -pedantic -Wall

# Pravilni testi
correct_tests=0

# Testi brez rešitve
done_tests=0

# Vsi testi
test_count=0

# funkcija ob koncu izvajanja
izpisi_rezultate() {
	# Izpiši število pravilnih testov na koncu
	echo -e "${white}---------------"
	if [ $((test_count -  done_tests)) -ne 0 ]; then
	  echo "Rezultat: $correct_tests/$((test_count - done_tests))"
	fi
	if [ $done_tests -ne 0 ]; then
	  echo "Ostali opravljeni testi : $done_tests"
	fi

	if [[ ${M_time} = 1 ]]; then
	  echo ""
	  averagetime=$(echo "scale=3; (${total_time} / ${test_count})" | bc);
	  if (( $(echo "$averagetime < 1" | bc -l) )); then
		averagetime="0$averagetime"
	  fi
	  averagetime="$averagetime s"
	  echo "Average time = ${averagetime}"
	fi

	echo -e ${reset}

	rm "${program}"
	exit 1
}

# Prekinitev programa
trap izpisi_rezultate SIGINT

# Testiranje
testing() {
	for input_file in test*.in;
	do
	  # Pridobi številko testa iz imena datoteke (npr. "test01.in" -> "01")
	  input_number=$(echo "$input_file" | sed 's/test\([0-9]\{2\}\)\.in/\1/')

	  # Preveri, ali je številka testa znotraj obsega

	  if [ $testi_zacetek -ne -1 ] && [ $input_number -lt $testi_zacetek ]; then
	  		continue
	  fi
	  if [ $testi_konec -ne -1 ] && [ $input_number -gt $testi_konec ]; then
	  		break
	  fi  
	  output_file_rez="test$input_number.out"
	  output_file_temp="test$input_number.res"
	  output_file_diff="test$input_number.diff"
	  rezultat=0
	  
	  if [ -f $output_file_temp ]; then
		rm $output_file_temp
	  fi
	  if [ -f $output_file_diff ]; then
		rm $output_file_diff
	  fi
	  
	  # Shranite trenutni čas
	  start_time=$(date +%s.%N)
	  
	  # Uporaba timeout za omejitev časovnega limita na 2 sekundi
	  timeout $to ./$program < $input_file > $output_file_temp 2> /dev/null
	  rezultat=$?
	  
	  # Shranite trenutni čas
	  end_time=$(date +%s.%N)
	  elapsed_time=$(echo "scale=3; (${end_time} - ${start_time}) / 1.0" | bc)
	  total_time=$(echo "$total_time + $elapsed_time" | bc)
	  
	  if (( $(echo "$elapsed_time < 1" | bc -l) )); then
		elapsed_time="0$elapsed_time"
	  fi
	  
	  measuredTimeString="";
	  if [[ ${M_time} = 1 ]]; then
		measuredTimeString=" [$elapsed_time s]"
	  fi

	  # Preveri, ali je program presegel časovni limit
	  if [ $rezultat -eq 124 ]; then
		echo -e "Test $input_number: ${purple}Timeout${reset}${measuredTimeString}"
	  else
		if [ -f $output_file_rez ]; then
			# Primerjaj izhod programa s pričakovanim izhodom
			diff -w $output_file_temp $output_file_rez > $output_file_diff
			rezultat=$?
		    if [ $rezultat -eq 0 ]; then
			  correct_tests=$((correct_tests + 1))
			  echo -e "Test $input_number: ${green}PASSED${reset}${measuredTimeString}"
		    else
			  echo -e "Test $input_number: ${red}FAILED${reset}${measuredTimeString}"
		    fi
		else
		   echo -e "Test $input_number: ${blue}DONE${reset}${measuredTimeString}"
		   done_tests=$((done_tests + 1))
		   rezultat=-1
		fi
	  fi
	  
	  test_count=$((test_count + 1))
	  
	  # Počisti začasno izhodno datoteko, če imamo rešitev
	  if [ $rezultat -eq 0 ]; then
	  	rm $output_file_temp
	  	rm $output_file_diff
	  fi
	done
}

testing
izpisi_rezultate