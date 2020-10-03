ARCH=host
BIN=opk/testsdl2
PKG=testsdl2.opk
OBJ=testsdl2.o

include ${ARCH}.mk

all: $(PKG)

%.o: %.c
	@echo CC $@
	@$(CC) -c -o $@ -Wall -Werror -pedantic -std=gnu99 `${SDLCONFIG} --cflags` $^

$(BIN): $(OBJ)
	@echo LD $@
	@$(LD) -o $@ $^ `${SDLCONFIG} --libs` -lSDL2_image

$(PKG): $(BIN)
	mksquashfs opk $@

clean:
	rm -rf $(PKG) $(BIN) $(OBJ)

run: $(PKG)
	(cd opk && ./testsdl2)

upload:
	scp $(PKG) od@10.1.1.2:/media/data/apps/$(PKG)
