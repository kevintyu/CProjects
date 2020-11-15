#include <stdio.h>

void printEncodedMaze(int maze[], unsigned char dimensions) {
  // loops through each row
  for(int i = 0; i <= dimensions-1; i++){
    // for loop to iterate through each column
    for(int j = dimensions - 1; j >= 0; j--)
      if ((1<<j &maze[i]) != 0){
        // prints "@" to represent a wall when the bit is equal to 1
        printf("@");
        //printf("%d\n", (1<<j)&maze[i]);
      }
      else{
        // prints " " to represent an empty space when the bit is equal to 0
        printf(" ");
        //printf("%d\n", (1<<j)&maze[i]);
      }
       printf("\n");
  }
}

void printEncodedMazeWithPath(int maze[], int path[], unsigned char dimensions){
  // loops through each row
  for(int i = 0; i <= dimensions-1; i++){
    // for loop to iterate through each column
    for(int j = dimensions-1; j >= 0; j--)
      if ((1<<j &maze[i]) != 0){
        // prints "@" to represent a wall when the bit is equal to 1
        printf("@");
        //printf("%d\n", (1<<j)&maze[i]);
      }
      // checks path and maze to determine whether or not to print "." for path
      else if ((1<<j &maze[i]) == 0 && (1<<j &path[i])!=0){
        printf(".");
        //printf("%d\n", (1<<j)&maze[i]);
      }

      else if ((1<<j &maze[i]) == 0){
        printf(" ");
        //printf("%d\n", (1<<j)&maze[i]);
      }
       printf("\n");
  }
}

void encode8by8Maze(char inputMaze[8][8], int encodedMaze[8]){
  for (int i = 0; i < 7; i++){
    int row = 0;
    for (int j = 0; j < 7; j++){
      if (inputMaze[i][j] == 1){
        row = row | (1 << 1);
      }
      else {
        row = row << 1;
      }
      encodedMaze[i] = row;
    }
  }
}

void merge8by8Mazes(int topLeft[8], int topRight[8], int bottomLeft[8], int bottomRight[8], int finalMaze[14]){
  for (int i = 0; i < 7; i++){
    finalMaze[i]=((topLeft[i]>>1)<<7)|(topRight[i]&(~(1<<8)));
    finalMaze[i+7]=((bottomLeft[i+1]>>1)<<7)|(bottomRight[i+1]&(~(1<<8)));
  }
}

int main(){
  int maze[32] = {-1,
      -2146430423,
      -1109928277,
      -1525661045,
      -1602496045,
      -1358950569,
      -1451509759,
      -1927115297,
      -1578180479,
      -1354977603,
      -1476294999,
      -2084818261,
      -1163749757,
      -1964319689,
      -1341614619,
      -1750141691,
      -1256060947,
      -1515522751,
      -1204136611,
      -1955867371,
      -1190652827,
      -1553272339,
      -1100839163,
      -1999963019,
      -631368865,
      -1882138047,
      -1172944163,
      -1412279803,
      -1567107339,
      -164346691,
      -2138762879,
      -1};

    int path[32] ={0,
      0, 0, 0, 12, 8, 56,
      32, 8032, 4416, 134115648, 67354944,
      67109184, 67109312, 133169152, 1048576,
      1835008, 262144, 262144, 262144, 458752, 65536,
      65536, 65536, 65536, 983040, 67633152, 67633152,
      201850880, 164102144, 259522560, 0};

    char maze8and1[8][8] =
   {{1,1,1,1,1,1,1,1},
    {1,0,0,0,1,0,0,1},
    {1,0,1,0,1,1,0,1},
    {1,0,1,0,0,0,0,1},
    {1,0,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,1,0,1,0,1,1},
    {1,1,1,1,1,1,1,1}};

    char maze8and2[8][8] =
    {{1,1,1,1,1,1,1,1},
    {1,0,0,0,0,1,0,1},
    {1,1,1,1,0,1,0,1},
    {1,0,0,1,0,1,1,1},
    {1,1,0,0,0,0,0,1},
    {1,1,1,1,0,1,1,1},
    {1,0,0,0,0,1,0,1},
    {1,1,1,1,1,1,1,1}};

    char maze8and3[8][8] =
    {{1,1,1,1,1,1,1,1},
    {1,0,1,0,0,0,1,1},
    {1,0,1,0,1,0,0,1},
    {1,0,1,0,1,0,1,1},
    {1,0,1,0,1,0,1,1},
    {1,0,1,0,1,0,1,1},
    {1,0,0,0,1,0,0,1},
    {1,1,1,1,1,1,1,1}};

    char maze8and4[8][8] =
    {{1,1,1,1,1,1,1,1},
    {1,0,1,0,1,0,1,1},
    {1,0,1,0,0,0,0,1},
    {1,0,0,0,1,1,1,1},
    {1,1,1,0,1,0,0,1},
    {1,0,0,0,0,0,1,1},
    {1,1,0,1,1,0,0,1},
    {1,1,1,1,1,1,1,1}};

    int empAr1[8];
    int empAr2[8];
    int empAr3[8];
    int empAr4[8];
    int finalArr[14];

    encode8by8Maze(maze8and1, empAr1);
    encode8by8Maze(maze8and2, empAr2);
    encode8by8Maze(maze8and3, empAr3);
    encode8by8Maze(maze8and4, empAr4);

    merge8by8Mazes(empAr1, empAr2, empAr3, empAr4, finalArr);

    printEncodedMaze(maze, 32);
    printEncodedMazeWithPath(maze, path, 32);
    printEncodedMaze(finalArr, 14);

    //printEncodedMaze();
    // merge8by8Mazes(encode8by8Maze(maze8and1))
    return 0;
}
