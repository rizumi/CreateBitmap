#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define WIDTH (600)
#define HEIGHT (400)
#define DATA_SIZE (WIDTH * HEIGHT * 4)

int CreatePicture(unsigned char* output)
{
  unsigned char r = 0;
  unsigned char g = 0;
  unsigned char b = 0;
  unsigned char a = 255;
  int stride = WIDTH * 4;

  for(int i=0; i<HEIGHT; i++){
    for(int j=0; j<stride; j+=4){
      int idx = j + (i*stride);
      output[idx] = b;
      output[idx+1] = g;
      output[idx+2] = r;
      output[idx+3] = a;
    }
    r += 1;
    g += 1;
    b += 1;
  }

  return 0;
}

void fputc2LowHigh(unsigned short d, FILE *s)
{
  putc(d & 0xFF, s);
  putc(d >> CHAR_BIT, s);
}

void fputc4LowHigh(unsigned long d, FILE *s)
{
  putc(d & 0xFF, s);
  putc((d >> CHAR_BIT) & 0xFF, s);
  putc((d >> CHAR_BIT * 2) & 0xFF, s);
  putc((d >> CHAR_BIT * 3) & 0xFF, s);
}

int PutHeader(FILE *s)
{
  if( s == NULL || ferror(s)){
    return -1;
  }

  unsigned long int bfOffBits = 14 + 40;

  fputs("BM", s);

  fputc4LowHigh(bfOffBits + (unsigned long)DATA_SIZE, s);

  fputc2LowHigh(0, s);
  fputc2LowHigh(0, s);

  fputc4LowHigh(bfOffBits, s);

  fputc4LowHigh(40, s);

  fputc4LowHigh(WIDTH, s);
  fputc4LowHigh(HEIGHT, s);

  fputc2LowHigh(1, s);
  fputc2LowHigh(32, s);
  
  fputc4LowHigh(0, s);
  fputc4LowHigh(0, s);
  fputc4LowHigh(0, s);
  fputc4LowHigh(0, s);
  fputc4LowHigh(0, s);
  fputc4LowHigh(0, s);

  return 0;
}

int main(int argc, char *argv[])
{
  FILE* f;
  
  unsigned char* b = (unsigned char*)malloc(DATA_SIZE);

  CreatePicture(b);

  f = fopen("test.bmp", "wb");

  PutHeader(f);

  fwrite(b, sizeof(unsigned char), DATA_SIZE, f);

  fclose(f);

  return 0;
}
