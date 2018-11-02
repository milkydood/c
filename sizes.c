#include <stdio.h>

int main(int argc, char **argv)
{
  fprintf(stdout,"woo\n");
  fprintf(stdout, "Integer types:\n");
  fprintf(stdout,"<char> %d\n", (int) sizeof(char));
  fprintf(stdout,"<short> %d\n",(int)  sizeof(short));
  fprintf(stdout,"<int> %d\n",(int)  sizeof(int));
  fprintf(stdout,"<long> %d\n", (int) sizeof(long));
  fprintf(stdout,"<long long> %d\n", (int) sizeof(long long));

  fprintf(stdout, "\nPointers:\n");
  fprintf(stdout,"<void*> %d\n", (int) sizeof(void*));

  fprintf(stdout, "\nFloating point types:\n");
  fprintf(stdout,"<float> %d\n", (int) sizeof(float));
  fprintf(stdout,"<double> %d\n", (int) sizeof(double));
  fprintf(stdout,"<long double> %d\n", (int) sizeof(long double));

  fprintf(stdout, "\nSizes from stddef.h:\n");
  fprintf(stdout,"<size_t> %d\n", (int) sizeof(size_t));
 // fprintf(0,"<ptrdiff_t>", sizeof(ptrdiff_t));

  return 0;
}
