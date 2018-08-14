BASE_SRC = release

SRC_DIR = $(BASE_SRC)

div.exe : Source.cpp
	gcc Source.cpp -o release/div.exe

.PHONY : clean
clean :
	cd release;	rm *.exe

release:
	make clean
	-mkdir $(BASE_SRC)
	make
	cp *.exe $(BASE_SRC)

test:
	./release/div "(1,2,3,4,5)" "(2,2,2,2,2)"