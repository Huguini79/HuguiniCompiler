CPP = g++
TARGET = HuguiniCompiler

all:
	clear
	$(CPP) main.cpp -o $(TARGET)
	./$(TARGET)

clean:
	rm -rf HuguiniCompiler
