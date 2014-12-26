CXX = g++
CXXV = -std=c++11
CXXFLAGS = -O2 -fPIC -lfastcgi-daemon2 -shared

main: 
	$(CXX) $(CXXV) $(CXXFLAGS) -o libStars.so fastcgi.cpp db.cpp

