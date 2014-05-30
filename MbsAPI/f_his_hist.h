#ifndef F_HIS_HIST
#define F_HIS_HIST

#include "typedefs.h"
#include "s_his_comm.h"
#include "s_his_head.h"

/* node, port, base, password, histogram, [header, ] buffer, size */
INTS4 f_his_getbas(CHARS*, INTS4, CHARS*, CHARS*, INTS4**);
INTS4 f_his_getdir(CHARS*, INTS4, CHARS*, CHARS*, CHARS*, INTS4**, INTS4*);
INTS4 f_his_gethis(CHARS*, INTS4, CHARS*, CHARS*, CHARS*, s_his_head**, INTS4**, INTS4*);
INTS4 f_his_server(CHARS*, CHARS*, INTS4*);
INTS4 f_his_wait(INTS4*, CHARS*);
INTS4 f_his_senddir(s_his_head*, INTS4);
INTS4 f_his_sendhis(s_his_head*, INTS4, CHARS*, INTS4*);
INTS4 f_his_close();

#endif
