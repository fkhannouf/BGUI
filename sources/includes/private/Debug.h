#pragma once

#define BGUI_LOG_LEVEL_NONE  0
#define BGUI_LOG_LEVEL_ERROR 1
#define BGUI_LOG_LEVEL_INFO  2
#define BGUI_LOG_LEVEL_DEBUG 3

#ifndef BGUI_LOG_LEVEL
#define BGUI_LOG_LEVEL BGUI_LOG_LEVEL_NONE
#endif

#if BGUI_LOG_LEVEL < BGUI_LOG_LEVEL_NONE || BGUI_LOG_LEVEL > BGUI_LOG_LEVEL_DEBUG
#error "BGUI_LOG_LEVEL must be between 0 (none) and 3 (debug)"
#endif

#if BGUI_LOG_LEVEL > BGUI_LOG_LEVEL_NONE
void VARARGS68K ___DEBUG( uint32 lvl, STRPTR fmt, ... );
#endif

#if BGUI_LOG_LEVEL >= BGUI_LOG_LEVEL_ERROR
#define __ERROR(...) ___DEBUG( BGUI_LOG_LEVEL_ERROR, __VA_ARGS__ )
#else
#define __ERROR(...) ((void)0)
#endif

#if BGUI_LOG_LEVEL >= BGUI_LOG_LEVEL_INFO
#define __INFO(...) ___DEBUG( BGUI_LOG_LEVEL_INFO, __VA_ARGS__ )
#else
#define __INFO(...) ((void)0)
#endif

#if BGUI_LOG_LEVEL >= BGUI_LOG_LEVEL_DEBUG
#define __DEBUG(...) ___DEBUG( BGUI_LOG_LEVEL_DEBUG, __VA_ARGS__ )
#else
#define __DEBUG(...) ((void)0)
#endif
