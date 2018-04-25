CC = gcc

TARGET=CreateBitmap

SRCDIR=src/
SRC=CreateBitmap.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -O2

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $^ $(CFLAGS) 

$(OBJ): $(SRCDIR)$(SRC)
	$(CC) $(CFLAGS) -c $<

.PHONY : clean
clean : 
	$(RM) $(TARGET) *.o 
