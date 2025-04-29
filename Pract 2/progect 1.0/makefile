# Название итогового исполняемого файла
TARGET = main

# Компилятор
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Все исходные .cpp файлы проекта
SRCS = main.cpp \
       task1.cpp task2.cpp task3.cpp \
       task4.cpp task5.cpp task6.cpp \
       utils.cpp

# Получаем список объектных файлов .o
OBJS = $(SRCS:.cpp=.o)

# Основное правило сборки
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Правило для компиляции каждого .cpp в .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка проекта
clean:
	rm -f $(OBJS) $(TARGET)
