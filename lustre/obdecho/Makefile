MODULES := obdecho
obdecho-objs := echo_client.o
obdecho-objs += echo.o

EXTRA_DIST = $(obdecho-objs:%.o=%.c) echo_internal.h
#EXTRA_DIST += echo.c

include /home/build/lustre-release/Rules
