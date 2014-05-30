#include "typedefs.h"
/* ++++++++++++++++++++++++++
 * +++   err_mask_def.h   +++
 * ++++++++++++++++++++++++++
 * RSMayer
 * 08-Feb-1994
 * output mask definitions
 * last update: 10-Feb-1994:RSM, MASK__DEBUG, MASK__VERBOSE
 * last update: 15-Feb-1994:RSM, File renamed to  err_mask_def.h
 */

#define MASK__DEBUG   1               /* output for debug purpose            */
#define MASK__VERBOSE 2               /* verbose output                      */
/* */
#define MASK__PRTNULL 0x0             /* no output, i.e. output suppressed   */
#define MASK__PRTTERM 0x80000000      /* Terminal output only                */
#define MASK__PRTSLOG 0x20000000      /* Log file output                     */
#define MASK__PRTT    0xa0000000      /* Terminal and log file output        */
#define MASK__PRTGLOG 0x10000000                          /* not implemented */
#define MASK__PRTPLOG 0x08000000                          /* not implemented */
#define MASK__PRTCLOG 0x04000000                          /* not implemented */
#define MASK__PRTERRL 0x40000000                          /* not implemented */
/* */
#define MASK__PRTL 0x20000000                             /* not implemented */
#define MASK__PRTE 0xf0000000                             /* not implemented */
#define MASK__PRTG 0xb0000000                             /* not implemented */
/* */
#define  MASK__PRTNOPAD 0x00000100                        /* not implemented */
/* */
#define MASK__PRTOPEN   1                                 /* not implemented */
#define MASK__PRTCLOSE  2                                 /* not implemented */
#define MASK__PRTFLUSH  4                                 /* not implemented */
