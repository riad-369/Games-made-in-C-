#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shuffle(int [],int); //Shuffles Deck of Cards Before Playing
void deal_hand(int [],int [], int []);// Deals the Deck to each player by dealing half and half
int check_hand(int,int []); //Checks the hand to seek the number of cards in that hand
void compare(int [],int [],int,int,int*,int*,int*); // Compares two different cards to obtain the larger of the two
void display_cards(int [],int [],int*); //Prints the corresponding card number and suite based on the number in the array
void war(int [],int [],int,int,int*,int*,int*,int*,int*); //Occurs when two cards are the same, then compares the next 4th card to obtain the larger of the two or repeat

int main(void)
{  
	int in_deck[52]; //The deck has 52 cards
	int z;
	int j,k;
	int size1=104; //Starting size of each hand is 104
	int size2=104;
	int check1=26;
	int check2=26;
	for(z=0;z<52;z++)
		in_deck[z]=z; //Creates the deck of cards 
	int hand1[size1];
	int hand2[size2];
	for(z=0;z<104;z++){  
		hand1[z]=-1;  //Sets all elements in the array as -1 to be used as placeholders
		hand2[z]=-1;
	}
	
	shuffle(in_deck,52); //shuffle cards
	deal_hand(in_deck,hand1,hand2); //deal cards
	
	int hand_size1,hand_size2;
	printf("Welcome to War!\n");  //Welcome Display for Players
	printf("Shuffling deck...\n");
	printf("Dealing cards...\n\n");
	char choice; 
	int i=0;
	
     
	
	do{
		  int flag=0;
	      hand_size1=check_hand(size1,hand1);
	      hand_size2=check_hand(size2,hand2);
		  
		  printf("Would you like to play (p) or exit (e):");
		  scanf(" %c",&choice); //User enters their choice to play or exit
		  if(choice=='p')
		  {	  
		       display_cards(hand1,hand2,&i); //Prints cards in play to the user
			  
              if(hand1[i]%13!=hand2[i]%13) //Checks if cards are not the same
              {				  
			    compare(hand1,hand2,hand_size1,hand_size2,&i,&check1,&check2); //Calls compare function to compare to different cards to obtain the larger of the two
				flag=1; 
			  }
			  if((hand1[i]%13==hand2[i]%13)&&(flag!=1)) //Checks if cards are the same
			  {
				  printf("\nThe cards match!It's a battle!\nDrawing 3 cards from each player for battle...\n\n"); //Display for players to show start of War
                  war(hand1,hand2,hand_size1,hand_size2,&i,&check1,&check2,&size1,&size2);//Calls war function
			  }	
			  i++;
			  
		  }
		  if((check1>=size1)&&((hand_size1>0)&&(hand_size2>0))){ //Checks Player's 1 hand size to see if it needs to be increased based on previous plays
		       size1=size1+10; //array size increased to facilitate game
		       for(j=check1;j<size1+10;j++)
			   hand1[j]=-1;
	     }
	     if((check2>=size2)&&((hand_size1>0)&&(hand_size2>0))){ //Checks Player's 2 hand size to see if it needs to be increased based on previous plays
		      size2=size2+10;//array size increased to facilitate game
		      for(k=check2;k<size2+10;k++)
			  hand2[k]=-1;
	     }
	     hand_size1=check_hand(size1,hand1); //Obtains the number of cards in play (not -1) 
	     hand_size2=check_hand(size2,hand2);//Obtains the number of cards in play (not -1)
		
	}while(((hand_size1>0)&&(hand_size2>0))&&(choice!='e')); //Game goes on once there are cards in each player's hand and the choice to play is not e (exit)
	if((hand_size1>0)&&(hand_size2<=0))
		printf("Player 1 Wins\n\nGoodbye! Thanks for playing War!"); //Winner Display if Player 1 wins
	else if((hand_size2>0)&&(hand_size1<=0))
		printf("Player 2 Wins\n\nGoodbye! Thanks for playing War!");//Winner Display if Player 2 wins
	else
	printf("\nThe game is a tie!\n\nGoodbye! Thanks for playing War!");//Game is automatically tied once player presses e 
	
	return 0;
}	
void war(int hand1[],int hand2[],int hand_size1,int hand_size2,int *i,int *check1,int *check2,int *size1,int *size2) //Occurs when two cards are the same, then compares the next 4th card to obtain the larger of the two or repeat
{ 
	
	int flag=0;
	do{
		int y=0;
		int war[10];
		int count=0;
		int remove;
		
	    hand_size1=check_hand(*size1,hand1);
	    hand_size2=check_hand(*size2,hand2);
		
		do{ //Puts 8 cards automatically into a temporary array
			
			war[2*y]=hand1[*i];
			war[(2*y)+1]=hand2[*i];
			count++;
			if(count<=4){
				hand1[*i]=-1;
				hand2[*i]=-1;
			}
			*i=*i+1; 
			y++; 
		}while(count!=5);
		*i=*i-1;
		
        if((hand1[*i]%13)<9)		
	    printf("Player 1's card: %d",hand1[*i]%13+2); //Display Player 1's card as number+2 once in range 0-9
	if((hand1[*i]%13)==9)
		printf("Player 1's card: J");//Display Player 1's card as Jack if card mod 13 is equal 9
	if((hand1[*i]%13)==10)
		printf("Player 1's card: Q");//Display Player 1's card as Queen if card mod 13 is equal 10
	if((hand1[*i]%13)==11)
		printf("Player 1's card: K");//Display Player 1's card as King if card mod 13 is equal 11
	if((hand1[*i]%13)==12)
		printf("Player 1's card: A");//Display Player 1's card as Ace if card mod 13 is equal 12
	if((hand1[*i]>=0)&&(hand1[*i]<=12))
		printf("S\n"); //Display Player 1's card suite as Spades if card is within the range 0-12
	if((hand1[*i]>=13)&&(hand1[*i]<=25))
		printf("D\n");//Display Player 1's card suite as Diamonds if card is within the range 13-25
	if((hand1[*i]>=26)&&(hand1[*i]<=38))
		printf("H\n");//Display Player 1's card suite as Hearts if card is within the range 26-38
	if((hand1[*i]>=39)&&(hand1[*i]<=51))
		printf("C\n");//Display Player 1's card suite as Clubs if card is within the range 39-51
	
	
	if((hand2[*i]%13)<9)
	    printf("Player 2's card: %d",hand2[*i]%13+2); 
	if((hand2[*i]%13)==9)
		printf("Player 2's card: J");
	if((hand2[*i]%13)==10)
		printf("Player 2's card: Q");
	if((hand2[*i]%13)==11)
		printf("Player 2's card: K");
	if((hand2[*i]%13)==12)
		printf("Player 2's card: A");
	if((hand2[*i]>=0)&&(hand2[*i]<=12))
		printf("S\n");
	if((hand2[*i]>=13)&&(hand2[*i]<=25))
		printf("D\n");
	if((hand2[*i]>=26)&&(hand2[*i]<=38))
		printf("H\n");
	if((hand2[*i]>=39)&&(hand2[*i]<=51))
		printf("C\n");
        
		if((hand1[*i]%13)>(hand2[*i]%13)) //Checks if Player 1 has the larger card
		{
		    
			for(y=0;y<10;y++) //Awards all the cards to Player 1 with the larger card
			{
				hand1[*check1]=war[y];
				*check1=*check1+1; //end of actual playing card in array incremented
			
				hand_size1++; 
			}
		
			flag=1;
			printf("\nPlayer 1 wins the round! Awarding played cards to Player 1...\n\n");
		}
		if(((hand1[*i]%13)<(hand2[*i]%13))&&(flag!=1))//Check if Player 2 has the larger card
		{
			for(y=0;y<10;y++)
			{
				hand2[*check2]=war[y]; //Awards all the cards to Player 2 with the larger card 
				*check2=*check2+1; //end of actual playing card in array incremented
				
				hand_size2++;
			}
			
			flag=1;
			printf("\nPlayer 2 wins the round! Awarding played cards to Player 2...\n\n"); 
		}
		hand1[*i]=-1;//Previous cards played get assigned -1
		hand2[*i]=-1; //Previous cards played get assigned -1
	}while(flag!=1);
}	
				
	
void display_cards(int hand1[],int hand2[],int *i)//Prints the corresponding card number and suite based on the number in the array
{
	if((hand1[*i]%13)<9)		
	    printf("Player 1's card: %d",hand1[*i]%13+2); //Display Player 1's card as number+2 once in range 0-9
	if((hand1[*i]%13)==9)
		printf("Player 1's card: J");//Display Player 1's card as Jack if card mod 13 is equal 9
	if((hand1[*i]%13)==10)
		printf("Player 1's card: Q");//Display Player 1's card as Queen if card mod 13 is equal 10
	if((hand1[*i]%13)==11)
		printf("Player 1's card: K");//Display Player 1's card as King if card mod 13 is equal 11
	if((hand1[*i]%13)==12)
		printf("Player 1's card: A");//Display Player 1's card as Ace if card mod 13 is equal 12
	if((hand1[*i]>=0)&&(hand1[*i]<=12))
		printf("S\n"); //Display Player 1's card suite as Spades if card is within the range 0-12
	if((hand1[*i]>=13)&&(hand1[*i]<=25))
		printf("D\n");//Display Player 1's card suite as Diamonds if card is within the range 13-25
	if((hand1[*i]>=26)&&(hand1[*i]<=38))
		printf("H\n");//Display Player 1's card suite as Hearts if card is within the range 26-38
	if((hand1[*i]>=39)&&(hand1[*i]<=51))
		printf("C\n");//Display Player 1's card suite as Clubs if card is within the range 39-51
	
	if((hand2[*i]%13)<9)
	    printf("Player 2's card: %d",hand2[*i]%13+2);
	if((hand2[*i]%13)==9)
		printf("Player 2's card: J");
	if((hand2[*i]%13)==10)
		printf("Player 2's card: Q");
	if((hand2[*i]%13)==11)
		printf("Player 2's card: K");
	if((hand2[*i]%13)==12)
		printf("Player 2's card: A");
	if((hand2[*i]>=0)&&(hand2[*i]<=12))
		printf("S\n");
	if((hand2[*i]>=13)&&(hand2[*i]<=25))
		printf("D\n");
	if((hand2[*i]>=26)&&(hand2[*i]<=38))
		printf("H\n");
	if((hand2[*i]>=39)&&(hand2[*i]<=51))
		printf("C\n");
}
void compare(int hand1[],int hand2[],int hand_size1,int hand_size2,int *i,int *check1,int *check2)// Compares two different cards to obtain the larger of the two
{
	if((hand1[*i]%13)>(hand2[*i]%13)) //Checks if Player 1 has the larger card 
    {
        hand1[*check1]=hand2[*i];
        hand1[*check1+1]=hand1[*i]; //Awards Player 1 both cards
		hand1[*i]=-1;//Previous cards get assigned -1
	    hand2[*i]=-1;//Previous cards get assigned -1
		*check1=*check1+2; //end of actual playing card in array incremented by 2
        printf("\nPlayer 1 wins the round! Awarding played cards to Player 1...\n\n");
    }
	else if((hand1[*i]%13)<(hand2[*i]%13))//Checks if Player 2 has the larger card
	{
		hand2[*check2]=hand1[*i];
		hand2[*check2+1]=hand2[*i];//Award Player 2 both cards
		hand1[*i]=-1;
	    hand2[*i]=-1;
		*check2=*check2+2;
        printf("\nPlayer 2 wins the round! Awarding played cards to Player 2...\n\n");
	}
}	
   	
int check_hand(int hand_size,int hand[]) //Checks the hand to seek and return the number of cards in that hand
{
	int count=0;
	for(int x=0;x<hand_size;x++)
	{
		if(hand[x]>-1)
			count++;
	}
	
	return(count);
}
void deal_hand(int in_deck[],int hand1[],int hand2[])// Deals the Deck to each player by dealing half and half
{
   int x,y=0;
   for(x=0;x<26;x++) 
      hand1[x]=in_deck[x];
   for(x=26;x<52;x++)
   {
	   hand2[y]=in_deck[x];
	   y++;
   }   
}   
void shuffle(int in_deck[],int n)//Randomly Shuffles Deck of Cards
{
	srand((unsigned)time(NULL));
	if(n>1){
		int i,k,t;
		for(i=0;i<(n-1);i++){
			k=i+rand()/(RAND_MAX/(n-i)+1);
			t=in_deck[k];
			in_deck[k]=in_deck[i];
			in_deck[i]=t;
	    }
	}
}


