#ifndef STRUCTURES_H

#define STRUCTURES_H

#include <assets.h>

#include <pdcurses.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

#define SCREEN_W 121
#define SCREEN_H 41

int max(int a, int b);


/* engine.c functions */
void setup();
void close();
void waitforsize();
void loop();
void loadprogr();
void saveprogr();
void updatestats();


/* draw.c functions */
void wdrawasset(WINDOW* win, char* asset, int y, int x);


/* windows.c functions */
WINDOW* spawnwin(int h, int w, int sy, int sx);
void focus(WINDOW** wins, int wl, WINDOW* f);


/* text.c functions */
void printcenter(WINDOW* win, char* fmt, ...);


/* titlescreen.c functions */
int titlescreen();


/* labscreen.c functions */
int labscreen();


/* global (? variables */
extern long long aberrations;
extern long long money;
extern int subjects;

extern int daberrations;
extern int dmoney;
extern int dsubjects;

extern long lastupdate;

extern int stability;

extern int houselvl;

extern int fendings;


#endif
