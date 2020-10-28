EMIPATH = /usr/cpp/emi/
OBJS = $(EMIPATH)obj/Debug/main.o $(EMIPATH)obj/Debug/src/Builder.o $(EMIPATH)obj/Debug/src/Communicator.o $(EMIPATH)obj/Debug/src/Global.o $(EMIPATH)obj/Debug/src/Helper.o $(EMIPATH)obj/Debug/src/Manager.o $(EMIPATH)obj/Debug/src/Starter.o
BINARY = $(EMIPATH)bin/Debug/emi.exe
COMP = g++
FLAGS = -Wall -fexceptions -g -std=c++17 -Iinclude

all: emi

emi: $(OBJS)
	$(COMP) -o $(BINARY) $(OBJS)

$(EMIPATH)obj/Debug/main.o: $(EMIPATH)main.cpp $(EMIPATH)include/Starter.h $(EMIPATH)include/Manager.h $(EMIPATH)include/Communicator.h $(EMIPATH)include/Global.h $(EMIPATH)include/Codes.h
	$(COMP) $(FLAGS) -c $(EMIPATH)main.cpp -o $(EMIPATH)obj/Debug/main.o 

$(EMIPATH)obj/Debug/src/Builder.o: $(EMIPATH)src/Builder.cpp $(EMIPATH)include/Builder.h $(EMIPATH)include/Helper.h $(EMIPATH)include/Communicator.h $(EMIPATH)include/Structures.h $(EMIPATH)include/Global.h $(EMIPATH)include/Codes.h
	$(COMP) $(FLAGS) -c $(EMIPATH)src/Builder.cpp -o $(EMIPATH)obj/Debug/src/Builder.o

$(EMIPATH)obj/Debug/src/Communicator.o: $(EMIPATH)src/Communicator.cpp $(EMIPATH)include/Communicator.h $(EMIPATH)include/Structures.h $(EMIPATH)include/Global.h $(EMIPATH)include/Codes.h
	$(COMP) $(FLAGS) -c $(EMIPATH)src/Communicator.cpp -o $(EMIPATH)obj/Debug/src/Communicator.o

$(EMIPATH)obj/Debug/src/Global.o: $(EMIPATH)src/Global.cpp $(EMIPATH)include/Global.h 
	$(COMP) $(FLAGS) -c $(EMIPATH)src/Global.cpp -o $(EMIPATH)obj/Debug/src/Global.o

$(EMIPATH)obj/Debug/src/Helper.o: $(EMIPATH)src/Helper.cpp $(EMIPATH)include/Helper.h $(EMIPATH)include/Structures.h $(EMIPATH)include/Global.h $(EMIPATH)include/Codes.h
	$(COMP) $(FLAGS) -c $(EMIPATH)src/Helper.cpp -o $(EMIPATH)obj/Debug/src/Helper.o

$(EMIPATH)obj/Debug/src/Manager.o: $(EMIPATH)src/Manager.cpp $(EMIPATH)include/Manager.h $(EMIPATH)include/Builder.h $(EMIPATH)include/Helper.h $(EMIPATH)include/Communicator.h $(EMIPATH)include/Structures.h $(EMIPATH)include/Global.h $(EMIPATH)include/Codes.h
	$(COMP) $(FLAGS) -c $(EMIPATH)src/Manager.cpp -o $(EMIPATH)obj/Debug/src/Manager.o

$(EMIPATH)obj/Debug/src/Starter.o: $(EMIPATH)src/Starter.cpp $(EMIPATH)include/Starter.h $(EMIPATH)include/Helper.h $(EMIPATH)include/Global.h $(EMIPATH)include/Codes.h
	$(COMP) $(FLAGS) -c $(EMIPATH)src/Starter.cpp -o $(EMIPATH)obj/Debug/src/Starter.o

clean:
	rm -f $(BINARY)
	rm -f $(OBJS)

