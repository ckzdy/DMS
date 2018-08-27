PROJ	= server
OBJS	= main.o server.o serversocket.o\
	  logthread.o storethread.o clientthread.o\
	  logqueue.o filedao.o oracledao.o 
CXX	= g++
LNK	= g++
RM	= rm -rf
CFLAGS	= -c -Wall -I.
LIBS	= -lpthread -lclntsh
$(PROJ):$(OBJS)
	$(LNK) $^ $(LIBS) -o $@
.cpp.o:
	$(CXX) $(CFLAGS) $^
clean:
	$(RM) $(PROJ) $(OBJS) *.gch
