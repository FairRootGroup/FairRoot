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
 * daq status structure
 * sorted for better byte swap  /HE
 * 30.05.2000 replaced run_start by histo_port /HE
 * 25.10.2005 added spill, event building, and pipe status /HE
 * 23.6.2008 DABC support /HE
 */

/* After allocating s_daqst, set by calling f_ut_status_ini */
/* ps_daqst->l_endian   = 1;                      */
/* ps_daqst->l_version  = n;                      */
/* ps_daqst->l_daqst_lw = sizeof(s_daqst)/4;      */
/* ps_daqst->l_fix_lw  = ((int)&c_pname[0][0]-(int)ps_daqst)/4; */
/* ps_daqst->l_sys__n_max_procs =  SYS__N_MAX_PROCS; */
/* ps_daqst->l_sbs__str_len_64 =   SBS__STR_LEN_64;  */
/* ps_daqst->l_sbs__n_trg_typ =    SBS__N_TRG_TYP;   */

typedef struct {
  INTU4 l_endian;                    /* set to 1 if sent */
  INTU4 l_version;                   /* increment in f_ut_status_ini after changes */
  INTU4 l_daqst_lw;                  /* sizeof(s_daqst)/4 : number of lw */
  INTU4 l_fix_lw;                    /* (&c_pname-ps_daqst)/4 : fix number of longwords to read */
  INTU4 l_sys__n_max_procs;          /* maximum number of processes */
  INTU4 l_sbs__str_len_64;           /* String length of process names */
  INTU4 l_sbs__n_trg_typ;            /* maximum number of triggers */
  INTU4 bh_daqst_initalized;         /* crea_daqst */
  INTU4 bh_acqui_started;            /* util(f_ut_op_trig_mod), read_cam_slav, read_meb */
  INTU4 bh_acqui_running;            /* collector, read_cam_slav, read_meb  */
  INTU4 l_procs_run;                 /* processes running (index in l_pid) */
  INTU4 bh_setup_loaded;             /* util(f_ut_load_setup) */
  INTU4 bh_set_ml_loaded;            /* util(f_ut_load_ml_setup) */
  INTU4 bh_set_mo_loaded;            /* util(f_ut_load_mo_setup) */
  INTU4 bh_cam_tab_loaded;           /* read_cam_slav, read_meb) */
  INTS4 l_free_streams;              /* transport */
  INTU4 bl_n_events;                 /* collector */
  INTU4 bl_n_buffers;                /* collector f_col_format */
  INTU4 bl_n_bufstream;              /* transport */
  INTU4 bl_n_kbyte;                  /* transport */
  INTU4 bl_n_evserv_events;          /* event_serv f_ev_checkevt  */
  INTU4 bl_n_evserv_kbytes;          /* event_serv f_ev_send */
  INTU4 bl_n_strserv_bufs;           /* stream_serv  */
  INTU4 bl_n_strserv_kbytes;         /* stream_serv  */
  INTU4 bl_n_kbyte_tape;             /* transport  */
  INTU4 bl_n_kbyte_file;             /* transport */
  INTU4 bl_r_events;                 /* rate  */
  INTU4 bl_r_buffers;                /* rate  */
  INTU4 bl_r_bufstream;              /* rate */
  INTU4 bl_r_kbyte;                  /* rate  */
  INTU4 bl_r_kbyte_tape;             /* rate  (from l_block_count) */
  INTU4 bl_r_evserv_events;          /* rate */
  INTU4 bl_r_evserv_kbytes;          /* rate  */
  INTU4 bl_r_strserv_bufs;           /* rate  */
  INTU4 bl_r_strserv_kbytes;         /* rate */
  INTU4 bl_flush_time;               /* stream flush time                */
  INTS4 l_pathnum;                   /* path number of open device */
  INTU4 l_block_length;              /* current block length */
  INTU4 l_pos_on_tape;               /* current tape position in kB */
  INTU4 l_max_tape_size;             /* maximal tape length in kB */
  INTU4 l_file_count;                /* file count on volume */
  INTU4 l_file_auto;                 /* file count on volume */
  INTU4 l_file_cur;                  /* file count on volume */
  INTU4 l_file_size;                 /* file size */
  INTU4 l_block_count;               /* buffers on file */
  INTU4 l_block_size;                /* block size (=buffer) in bytes */
  INTU4 l_record_size;               /* record size on bytes */
  INTS4 l_open_vol;                  /* open mode of volume */
  INTS4 l_open_file;                 /* open  file flag */
  INTS4 l_rate_on;                   /* for m_daq_rate */
  INTS4 l_rate_sec;                  /* for m_daq_rate */
  INTU4 bh_trig_master;              /* util(f_ut_op_trig_mod) */
  INTU4 bh_histo_enable;             /* collector */
  INTU4 bh_histo_ready;              /* collector */
  INTU4 bh_ena_evt_copy;             /* collector */
  INTU4 bl_n_trig[SBS__N_TRG_TYP];   /* Trigger counter (read_cam_slav or read_meb) */
  INTU4 bl_n_si  [SBS__N_TRG_TYP];   /* Invalid subevents (collector) */
  INTU4 bl_n_evt [SBS__N_TRG_TYP];   /* Valid triggers (collector) */
  INTU4 bl_r_trig[SBS__N_TRG_TYP];   /* Rate Trigger counter (read_cam_slav or read_meb) */
  INTU4 bl_r_si  [SBS__N_TRG_TYP];   /* Rate Invalid subevents (collector) */
  INTU4 bl_r_evt [SBS__N_TRG_TYP];   /* Rate Valid triggers (collector) */
  INTU4 bh_running[SYS__N_MAX_PROCS];/* run bit for tasks */
  INTU4 l_pid[SYS__N_MAX_PROCS];     /* pid table */
  INTU4 l_type[SYS__N_MAX_PROCS];    /* Type number defined in sys_def.h */
  INTS4 l_pprio[SYS__N_MAX_PROCS];   /* daq processes priority */
  /*   f_ut_init_daq_proc,  */
  /*   f_ut_clear_daqst,    */
  /*   f_ut_exit_daq_proc,  */
  /*   f_ut_show_acq,       */
  /*   dispatch,            */
  /*   prompt               */
  /*   tasks                */
  INTU4 bh_pact[SYS__N_MAX_PROCS];   /* daq processes, 1 = active, as pprio */
  INTU4 bh_verbose_flg;              /* */
  INTU4 bl_histo_port;                /* not used */
  INTU4 bl_run_time;                 /* not used */
  INTS4 l_irq_driv_id;               /* 0=irq driver/device not installed */
  INTS4 l_irq_maj_dev_id;            /*            "="                    */
  INTU4 bh_event_serv_ready;         /* event_serv, stream_serv */
  INTU4 bl_strsrv_scale;             /* stream server */
  INTU4 bl_strsrv_sync;              /* stream server  */
  INTU4 bl_strsrv_nosync;            /* stream server  */
  INTU4 bl_strsrv_keep;              /* stream server  */
  INTU4 bl_strsrv_nokeep;            /* stream server  */
  INTU4 bl_strsrv_scaled;            /* stream server  */
  INTU4 bl_evtsrv_scale;             /* event server  */
  INTU4 bl_evtsrv_events;            /* event server  */
  INTU4 bl_evtsrv_maxcli;            /* event server  */
  INTU4 bl_evtsrv_all;               /* event server  */
  INTU4 bl_esosrv_maxcli;            /* esone server  */
  INTU4 bl_pipe_slots;               /* sub event slots in readout pipe */
  INTU4 bl_pipe_slots_filled;        /* sub event slots used */
  INTU4 bl_pipe_size_KB;             /* readout pipe size */
  INTU4 bl_pipe_filled_KB;           /* readout pipe size occupied */
  INTU4 bl_spill_on;                 /* Spill on/off */
  INTU4 bl_delayed_eb_ena;           /* Delayed event building enabled/disab.*/
  INTU4 bl_event_build_on;           /* Event building on/off */
  INTU4 bl_dabc_enabled;             /* DABC event builder mode off/on */
  INTU4 bl_trans_ready;              /* transport server ready */
  INTU4 bl_trans_connected;          /* Client to transport connected */
  INTU4 bl_no_streams;               /* Number of streams */
  INTU4 bl_user[16];                /* for user */
  INTU4 bl_filler[190];              /* filler */
  INTU4 bl_no_stream_buf;             /* bufs per stream */
  INTU4 bl_rfio_connected;           /* RFIO connected */
  CHARS c_user[SBS__STR_LEN_64];     /* username */
  CHARS c_date[SBS__STR_LEN_64];     /* date of last update (m_daq_rate) */
  CHARS c_exprun[SBS__STR_LEN_64];   /* run name */
  CHARS c_exper[SBS__STR_LEN_64];    /* experiment */
  CHARS c_host[SBS__STR_LEN_64];           /* name of host */
  CHARS c_remote[SBS__STR_LEN_64];         /* name of remote control node */
  CHARS c_display[SBS__STR_LEN_64];         /* name of remote display node */
  CHARS c_anal_segm_name[SBS__STR_LEN_64]; /* name of histogram segment in use */
  /* by f_his_anal() in m_collector   */
  CHARS c_setup_name[SBS__STR_LEN_64];     /* setup table loaded */
  CHARS c_ml_setup_name[SBS__STR_LEN_64];  /* ml setup table loaded */
  CHARS c_readout_name[SBS__STR_LEN_64];   /* readout table loaded */
  CHARS c_pathstr[SBS__STR_LEN_64];        /* path string */
  CHARS c_devname[SBS__STR_LEN_64];        /* Name of tape device */
  CHARS c_tape_label[SBS__STR_LEN_64];     /* current tape label */
  CHARS c_file_name[256];                  /* current file name */
  CHARS c_out_chan[SBS__STR_LEN_64];       /* active ouput media */
  /* ------------------ end of fixed block --------------------------*/
  CHARS c_pname[SYS__N_MAX_PROCS][SBS__STR_LEN_64]; /* as pprio */
} s_daqst;
