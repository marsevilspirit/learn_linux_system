CC = gcc
CFLAGS = -g
LDFLAGS = -lesmtp

SRCS = main.c mail.c patient.c account.c
OBJS = $(SRCS:.c=.o)
EXEC = test

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXEC) $(OBJS)

