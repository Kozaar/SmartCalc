CC=g++
WFLAGS=-std=c++17 
SOURCESTESTING=./SmartCalc_v2/model.cpp
SOURCESTEST=tests.cpp
TEXINFO=info.texi
GCOVFLAGS=--coverage
HTML_CREATE=lcov --no-external -t a.out -o rep.info -c -d .; genhtml -o report rep.info
OS=$(shell uname)
ifeq ($(OS), Linux)
	TESTFLAGS= -lgtest -pthread
else
	TESTFLAGS= -lgtest
endif

all: clean install

build:
	qmake ./SmartCalc_v2/ -o ./SmartCalc_v2/Makefile
	make -C ./SmartCalc_v2/
	cp -R ./SmartCalc_v2/SmartCalc_v2.app ./SmartCalc.app

install: build
	cp -R ./SmartCalc_v2/SmartCalc_v2.app ~/SmartCalc.app
	~/SmartCalc.app/Contents/MacOS/SmartCalc_v2

uninstall:
	rm -rf ./SmartCalc_v2/SmartCalc_v2.app ./SmartCalc.app

clean:
	rm -rf *.o *.g* *.out report *.a *.info readme ./SmartCalc.app ./SmartCalc_v2/SmartCalc_v2.app ./SmartCalc_v2/*.o ./SmartCalc_v2/Makefile ./SmartCalc_v2/moc_* ./SmartCalc_v2/ui_* ~/SmartCalc.app

dvi:
	rm -rf readme
	makeinfo --html $(TEXINFO)

dist: clean
	rm -rf smart_calcv2.0
	mkdir smart_calcv2.0
	mkdir smart_calcv2.0/src
	mkdir smart_calcv2.0/src/SmartCalc_v2
	cp ./Makefile smart_calcv2.0/src
	cp ./*.c* smart_calcv2.0/src
	cp ./SmartCalc_v2/* smart_calcv2.0/src/SmartCalc_v2
	cp ./*.texi smart_calcv2.0/src
	mkdir smart_calcv2.0/materials/
	mkdir smart_calcv2.0/materials/linters
	cp ../materials/linters/* smart_calcv2.0/materials/linters
	tar -czf smart_calcv2.0.tar.gz smart_calcv2.0
	rm -rf smart_calcv2.0

tests: clean
	$(CC) $(SOURCESTEST) $(SOURCESTESTING) $(TESTFLAGS) $(WFLAGS)
	./a.out

leaks: tests
	leaks --atExit -- ./a.out

gcov_report: clean
	$(CC) $(SOURCESTEST) $(SOURCESTESTING) $(TESTFLAGS) $(WFLAGS) $(GCOVFLAGS)
	./a.out
	$(HTML_CREATE)

style:
	cp ../materials/linters/CPPLINT.cfg ./
	python3 ../materials/linters/cpplint.py --extensions=cpp ./SmartCalc_v2/*.cpp ./SmartCalc_v2/*.h
	rm CPPLINT.cfg
