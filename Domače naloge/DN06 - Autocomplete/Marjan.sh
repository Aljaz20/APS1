#####################################
			VERSION=1.7
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
  echo "Uporaba: $0 <ime_programa brez koncnice> <dodatni_parametri>"
  echo "Dodatni parametri: T={} - timeoutlimit, M={} - measuretime, R={} - range of tests (1- || -4 || 2-5)"
  exit 1
fi

# Argumenti
program="$1"
shift 1
remove=1

if [ ! -f "${program}.cpp" ]; then
  if [ ! -f "${program}" ]; then
	echo "Datoteka ${program} in ${program}.cpp ne obstaja."
	exit 1
  else
	remove=0
  fi
else
  g++ "${program}.cpp" -o ${program} -std=c++20 -pedantic -Wall
fi


# Čas za timeout
to=2.0

# Izpiši čas
M_time=1
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




# Pravilni testi
correct_tests=0

# Testi brez rešitve
done_tests=0

# Vsi testi
test_count=0

# funkcija ob koncu izvajanja
izpisi_rezultate() {
	preimenuj=0
	# Izpiši število pravilnih testov na koncu
	echo -e "${white}---------------"
	if [ $((test_count -  done_tests)) -ne 0 ]; then
	  echo "Rezultat: $correct_tests/$((test_count - done_tests))"
	fi
	if [ $done_tests -ne 0 ]; then
	  echo "Ostali opravljeni testi : $done_tests"
	  preimenuj=1
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
	
	if [ $preimenuj -eq 1 ]; then
	  echo ""
	  echo -e "${blue}Do you want to rename .res to .out? (y/n)${reset}"
	  read -r answer
	  if [[ $answer =~ ^[Yy]$ ]]; then
	    echo -e "${white}Renaming..."
		for input_file in test*.in;
		do
		  input_number=$(echo "$input_file" | sed 's/test\([0-9]\{2\}\)\.in/\1/')
		  output_file_rez="test$input_number.out"
		  output_file_temp="test$input_number.res"
		  if [ -f $output_file_rez ]; then
			continue
		  else
		    if [ -f $output_file_temp ]; then
		  	  mv $output_file_temp $output_file_rez
			fi  
		  fi
		done
		echo -e "${green}Done."
	  fi  	
	fi
	
	echo -e ${reset}
	if [ $remove -eq 1 ]; then
	  rm "${program}"
	fi
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
		rm $output_file_temp
		if [ -f $output_file_rez ];then
		  rezultat=-1
		else
		   done_tests=$((done_tests + 1))
		fi
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
