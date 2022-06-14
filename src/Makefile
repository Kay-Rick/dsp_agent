SRC = main.cc proto/protogen/legacy.pb.cc \
	service.cc 

SERVER = ../main 
CLIENT = ../dsp_client
LDFLAGS = -L../lib -static-libgcc -no-pie -lsrpc -pthread -lserviceMgr -ljsoncpp -lcurl
CC=g++
CFLGAS = -std=c++11
INCLUDES =  -I. -I../include

OBJ = $(patsubst %.cc, %.o, $(SRC))

all:$(SERVER) $(CLIENT)

$(SERVER):$(OBJ)
	$(CC) -o $@  $^ $(LDFLAGS)

$(CLIENT):client/client.cc proto/protogen/legacy.pb.cc
	$(CC) -o $(CLIENT) $^ -I. -lsrpc -L../lib -lserviceMgr -ljsoncpp -lcurl

%.o:%.cc
	$(CC) $(CFLGAS) $(INCLUDES)  -c  $< -o $@


.PHONY: clean
clean:
	@echo "clean all!"
	rm -rf $(OBJ) 
	rm -rf $(SERVER) $(CLIENT)