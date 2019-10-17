SOURCE:=$(wildcard *.cpp)
OBJS:=$(patsubst %.cpp,%.o,$(SOURCE))

TARGET:=ShopServer
CC:=g++
LIBS:=-lpthread
INCLUDE:=-I../include
CFLAGS:= -std=c++11 -g -O3 $(INCLUDE)
CPPFLAGS:=$(CFLAGS)
RM:=rm -rf 

.PHONY:all clean objs debug
all:$(TARGET)
objs:$(OBJS)
clean:
	$(RM) $(OBJS)
	$(RM) $(TARGET)
debug:
	@echo $(SOURCE)

$(TARGET):$(OBJS)
	$(CC) $^ $(LIBS) -o $@
%.o:%.c
	$(CC) $(CPPFLAGS) $< 

