/* OE2MBX 1.21
   Copyright (C) 2000 Stephan B. Nedregaard (stephan@micropop.com) */

/*  This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef DYNAMIC
#include <liboe.h>
#else
#include "liboe.h"
#endif

#ifdef WINDOWS
#define SLASH '\\'
#else
#define SLASH '/'
#endif

FILE *mbox = NULL;
char *filename = NULL, *fn;

void msgandquit(int h) {
  if (h==0)
    printf("\n  OE2MBX 1.21\n  (c) 2000 Stephan B. Nedregaard - stephan@micropop.com\n\n  Syntax: oe2mbx [OE mailbox]*\n\n");
  else if (h==1) 
    printf("OE2MBX cannot run on this platform. Please consult the Web site at http://www.micropop.com/code/");
  exit(h);
}

void fatal(char *s) {
  printf("Fatal error: %s\n\n",s);
  exit(1);
}

void writeit(char *s) {
  if (mbox==NULL) {
    mbox=fopen(fn,"w");
    if(mbox==NULL) fatal("Cannot create output file");
  }
  fprintf(mbox,"%s",s);
}

int main(int argc, char*argv[]) {
  int i;

  /* Handle errors, help and syntax */
  if (argc<2) msgandquit(0);
  for (i=1;i<argc;i++) 
    if ( !strcmp(argv[i],"-h") || !strcmp(argv[i],"--help") ) 
      msgandquit(0);

  /* Process mailboxes */
  for (i=1;i<argc;i++) {
    oe_data *j;
    printf("Converting %s...\n",argv[i]);
    filename = malloc(strlen(argv[i])+5);
    strcpy(filename,argv[i]);
    strcpy(filename+strlen(filename),".mbx");
    fn = filename+strlen(filename);
    while ((*fn!=SLASH) && (fn!=filename)) fn--;
    if (*fn==SLASH) fn++;
    printf("  => %s\n",fn);
    j = (oe_data*) oe_readbox(argv[i],writeit);
    if (j!=NULL) {
      if (!j->success) printf("  No messages converted"); else
	printf("  %d messages converted",j->success);
      if (j->justheaders) printf(" (%d headers w/o bodies)",j->justheaders);
      if (j->failure) printf(" (%d messages failed)",j->failure);
      printf("\n");
    } else printf("  Empty mailbox\n");
    if (mbox!=NULL) fclose(mbox);
    mbox=NULL;
    free(filename);
  }
  return 0;
}
