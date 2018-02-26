CXX = g++
CXXFLAGS = -std=c++11 -O3 -I../include
# 如果链接失败, 请添加boost库, 我只使用了boost::lexical_cast这一项
OBJ = miliobj.o utils.o defence.o offense.o missile.o bomber.o target.o common.o command.o ccommand.o simulator.o timer.o logger.o func.o main.o
TARGET = simulator

all : $(TARGET)

utils.o : utils.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

miliobj.o : miliobj.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@	

defence.o : defence.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

offense.o : offense.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

missile.o : missile.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

bomber.o : bomber.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

target.o : target.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

common.o : common.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

command.o : command.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

ccommand.o : ccommand.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

simulator.o : simulator.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

timer.o : timer.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

logger.o : logger.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

func.o : func.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

main.o : main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET) : $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

clean :
	rm -f $(OBJ) $(TARGET)

