/*
  Copyright (c) 2008 Gordon Gremme <gremme@zbh.uni-hamburg.de>
  Copyright (c) 2008 Center for Bioinformatics, University of Hamburg

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

#include <stdlib.h>
#include <string.h>
#include "core/assert_api.h"
#include "core/hashtable.h"
#include "core/ma.h"
#include "core/strcmp.h"
#include "extended/type_checker_builtin.h"
#include "extended/type_checker_rep.h"

struct GtTypeCheckerBuiltin {
  const GtTypeChecker parent_instance;
};

#define gt_type_checker_builtin_cast(FTF)\
        gt_type_checker_cast(gt_type_checker_builtin_class(), FTF)

static const char *gt_feature_node_type_strings[] = { "CDS",
                                                     "EST_match",
                                                     "LTR_retrotransposon",
                                                     "SNP",
                                                     "TF_binding_site",
                                                     "cDNA_match",
                                                     "exon",
                                                     "five_prime_UTR",
                                                     "five_prime_splice_site",
                                                     "gene",
                                                     "intron",
                                                     "inverted_repeat",
                                                     "long_terminal_repeat",
                                                     "mRNA",
                                                     "protein_match",
                                                     "repeat_region",
                                                     "target_site_duplication",
                                                     "three_prime_UTR",
                                                     "three_prime_splice_site",
                                                     "transcript",
                                                     "undefined"
                                                   };

static const char* find_type(const char *gft_string)
{
  void *result;
  gt_assert(gft_string);
  /* do not convert undefined string */
  gt_assert(strcmp(gft_string, "undefined"));
  result = bsearch(&gft_string,
                   gt_feature_node_type_strings,
                   sizeof (gt_feature_node_type_strings) /
                   sizeof (gt_feature_node_type_strings[0]),
                   sizeof (char*),
                   gt_strcmpptr);
  if (result)
    return *(char**) result;
  return NULL;
}

static bool gt_type_checker_builtin_create_gft(GT_UNUSED GtTypeChecker
                                               *type_checker,
                                               const char *type)
{
  gt_assert(type_checker && type);
  return find_type(type) ? true : false;
}

const GtTypeCheckerClass* gt_type_checker_builtin_class(void)
{
  static const GtTypeCheckerClass gt_type_checker_class =
    { sizeof (GtTypeCheckerBuiltin),
      gt_type_checker_builtin_create_gft,
      NULL };
  return &gt_type_checker_class;
}

GtTypeChecker* gt_type_checker_builtin_new(void)
{
  GT_UNUSED GtTypeCheckerBuiltin *type_checker_builtin;
  GtTypeChecker *type_checker;
  type_checker = gt_type_checker_create(gt_type_checker_builtin_class());
  type_checker_builtin = gt_type_checker_builtin_cast(type_checker);
  return type_checker;
}
