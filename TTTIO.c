#include "TTTIO.h"
#include "Board.h"

#define MAXSTR 512

int
get_move( board brd )
{
  int move;
  char line[MAXSTR];

  while( 1 )
    {
      printf("Move: ");
      fgets( line, MAXSTR, stdin );

      if( 1 != sscanf( line, "%d", &move ) )
	{
	  printf("Invalid input!\n");
	  continue;
	}

      else if( move < 0 || move >= SIZE )
	{
	  printf("Move out of range!\n");
	  continue;
	}

      else if( ISSET( brd, move ) )
	{
	  printf("Spot already taken!\n");
	  continue;
	}

      else
	{
	  return move;
	}
    }
}
