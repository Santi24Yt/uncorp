#include <game.h>

int max(int a, int b)
{
  if (a >= b)
  {
    return a;
  }
  return b;
}

void printcenter(WINDOW* win, char* fmt, ...)
{
  va_list args;
  va_start(args, fmt);

  int h;
  int w;
  getmaxyx(win, h, w);


  char* buf = calloc(512, sizeof(char));
  buf[510] = 'x';

  vsprintf(buf, fmt, args);

  if (buf[510] != 'x')
  {
    debug1("Possible buffer overflow");
    close();
    printf("Possible buffer overflow\n");
    exit(1);
  }

  int ofy = strlen(buf)/w/2;

  int cy = max(0, h/2 + h%2 - ofy);
  int cx = max(0, w/2 - strlen(buf)/2 - w%2);

  mvwaddstr(win, cy, cx, buf);

  va_end(args);
  free(buf);
}
