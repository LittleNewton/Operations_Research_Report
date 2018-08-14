objects = Divide.h Dynamic_Array.h Matrix_Operation.h Shell_Reader.h Simplex.h Source.cpp

simplex.exe : $(objects)
	-mkdir release
	@gcc Source.cpp -o release/simplex.exe

.PHONY : clean
clean :
	@cd release; rm *.exe

test :
	./release/simplex.exe