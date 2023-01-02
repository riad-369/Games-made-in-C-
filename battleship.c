/*
   Author:Riad Mohammed
   Program:battleship.c
   version:1
   Date:05/01/2020
   Description: This is a single-user, simplified version of battleship 
                whose initial map is stored in a text file containing a description
				of where the opponent's ships are located.The idea is that when your 
				program starts, it will read the description of the opponents map from the
                text file and store it in a 2-dim array.Throughout the game, the player repeatedly tries
                to guess where battleships are located by specifying individual map coordinates 
				(just like in the actual game). For each guess, the program will tell the player 
				if they hit or miss. After each time the player makes a guess, the program will print out 
				an “ASCII art” representation of the playing field (the currently known portion of the map). 
				This will allow the player to see their progress as they play the game.Since there is technically 
				no opposing player (nobody is trying to guess where the player’s battleships are), the player will 
				be limited by the number of “shots” they can take. If the player sinks all of the battleships in 
				fewer than the limit, then they win, otherwise they lose. 
*/

#include <stdio.h>
#include <stdlib.h>

/* Function Prototypes */

int read_map(FILE*,int,int*,int*,int x,int y,char grid2[x][y]); /* Reads the game map from a text file and stores into 2D array */
void print_map(int x,int y,char game_board[x][y]); /* Dispays game map to the player */
void play_game(int *,int x,int y,char grid2[x][y],int *,int *,char game_board[x][y]); /* Controls game mechanics */



int main(int argc,char *argv[]) /* Command Line Arguments Passed: Shot Limit and Map Text File */
{
   FILE *map=fopen(argv[2],"r"); /* Open map text file to read */
   int x,y;
   fscanf(map,"%d",&x); /* Map dimensions read first: Row and Column */
   fscanf(map,"%d",&y);                                               
   int i,j;
   int flag=0; /* Ensures play_game */
   char grid2[x][y]; /* 2D array created to store map */
   
   int shot=atoi(argv[1]); /* 2nd command line argument, number of shots, stored in integer variable */
   int check=read_map(map,shot,&x,&y,x,y,grid2); /* Calling read function */

 
   if (check==-1) /*If shot number from command line is less than number of ships, program terminates */
     return 0;
   else
   {
	  
      char game_board[x][y]; /*2D array created to store game board to be displayed to player */
	  
      for (i=0;i<(x);i++)
      {
         for (j=0;j<(y);j++)
           game_board[i][j]='~';  /*Game Board defaults setting, all ~ */
      }
	  do{ /* Loops until Player runs out of shots or destroys all ships */
	       play_game(&flag,x,y,grid2,&shot,&check,game_board); /* Calling play_game function */
	  }while (shot>0&&check!=0);
	  print_map(x,y,game_board); 
	  if (check>0) /*If any ships remain, player loses */
		  printf("\nCaptain, we ran out of ammo. You lose!");
	  else /*If no ships remain,player wins */
		  printf("\nCaptain, we have sunk all the battleships. You win!");
 
      return 0;
   }
} /* End main program */
int read_map(FILE *map,int shot1, int *x_p,int *y_p,int x,int y,char grid2[x][y])/* Reads the game map from a text file and stores into 2D array */
{
   int i,j; 
   int shot_limit=0;
   fscanf(map,"%d",&*x_p); /* Map dimensions read first: Row and Column */
   fscanf(map,"%d",&*y_p);
   char grid[*x_p][*y_p]; /* Temporary 2d array created based on received dimensions */
   for (i=0;i<(*x_p);i++)   
   {                      /* Nested Loops to read map from text file into 2D array */
      for (j=0;j<(*y_p);j++){  
         fscanf(map," %c",&grid[i][j]);
		 if (grid[i][j]!='~'&&grid[i][j]!='B')
			 return -1;
		 grid2[i][j]=grid[i][j];
         if (grid[i][j]=='B') /* If grid has a 'B', shot limit increments, because shot limit must be >= number of ships */
            shot_limit++;
      }
   }
   fclose(map); /* File closes */
   if (shot1<shot_limit){  /* Program Terminates if shot given in command line is less than number of ships */
       printf("Invalid Shot Limit!\nPlease enter a Shot Limit greater than or equal to %d\n",shot_limit);
       return -1;
   }
   else
       return (shot_limit);
}
void print_map(int x,int y,char game_board[x][y]) /* Dispays game map to the player */
{
    int i,j;
    printf("Map\n\n"); 
    for (i=0;i<(x);i++)
    {
       for (j=0;j<(y);j++)
           printf("%c",game_board[i][j]);
  printf("\n");
    }

}
void play_game(int *flag1,int x,int y,char grid2[x][y],int *shot2,int *shot_limit2,char game_board[x][y]) /* Controls game mechanics */
{
	int a,b,i,j;
	print_map(x,y,game_board); /*Calling print function */
	do{
	printf("%d shots remaining.\n",*shot2);
	printf("Captain, please enter coordinates:");
	scanf("%d %d",&a,&b);
	} while(((a<0)||(b<0))||((a>=x)||(b>=y))); /*Loops until a valid shot coordinate is entered */
	*flag1=1;
	if ((game_board[a][b]!='H')^(game_board[a][b]!='M')^(*flag1==1)){ /*Ensures the player does not enter the same coordinate twice */
	     if ((grid2[a][b]=='B'))
	     {
		    game_board[a][b]='H'; 
		    *shot_limit2=*shot_limit2-1; 
	     }
	     else
	     {
		 game_board[a][b]='M';
    }
	*shot2=*shot2-1; /*Shot decrements */
	}	
}