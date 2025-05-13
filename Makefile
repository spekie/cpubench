BINARY=cpubench
SRC=cpubench.c
CC=gcc
CFLAGS=-o
INSTALL_DIR=/usr/local/bin

$(BINARY): $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(BINARY)

install: $(BINARY)
	install -m 755 $(BINARY) $(INSTALL_DIR)

uninstall:
	rm -f $(INSTALL_DIR)/$(BINARY)

clean:
	rm -f $(BINARY)
