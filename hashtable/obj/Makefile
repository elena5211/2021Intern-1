CC		= g++
LD		= g++

INCDIR	= -I../src/ \
	  -I../src/kvs \

SRCDIR			= ../src
KVSDIR			= ../src/kvs

VPATH	= $(SRCDIR) $(KVSDIR)

COMMON_CFLAGS	= $(INCDIR) \
		  -Wall \
		  -O0 \
		  -g -pg \
		  -std=c++11

CFLAGS		= $(COMMON_CFLAGS) \
		  -fsanitize=address \
		  -static-libasan

TRACE_CFLAGS	= $(COMMON_CFLAGS)

LIBS	=	-lpthread \


TARGET	= my_kvs
TRACE_TARGET	= my_kvs-trace

SRCS	= $(foreach dir, .. $(SRCDIR) $(KVSDIR), $(wildcard $(dir)/*.c) $(wildcard $(dir)/*.cpp))
SRCS	:= $(notdir $(SRCS))

OBJS	= $(SRCS:.c=.o)

all: $(TARGET) $(TRACE_TARGET)

$(TARGET): $(SRCS)
	$(CC) $^ -o $(TARGET) $(CFLAGS) $(LIBS)
	mv $(TARGET) ../

$(TRACE_TARGET): $(SRCS)
	$(CC) $^ -o $(TRACE_TARGET) $(TRACE_CFLAGS) $(LIBS)
	mv $(TRACE_TARGET) ../

%o: %c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)
	rm -f ../$(TARGET)

depend: $(SRCS)
	$(CC) -M $(CFLAGS) $^ > $@

-include depend
