#################################################################
#                           MakeFile                            #
#################################################################

EXEC  = test
CC    = g++
EXT   = .cpp
DEBUG = no

#################################################################
#                            Options                            #
#################################################################

FLAGS   = -W -Wall -ansi -pedantic -lGL -lglut -lGLU

#################################################################
#                                                               #
#################################################################

ifeq ($(DEBUG),yes)
	CFLAGS=$(FLAGS) -g
	LDFLAGS=$(FLAGS) -g
else
	CFLAGS=$(FLAGS)
	LDFLAGS=$(FLAGS)
endif

SRC= $(wildcard *$(EXT))
OBJ= $(SRC:$(EXT)=.o)

all: $(EXEC) clean

ifeq ($(DEBUG),yes)
	@echo "Génération en mode debug:"
else
	@echo "Génération en mode release:"
endif

$(EXEC): $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.$(EXT)
	@$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf $(EXEC)
