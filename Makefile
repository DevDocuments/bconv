CFLAGS += -std=c11 -Os
LDFLAGS += -static

bconv: bconv.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o bconv bconv.c $(LDLIBS)
