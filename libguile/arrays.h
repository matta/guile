#ifndef SCM_ARRAY_H
#define SCM_ARRAY_H

/* Copyright 1995-1997,1999-2001,2004,2006,2008-2010,2012,2018
     Free Software Foundation, Inc.

   This file is part of Guile.

   Guile is free software: you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as published
   by the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Guile is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
   License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with Guile.  If not, see
   <https://www.gnu.org/licenses/>.  */



#include "libguile/print.h"



/* Multidimensional arrays. Woo hoo!
   Also see ....
 */

#define SCM_VALIDATE_ARRAY(pos, v) \
  do { \
    SCM_ASSERT (SCM_HEAP_OBJECT_P (v) \
                && scm_is_true (scm_array_p (v, SCM_UNDEFINED)), \
                v, pos, FUNC_NAME); \
  } while (0)

/** Arrays */

SCM_API SCM scm_make_array (SCM fill, SCM bounds);
SCM_API SCM scm_make_typed_array (SCM type, SCM fill, SCM bounds);

SCM_API SCM scm_shared_array_root (SCM ra);
SCM_API SCM scm_shared_array_offset (SCM ra);
SCM_API SCM scm_shared_array_increments (SCM ra);

SCM_API SCM scm_make_shared_array (SCM oldra, SCM mapfunc, SCM dims);
SCM_API SCM scm_transpose_array (SCM ra, SCM args);
SCM_API SCM scm_array_contents (SCM ra, SCM strict);
SCM_API SCM scm_array_slice (SCM ra, SCM indices);
SCM_API SCM scm_array_cell_ref (SCM ra, SCM indices);
SCM_API SCM scm_array_cell_set_x (SCM ra, SCM b, SCM indices);

SCM_API SCM scm_list_to_array (SCM ndim, SCM lst);
SCM_API SCM scm_list_to_typed_array (SCM type, SCM ndim, SCM lst);

SCM_API size_t scm_c_array_rank (SCM ra);
SCM_API SCM scm_array_rank (SCM ra);

SCM_API int scm_is_array (SCM obj);
SCM_API SCM scm_array_p (SCM v, SCM unused);
SCM_INTERNAL SCM scm_array_p_2 (SCM);

SCM_API int scm_is_typed_array (SCM obj, SCM type);
SCM_API SCM scm_typed_array_p (SCM v, SCM type);

SCM_API size_t scm_c_array_length (SCM ra);
SCM_API SCM scm_array_length (SCM ra);

SCM_API SCM scm_array_dimensions (SCM ra);
SCM_API SCM scm_array_type (SCM ra);
SCM_API SCM scm_array_type_code (SCM ra);
SCM_API SCM scm_array_in_bounds_p (SCM v, SCM args);

SCM_API SCM scm_c_array_ref_1 (SCM v, ssize_t idx0);
SCM_API SCM scm_c_array_ref_2 (SCM v, ssize_t idx0, ssize_t idx1);

SCM_API void scm_c_array_set_1_x (SCM v, SCM obj, ssize_t idx0);
SCM_API void scm_c_array_set_2_x (SCM v, SCM obj, ssize_t idx0, ssize_t idx1);

SCM_API SCM scm_array_ref (SCM v, SCM args);
SCM_API SCM scm_array_set_x (SCM v, SCM obj, SCM args);
SCM_API SCM scm_array_to_list (SCM v);

typedef struct scm_t_array_dim
{
  ssize_t lbnd;
  ssize_t ubnd;
  ssize_t inc;
} scm_t_array_dim;

/* internal. */

#define SCM_I_ARRAYP(a)	    SCM_TYP16_PREDICATE (scm_tc7_array, a)
#define SCM_I_ARRAY_NDIM(x)  ((size_t) (SCM_CELL_WORD_0 (x)>>17))
#define SCM_I_ARRAY_V(a)    SCM_CELL_OBJECT_1 (a)
#define SCM_I_ARRAY_BASE(a) ((size_t) SCM_CELL_WORD_2 (a))
#define SCM_I_ARRAY_DIMS(a) ((scm_t_array_dim *) SCM_CELL_OBJECT_LOC (a, 3))
#define SCM_I_ARRAY_SET_V(a, v)       SCM_SET_CELL_OBJECT_1(a, v)
#define SCM_I_ARRAY_SET_BASE(a, base) SCM_SET_CELL_WORD_2(a, base)

/* See the array cases in system/vm/assembler.scm. */

static inline SCM
scm_i_raw_array (int ndim)
{
  return scm_words (((scm_t_bits) ndim << 17) + scm_tc7_array, 3 + ndim*3);
}

SCM_INTERNAL SCM scm_i_make_array (int ndim);
SCM_INTERNAL int scm_i_print_array (SCM array, SCM port, scm_print_state *pstate);
SCM_INTERNAL SCM scm_i_shap2ra (SCM args);

SCM_INTERNAL void scm_init_arrays (void);

#endif  /* SCM_ARRAYS_H */
