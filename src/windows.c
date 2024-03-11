#include <game.h>

WINDOW* spawnwin(int h, int w, int sy, int sx)
{
  refresh();

  WINDOW* win = derwin(stdscr, h, w, sy, sx);

  wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
  wrefresh(win);

  return win;
}

void focus(WINDOW** wins, int wl, WINDOW* f)
{
  int i;
  for (i = 0; i < wl; i++)
  {
    if (wins[i] == f)
    {
      wborder(wins[i], '#', '#', '#', '#', '#', '#', '#', '#');
    } else {
      wborder(wins[i], '|', '|', '-', '-', '+', '+', '+', '+');
    }
    wrefresh(wins[i]);
  }
}
