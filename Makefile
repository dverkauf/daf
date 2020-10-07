all: main library
	g++ main.cpp -L./library -ldaf -o app -std=c++11

objects:
	cd includes && \
	g++ -c *.cpp -fPIC -std=c++11

library: objects
	g++ -shared -fPIC -o library/libdaf.so includes/*.o -std=c++11

main: main.cpp
	g++ -c main.cpp -std=c++11

clean:
	rm -f *.o includes/*.o library/*.so

run:
	LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:./library ./app scan -c config.json
	