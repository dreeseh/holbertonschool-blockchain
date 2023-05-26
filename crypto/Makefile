CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -g
RM = rm -f
TARGET_LIB = libhblk_crypto.a

SRCS = sha256.c ec_create.c ec_to_pub.c ec_from_pub.c ec_save.c ec_load.c ec_sign.c ec_verify.c
OBJS = $(SRCS:.c=.o)

.PHONY: clean

libhblk_crypto.a: $(OBJS) hblk_crypto.h
		ar rcs $(TARGET_LIB) $(OBJS)

clean:
	$(RM) $(SRCS:.c=.o)
