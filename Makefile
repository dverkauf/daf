all: main library
	g++ main.cpp -L./library -ldaf -o app

objects:
	cd includes && \
	g++ -c *.cpp -fPIC

library: objects
	g++ -shared -fPIC -o library/libdaf.so includes/*.o

main: main.cpp
	g++ -c main.cpp

clean:
	rm -f *.o includes/*.o library/*.so

run:
	LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:./library ./app scan -c config.json
	