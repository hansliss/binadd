#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void usage(char *progname)
{
  fprintf(stderr, "Usage: %s <file> ...\n", progname);
}

#define BUFSIZE 1024*1024*1024

int main(int argc, char *argv[])
{
  static unsigned char inbuf[BUFSIZE];
  static unsigned char outbuf[BUFSIZE];
  unsigned int dlen=0;
  FILE **infiles;
  int infileCount = argc - 1;
  int done=0;

  infiles=(FILE **)malloc(infileCount * sizeof(FILE *));
  for (int i=0; i<infileCount; i++) {
    if (!(infiles[i]=fopen(argv[i + 1],"r"))) {
      perror(argv[i + 1]);
      return -1;
    }
  }
  while (!done) {
    memset(outbuf, 0, BUFSIZE);
    for (int i=0; i<infileCount; i++) {
      if (!(dlen=fread(inbuf, 1, BUFSIZE, infiles[i]))) {
	done=1;
	break;
      } else {
	for (int j=0; j<dlen; j++) {
	  int val = ((int)outbuf[j] + (int)inbuf[j]);
	  if (val > 0xFF) {
	    val = 0xFF;
	  }
	  outbuf[j] = val;
	}
      }
    }
    if (dlen > 0) {
      fwrite(outbuf, 1, dlen, stdout);
    }
  }
	  
  for (int i=0; i<infileCount; i++) {
    fclose(infiles[i]);
  }
  return 0;
}
