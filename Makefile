CXXFLAGS = -g -O2

PREFIX = /usr/local
DESTDIR = ""

ldd-dep-cp : main.cpp
	$(CXX) $(CXXFLAGS) -o ldd-dep-cp main.cpp -lfmt

.PHONY: install clean
install:
	mkdir -p ${DESTDIR}/${PREFIX}/bin
	cp ldd-dep-cp ${DESTDIR}/${PREFIX}/bin

clean:
	rm ldd-dep-cp
