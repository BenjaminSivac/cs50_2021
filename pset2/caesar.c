#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
  printf("argc %d\n", argc);
  if (argc != 2) 
  {
    printf("Invalid Input\n");
    return 1;
  }

  string m = argv[1];
  for (char *p = m; *p; p++)
    if (!isdigit(*p)) 
    {
      printf("Expect a number string, but found %s\n", m);
      return 1;
    }

  int k = atoi(argv[1]);
  string p = get_string("plaintext: ");
  
  int l = strlen(p);
  printf("ciphertext: ");
  for (int i = 0; i < l; i++) 
  {
    if (p[i] >= 97 && p[i] <= 122) 
    {
      int a = (int)p[i] + 1 - 97;
      int b = (a + k) % 26;
      int c = b - 1 + 97;
      char cipher = (char)c;
      printf("%c", cipher);
    } 
    else if (p[i] >= 65 && p[i] <= 90) 
    {
      int A = (int)p[i] + 1 - 65;
      int B = (A + k) % 26;
      int C = B - 1 + 65;
      char cipher = (char)C;
      printf("%c", cipher);
    } 
    else 
    {
      char d = p[i];
      printf("%c", d);
    }
  }
  printf("\n");
}