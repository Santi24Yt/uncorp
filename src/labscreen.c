#include <game.h>

int labscreen()
{
  int ch = ERR;
  while(1)
  {
    switch (ch)
    {
      case 'q':
        return 1;
    }
    
    ch = getch();
    refresh();
  }

  return 0;
}
