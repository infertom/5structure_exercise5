CC=g++
CFLAGS=-g -ansi -pedantic
LFLAGS=-L/lib -lwsock32

SERVER-SRC=main.cpp processrequest.cpp buildpage.cpp \
		Date.cpp Advertisement.cpp Client.cpp \
		Listing.cpp Group.cpp \
		Category.cpp Categories.cpp \
		buildbidpage.cpp Bid.cpp bidhistory.cpp

SERVER-INC=main.h processrequest.h buildpage.h \
		Date.h Advertisement.h Client.h \
		Listing.h Group.h \
		Category.h Categories.h \
		buildbidpage.h Bid.h bidhistory.h 

SERVER-OBJ=main.o processrequest.o buildpage.o \
		Date.o Advertisement.o Client.o \
		Listing.o Group.o \
		Category.o Categories.o \
		buildbidpage.o Bid.o bidhistory.o 

all: server 

server: $(SERVER-INC) $(SERVER-OBJ)
	$(CC) $(SERVER-SRC) $(CFLAGS) $(LFLAGS) -o auction-server.exe

clean: 
	rm *.o
	rm auction-server.exe

%.o: %.cpp
	$(CC) $(CFLAGS) -c $(@:%.o=%.cpp)
