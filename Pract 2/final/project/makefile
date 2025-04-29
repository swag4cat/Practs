# Название итогового исполняемого файла
TARGET = main

# Компилятор
CXX = g++

# Все исходные .cpp файлы проекта
SRCS = main.cpp RunTasks.cpp utils.cpp

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
