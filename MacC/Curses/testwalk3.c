#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <fcntl.h>

#include <sys/time.h>
#include <curses.h>

/*this program does not work.*/

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

char *str[4] ={"-","/","|","\\"}; 

main() 
{
  int y=1;
  int x=1;
  int c;
  int yy;
  int xx;
  int flags;

  int cycle = 0;
  int ret;

  /*keypad(initscr(),1);*/

  flags = fcntl(0, F_GETFL); /* get current file status flags */
  flags |= O_NONBLOCK;		/* turn off blocking flag */
  fcntl(0, F_SETFL, flags);		/* set up non-blocking read */

  initscr();

  for(yy=0;yy<10;yy++)
    for(xx=0;xx<15;xx++)
      mvaddch(yy,xx,map[yy][xx]);

  mvaddch(y,x,str[cycle][0]);

  /*c = '\0';*/

  /*
  if(kbhit())
    {
      c=getch();
    }
  */

  while('q'!= c){

    /*timeout(-1);*/

    ret = read (0,&c,sizeof(c));
    if ( -1 == ret )
    {
	c = '\0';
    }

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
    
    mvaddch(y,x,str[cycle][0]);
    
    cycle = (cycle + 1) % 4;

    sleep(1);
  }

  /*Restore the window to the proper setting*/
  endwin();
}



int kbhit(void)
{
  /*  
  struct timeval tv;
  
  fd_set read_fd;
  tv.tv_sec=0;
  tv.tv_usec=0;
  
  FD_ZERO(&read_fd);
  
  FD_SET(0,&read_fd);
  
  if(select(1, &read_fd, NULL, NULL, &tv) == -1)
    
    return 0;
  
  if(FD_ISSET(0,&read_fd))
    { 
      return 1;
    }

  return 0;
  */
}
