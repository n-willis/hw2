#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double get_time() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + tv.tv_usec * 1e-6;
}

int main(int argc, char** argv) {
  if(argc != 2) {
    printf("usage: %s N\n", argv[0]);
    return -1;
  }

  int n = atoi(argv[1]);
  double* a = (double*)malloc(n * n * sizeof(double));
  double* b = (double*)malloc(n * n * sizeof(double));
  double* c = (double*)malloc(n * n * sizeof(double));

  int i, j;
  for(i = 0; i < n; i++) {
    for(j = 0; j < n; j++) {
      a[i * n + j] = i * n + j;
      b[i * n + j] = j * n + i;
      c[i * n + j] = 0;
    }
  }

  double begin = get_time();

  int k;
  for(i = 0; i < n; i++) {
    for(j = 0; j < n; j++) {
      for(k = 0; k < n; k++) {
	c[i * n + j] += a[i * n + k] * b[k * n + j];
      }
    }
  }

  double end = get_time();
  printf("time: %.6lf sec\n", end - begin);

  double sum = 0;
  for(i = 0; i < n; i++) {
    for(j = 0; j < n; j++) {
      sum += c[i * n + j];
      //printf("c[%d][%d] = %lf\n", i, j, c[i * n + j]);
    }
  }

  printf("sum: %.6lf\n", sum);

  free(a);
  free(b);
  free(c);
  return 0;
}
