TARGET= main
LIB= cvlib
all: $(TARGET)

$(TARGET): $(TARGET).o $(LIB).o
	g++ -ggdb $(TARGET).o $(LIB).o `pkg-config --cflags --libs opencv` -o $(TARGET)
	rm $(TARGET).o $(LIB).o

$(TARGET).o:
	g++ -ggdb -c $(TARGET).cpp $(LIB).cpp 

clean:
	rm $(TARGET).o $(TARGET)
