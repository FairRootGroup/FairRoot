#include "typedefs.h"
/*
 * N. Kurz:
 * global definitions for the single branch system (sbs)
 */

#define SBS__STR_LEN_32      32
#define SBS__STR_LEN_64      64
#define SBS__STR_LEN_96      96
#define SBS__STR_LEN_128     128
#define SBS__N_CR            16 /* maximal nr. of crates in the sbs  */
#define SBS__N_TRG_TYP       16 /* maximal nr. of different trigger types */
#define SBS__B_TRG_TYP       1  /* first valid trigger type */

#define TRIG__CLEARED 0x10

#define SBS__SETUP_TAB       "setup"
#define SBS__READOUT_TAB     "readout_table"
#define SBS__DAQ_STATUS_TAB  "daq_status"
#define REM__MEM_NAME        "rem_mem"
#define REM__CAM_NAME        "rem_cam"
#define LOC__MEM_NAME        "loc_crate_access"
#define SE__MEB_ASY_NAME     "to be defined"
#define SE__PIPE_NAME        "se_pipe"
#define CVC__IRQ_NAME        "CVC_irq_control"
#define EVT__BUF_STREAMS     "event_buffer_streams"

#define LOC__ESONE_NAME      "loc_esone"
#define REM__ESONE_NAME      "rem_esone"
#define LOC__ESONE_LEN       0x50000
#define REM__ESONE_LEN       0x2000000

#define TRIG__VME_BASE       0x2000000L
#define TRIG__VME_SIZE       0x1000L
#define TRIG__VME_NAME       "VME_trig_mod"
#define TRIG__VME_RIO2_OFF   0xE0000000L

#define TRIG__REM_SIZE       0x2000L
#define TRIG__REM_NAME       "rem_trig_mod"
