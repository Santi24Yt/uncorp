#include <game.h>

void setup()
{
  srand(time(NULL));
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

  loadprogr();
}

void close()
{

  saveprogr();

  endwin();
  debug1("Window finished");
  remove("screen.dmp");

  printf("Goodbye\n");
}

void waitforsize()
{
  resize_term(SCREEN_H, SCREEN_W);
  
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
  wborder(stdscr, '|', '|', '-', '-', '*', '*', '*', '*');
}

void loop()
{
  int h;
  int w;

  int exitf = 0;
  while(!exitf)
  {
    move(0, SCREEN_W-1);
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


    exitf = titlescreen();

    if (exitf == 0)
    {
      exitf = labscreen();
    }

    switch (exitf-1)
    {
      /* overflow ending */
      case 1:
        fendings = fendings | 0b001;
        exitf = overflowscreen();
        break;

      /* unstability ending */
      case 2:
        fendings = fendings | 0b010;
        exitf = unstabilityscreen();
        break;

      /* maxhouse ending */
      case 3:
        fendings = fendings | 0b100;
        exitf = maxhousescreen();
        break;
    }

    refresh();
  }
}

long long aberrations = 0;
long long money = 1000;
int subjects = 0;

int daberrations = 0;
int dmoney = 0;
int dsubjects = 0;

long lastupdate;
int stability = 100;
int houselvl = 0;
int fendings = 0;

void loadprogr()
{
  FILE* fp = fopen("gamesave.zzz", "r");
  
  if (fp == NULL)
  {
    debug1("Can't load progress");
    fp = fopen("gamesave.zzz", "w");
    fprintf(fp, "%lld %lld %d %d %d %d %d %d %d", aberrations, money, subjects, daberrations, dmoney, dsubjects, stability, houselvl, fendings);
  } else {
    fscanf(fp, "%lld %lld %d %d %d %d %d %d %d", &aberrations, &money, &subjects, &daberrations, &dmoney, &dsubjects, &stability, &houselvl, &fendings);
  }

  lastupdate = time(NULL);
  fclose(fp);
}

void saveprogr()
{
  FILE* fp = fopen("gamesave.zzz", "w");
  
  if (fp == NULL)
  {
    debug1("Can't save progress");
  } else {
    fprintf(fp, "%lld %lld %d %d %d %d %d %d %d", aberrations, money, subjects, daberrations, dmoney, dsubjects, stability, houselvl, fendings);
  }
  fclose(fp);
}

void updatestats()
{
  long newupdate = time(NULL);
  int delta = newupdate - lastupdate;
  if (delta > 0)
  {
    money += (dmoney + aberrations/25) * delta;
    aberrations += daberrations * delta;
    subjects += dsubjects * delta;
    lastupdate = time(NULL);
  }
}
