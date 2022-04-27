CXX = g++ -Wall -Wextra -ggdb
CPP_FILES = server.cpp generator.cpp socket.cpp socket_ex.cpp
H_FILES = socket.h generator.h socket_ex.h
BIN_OUT = server_of_seq
OBJ_FILE = server.o

$(BIN_OUT): $(H_FILES) $(CPP_FILES)
	$(CXX) $(CPP_FILES) -o $(BIN_OUT)

run:
	@echo "Launching server...."
	./$(BIN_OUT)

clean:
	rm $(BIN_OUT)
