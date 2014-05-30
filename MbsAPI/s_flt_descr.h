/* filter descriptor */
struct s_flt_descr {
  char                   hf_wrtdescr;   /* write descriptor          */
  char                   hf_fltdescr;       /* filter descriptor         */
  /* indices to filter[]  */
  char                   h_fltblkbeg;   /* begin filter block        */
  char                   h_fltblkend;       /* end filter block          */
  /* index to flt_descr[] */
  char                   h_nextdescr;       /* next descriptor           */
  char                   h_dummy;
  short                  i_descriptors;     /* number of descriptors     */
};

