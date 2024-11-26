CC=gcc
CFLAGS=-c -Wall -g -pthread
LDFLAGS=-ljpeg -lrt
SOURCES= mandelmovie.c jpegrw.c processor.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=mandel

all: $(SOURCES) $(EXECUTABLE) 

# pull in dependency info for *existing* .o files
-include $(OBJECTS:.o=.d)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o: 
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM $< > $*.d

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) *.d
