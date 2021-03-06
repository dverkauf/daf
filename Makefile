all: main library
	g++ main.cpp -L./library -ldaf -o app -std=c++17

objects:
	cd includes && \
	g++ -c *.cpp -fPIC -std=c++17

library: objects
	g++ -shared -fPIC -lcurl -o library/libdaf.so includes/*.o -std=c++17

main: main.cpp
	g++ -c main.cpp -std=c++17

clean:
	rm -f *.o includes/*.o library/*.so

run:
	LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:./library ./app test -d

test: library
	g++ test.cpp -L./library -ldaf -lcurl -o test -std=c++17

run_test:
	LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:./library ./test

wlanscan: library
	g++ wlanscan.cpp -L./library -ldaf -o wlanscan -std=c++17