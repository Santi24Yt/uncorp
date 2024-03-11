#include <game.h>

int titlescreen()
{
  WINDOW* wins[32];
  int wl = 0;

  wdrawasset(stdscr, houselvl6, 0, 27);

  wdrawasset(stdscr, logotitle, 2, 2);

  WINDOW* playb = spawnwin(7, 22, 2, 95);
  wins[wl++] = playb;
  printcenter(playb, "Play");

  WINDOW* quitb = spawnwin(7, 22, 32, 95);
  wins[wl++] = quitb;
  printcenter(quitb, "Quit - 'q'");

  WINDOW* stats = spawnwin(21, 32, 10, 85);
  printcenter(stats, "test");

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

    ch = getch();
    wrefresh(stats);
    refresh();
  }

  return 0;
}
