#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #include <iostream>

int main()
{
  // declare variables
  float SMALL_PRICE = 5.99;
  float MED_PRICE = 5.99;
  float LARGE_PRICE = 5.99;
  float CARDBOARD = 1.49;
  int numBoxes = 0;
  int packages = 24;
  int small = 0;
  int medium = 0;
  int large = 0;
  int boxCount = 0;
  int packagesRemaining = packages;

  //while loop that randomly generates the number of packages of each size
  srand(time(NULL));
  while ((small + medium + large) != 24) {
    small = rand() % 25;
    medium = rand() % 25;
    large = rand() % 25;
  }

  int smallRemaining = small;
  int mediumRemaining = medium;
  int largeRemaining = large;

  while(packagesRemaining > 0){
    char board[5][4] = {
      {' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' '},
      {' ', ' ', ' ', ' '},
    };
    int count = 0; // represents the number of spaces in the box that are used
    int x = 0;
    int y = 0;

    // printf("%d\n", large); // debugging
    // printf("%d\n", medium); // debugging
    // printf("%d\n", small); // debugging

    while(count < 20 && packagesRemaining != 0){
      while(largeRemaining > 0 && count < 16){

        // int randomS = rand();
        // printf("%d\n", randomS);
        if(count == 0){
          x = 0;
          y = 0;
        }
        if(count == 4){
          x = 2;
          y = 0;
        }
        if(count == 8){
          x = 0;
          y = 2;
        }
        if(count == 12){
          x = 2;
          y = 2;
        }
        board[y][x] = 'L';
        board[y+1][x] = 'L';
        board[y][x+1] = 'L'; //bottom left
        board[y+1][x+1] = 'L';// bottom right

        // printf("%d\n", large); // debugging
        largeRemaining --;
        count += 4;
        packagesRemaining--;
      }
      //printf("%d\n", mediumRemaining); // debugging

      for(int i = 0; i <= 4 && mediumRemaining > 0 && count < 19; i+=2){
        for(int j = 0; j <= 5 && mediumRemaining > 0 && count < 19; j++){
          if(board[j][i] == ' '){
            board[j][i] = 'M';
            board[j][i+1] = 'M';
            count += 2;
            mediumRemaining--;
            packagesRemaining--;
          }
        }
      }
      for(int i = 0; i < 4 && smallRemaining > 0 && count < 20; i++){
        for(int j = 0; j < 5 && smallRemaining > 0 && count < 20; j++){
          if(board[j][i] == ' '){
            board[j][i] = 'S';
            count += 1;
            packagesRemaining--;
            smallRemaining--;
          }
        }
        // printf("%d\n", count ); // debugging
      }
    }
    // printing the packages
    for(int i = 0; i < 5; i++){
      for(int j = 0; j < 4; j++){
        printf("%c", board[i][j]);
        if (j == 3){
          printf("\n" );
        }
      }
    }
    printf("\n" );
    printf("\n" );
    boxCount++;
    numBoxes++;
  }
  printf("Order: Large=%d, Medium=%d, Small=%d \n", large, medium, small);

  printf("%d small %d medium %d large\n", small, medium, large);
  printf("Small (%d units)   $%8.2f\n", small, small*SMALL_PRICE);
  printf("Medium (%d units)  $%8.2f\n", medium, medium*MED_PRICE);
  printf("Large (%d units)   $%8.2f\n", large, large*LARGE_PRICE);
  printf("---------------------------------\n");
  printf("Total %8.2f\n",small*SMALL_PRICE + medium*MED_PRICE + large*LARGE_PRICE);
  printf("Shipping (%d boxes) %8.2f\n", numBoxes,numBoxes*CARDBOARD);
  printf("HST %8.2f\n",small*SMALL_PRICE + medium*MED_PRICE + large*LARGE_PRICE*0.13);
  printf("---------------------------------\n");
  printf("Total %8.2f\n",(small*SMALL_PRICE + medium*MED_PRICE + large*LARGE_PRICE)+(small*SMALL_PRICE + medium*MED_PRICE + large*LARGE_PRICE*0.13));
  return 0;
}
