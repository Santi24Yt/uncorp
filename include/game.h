#ifndef STRUCTURES_H

#define STRUCTURES_H

#include <curses.h>
#include <time.h>

#define DEBUG_LEVEL 3

#ifndef DEBUG_LEVEL
  #define DEBUG_LEVEL 1
#endif

/* Debug macro */
#define debug1(fmt, ...)  { \
  time_t timestamp = time(NULL); \
  struct tm *tmp; \
  char times[30]; \
  tmp = localtime(&timestamp); \
  strftime(times, sizeof(times), "%x - %H:%M:%S", tmp); \
  fprintf(stderr, "[%s] %s:%d: " fmt "\n", times, __FILE__, __LINE__, ##__VA_ARGS__); \
}

#define debug2(fmt, ...) { \
  if (DEBUG_LEVEL >= 2) { debug1(fmt, ##__VA_ARGS__); } \
}

#define debug3(fmt, ...) { \
  if (DEBUG_LEVEL >= 3) { debug1(fmt, ##__VA_ARGS__); } \
}

#endif
