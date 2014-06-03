/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "typedefs.h"
/*
 * N. Kurz
 * global SBS setup parameter structure
 */

/* After allocating s_setup, set in f_ut_setup_ini */
/* ps_setup->l_endian = 1;   */
/* ps_setup->l_version = n;   */
/* ps_setup->bl_struc_len = sizeof(s_setup)/4;   */
/* ps_setup->l_fix_lw = ((int)&lp_rem_mem_base[0]-(int)ps_setup)/4;   */
/* ps_setup->bl_sbs__n_cr = SBS__N_CR;   */
/* ps_setup->bl_sbs__n_trg_typ = SBS__N_TRG_TYP;   */

typedef struct {
  /*---------------------------------------------------------------------------*/
  INTU4 l_endian;            /* set to 1 */
  INTU4 l_version;           /* increment in f_ut_setup_ini after changes */
  INTU4 bl_struc_len;      /* sizeof(s_setup)/4 : length of this structure             */
  INTU4 l_fix_lw;      /* (&lp_rem_mem_base-ps_setup)/4 : swapping size          */
  INTU4 bl_sbs__n_cr;        /* set to SBS__N_CR  */
  INTU4 bl_sbs__n_trg_typ;   /* set to SBS__N_TRG_TYP */
  /*---------------------------------------------------------------------------*/
  INTU4 bi_master;      /* indicates type of master event builder                 */
  /* meb:   1 = CVC, 2 = E6, 3 = E7                         */
  INTU4 bl_no_crates;      /* Number of crates to read (bh_rd_flg > 0)               */
  INTU4 bh_crate_nr;      /* crate nr. of readout processor: meb = 0, slave = 1-15  */
  /* this value will be set by the load setup command and   */
  /* is not parsed from the .usf file                       */
  /*---------------------------------------------------------------------------*/
  INTU4 bl_ev_buf_len;      /* length of single event buffer                          */
  INTU4 bl_n_ev_buf;      /* number of event buffers in a stream                    */
  INTU4 bl_n_stream;      /* number of streams                                      */
  /*---------------------------------------------------------------------------*/
  INTU4 bi_evt_typ_sy;      /* event type of synchronous events,     default = 10     */
  INTU4 bi_evt_typ_asy;      /* event type of asynchronous events,    default = 10     */
  INTU4 bi_evt_subtyp_sy;      /* event subtype of synchronous events,  default = 1      */
  INTU4 bi_evt_subtyp_asy;   /* event subtype of asynchronous events, default = 2      */
  INTS4 h_se_control;      /* serves as branch identifier in a multi-branch system   */
  /*---------------------------------------------------------------------------*/
  INTU4 bh_rd_typ;      /* 0 = standard readout with  readout tables              */
  /* 1 = user readout (function)                            */
  /* if the following bh_meb_asy_flg is set to 1 there will be a second    */
  /* async. subevent pipe installed, which will be collected by the meb    */
  /* collector, but must be filled by a seperate process                   */
  INTU4 bh_col_mode;       /* indicates mode of this MEB collector or master readout:*/
  /* 0 = standard, the collector formats events and passes  */
  /*     the formatted event buffer streams to the          */
  /*     transport                                          */
  /* 1 = collector collects subevents from the various      */
  /*     SBS pipes, but no event formatting will be done.   */
  /*     instead the collected subevents are written into a */
  /*     output pipe for the next layer node of the         */
  /*     multi-branch multi-layer daq system. this mode     */
  /*     requires bl_ml_pipe_base_addr, bl_ml_pipe_seg_len  */
  /*     and bl_ml_pipe_len to be specified (see below).    */
  /* 2 = only m_read_meb and no collector runs on the       */
  /*     SBS master (MEB). Its subevent pipe will be read   */
  /*     by a node of the multi-branch multi-layer daq      */
  /*     system. in this case the mb ml node gets the pipe  */
  /*     specs from bl_pipe_seg_len and bl_pipe_len         */
  /*     (see above).                                       */
  /* 3 = includes both 0 and 1 mode.                        */
  /*---------------------------------------------------------------------------*/
  INTU4 bl_loc_esone_base;   /* base address to execute CAMAC cnafs via the ESONE      */
  /* window on the local crate*/
  INTU4 bl_rem_esone_base;   /* base address to execute CAMAC cnafs via the ESONE      */
  /* window on the remote crate*/
  INTU4 bl_esone_off;      /* offset from standard to ESONE window in bytes          */
  INTU4 bl_cvc_crr_off;      /* offset from  to the CVC CAMAC Read Register            */
  INTU4 bl_cvc_csr_off;      /* offset to the CVC Control and Status Register          */
  INTU4 bl_cvc_clb_off;      /* offset to the CVC CAMAC Lam Buffer                     */
  INTU4 bl_se_meb_asy_len;   /* length of the async. pipe of the master, including     */
  /* control and data                                       */
  INTU4 bh_meb_asy_flg;      /* indicates if meb must collect must an async. pipe      */
  /* residing on the meb: 0 = no, 1 = yes                   */
  INTU4 bl_ml_pipe_base_addr;/* base address of the multi-branch multi-layer daq       */
  /* system output pipe.                                    */
  /* only requested ig bh_col_mode = 1,2                    */
  INTU4 bl_ml_pipe_seg_len;  /* length of the multi-branch multi-layer daq system      */
  /* output pipe.  (total lengt of subevent pipe)           */
  /* only requested ig bh_col_mode = 1,2                    */
  INTU4 bl_ml_pipe_len;       /* number of subevent/fragment slots in the multi-branch  */
  /* multi-layer daq system output pipe                     */
  /* only requested ig bh_col_mode = 1,2                    */
  INTU4 bl_n_col_retry;      /* number of retries the subevent collect process makes   */
  /* until giving up time slice                             */
  /*---------------------------------------------------------------------------*/
  INTU4 bh_meb_trig_mode;    /* if this is set to NON zero a special mode is requested */
  /* for the trigger module serving m_read_meb.             */
  /* this could be:                                         */
  /*       NOT irq (LAM, VME irq)                           */
  /*    or NOT standard base address (VME)                  */
  /*    or NOT local crate                                  */
  /* if bh_meb_trig_mode is NOT 0 always the following two  */
  /* setup paramters will be taken for type and base addr.  */
  /*                                                        */
  /* NOTE: the fast clear and conversion time will be taken */
  /*       from bl_trig_fct[0] and bl_trig_cvt[0] from this */
  /*       setup structure                                  */
  /*                                                        */
  /*  0 = standard = local  interrupt (CAMAC LAM, VME IRQ)  */
  /*  1 = special:   local  interrupt (CAMAC LAM, VME IRQ)  */
  /*  2 = special:   remote VSB interrupt (not yet impleme) */
  /*  3 = special:   polling                                */
  INTU4 bh_special_meb_trig_type;
  /*  1 = CAMAC   type trigger module                       */
  /*  2 = VME     type trigger module                       */
  /*  3 = FASTBUS type triggermodule                        */
  INTU4 bl_special_meb_trig_base;
  /* base address of trigger module acting together with    */
  /* m_read_meb if bh_meb_trig_mode != 0                    */
  /* NOTE: if trigger module is remote the complete (VSB)   */
  /*       base address must be specified. example:         */
  /*       f0580000 for a CAMAC trigger module in crate 2   */
  /*       serving m_read_meb running on an E7 in a VME     */
  /*       crate. (see sketch at end of this file)          */
  /*---------------------------------------------------------------------------*/
  INTU4 lp_cvc_irq;       /* start address of the CVC irq physical segment          */
  INTU4 bl_cvc_irq_len;       /* length of CVC irq phys. segment                        */
  INTU4 bl_cvc_irq_source_off;/* offset from lp_cvc_irq to the CVC irq source register  */
  INTU4 bl_cvc_irq_mask_off;  /* offset from lp_cvc_irq to the CVC irq mask register    */
  /*---------------------------------------------------------------------------*/
  /* all values in this section will be initalized by a loader task */
  INTS4 h_rd_tab_flg;      /* -1 = init and readout tables invalid (this is set by   */
  /*      the write_sbs_setup task                          */
  /* 0  = init and readout tables have to be modified to    */
  /*      virtual cnafs                                     */
  /* 1  = this modification is done and must not be done    */
  /*      before a new table was loaded                     */
  INTU4 bl_init_read_len;      /* total length of init and readout CAMAC cnaf list for   */
  /* all crates and trigger types (in bytes)                */
  /* ------------------ end of fixed block --------------------------*/
  /*---------------------------------------------------------------------------*/
  INTU4 lp_rem_mem_base[SBS__N_CR];
  /* physical base address for accessing slave crate memory */
  /* seen from the MEB (pipes). This could be the VSB       */
  /* base address for accessing remote crates               */
  INTU4 bl_rem_mem_off[SBS__N_CR];
  /* offset from  lp_rem_mem_base[SBS__N_CR] to the memory  */
  /* space of the remote slaves (seen from MEB)             */
  INTU4 bl_rem_mem_len[SBS__N_CR];
  /* lenght of the memory address window with the physical  */
  /* base adress lp_rem_mem_base[SBS__N_CR]                 */
  /*---------------------------------------------------------------------------*/
  INTU4 lp_rem_cam_base[SBS__N_CR];
  /* physical base address for accessing slave directly via CAMAC */
  INTU4 bl_rem_cam_off[SBS__N_CR];
  /* offset from lp_rem_cam_base[SBS__N_CR] to the remote   */
  /* CAMAC space of the slaves (seen from MEB).             */
  INTU4 bl_rem_cam_len[SBS__N_CR];
  /* lenght of the CAMAC address window with the physical   */
  /*---------------------------------------------------------------------------*/
  INTU4 lp_loc_mem_base[SBS__N_CR];
  /* base address for accessing local crate. (could be for  */
  /* example local CAMAC base or extended VME base.)        */
  INTU4 bl_loc_mem_len[SBS__N_CR];
  /* length of physical segment for accessing local crate   */
  /* starting from lp_loc_mem_base[SBS__N_CR].              */
  /*---------------------------------------------------------------------------*/
  INTU4 l_loc_pipe_type[SBS__N_CR];
  /* type of subevent pipe:   0: with smem_create           */
  /*                          1: direct mapping             */
  INTU4 lp_loc_pipe_base[SBS__N_CR];
  /* RAM start address of the crate controller (used for    */
  /* location of subevent pipe)                             */
  INTU4 bl_pipe_off[SBS__N_CR];
  /* offset from lp_ram_loc_start to start of the remote    */
  /* communication segment slave <-> master seen from the   */
  /* slave in bytes = start of subevent pipe                */
  INTU4 bl_pipe_seg_len[SBS__N_CR];
  /* length of the remote communication segment in bytes    */
  /* = total lengt of subevent pipe                         */
  INTU4 bl_pipe_len[SBS__N_CR];      /* number of subevent slots in a pipe                     */
  INTU4 bh_controller_id[SBS__N_CR];
  /* bh_controller_id MUST be set for ESONE CNAF execution  */
  /* 1 = CVC, 2 = E6, 3 = E7, 4 = AEB, 5 = CBV, 6 = CVI     */
  /* 7 = CAV (Q and X inverted)                             */
  INTU4 bh_sy_asy_flg[SBS__N_CR];
  /* indicates if this crate must be readout synchronous    */
  /* or asynchronous: 0 = synchronous, 1 = asynchronous     */
  /* this flag is only valid for crates with intelligent    */
  /* controller. At this point it is decided wether a crate */
  /* is readout sync. or async.                             */
  INTU4 bh_trig_stat_nr[SBS__N_CR];/* CAMAC station nr. of the trigger module, must be 1     */
  INTU4 bl_trig_cvt[SBS__N_CR];      /* conversion time of trigger module                      */
  INTU4 bl_trig_fct[SBS__N_CR];     /* fast clear acceptance time of trigger module           */
  INTS4 i_se_typ[SBS__N_CR];     /* subevent typ, default = 10                             */
  INTS4 i_se_subtyp[SBS__N_CR];     /* subevent subtyp: CAMAC = 1, FASTBUS = 2                */
  INTS4 i_se_procid[SBS__N_CR];     /* subevent processor id                                  */
  /*---------------------------------------------------------------------------*/
  INTU4 bh_rd_flg[SBS__N_CR];
  /* 0 = crate not readout                                  */
  /* 1 = crate read out by meb                              */
  /* 2 = crate readout by intelligent crate controller      */
  INTU4 bl_init_tab_off[SBS__N_CR];
  /* offset from start of readout table segment to the      */
  /* start of the init table as a function of crate number  */
  /* (in longwords)                                         */
  INTU4 bi_init_tab_len[SBS__N_CR];
  /* lenght of the init tables. if one of this values is 0  */
  /* it means that this crate must not be not initalized    */
  /* (in longwords)                                         */
  INTU4 bl_max_se_len[SBS__N_CR][SBS__N_TRG_TYP];
  /* maximal subevent length [b] of this crate and trigger  */
  INTU4 bl_rd_tab_off[SBS__N_CR][SBS__N_TRG_TYP];
  /* offset from start of readout table segment to the      */
  /* start of the readout tables as a function of crate     */
  /* number and trigger type (in longwords)                 */
  INTU4 bi_rd_tab_len[SBS__N_CR][SBS__N_TRG_TYP];
  /* lenght of the readout tables. if one of this values    */
  /* is 0 it means that this crate for this trigger type is */
  /* not read out (in longwords)                            */
  /*---------------------------------------------------------------------------*/
} s_setup;

/*
*  address offset for memory access from the master event builder to the slave
*  CVC's via VSB. these offsets point to the memory address 0x100000 seen
*  from the slave CVC, which is the beginning of the RAM of the CVC. only
*  longword access possible, the following offsets are given in bytes.
*
*  in the case of accessing non local crates by CAMAC cnaf's via VSB, the
*  shown address offset (CAM_CRT_OFF) between two consecutive crates is
*  automatically included by crate number contained in the cnaf. the effective
*  physical offset to the cnafs is 0x08180000
*/
/*----------------------------------------------------------------------------!
!     VSB and CAMAC memory on the CVC slaves, seen from the MEB CVC           !
!                                                                             !
!                                                                             !
!          0x8000000           0x8200000           0x8400000                  !
!               |                   |                   |                     !
!               |                   |                   |                     !
!               |    VSB_CRT_OFF    |    VSB_CRT_OFF    |                     !
!    V S B      |===================|===================|===...               !
!               |      0x200000     |      0x200000     |                     !
!               |                   |                   |                     !
!               |              crate|1             crate|2                    !
!               |                   |                   |                     !
! VSB_CAM_START | (VSB_OFF = 0x0)                                             !
!==============>|                                                             !
!   0x8000000   |                                    |                   |    !
!               |                               crate|1             crate|2   !
!               |                                    |                   |    !
!               |    CAM_OFF     |    CAM_CRT_OFF    |    CAM_CRT_OFF    |    !
!   C A M A C   |================|===================|===================|==..!
!               |    0x180000    |     0x200000      |      0x200000     |    !
!               |                |                   |                   |    !
!               |                |                   |                   |    !
!          0x8000000        0x8180000           0x8380000           0x8580000 !
!----------------------------------------------------------------------------*/
