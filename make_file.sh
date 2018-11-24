gcc -Wall -w -o structure.o -c structure.c
gcc -Wall -w -o biblio.o -c biblio.c
gcc -Wall -w -o interface.o -c interface.c
gcc -Wall -w -o tests/test_unit.o -c tests/test_unit.c
gcc -Wall -w -o main main.c *.o tests/*.o
