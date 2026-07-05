CC=gcc
cflags= I$(IDIR)

_DEPS = stdio.h string.h concord/discord.h cjson/cJSON.h
DEPS = $(pathsubst %,$(IDIR)/%,$(_DEPS))

src/blahaj: src/bot.c
	$(CC) src/bot.c -lcjson -ldiscord -lcurl -pthread -o src/blahaj
