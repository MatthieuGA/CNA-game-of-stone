CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
SRC_DIR = src
TARGET = game_of_stones

SRCS = src/main.cpp	\
	src/Matrix.cpp	\
	src/Oriented_Graph.cpp	\
	src/Conspiracy.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)

re: clean all

.PHONY: all clean re
