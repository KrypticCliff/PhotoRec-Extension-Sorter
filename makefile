CXX 			= g++
LIB_BOOST = -lboost_system -lboost_filesystem

ext_sorter: ext_sorter.cpp
	$(CXX) ext_sorter.cpp -o ext_sorter $(LIB_BOOST)

clean:
	rm ext_sorter
