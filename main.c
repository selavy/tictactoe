#include<stdio.h>
#include<stdlib.h>

#include "Board.h"
#include "TTTIO.h"

int main( int argc, char ** argv )
{
  board brdx;
  board brdy;
  int move;
  int curr;

  curr = 0;
  //  clear( &brdx );
  //clear( &brdy );
  brdx = 0;
  brdy = 0;

  while( 1 )
    {
      print_board( brdx, brdy );
      move = get_move( ( brdx | brdy ) );

      if( curr )
	{
	  /* O's move */
	  SET( brdy, move );
	  if( win( brdy ) )
	    {
	      print_board( brdx, brdy );
	      printf("O's won!\n");
	      return 0;
	    }
	}
      else
	{
	  /* X's move */
	  SET( brdx, move );
	  if( win( brdx ) )
	    {
	      print_board( brdx, brdy );
	      printf("X's won!\n");
	      return 0;
	    }
	}

      if( DRAW( brdx, brdy ) )
	{
	  print_board( brdx, brdy );
	  printf("Cat's game!\n");
	  return 0;
	}

      curr ^= 1;
    }
  return 0;
}
