#include <game.h>

int titlescreen()
{
  WINDOW* wins[32];
  int wl = 0;

  wdrawasset(stdscr, houselvl4, 5, 27);

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

      case 'q':
        return 1;
    }

    focus(wins, wl, wins[cf]);

    ch = getch();
    refresh();
  }

  return 0;
}
