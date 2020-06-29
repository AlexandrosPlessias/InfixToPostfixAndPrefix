project_infix: main.o basicFunctions.o inputFunctions.o listFunctions.o stackFunctions.o treeFunctions.o displayFunctions.o
	gcc -o project_infix main.o basicFunctions.o  inputFunctions.o listFunctions.o stackFunctions.o treeFunctions.o displayFunctions.o -lm

main.o: header.h main.c
	gcc -c main.c

basicFunctions.o: basicFunctions.c
	gcc -c basicFunctions.c
	
inputFunctions.o: inputFunctions.c
	gcc -c inputFunctions.c
	
listFunctions.o: listFunctions.c
	gcc -c listFunctions.c	
	
stackFunctions.o: stackFunctions.c
	gcc -c stackFunctions.c	
	
treeFunctions.o: treeFunctions.c
	gcc -c treeFunctions.c
	
displayFunctions.o: displayFunctions.c
	gcc -c displayFunctions.c
