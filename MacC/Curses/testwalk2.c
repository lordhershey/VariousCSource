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
  char up;
  char down;
  char left;
  char right;

  keypad(initscr(),1);

  for(yy=0;yy<10;yy++)
    for(xx=0;xx<15;xx++)
      mvaddch(yy,xx,map[yy][xx]);
  mvaddch(y,x,'@');

  while('q'!=(c=getch())){
    
    /*
    for(yy=0;yy<10;yy++)
      for(xx=0;xx<15;xx++)
	mvaddch(yy,xx,map[yy][xx]);
    */
    up = (char)mvinch(y-1,x);
    down = (char)mvinch(y+1,x);
    left = (char)mvinch(y,x-1);
    right = (char)mvinch(y,x+1);

    mvaddch(y,x,' ');
    if(KEY_UP==c && ' '== up)
      y--;
    if(KEY_DOWN==c && ' '== down)
      y++;
    if(KEY_LEFT==c && ' '== left)
      x--;
    if(KEY_RIGHT==c && ' '== right)
      x++;
    mvaddch(y,x,'@');
  }

  /*Restore the window to the proper setting*/
  endwin();
}
