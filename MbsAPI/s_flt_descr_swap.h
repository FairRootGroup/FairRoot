/* filter descriptor */
/* -------> Swapped <-------- */
/* --------=========--------- */
struct s_flt_descr {
  /* indices to filter[]  */
  char                   h_fltblkend;       /* end filter block          */
  char                   h_fltblkbeg;   /* begin filter block        */
  char                   hf_fltdescr;       /* filter descriptor         */
  char                   hf_wrtdescr;   /* write descriptor          */
  /* index to flt_descr[] */
  short                  i_descriptors;     /* number of descriptors     */
  char                   h_dummy;
  char                   h_nextdescr;       /* next descriptor           */
};
