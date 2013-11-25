//============================================================================
// Name        : jrecog.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstring>

#include <stdio.h>
#include <cstdlib>
#include <dirent.h>

#include "jpeglib/jpeg_decoder.h"
using namespace Jpeg;

#include "Recog.h"
using namespace Recog;


char *readfile(const char *path, int *psize) {
	int buffersize = 128;
	int readsize = 0;
	char *bytes = (char *)malloc(buffersize);
	FILE *file = fopen(path, "rb");
	int aread = 0;
	while (aread = fread(bytes + readsize, buffersize - readsize, buffersize - readsize, file)) {
		readsize += aread;
		if (readsize >= buffersize) {
			buffersize *= 2;
			bytes = realloc(bytes, buffersize);
		}
	}
	*psize = buffersize;
}

void freememory(const char *bytes) {
	free((void *)bytes);
}

void strtolower(char *p) {
	while (p && *p)
		if ('A' <= *p && *p <= 'Z')
			*p = *p++ + ('z' - 'Z');
		else ++p;
}

void strrcut(char *m, char *p) {
	int plen = strlen(p);
	int mlen = strlen(m);
	int i = 0;
	while (m && p && m <= m + mlen - plen) {
		if (strcmp(m + mlen - plen - i--, p)) continue;
		m[mlen - plen - ++i] = 0;
	}
}

int main() {

	printf("hello world\n");


	DIR *dp;
    struct dirent *ep;
    char subpath[100];
    const char *dirname="./j";
    char *filename;
    int recogCount = 0;

    dp = opendir (dirname);
    if (dp != NULL)
      {
        while (ep = readdir (dp))
        {
          filename=ep->d_name;
          sprintf(subpath, "%s/%s", dirname, filename);
          printf("%s\n", subpath);
          char tmpfilename[100] = strcpy(tmpfilename, filename);
          strtolower(tmpfilename);
          strrcut(tmpfilename, ".jpeg");
          strrcut(tmpfilename, ".jpg");
          int size = 0;
          const char *data = readfile(subpath, &size);
          Decoder *decoder = new Decoder((const unsigned char *)data, size);
          Recog *recog = new Recog;
          if (!recog->recognize(decoder).compare(tmpfilename)) {
        	  ++recogCount;
          }
          freememory(data);
        }
        (void) closedir (dp);
      }

    printf("%d\n", recogCount);

	return 0;
}



