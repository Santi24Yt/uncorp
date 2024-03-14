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
  mvwaddstr(newsubb, 3, 2, "=100 stab +1 subj");
  printcenter(newsubb, "New subject");



  WINDOW* stats = spawnwin(21, 32, 2, 3);

  int cf = 0;

  int savei = 0;

  int ch = ERR;
  while(1)
  {
    switch (ch)
    {
      /* left */
      case 260:
      /* up */
      case 259: 
        if (cf <= 0)
        {
          cf = wl - 1;
        } else {
          cf--;
        }
        break;
      /* right */
      case 261:
      /* down */
      case 258:
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
          if (money < subjects*100-(subjects/50))
          {
            break;
          }
          money -= subjects*100-(subjects/50);
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
    mvwprintw(stats, 3, 2, "Aberration gain: %d/t", daberrations);

    mvwprintw(stats, 5, 2, "                      ");
    mvwprintw(stats, 5, 2, "Money: %lld", money);
    mvwprintw(stats, 6, 2, "                      ");
    mvwprintw(stats, 6, 2, "Money gain: %d/t", (int)(dmoney + aberrations/25));

    mvwprintw(stats, 8, 2, "                      ");
    mvwprintw(stats, 8, 2, "Subjects: %d", subjects);

    mvwprintw(stats, 10, 2, "                     ");
    mvwprintw(stats, 10, 2, "House lvl: %d/6", houselvl);
    
    mvwprintw(stats, 18, 2, "                     ");
    mvwprintw(stats, 18, 2, "Endings: %d/3", fendings);


    mvwprintw(houseb, 3, 2, "                      ");
    mvwprintw(houseb, 3, 2, "-%lld money", (long long)(10000 * pow(10, houselvl)));

    mvwprintw(newsubb, 1, 2, "-%d money", subjects*100-(subjects/50));

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

    if (money < INT32_MIN)
    {
      return 2;
    }
    if (aberrations < INT32_MIN)
    {
      return 2;
    }

    if (stability < 0)
    {
      return 3;
    }

    if (houselvl >= 6)
    {
      return 4;
    }

    savei++;

    if (savei == 1000)
    {
      saveprogr();
      savei = 0;
    }
  }

  return 0;
}
