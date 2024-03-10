#include <game.h>

void wdrawasset(WINDOW* win, char* asset, int ys, int xs)
{
  int y = ys;
  int x = xs;
  int l = strlen(asset);

  int i;
  for (i = 0; i < l; i++)
  {
    char ch = asset[i];
    if (ch == '\n')
    {
      x = xs;
      y++;
    } else {
      mvwaddch(win, y, x, ch);
      x++;
    }
  }
}
