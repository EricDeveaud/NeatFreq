/*
  Copyright (c) 2010 Gordon Gremme <gremme@zbh.uni-hamburg.de>

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

#ifndef BIOSEQ_COLLECTION_H
#define BIOSEQ_COLLECTION_H

#include "core/str_array_api.h"

typedef struct GtBioseqCollection GtBioseqCollection;

GtBioseqCollection* gt_bioseq_collection_new(GtStrArray *sequence_files,
                                             GtError *err);
void                gt_bioseq_collection_delete(GtBioseqCollection*);
int                 gt_bioseq_collection_grep_desc(GtBioseqCollection*,
                                                   const char **rawseq,
                                                   unsigned long *length,
                                                   GtStr *seqid, GtError*);
int                 gt_bioseq_collection_grep_desc_md5(GtBioseqCollection*,
                                                       const char **md5,
                                                       GtStr *seqid, GtError*);
int                 gt_bioseq_collection_md5_to_seq(GtBioseqCollection*,
                                                    const char **seq,
                                                    unsigned long *length,
                                                    GtStr *md5_seqid,
                                                    GtError *err);
int                 gt_bioseq_collection_md5_to_description(GtBioseqCollection*,
                                                            GtStr *desc,
                                                            GtStr *md5_seqid,
                                                            GtError *err);

#endif
