include clear-config.mk
DEP_MODULE:common sys
CFLAGS:=-O0 -std=gnu99
SRCS:=tc_blend.c ../common/verify_gfx.c
LIBS:=mi_sys mi_gfx
include add-config.mk
