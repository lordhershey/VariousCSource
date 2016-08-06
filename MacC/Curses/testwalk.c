#include <curses.h>

/* compile with -lcurses */

char *map[]={
"***************",
"*      *      *",
"*             *",
"*      *** ****",
"**** ***   *  *",
"*          *  *",
"*          *  *",
"*             *",
"*          *  *",
"***************"
};

main() 
{
  int y=1;
  int x=1;
  int c;
  int yy;
  int xx;
  keypad(initscr(),1);

  for(yy=0;yy<10;yy++)
    for(xx=0;xx<15;xx++)
      mvaddch(yy,xx,map[yy][xx]);
  mvaddch(y,x,'@');

  while('q'!=(c=getch())){
    for(yy=0;yy<10;yy++)
      for(xx=0;xx<15;xx++)
	mvaddch(yy,xx,map[yy][xx]);
    if(KEY_UP==c && ' '==map[y-1][x])
      y--;
    if(KEY_DOWN==c && ' '==map[y+1][x])
      y++;
    if(KEY_LEFT==c && ' '==map[y][x-1])
      x--;
    if(KEY_RIGHT==c && ' '==map[y][x+1])
      x++;
    mvaddch(y,x,'@');
  }

  /*Restore the window to the proper setting*/
  endwin();
}
