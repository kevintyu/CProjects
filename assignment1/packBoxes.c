#include <stdio.h>
#include <stdlib.h>

int main()
{
  int packages = 24;
  int small = 0;
  int medium = 0;
  int large = 0;

  while ((small + medium + large) != 24) {
    small = rand() %25;
    medium = rand() %25;
    large = rand() %25;
  }
  
  printf("%d small %d medium %d large\n", small, medium, large);
  return 0;
}
