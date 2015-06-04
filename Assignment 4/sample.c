#include <stdio.h>

int main(int argc, char** argv)
{
  if(argc == 2)
  {
    printf("Command line arg is : %s\n",argv[1]);
  }
  else
  {
  	printf("No command line arg is passed.\n");
  }
  printf("Hello World !!\n This is the great day\n");

  return 0;
}
