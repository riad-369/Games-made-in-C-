#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void print_board(char in_board[4][4]); //Function that displays board to player
void fill_board(char in_board[4][4],char in_board2[4][4]); //Function that fills board with $ and random letters into two separate arrays
void pick_cards(char in_board[4][4],char in_board2[4][4],int *); //Function to explore picking cards



int main(void)
{
    char in_board[4][4]; //first array created to store and display $ characters and letters played
	char in_board2[4][4];//second array created to manipulate letters and then swap into array 1
    fill_board(in_board,in_board2); 
	char choice='T'; //default choice assigned to enter do..while loop
	int points=0;//starts the accumulation of the points
	int flag=0;
	int end_game=0;
	printf("Welcome to Memory! Ready Player One...\n\n");
	do{
		flag=0;
		print_board(in_board); //displays the board
		printf("Choose an option:\n");
		printf("(F) Find a match\n"); //Player Prompts 
		printf("(Q) Quit\n");
		printf("Choice:");
		scanf(" %c",&choice);
		if(choice=='F') 
		{
			pick_cards(in_board,in_board2,&flag); //calls pick cards function 
			if(flag==1)
			{
				points++; //Points accumulate if letters are the same
				printf("Your current points: %d\n",points);
				
				
		    }
			end_game++;//accumulates number of plays inorder to know if game has to end
		}
		
	}while((choice!='Q')&&(end_game!=8)); //Loops until player enters Q or player reaches maximum plays
	printf("Your total points: %d. Goodbye!",points);
	
	return 0;
}
	
void pick_cards(char in_board[4][4],char in_board2[4][4],int *flag) //Function to explore picking cards
{
     int choice1,choice2,choice3,choice4;
     printf("Pick first card (row,column):"); //Player prompts
     scanf("%d %d",&choice1,&choice2);
	 printf("Pick second card (row,column):");
	 scanf("%d %d",&choice3,&choice4);
	 for(int x=0;x<1;x++)
	 {
	    if(((choice1==choice3)&&(choice2==choice4)))
	    {
		   break; // Loops breaks once player enters the same letter position twice
	     }
	 	 
	 in_board[choice1][choice2]=in_board2[choice1][choice2]; //array2 with letters are swapped with the first array to display the corresponding letter
	 in_board[choice3][choice4]=in_board2[choice3][choice4];
	 if(in_board2[choice1][choice2]==in_board2[choice3][choice4])//Case 1 Letters are the same
     {
		   printf("\n\nCards match! You get a point!\n");
		   *flag=1; //Flag flipped to 1 to ensure correct points awared
	 }
	 else
		    printf("\n\nCards do not match! Try again!\n");
		   
	 }	
}
	
	
	
	
void print_board(char in_board[4][4])//Function that displays board to player
{
   int x,y;
   printf("\n\nHere's the board:\n\n");
   printf("    0   1   2   3\n");
   for(x=0;x<4;x++)
   {
	  printf("%d",x);
      for(y=0;y<4;y++)
         printf(" | %c",in_board[x][y]); //Display board with corresponding Letters to player
      printf("\n-----------------\n");
   }
   printf("\n");
}
   	  
void fill_board(char in_board[4][4],char in_board2[4][4])//Function that fills board with $ and random letters into two separate arrays
{
   int x,y;
   for(x=0;x<4;x++)
   {
      for(y=0;y<4;y++)
	     in_board[x][y]='$'; //Assigns all characters in the array to $ - This is the display board
		 
   }
   char randChar[8];
   int counter = 0;
   int randNum = 0;
   srand(time(NULL));
   for (counter = 0; counter < 8; counter++)
   {   
          randNum = 26 * (rand() / (RAND_MAX + 1.0)); //finds a random number between 0 and 26
          randNum = randNum + 65; //adds 65 to obtain the ASCII capital letter equilivalent 
          randChar[counter] = (char) randNum; //cast the number to a letter (i.e a random letter)
   }
   in_board2[0][0]=randChar[0];
   in_board2[3][2]=randChar[0];
   in_board2[1][1]=randChar[1];
   in_board2[3][3]=randChar[1]; //manually sets grid to play
   in_board2[2][2]=randChar[2];
   in_board2[3][1]=randChar[2];
   in_board2[1][2]=randChar[3];
   in_board2[2][1]=randChar[3];
   in_board2[0][3]=randChar[4];
   in_board2[2][0]=randChar[4];
   in_board2[3][0]=randChar[5];
   in_board2[1][3]=randChar[5];
   in_board2[0][1]=randChar[6];
   in_board2[0][2]=randChar[6];
   in_board2[1][0]=randChar[7];
   in_board2[2][3]=randChar[7];   
}
			  
			  
			  
			  
			  
			  
			  
			  
			  
		  

         
   
	