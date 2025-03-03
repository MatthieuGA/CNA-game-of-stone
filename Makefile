
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
SRC_DIR = src
TARGET = main

SRCS = src/main.cpp	\
	src/Matrix.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR) 

.PHONY: all clean
