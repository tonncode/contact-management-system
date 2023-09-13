output: main.o contact.o contactbst.o
	g++ main.o contact.o contactbst.o -o output

main.o: main.cpp
	g++ -c main.cpp

contact.o: contact.cpp
	g++ -c contact.cpp

contactbst.o: contactbst.cpp
	g++ -c contactbst.cpp

clean:
	rn *.o output
