libxsocket.so:	./src/XTcp.cpp ./src/XTcp.hpp
	clang++ $+ -o $@ -fPIC -shared -std=c++11
