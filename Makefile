src=Dictionary
build=build

hash: dictionary.o main.o
	clang $(build)/dictionary.o $(build)/main.o -o hash

dictionary.o:
	clang -c $(src)/dictionary.c -o $(build)/dictionary.o

main.o:
	clang -c $(src)/main.c -o $(build)/main.o

.PHONY : clean

clean:
	rm $(build)/*
	rm hash
