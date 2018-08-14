BASE_SRC = release

SRC_DIR = $(BASE_SRC)

div.exe : Source.cpp
	-mkdir $(BASE_SRC)
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
	./release/div.exe