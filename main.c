#include<stdio.h>
#include<stdlib.h>

#include "Board.h"
#include "TTTIO.h"
#include "AI.h"

struct node * ntree = NULL;

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

  printf("populating tree!");
  
  ntree = malloc( sizeof *ntree );
  if( ntree == NULL )
    {
      printf("Unable to allocate memory for tree!\n");
      exit(EXIT_FAILURE);
    }

  while( 1 )
    {
      print_board( brdx, brdy );

      /* testing AI */
      /*
      if(! curr )
	printf("BEST MOVE: %d\n", solve( brdx, brdy, TRUE ) );
      */
      /* end testing AI */
      /*
      move = get_move( ( brdx | brdy ) );
      */

      if( curr )
	{
	  move = get_move( ( brdx | brdy ) );
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
	  move = solve( brdx, brdy, TRUE );

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


      printf("\nmoves made: %d\n", num_moves( brdx | brdy ) );
      curr ^= 1;
    }
  return 0;
}
