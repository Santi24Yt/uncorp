#include <game.h>

void setup()
{
  debug2("Initializing screen");
  initscr();
  debug2("Screen initialized");

  noecho();
  debug3("No echo active");

  /* raw();*/
  keypad(stdscr, TRUE);
  /* nodelay(stdscr,TRUE); */
  halfdelay(1);
  debug3("10ms delay characters mode active");

  curs_set(0);
  debug3("Cursor mode set to 0");

  debug1("Checking for colors");
  if (has_colors() == FALSE)
  {
    debug1("No colors, exiting");
    close();
    printf("Colors are not supported by your terminal\n");
    exit(1);
  }

  start_color();
  debug1("Colors initialized");

  waitforsize();
}

void close()
{
  endwin();
  debug1("Window finished");
  remove("screen.dmp");

  printf("Goodbye\n");
}

void waitforsize()
{
  int h;
  int w;
  getmaxyx(stdscr, h, w); 

  int ch = ERR;

  while(1)
  {
    if (ch == 'q')
    {
      close();
      exit(0);
    }
    if (ch == 410)
    {
      clear();
    }
    getmaxyx(stdscr, h, w); 
    resize_term(h, w);

    if (h >= SCREEN_H && w >= SCREEN_W)
    {
      break;
    }

    printcenter(stdscr, "Resize your terminal to be at least %dx%d Current size: %dx%d", SCREEN_H, SCREEN_W, h, w);
    ch = getch();
  }
  clear();
  debug2("Correct size confirmed");
  resize_term(SCREEN_H, SCREEN_W);
  wborder(stdscr, '|', '|', '-', '-', '+', '+', '+', '+');
}

void loop()
{
  int h;
  int w;

  int ch = ERR;
  int i = 0;
  while(ch != 'q')
  {
    move(0, SCREEN_W-1);
    mvprintw(1,1,"Test dump %d", i);
    getmaxyx(stdscr, h, w);
    if (h < SCREEN_H || w < SCREEN_W)
    {
      refresh();
      scr_dump("screen.dmp");
      clear();
      waitforsize();
      scr_restore("screen.dmp");
      refresh();
      remove("screen.dmp");
    }

    i = (i + 1) % 1000000;
    refresh();
    ch = getch();
  }
}