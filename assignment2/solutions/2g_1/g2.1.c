#include <stdio.h>
#include <ctype.h>

#define MAXSIZE 32

void encrypt(int, char*);
void decrypt(int, char*);

char* strcpy(char* dst, const char* src) {
  while(*dst++ = *src++) {
  }
  return dst;
}

int atoi(char* string) {
  int result = 0;
  int acc = 1;
  char* ptr = string;

  while (*ptr++ != 0) {
  }
  *ptr--;

  while (ptr-- != string) {
    result += (*ptr - 48) * acc;
    acc *= 10;
  }

  return result;
}

void print_message (char* string, char* buffer) {
  printf("%s", string);
  printf("%s", buffer);
  printf("\n");
}

void caesar_encryption (int cipher_shift, const char* string) {
  char buffer[MAXSIZE];

  strcpy(buffer, string);
  print_message("The original message: ", (char *)string);

  encrypt(cipher_shift, buffer);
  print_message("The encrypted message: ", buffer);

  decrypt(cipher_shift, buffer);
  print_message("The decrypted message: ", buffer);
}

int main (int argc, char** argv) {
  if (argc != 3) {
    printf("Usage: %s cipher_shift message\n", argv[0]);
    return -1;
  }

  caesar_encryption(atoi(argv[1]), argv[2]);
  return 0;
}

/*
  Functions you have to implement
*/

#define ALPHA_START 'A'
#define ALPHA_END 'Z'
#define ALPHA_LEN 26

void encrypt(int cipher_shift, char* string)
{
    cipher_shift = cipher_shift % ALPHA_LEN;

    while (*string != 0)
    {
        if (*string != ' ')
        {
            *string = (toupper(*string) + cipher_shift) % (ALPHA_END + 1);
            if (*string < ALPHA_START) *string += ALPHA_START;
        }

        string++;
    }
}

void decrypt(int cipher_shift, char* string)
{
    cipher_shift = cipher_shift % ALPHA_LEN;

    while (*string != 0)
    {
        if (*string != ' ')
        {
            *string = *string - cipher_shift;
            if (*string < ALPHA_START) *string += ALPHA_LEN;
        }

        string++;
    }
}
