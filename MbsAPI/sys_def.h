#include "typedefs.h"
/*
 * N. Kurz
 * Lynx specific definitions
 */

#define FALSE              0
#define TRUE               1
#define SYS__N_MAX_PROCS   30
#define SYS__SEGM_BLK_SIZE 0x1000
/* index in daqst-> bh_running[] */
#define SYS__read_meb         0
#define SYS__collector        1
#define SYS__transport        2
#define SYS__event_serv       3
#define SYS__msg_log          4
#define SYS__dispatch         5
#define SYS__util             6
#define SYS__sbs_mon          7
#define SYS__read_cam_slav    8
#define SYS__esone_serv       9
#define SYS__stream_serv     10
#define SYS__histogram       11
#define SYS__prompt          12
#define SYS__daq_rate        13
#define SYS__smi             14
#define SYS__ds              15
#define SYS__dr              16
#define SYS__ar              17
#define SYS__rirec           18
#define SYS__to              19
#define SYS__vme_serv        20
