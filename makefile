all:
	gcc -o sucesion coordinador.c -Wall
	gcc -o comparador comparador.c -Wall
	echo "./sucesion -i ejemplo1.txt -n 5 -c 60 -p AAAA -d"
