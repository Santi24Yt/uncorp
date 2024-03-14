#include <game.h>

int maxhousescreen()
{
  clear();
  saveprogr();

  wborder(stdscr, '|', '|', '-', '-', '*', '*', '*', '*');

  mvaddstr(25, 6, "Ending 3/3 MAX. HOUSE");

  wdrawasset(stdscr, houselvl6, 0, 40);

  mvaddstr(SCREEN_H - 5, 2, "(c)ontinue playing");
  mvaddstr(SCREEN_H - 3, 2, "(n)ew game [remove all progress] (you can copy the gamesave to other directory to save it)");

  mvprintw(2, 2, "                      ");
  mvprintw(2, 2, "Aberrations: %lld", aberrations);
  mvprintw(3, 2, "                      ");
  mvprintw(3, 2, "Aberration gain: %d/t", daberrations);

  mvprintw(5, 2, "                      ");
  mvprintw(5, 2, "Money: %lld", money);
  mvprintw(6, 2, "                      ");
  mvprintw(6, 2, "Money gain: %d/t", (int)(dmoney + aberrations/25));

  mvprintw(8, 2, "                      ");
  mvprintw(8, 2, "Subjects: %d", subjects);

  mvprintw(10, 2, "                     ");
  mvprintw(10, 2, "House lvl: %d/6", houselvl);
  
  int nendings = 0;
  if ((fendings & 0b001) == 0b001)
  {
    nendings++;
  }
  if ((fendings & 0b010) == 0b010)
  {
    nendings++;
  }
  if ((fendings & 0b100) == 0b100)
  {
    nendings++;
  }
  mvprintw(18, 2, "                     ");
  mvprintw(18, 2, "Endings: %d/3", nendings);

  mvprintw(20, 2, "                     ");
  mvprintw(20, 2, "Stability: %d", stability);

  
  int ch = ERR;
  while(1)
  {
    switch (ch)
    {
      case 'c':
        houselvl++;
        return 0;

      case 'n':
        aberrations = 0;
        money = 1000;
        subjects = 0;

        daberrations = 0;
        dmoney = 0;
        dsubjects = 0;

        lastupdate;
        stability = 100;
        houselvl = 0;

        saveprogr();
        return 0;
        break;

      case 'q':
        return 1;
    }

    ch = getch();
    refresh();

  }

  return 0;
}
