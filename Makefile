CXX = g++
CXXV = -std=c++11
CXXFLAGS_DAEMON = -O2 -fPIC -lfastcgi-daemon2 -shared
CXXFLAGS_MONGO = -pthread -lmongoclient -lboost_thread -lboost_system -lboost_regex -lboost_program_options -lboost_filesystem

main: 
	$(CXX) mongo.h mongo.cpp fastcgi.cpp $(CXXFLAGS_MONGO) $(CXXFLAGS_DAEMON) -o libStars.so 

