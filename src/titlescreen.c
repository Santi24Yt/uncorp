#include <game.h>

int titlescreen()
{
  clear();

  WINDOW* wins[3];
  int wl = 0;

  wborder(stdscr, '|', '|', '-', '-', '*', '*', '*', '*');

  switch (houselvl)
  {
    case 0:
      wdrawasset(stdscr, houselvl0, SCREEN_H - 11, 27);
      break;

    case 1:
      wdrawasset(stdscr, houselvl1, SCREEN_H - 15, 27);
      break;

    case 2:
      wdrawasset(stdscr, houselvl2, SCREEN_H - 17, 27);
      break;

    case 3:
      wdrawasset(stdscr, houselvl3, SCREEN_H - 28, 27);
      break;

    case 4:
      wdrawasset(stdscr, houselvl4, SCREEN_H - 36, 27);
      break;

    case 5:
      wdrawasset(stdscr, houselvl5, SCREEN_H - 41, 27);
      break;

    case 6:
    default:
      wdrawasset(stdscr, houselvl6, SCREEN_H - 41, 27);
      break;
  }

  wdrawasset(stdscr, logotitle, 2, 2);

  WINDOW* playb = spawnwin(7, 22, 2, 95);
  wins[wl++] = playb;
  printcenter(playb, "Play");

  WINDOW* quitb = spawnwin(7, 22, 32, 95);
  wins[wl++] = quitb;
  printcenter(quitb, "Quit - 'q'");

  WINDOW* stats = spawnwin(21, 32, 10, 85);

  int cf = 0;

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
        if (wins[cf] == quitb)
        {
          return 1;
        }
        if (wins[cf] == playb)
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

    ch = getch();
    wrefresh(stats);
    refresh();
    updatestats();
  }

  return 0;
}
