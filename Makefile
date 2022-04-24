CC = g++ -ggdb
CPP_FILES = socket.cpp server.cpp socket_ex.cpp
H_FILES = socket_ex.h socket.h
BIN_OUT = server_launch

$(BIN_OUT): $(H_FILES) $(CPP_FILES)
	$(CC) $(CPP_FILES) -o $(BIN_OUT)

clean:
	rm $(BIN_OUT)