#pragma once
/*
 * いやだなーとか言いながら使うグローバル変数
 * */

#ifndef GLOBAL_MASTER
#define GLOBALEXT extern
#define GLOBALVAR(x)
#else
#define GLOBALEXT
#define GLOBALVAR(x) = x
#endif

GLOBALEXT int WINDOW_WIDTH GLOBALVAR(1024);
GLOBALEXT int WINDOW_HEIGHT GLOBALVAR(768);

