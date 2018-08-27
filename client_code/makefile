PROJ	= client
OBJS	= main.o client.o socketsender.o consolesender.o\
	  logreader.o
CXX	= g++
LNK	= g++
RM	= rm -rf
CFLAGS	= -c -Wall -I. 
$(PROJ):$(OBJS)
	$(LNK) $^ -o $@
.cpp.o:
	$(LNK) $(CFLAGS) $^
clean:
	$(RM) $(PROJ) $(OBJS) *.gch
