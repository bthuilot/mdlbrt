##########################
# (c) Bryce Thuilot 2021 #
##########################

OUT_DIR = build
INC_DIR = include
SRC_DIR = src

MKDIR_P = mkdir -p

CFLAGS = -std=c17 -D_THREAD_SAFE -I/usr/local/include/SDL2 -I$(INC_DIR)
TARGET = mdlbrt
LIBS = -L/usr/local/lib -lm -lSDL2 

_SOURCES = main.c graph.c colors.c
SOURCES = $(patsubst %,$(SRC_DIR)/%,$(_SOURCES))

_DEPS = $(_SOURCES:.c=.h)
DEPS = $(patsubst %,$(INC_DIR)/%,$(_DEPS))

_OBJS = $(_SOURCES:.c=.o)
OBJS = $(patsubst %,$(OUT_DIR)/%,$(_OBJS))

all: directories $(SOURCES) $(TARGET)

$(OUT_DIR)/main.o: $(SRC_DIR)/main.c $(INC_DIR)/main.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUT_DIR)/graph.o: $(SRC_DIR)/graph.c $(INC_DIR)/graph.h $(INC_DIR)/colors.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUT_DIR)/colors.o: $(SRC_DIR)/colors.c
	$(CC) -c -o $@ $< $(CFLAGS)


$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean directories

directories: $(OUT_DIR)

$(OUT_DIR):
	$(MKDIR_P) $(OUT_DIR)

clean:
	rm -f $(OUT_DIR)/*.o $(TARGET) core *~ 
