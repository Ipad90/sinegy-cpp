LIBS = -lcurl -ljsoncpp -lssl -lcrypto

main: main.cpp
	g++ -o main.o main.cpp src/marketplace.cpp $(LIBS)

clean:
	rm main.o
