CXX = g++

CXXFLAGS = -std=c++17 -Wall

BUILD_DIR = build

TARGET = tests

OBJECTS = $(BUILD_DIR)/s_box.o $(BUILD_DIR)/p_box.o $(BUILD_DIR)/tests.o

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

$(BUILD_DIR)/s_box.o: s_box.cpp s_box.h
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c s_box.cpp -o $(BUILD_DIR)/s_box.o

$(BUILD_DIR)/p_box.o: p_box.cpp p_box.h
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c p_box.cpp -o $(BUILD_DIR)/p_box.o

$(BUILD_DIR)/tests.o: tests.cpp s_box.h p_box.h
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c tests.cpp -o $(BUILD_DIR)/tests.o

.PHONY: clean
