CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -std=c17
DFLAGS = -Wall -Werror -Wextra -pedantic -std=c17 -fsanitize=address -g
LFLAGS = -lSDL2 -lSDL2_image
SRC = src/main.c src/game.c
TARGET = game
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(TARGET) $(LFLAGS)

debug: $(OBJ)
	$(CC) $(DFLAGS) $(OBJ) -o $(TARGET) $(LFLAGS)

clean:
	$(RM) $(OBJ) *~ src/*~

fclean: clean
	$(RM) $(TARGET)

re: fclean all

.PHONY: all clean fclean re