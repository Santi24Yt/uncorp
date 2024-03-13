#include <game.h>

int labscreen()
{
  clear();

  wborder(stdscr, '|', '|', '-', '-', '*', '*', '*', '*');

  wdrawasset(stdscr, aberration, 5, 80);

  WINDOW* wins[10];
  int wl = 0;

  WINDOW* houseb = spawnwin(5, 22, 25, 3);
  wins[wl++] = houseb;
  printcenter(houseb, "Upgrade home");

  WINDOW* bhouseb = spawnwin(5, 22, 31, 3);
  wins[wl++] = bhouseb;
  printcenter(bhouseb, "Show home");

  WINDOW* brainb = spawnwin(5, 22, 3, 64);
  wins[wl++] = brainb;
  mvwaddstr(brainb, 1, 2, "-100 money");
  mvwaddstr(brainb, 3, 2, "+10 aberr/t");
  printcenter(brainb, "Neural mod.");

  WINDOW* eyesb = spawnwin(5, 22, 9, 55);
  wins[wl++] = eyesb;
  mvwaddstr(eyesb, 1, 2, "-70 money");
  mvwaddstr(eyesb, 3, 2, "+8 aberr/t");
  printcenter(eyesb, "Eyes mod.");

  WINDOW* armsb = spawnwin(5, 22, 15, 57);
  wins[wl++] = armsb;
  mvwaddstr(armsb, 1, 2, "-50 money");
  mvwaddstr(armsb, 3, 2, "+6 aberr/t");
  printcenter(armsb, "Arms mod.");

  WINDOW* chestb = spawnwin(5, 22, 21, 58);
  wins[wl++] = chestb;
  mvwaddstr(chestb, 1, 2, "-90 money");
  mvwaddstr(chestb, 3, 2, "+9 aberr/t");
  printcenter(chestb, "Chest mod.");

  WINDOW* legsb = spawnwin(5, 22, 27, 62);
  wins[wl++] = legsb;
  mvwaddstr(legsb, 1, 2, "-60 money");
  mvwaddstr(legsb, 3, 2, "+6 aberr/t");
  printcenter(legsb, "Legs mod.");

  WINDOW* newsubb = spawnwin(5, 22, 33, 60);
  wins[wl++] = newsubb;
  printcenter(newsubb, "New subject");



  WINDOW* stats = spawnwin(21, 32, 2, 3);

  int cf = 0;

  int ch = ERR;
  while(1)
  {
    switch (ch)
    {
      /* left */
      case 60420:
      /* up */
      case 60419: 
        if (cf <= 0)
        {
          cf = wl - 1;
        } else {
          cf--;
        }
        break;
      /* right */
      case 60421:
      /* down */
      case 60418:
        if (cf >= wl - 1)
        {
          cf = 0;
        } else {
          cf++;
        }
        break;

      /* enter */
      case 10:
      /* space */
      case 32:
        if (wins[cf] == brainb)
        { 
          if (money < 100)
          {
            break;
          }
          money -= 100;
          daberrations += 10;
          stability -= 5 + (rand() % 20);
        }
        if (wins[cf] == eyesb)
        { 
          if (money < 70)
          {
            break;
          }
          money -= 70;
          daberrations += 8;
          stability -= 4 + (rand() % 16);
        }
        if (wins[cf] == armsb)
        { 
          if (money < 50)
          {
            break;
          }
          money -= 50;
          daberrations += 6;
          stability -= 3 + (rand() % 15);
        }
        if (wins[cf] == chestb)
        { 
          if (money < 90)
          {
            break;
          }
          money -= 90;
          daberrations += 9;
          stability -= 5 + (rand() % 17);
        }
        if (wins[cf] == legsb)
        { 
          if (money < 60)
          {
            break;
          }
          money -= 60;
          daberrations += 6;
          stability -= 2 + (rand() % 15);
        }
        if (wins[cf] == newsubb)
        { 
          if (money < 100)
          {
            break;
          }
          stability = 100;
          subjects++;
        }
        if (wins[cf] == houseb && houselvl < 6)
        { 
          if (money < 10000 * pow(10, houselvl))
          {
            break;
          }
          money -= 10000 * pow(10, houselvl);
          houselvl++;
        }
        if (wins[cf] == bhouseb)
        {
          return 0;
        }
        break;

      case 'q':
        return 1;
    }

    focus(wins, wl, wins[cf]);

    mvwprintw(stats, 2, 2, "                      ");
    mvwprintw(stats, 2, 2, "Aberrations: %lld", aberrations);
    mvwprintw(stats, 3, 2, "                      ");
    mvwprintw(stats, 3, 2, "Money: %lld", money);
    mvwprintw(stats, 4, 2, "                      ");
    mvwprintw(stats, 4, 2, "Subjects: %d", subjects);

    mvwprintw(houseb, 3, 2, "                      ");
    mvwprintw(houseb, 3, 2, "-%lld money", (long long)(10000 * pow(10, houselvl)));

    mvprintw(SCREEN_H - 4, 2, "                     ");
    mvprintw(SCREEN_H - 4, 2, "Stability: %d", stability);
    int bp = stability*50/100;
    int i;
    for (i = 0; i < 50; i++)
    {
      if (i < bp)
      {
        mvaddch(SCREEN_H - 3, 2+i, '#');
      } else {
        mvaddch(SCREEN_H - 3, 2+i, ' ');
      }
    }

    ch = getch();
    wrefresh(stats);
    refresh();
    updatestats();
  }

  return 0;
}
