bintree:
	g++ bintree.cpp
all:
	g++ -o testtree.exe testtree.cpp bintree.cpp -lgtest -lgtest_main -pthread
	g++ -o testbalance.exe testbalance.cpp
tests:
	./testtree.exe
	./testbalance.exe