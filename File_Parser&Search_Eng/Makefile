CXX=g++
CXXFLAGS=-g -Wall -std=c++11 
GTESTINCL := -I /usr/include/gtest/  
GTESTLIBS := -lgtest -lgtest_main  -lpthread
VALGRIND := valgrind --tool=memcheck --leak-check=yes --track-origins=yes

OBJS_COMPONENTS=searcheng.o searchui.o md_parser.o txt_parser.o util.o webpage.o handler.o cmdhandler.o combiners.o
OBJS=search-shell.o $(OBJS_COMPONENTS)

all: search-shell 

search-shell.o: search-shell.cpp pageparser.h md_parser.h txt_parser.h cmdhandler.h handler.h webpage.h searcheng.h searchui.h util.h combiners.h
	$(CXX) $(CXXFLAGS) $(DEFS) -c -o $@ search-shell.cpp
util.o: util.cpp util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -c -o $@ util.cpp
txt_parser.o: txt_parser.cpp txt_parser.h pageparser.h util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -c -o $@ txt_parser.cpp
md_parser.o: md_parser.cpp md_parser.h pageparser.h util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -c -o $@ md_parser.cpp
searchui.o: searchui.cpp searchui.h searcheng.h handler.h cmdhandler.h util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -c -o $@ searchui.cpp
handler.o: handler.cpp handler.h
	$(CXX) $(CXXFLAGS) $(DEFS) -c -o $@ handler.cpp
webpage.o: webpage.cpp webpage.h util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -c -o $@ webpage.cpp
cmdhandler.o: cmdhandler.cpp cmdhandler.h handler.h
	$(CXX) $(CXXFLAGS) $(DEFS)  -c -o $@ cmdhandler.cpp
searcheng.o: searcheng.cpp searcheng.h webpage.h pageparser.h txt_parser.h md_parser.h cmdhandler.h handler.h util.h combiners.h
	$(CXX) $(CXXFLAGS) $(DEFS) -c -o $@ searcheng.cpp
combiners.o: combiners.cpp combiners.h searcheng.h util.h
	$(CXX) $(CXXFLAGS) $(DEFS) -c -o $@ combiners.cpp
search-shell :  $(OBJS) 
	$(CXX) $(CXXFLAGS) $(DEFS) $^ -o $@ 



clean:
	rm -f *.o search-shell 
