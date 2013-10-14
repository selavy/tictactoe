#include "Board.h"

void
clear( board * x )
{
  *x = 0;
}

void
print_board( board x, board y )
{
  board i;
  
  for( i = 0; i < SIZE; ++i )
    {
      if( i % 3 == 0 )
	{
	  printf("\n");
	  if( i != (SIZE - 1) && i != 0 )
	    printf("-----------\n");
	}
      else
	printf("|");

      if( ISSET( x, i ) )
	{
	  printf(" X ");
	}
      else if( ISSET( y, i ) )
	{
	  printf(" O ");
	}
      else
	{
	  printf(" %i ", i);
	}
    }

  printf("\n");
}

int
win( board x )
{
  short i;

  /* 
     should unroll this loop,
     hopefully, the compiler will
     do that for me...
  */
  for( i = 0; i < NUMMASKS; ++i )
    {
      if( ( x & MASKS[i] ) == MASKS[i] )
	return 1;
    }
  return 0;
}
