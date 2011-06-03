/*	test.cc is a program that will test and prove the minimum moves it take to cover
	the entire board.  It will first try to cover the corners and the sides then utilizes 
	recursion to finsih up the remaining spaces on the board.  The reason for the combination 
	approach is to reduce the time it takes to complete the test.  It would take way to long
	under the full recursion method, because it takes exponentially longer to travers all
	the spaces on the board. The assumption is the shortest path exists when the knight 
	traversed all the postions available on the board without overlaping any of its previous 
	moves.   

	position tested: Corner rank 8 file 8.  Side rank 4 file 1.
	typcial Starting position rank 1 file 2. center posistion rank 5 file 5. 

	This program is written with Microsoft Visual C++ 2010 express
	Chester
*/ 






#include <stdlib.h>
#include <stdio.h>




void printBoard( int cBoard[][8] );			// to display the board
int cMoveP( int cBoard[][8], int *trnk, int *tfle );	// move to cover corners and sides 
int checkCrn( int trnk2, int tfle2 );			// to determine the closest move to corner
int checkSide( int trnk3, int tfle3 );			// to determine the closest move to side
int checkIfFilled(int cBoard[][8]);			// check if the board is fully covered by the knight
							// recurrsion function to cover the remaining spaces
int moveKnight( int cBoard[][8], int *prevRnk, int *prevFle, int *total, int *currRnk, int *currFle);
										


int main(void)
{
	
	int rnk = 0, fle = 0;				// keep track position
	int input = 0, moves = 0;			// keep track of total input and user input
	int cBoard[8][8] = {0};				// initialize chess board
	int dtn = 0;
	
	

	printf("\n\n");

	while( input != 1 )
	{
		if( moves == 0)				// get starting rank and file
		{
			printf("enter starting point ---> rank _ file\n");
			scanf("%d %d", &rnk, &fle );
		}
		if (rnk < 1 || rnk > 8 || fle < 1 || fle > 8 )
			printf("invalid input pls try again\n\n");
		else
		{								
			if( moves == 0 )		// move knight start position
			{
				cBoard[rnk-1][fle-1]= 9;
			}
			else				// move knight to cover corners and side
			{						
				dtn = cMoveP(cBoard, &rnk, &fle);		
			}
			dtn = checkIfFilled(cBoard);	
			if( dtn == 1 )			// check if board is filled.
			{
				printf("Board filled and the total moves taken is: %d\n\n", moves );
				printBoard(cBoard);
				printf("\n\nEnding location is %d , %d\n", rnk, fle);
				input = 1;
			}
			else if ( dtn == 4 )		// check if corners are filled
			{							// if so start the recurrsion method
				moveKnight( cBoard, &rnk, &fle, &moves, &rnk, &fle );
				printBoard(cBoard);
				input = 1;
			}
			else
			{
				printBoard(cBoard);
				if( input == 0 )	// giving the choices to move knight manually
				{			// or have the program auto move it
					printf("\nCurrent location is %d , %d\n", rnk, fle);
					printf("\nBoard to be filled, continue? 0 to move manually, 9 to auto move, or 1 to exit\n");
					scanf("%d", &input);
				}
				moves+=1;
			}
		}
	}
	while( input == 1 )				// keeping the cmd prompt up
	{
			printf("total = %d\n", moves);
			printf("\n1 to stay | 2 to exist\n");
			scanf("%d", &input);
	}
	return 0; 

}
void printBoard( int cBoard[][8] )
{
	int x, y;
	printf("\n");
	for ( x = 7; x >= 0; x-- )
	{
		printf("row %d ", x+1 );
		for( y = 0; y < 8; y++ )
		{
			printf("%d ", cBoard[x][y]);
		}
		printf("\n");
	}
	printf("file0 ");
	for( y = 0; y < 8; y++ )
		printf("%d ", y+1);
	printf("\n");

}
int cMoveP( int cBoard[][8], int *trnk, int *tfle)
{
	int sidGrd = 99, crnGrd = 99;
	int x = 0, y = 0, z = 99, r = 1, f = 1;

	for( x = -2; x<=2; x++ )
	{
		
		if ( x != 0 && *trnk +x >=1 && *trnk +x <= 8 )
		{					// check for breach of border
			for( y = -2; y<=2; y++ )		
			{							
				if( x != y && x != y*-1 && y!=0 && *tfle +y >=1 && *tfle +y <= 8)
				{			// check to make sure only the 8 knight moves are tested
					if(cBoard[*trnk+x-1][*tfle+y-1] == 0)
					{
						crnGrd = checkCrn( *trnk+x, *tfle+y);
						if ( crnGrd == 1 )
						{	// prioritized corners over sides	
							*trnk = *trnk+x;
							*tfle = *tfle+y;
							cBoard[*trnk-1][*tfle-1]=9;
							printf("\n\nCourner Found!\n\n");
							return 7;
						}
						else
						{
							z = checkSide( *trnk+x, *tfle+y );
							if(sidGrd > z )
							{
								sidGrd = z;
								r = x;
								f = y;
							}
						}
					}
				}
			}
		}
	}
	*trnk = *trnk+r;
	*tfle = *tfle+f;
	cBoard[*trnk-1][*tfle-1]=9;
	printf("\n\nMoved!\n\n");
	return 8;
}
int checkCrn(int trnk2, int tfle2)
{	
	if ( trnk2 == 1 && tfle2 == 1 )
		return 1;
	else if(trnk2 == 1 && tfle2 == 8 )
		return 1;
	else if (trnk2 == 8 && tfle2 == 1 )
		return 1;
	else if (trnk2 == 8 && tfle2 == 8 )
		return 1;
	else
		return 0;
}
int checkSide(int trnk3, int tfle3)
{
							// check how close the moves are to the sides
	int tz = 99;
	if( trnk3 - 1 < tz )
		tz = trnk3-1;
	if( 8-trnk3 < tz)
		tz = 8-trnk3;
	if( tfle3 - 1 < tz )
		tz = tfle3-1;
	if (8-tfle3 < tz )
		tz = 8-tfle3;
	return tz;
}
int checkIfFilled(int cBoard[][8])
{							// check to see if board is filled
	int x, y, emp = 1;
	
	for( x = 0; x < 8; x++ )
	{
		for (y = 0; y < 8; y++)
		{
			if( cBoard[x][y] == 0 )
				emp = 0;
		}
	}
	if( emp == 0 )
	{						// check if corners are filled when board is not filled
		if( cBoard[0][0] == 9 && cBoard[7][7] == 9 && cBoard[0][7] == 9 && cBoard[7][0] ==9 )
			return 4;
		else 
			return 0;					
	}
	else
		return 1;
}

int moveKnight( int cBoard[][8], int *prevRnk, int *prevFle, int *total, int *currRnk, int *currFle )
{										

	int opr= *prevRnk, opf = *prevFle;		// keep track of previous position during recursive calls

	printBoard(cBoard);

	if( *currRnk -2 >= 1 && *currFle -1 >= 1 && cBoard[*currRnk-2-1][*currFle-1-1] != 9)
	{						//move knight in direction of 7 o'clock
			
			if( cBoard[*currRnk-2-1][*currFle-1-1] != 1 )
			{				// check if the position has traversed already
				cBoard[*currRnk-2-1][*currFle-1-1] = 9;
				if(checkIfFilled(cBoard) == 1)
					return 1;	// advance knight to the next positio
				*prevRnk = *currRnk; *prevFle = *currFle;
				*currRnk -=2; *currFle-=1;
				*total+=1;
				*total+= moveKnight(cBoard, prevRnk, prevFle, total, currRnk, currFle);
				if(checkIfFilled(cBoard) == 1)
					return 0;	// if the board is filled, shortest path is found
				cBoard[*currRnk-1][*currFle-1] = 0;
				*currRnk = *prevRnk; *currFle = *prevFle;
				*prevRnk = opr; *prevFle = opf;
							// backing knight to previous position when hit a dead end
				
			}
	}
	if( *currRnk -1 >= 1 && *currFle -2 >= 1 && cBoard[*currRnk-1-1][*currFle-2-1] != 9)
	{						//move knight in direction of 8 o'clock
			
			if( cBoard[*currRnk-1-1][*currFle-2-1] != 1 )
			{
				cBoard[*currRnk-1-1][*currFle-2-1] = 9;
				if(checkIfFilled(cBoard) == 1)
					return 1;
				*prevRnk = *currRnk; *prevFle = *currFle;
				*currRnk -=1; *currFle-=2;
				*total+=1;
				*total+= moveKnight(cBoard, prevRnk, prevFle, total, currRnk, currFle);
				if(checkIfFilled(cBoard) == 1)
					return 0;
				cBoard[*currRnk-1][*currFle-1] = 0;
				*currRnk = *prevRnk; *currFle = *prevFle;
				*prevRnk = opr; *prevFle = opf;
			}
	}
	if( *currRnk +1 <= 8 && *currFle -2 >= 1 && cBoard[*currRnk+1-1][*currFle-2-1] != 9)
	{						//move knight in direction of 8 o'clock
			
			if( cBoard[*currRnk+1-1][*currFle-2-1] != 1 )
			{
				cBoard[*currRnk+1-1][*currFle-2-1] = 9;
				if(checkIfFilled(cBoard) == 1)
					return 1;
				*prevRnk = *currRnk; *prevFle = *currFle;
				*currRnk +=1; *currFle-=2;
				*total+=1;
				*total+= moveKnight(cBoard, prevRnk, prevFle, total, currRnk, currFle);
				if(checkIfFilled(cBoard) == 1)
					return 0;
				cBoard[*currRnk-1][*currFle-1] = 0;
				*currRnk = *prevRnk; *currFle = *prevFle;
				*prevRnk = opr; *prevFle = opf;
			}
	}
	if( *currRnk +2 <= 8 && *currFle -1 >= 1 && cBoard[*currRnk+2-1][*currFle-1-1] != 9)
	{						//move knight in direction of 10 o'clock
			
			if( cBoard[*currRnk+2-1][*currFle-1-1] != 1 )
			{
				cBoard[*currRnk+2-1][*currFle-1-1] = 9;
				if(checkIfFilled(cBoard) == 1)
					return 1;
				*prevRnk = *currRnk; *prevFle = *currFle;
				*currRnk +=2; *currFle-=1;
				*total+=1;
				*total+= moveKnight(cBoard, prevRnk, prevFle, total, currRnk, currFle);
				if(checkIfFilled(cBoard) == 1)
					return 0;
				cBoard[*currRnk-1][*currFle-1] = 0;
				*currRnk = *prevRnk; *currFle = *prevFle;
				*prevRnk = opr; *prevFle = opf;
			}
	}
	if( *currRnk +2 <= 8 && *currFle +1 <= 8 && cBoard[*currRnk+2-1][*currFle+1-1] != 9)
	{						//move knight in direction of 11 o'clock
			
			if( cBoard[*currRnk+2-1][*currFle+1-1] != 1 )
			{
				cBoard[*currRnk+2-1][*currFle+1-1] = 9;
				if(checkIfFilled(cBoard) == 1)
					return 1;
				*prevRnk = *currRnk; *prevFle = *currFle;
				*currRnk +=2; *currFle+=1;
				*total+=1;
				*total+= moveKnight(cBoard, prevRnk, prevFle, total, currRnk, currFle);
				if(checkIfFilled(cBoard) == 1)
					return 0;
				cBoard[*currRnk-1][*currFle-1] = 0;
				*currRnk = *prevRnk; *currFle = *prevFle;
				*prevRnk = opr; *prevFle = opf;
			}
	}
	if( *currRnk +1 <= 8 && *currFle +2 <= 8 && cBoard[*currRnk+1-1][*currFle+2-1] != 9)
	{						//move knight in direction of 1 o'clock
			
			if( cBoard[*currRnk+1-1][*currFle+2-1] != 1 )
			{
				cBoard[*currRnk+1-1][*currFle+2-1] = 9;
				if(checkIfFilled(cBoard) == 1)
					return 1;
				*prevRnk = *currRnk; *prevFle = *currFle;
				*currRnk +=1; *currFle+=2;
				*total+=1;
				*total+= moveKnight(cBoard, prevRnk, prevFle, total, currRnk, currFle);
				if(checkIfFilled(cBoard) == 1)
					return 0;
				cBoard[*currRnk-1][*currFle-1] = 0;
				*currRnk = *prevRnk; *currFle = *prevFle;
				*prevRnk = opr; *prevFle = opf;			
			}
	}
	if( *currRnk -1 >= 1 && *currFle +2 <= 8 && cBoard[*currRnk-1-1][*currFle+2-1] != 9)
	{						//move knight in direction of 4 o'clock
			
			if( cBoard[*currRnk-1-1][*currFle+2-1] != 1 )
			{
				cBoard[*currRnk-1-1][*currFle+2-1] = 9;
				if(checkIfFilled(cBoard) == 1)
					return 1;
				*prevRnk = *currRnk; *prevFle = *currFle;
				*currRnk -=1; *currFle+=2;
				*total+=1;
				*total+= moveKnight(cBoard, prevRnk, prevFle, total, currRnk, currFle);
				if(checkIfFilled(cBoard) == 1)
					return 0;
				cBoard[*currRnk-1][*currFle-1] = 0;
				*currRnk = *prevRnk; *currFle = *prevFle;
				*prevRnk = opr; *prevFle = opf;
			}
	}
	if( *currRnk -2 >= 1 && *currFle +1 <= 8 && cBoard[*currRnk-2-1][*currFle+1-1] != 9)//5
	{						//move knight in direction of 5 o'clock
			

			if( cBoard[*currRnk-2-1][*currFle+1-1] != 1 )
			{
				cBoard[*currRnk-2-1][*currFle+1-1] = 9;
				if(checkIfFilled(cBoard) == 1)
					return 1;
				*prevRnk = *currRnk; *prevFle = *currFle;
				*currRnk -=2; *currFle+=1;
				*total+=1;
				*total+= moveKnight(cBoard, prevRnk, prevFle, total, currRnk, currFle);
				if(checkIfFilled(cBoard) == 1)
					return 0;
				cBoard[*currRnk-1][*currFle-1] = 0;
				*currRnk = *prevRnk; *currFle = *prevFle;
				*prevRnk = opr; *prevFle = opf;
			}
	}
	if(checkIfFilled(cBoard) == 1)
	{
				printf("board is filled\n\n");

				return 0;
	}
	else
	{						// to back the knight up and to remember the path has been traversed
		cBoard[*currRnk-1][*currFle-1] = 1;
		
		return -1;
	}
}

