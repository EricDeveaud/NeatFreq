/*
  Copyright (c) 2011 Dirk Willrodt <willrodt@zbh.uni-hamburg.de>
  Copyright (c) 2011 Center for Bioinformatics, University of Hamburg

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

#ifndef SAM_ALIGNMENT_H
#define SAM_ALIGNMENT_H

#include <stdbool.h>

#include "core/alphabet_api.h"
#include "core/str_api.h"
#include "core/types_api.h"

typedef struct GtSamAlignment GtSamAlignment;

GtSamAlignment* gt_sam_alignment_new(GtAlphabet *alphabet);

const char*     gt_sam_alignment_identifier(GtSamAlignment *s_alignment);

/* Returns the number of the reference sequence this alignment corresponds to,
   mapping of numbers to names is done in the sam/bam-header. Access through
   GtSamfileIterator */
int32_t         gt_sam_alignment_ref_num(GtSamAlignment *s_alignment);

/* Returns the starting position of the alignment in the reference sequence */
unsigned long   gt_sam_alignment_pos(GtSamAlignment *s_alignment);

/* Returns length of read, not length of the alignment */
unsigned long   gt_sam_alignment_read_length(GtSamAlignment *s_alignment);

/* Returns encoded read sequence from <s_alignment>. */
const GtUchar*  gt_sam_alignment_sequence(GtSamAlignment *s_alignment);

/* Returns string of qualities in ASCII format as in Sanger FASTQ for the
   read sequence from <s_alignment>.
   The length is the same as the length of the read sequence. */
const GtUchar*  gt_sam_alignment_qualitystring(GtSamAlignment *s_alignment);

/* Returns the number of CIGAR operations in <s_alignment>. */
uint16_t        gt_sam_alignment_cigar_length(GtSamAlignment *s_alignment);

/* Returns the length of CIGAR operation <i> in <s_alignment>. */
uint32_t        gt_sam_alignment_cigar_i_length(GtSamAlignment *s_alignment,
                                                uint16_t i);

/* Returns the type of CIGAR operation <i> in <s_alignment>.
   type is one of [MIDNSHP=X] (see sam/bam fileformat documentation for
   details) */
unsigned char   gt_sam_alignment_cigar_i_operation(GtSamAlignment *s_alignment,
                                                   uint16_t i);
/* For explanation of the flag and how to interpret see samtools
   documentation. */
uint32_t gt_sam_alignment_flag(GtSamAlignment *s_alignment);

/* Checks the flag and returns true if bit is set in flag of <s_alignment>. See
   sam/bam fileformat documentation for explanation of meaning of bits. */
bool     gt_sam_alignment_is_paired(GtSamAlignment *s_alignment);
bool     gt_sam_alignment_is_proper_paired(GtSamAlignment *s_alignment);
bool     gt_sam_alignment_is_unmapped(GtSamAlignment *s_alignment);
bool     gt_sam_alignment_mate_is_unmapped(GtSamAlignment *s_alignment);
bool     gt_sam_alignment_is_reverse(GtSamAlignment *s_alignment);
bool     gt_sam_alignment_mate_is_reverse(GtSamAlignment *s_alignment);
bool     gt_sam_alignment_is_read1(GtSamAlignment *s_alignment);
bool     gt_sam_alignment_is_read2(GtSamAlignment *s_alignment);
bool     gt_sam_alignment_is_secondary(GtSamAlignment *s_alignment);
bool     gt_sam_alignment_has_qc_failure(GtSamAlignment *s_alignment);
bool     gt_sam_alignment_is_optical_pcr_duplicate(GtSamAlignment *s_alignment);

void            gt_sam_alignment_delete(GtSamAlignment *s_alignment);
#endif
