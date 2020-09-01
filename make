db : db.o readfile.o prompt.o
	gcc -o db db.o readfile.o prompt.o
db.o : db.c readfile.h
	gcc -c db.c
readfile.o : readfile.c prompt.h
	gcc -c readfile.c
prompt.o : prompt.c
	gcc -c prompt.c
all : db
clean :
	rm -f db db.o readfile.o prompt.o
tarball : db db.c readfile.c readfile.h prompt.c prompt.h make makefile
	tar -c db.tar readfile.c readfile.h prompt.c prompt.h make db.c makefile 
	
