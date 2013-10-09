/*
  Copyright (c) 2007 Stefan Kurtz <kurtz@zbh.uni-hamburg.de>
  Copyright (c) 2007 Center for Bioinformatics, University of Hamburg

  Permission to use, copy, modify, and distribute this software for any
  purpose with or without fee is hereby granted, provided that the above
  copyright notice and this permission notice appear in all copies.

  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#ifndef FASTABUFFER_IMP_H
#define FASTABUFFER_IMP_H

#ifndef S_SPLINT_S
#include <unistd.h>
#else
typedef long ssize_t;
#endif

#define OUTPUTFILEBUFFERSIZE 4096
#define INPUTFILEBUFFERSIZE  4096

struct GtFastaBuffer
{
  unsigned int filenum;
  uint64_t linenum;
  unsigned long nextread,
                nextfree;
  bool indesc,
       firstoverallseq,
       firstseqinfile,
       complete,
       nextfile;
  GtQueue *descptr;
  GtFile *inputstream;
  GtUchar outputbuffer[OUTPUTFILEBUFFERSIZE],
        inputbuffer[INPUTFILEBUFFERSIZE];
  ssize_t currentinpos, currentfillpos;
  uint64_t lastspeciallength;
  GtFilelengthvalues *filelengthtab;
  const GtStrArray *filenametab;
  const GtUchar *symbolmap;
  bool plainformat;
  unsigned long *characterdistribution;
  GtArraychar headerbuffer;
};

int gt_fastabuffer_advance(GtFastaBuffer *fb, GtError*);

static inline int gt_fastabuffer_next(GtFastaBuffer *fb,
                                      GtUchar *val,
                                      GtError *err)
{
  if (fb->nextread >= fb->nextfree)
  {
    if (fb->complete)
    {
      return 0;
    }
    if (gt_fastabuffer_advance(fb, err) != 0)
    {
      return -1;
    }
    fb->nextread = 0;
    if (fb->nextfree == 0)
    {
      return 0;
    }
  }
  *val = fb->outputbuffer[fb->nextread++];
  return 1;
}

#endif
