/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// print of daq status, setup, and multi layer setup

#include "typedefs.h"
#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "sys_def.h"
#include "sbs_def.h"
#include "ml_def.h"
#include "s_setup.h"
#include "s_set_ml.h"
#include "s_set_mo.h"
#include "s_daqst.h"
#include "err_mask_def.h"
#include "errnum_def.h"

#ifdef Linux
#define LOUT printf("%s\n",c_line);
#endif
#ifdef Solaris
#define LOUT printf("%s\n",c_line);
#endif
#ifdef Darwin
#define LOUT printf("%s\n",c_line);
#endif

#ifdef WIN32
#define LOUT printf("%s\n",c_line);
#endif
#ifdef Lynx
#include "f_ut_error.h"
#define LOUT f_ut_error("",ERR__MSG_INFO,0,c_line,MASK__PRTTERM);
#endif

CHARS* f_ut_time(CHARS*);

INTS4 f_ut_seg_show (s_daqst* ps_daqst, s_setup* ps_setup, s_set_ml* ps_set_ml, s_set_mo* ps_set_mo)
{
  INTS4 i,j;
  CHARS c_time[32];
  CHARS c_line[128];
  CHARS* ps_master[16]= {"CVC","E6","E7","AEB","CBV","CVI","CAV","RIO2","PC","RIO3","V32C32","RIO4","nn","nn","nn","nn"};

  sprintf(c_line,"%s",f_ut_time(c_time));
  LOUT;
  if(ps_daqst != NULL) {
    sprintf(c_line,"S_daqst *********************************************************************");
    LOUT;
    sprintf(c_line," l_version   __________%5d l_endian   ___________%5d",
            ps_daqst->l_version,          ps_daqst->l_endian);
    LOUT;
    sprintf(c_line," l_daqst_lw   _________%5d l_fix_lw   ___________%5d",
            ps_daqst->l_daqst_lw,         ps_daqst->l_fix_lw);
    LOUT;
    sprintf(c_line," l_sys__n_max_procs   _%5d l_sbs__str_len_64   __%5d",
            ps_daqst->l_sys__n_max_procs, ps_daqst->l_sbs__str_len_64);
    LOUT;
    sprintf(c_line," l_sbs__n_trg_typ   ___%5d bh_verbose_flg   _____%5d",
            ps_daqst->l_sbs__n_trg_typ,   ps_daqst->bh_verbose_flg);
    LOUT;
    sprintf(c_line," bl_n_events   ___%10d bl_r_events   ________%5d",
            ps_daqst->bl_n_events,        ps_daqst->bl_r_events);
    LOUT;
    sprintf(c_line," bl_n_buffers   ___%9d bl_r_buffers   _______%5d",
            ps_daqst->bl_n_buffers,       ps_daqst->bl_r_buffers);
    LOUT;
    sprintf(c_line," bl_n_bufstream   _%9d bl_r_bufstream   _____%5d",
            ps_daqst->bl_n_bufstream,     ps_daqst->bl_r_bufstream);
    LOUT;
    sprintf(c_line," bl_n_kbyte   ____%10d bl_r_kbyte   _________%5d",
            ps_daqst->bl_n_kbyte,         ps_daqst->bl_r_kbyte);
    LOUT;
    sprintf(c_line," bl_n_evserv_events %8d bl_r_evserv_events    %5d",
            ps_daqst->bl_n_evserv_events, ps_daqst->bl_r_evserv_events);
    LOUT;
    sprintf(c_line," bl_n_evserv_kbytes %8d bl_r_evserv_kbytes   _%5d",
            ps_daqst->bl_n_evserv_kbytes, ps_daqst->bl_r_evserv_kbytes);
    LOUT;
    sprintf(c_line," bl_n_strserv_bufs %9d bl_r_strserv_bufs   __%5d",
            ps_daqst->bl_n_strserv_bufs,  ps_daqst->bl_r_strserv_bufs);
    LOUT;
    sprintf(c_line," bl_n_strserv_kbytes %7d bl_r_strserv_kbytes   %5d",
            ps_daqst->bl_n_strserv_kbytes,ps_daqst->bl_r_strserv_kbytes);
    LOUT;
    sprintf(c_line," bl_n_kbyte_tape  %10d bl_r_kbyte_tape   ____%5d",
            ps_daqst->bl_n_kbyte_tape,    ps_daqst->bl_r_kbyte_tape);
    LOUT;
    sprintf(c_line," bl_n_kbyte_file   %9d l_free_streams________%5d",
            ps_daqst->bl_n_kbyte_file,    ps_daqst->l_free_streams);
    LOUT;
    sprintf(c_line," l_block_length   _____%5d l_record_size   ______%5d",
            ps_daqst->l_block_length,     ps_daqst->l_record_size);
    LOUT;
    sprintf(c_line," l_block_size   _______%5d bl_flush_time   ______%5d",
            ps_daqst->l_block_size,       ps_daqst->bl_flush_time);
    LOUT;
    sprintf(c_line," l_open_vol   _________%5d l_open_file   ________%5d",
            ps_daqst->l_open_vol,         ps_daqst->l_open_file);
    LOUT;
    sprintf(c_line," l_max_tape_size   __%7d l_pos_on_tape   ____%7d",
            ps_daqst->l_max_tape_size,    ps_daqst->l_pos_on_tape);
    LOUT;
    sprintf(c_line," l_file_auto   ________%5d l_file_cur   _________%5d",
            ps_daqst->l_file_auto-1,        ps_daqst->l_file_cur-1);
    LOUT;
    sprintf(c_line," l_file_count   _______%5d l_pathnum   __________%5d",
            ps_daqst->l_file_count,       ps_daqst->l_pathnum);
    LOUT;
    sprintf(c_line," l_file_size   ________%5d l_block_count   ______%5d",
            ps_daqst->l_file_size,       ps_daqst->l_block_count);
    LOUT;
    sprintf(c_line," l_rate_on   __________%5d l_rate_sec   _________%5d",
            ps_daqst->l_rate_on,          ps_daqst->l_rate_sec);
    LOUT;
    sprintf(c_line," bl_histo_port  _______%5d bl_run_time   ________%5d",
            ps_daqst->bl_histo_port,       ps_daqst->bl_run_time);
    LOUT;
    sprintf(c_line," l_irq_driv_id   ______%5d l_irq_maj_dev_id   ___%5d",
            ps_daqst->l_irq_driv_id,      ps_daqst->l_irq_maj_dev_id);
    LOUT;
    for(i=0; i<SBS__N_TRG_TYP; i++)
      if(ps_daqst->bl_n_trig[i] != 0) {
        sprintf(c_line," %2d bl_n_trig %9d bl_n_si   _____%9d bl_n_evt   _%9d",
                i,ps_daqst->bl_n_trig[i],ps_daqst->bl_n_si[i],ps_daqst->bl_n_evt[i]);
        LOUT;
      }
    sprintf(c_line," bl_spill_on   _______%d bl_delayed_eb_ena   ___%d bl_event_build_on   %d",
            ps_daqst->bl_spill_on,           ps_daqst->bl_delayed_eb_ena,           ps_daqst->bl_event_build_on);
    LOUT;
    sprintf(c_line," bl_trans_ready   ___%2d bl_trans_connected   _%2d bl_dabc_enabled  _%3d",
            ps_daqst->bl_trans_ready,         ps_daqst->bl_trans_connected,           ps_daqst->bl_dabc_enabled);
    LOUT;

    sprintf(c_line," bl_strsrv_scale   __%2d bl_strsrv_sync   ______%d bl_strsrv_keep   ___%d",
            ps_daqst->bl_strsrv_scale,         ps_daqst->bl_strsrv_sync,           ps_daqst->bl_strsrv_keep);
    LOUT;
    sprintf(c_line," bl_strsrv_scaled   __%d bl_strsrv_nosync   ____%d bl_strsrv_nokeep   _%d",
            ps_daqst->bl_strsrv_scaled,         ps_daqst->bl_strsrv_nosync,           ps_daqst->bl_strsrv_nokeep);
    LOUT;
    sprintf(c_line," bl_evtsrv_maxcli   _%2d bl_evtsrv_scale   ____%2d bl_evtsrv_events  %3d",
            ps_daqst->bl_evtsrv_maxcli,         ps_daqst->bl_evtsrv_scale,           ps_daqst->bl_evtsrv_events);
    LOUT;
    sprintf(c_line," bl_evtsrv_all   _____%d bl_esosrv_maxcli   ___%2d",
            ps_daqst->bl_evtsrv_all,           ps_daqst->bl_esosrv_maxcli);
    LOUT;
//sprintf(c_line," bl_pipe_slots   ___%3d bl_pipe_slots_filled %3d",
//ps_daqst->bl_pipe_slots,           ps_daqst->bl_pipe_slots_filled);LOUT;
//sprintf(c_line," bl_pipe_size_KB %6d bl_pipe_filled_KB %6d",
//ps_daqst->bl_pipe_size_KB,           ps_daqst->bl_pipe_filled_KB);LOUT;

    sprintf(c_line," c_user  ______________%s",ps_daqst->c_user);
    LOUT;
    sprintf(c_line," c_date  ______________%s",ps_daqst->c_date);
    LOUT;
    sprintf(c_line," c_exprun  ____________%s",ps_daqst->c_exprun);
    LOUT;
    sprintf(c_line," c_exper  _____________%s",ps_daqst->c_exper);
    LOUT;
    sprintf(c_line," c_host  ______________%s",ps_daqst->c_host);
    LOUT;
    sprintf(c_line," c_remote______________%s",ps_daqst->c_remote);
    LOUT;
    sprintf(c_line," c_display_____________%s",ps_daqst->c_display);
    LOUT;
    sprintf(c_line," c_anal_segm_name  ____%s",ps_daqst->c_anal_segm_name);
    LOUT;
    sprintf(c_line," c_setup_name  ________%s",ps_daqst->c_setup_name);
    LOUT;
    sprintf(c_line," c_ml/o_setup_name  ___%s",ps_daqst->c_ml_setup_name);
    LOUT;
    sprintf(c_line," c_readout_name  ______%s",ps_daqst->c_readout_name);
    LOUT;
    sprintf(c_line," c_pathstr  ___________%s",ps_daqst->c_pathstr);
    LOUT;
    sprintf(c_line," c_devname  ___________%s",ps_daqst->c_devname);
    LOUT;
    sprintf(c_line," c_tape_label  ________%s",ps_daqst->c_tape_label);
    LOUT;
    sprintf(c_line," c_file_name  _________%s",ps_daqst->c_file_name);
    LOUT;
    sprintf(c_line," c_out_chan  __________%s",ps_daqst->c_out_chan);
    LOUT;

    sprintf(c_line," bh_daqst_initalized %d bh_acqui_started   __%d bh_acqui_running   _%d",
            ps_daqst->bh_daqst_initalized,         ps_daqst->bh_acqui_started,           ps_daqst->bh_acqui_running);
    LOUT;
    sprintf(c_line," bh_setup_loaded   __%d bh_set_ml/o_loaded %d %d bh_cam_tab_loaded   %d",
            ps_daqst->bh_setup_loaded,             ps_daqst->bh_set_ml_loaded,             ps_daqst->bh_set_mo_loaded,           ps_daqst->bh_cam_tab_loaded);
    LOUT;
    sprintf(c_line," bh_trig_master   ___%d bh_histo_enable   ___%d bh_histo_ready   ___%d",
            ps_daqst->bh_trig_master,              ps_daqst->bh_histo_enable,            ps_daqst->bh_histo_ready);
    LOUT;
    sprintf(c_line," bh_event_serv_ready %d bh_ena_evt_copy   ___%d l_procs_run _______%2d",
            ps_daqst->bh_event_serv_ready,         ps_daqst->bh_ena_evt_copy,            ps_daqst->l_procs_run);
    LOUT;
    sprintf(c_line," m_dispatch   _______%d m_msg_log   _________%d m_util   ___________%d",
            ps_daqst->bh_running[SYS__dispatch],   ps_daqst->bh_running[SYS__msg_log],   ps_daqst->bh_running[SYS__util]);
    LOUT;
    sprintf(c_line," m_collector   ______%d m_transport   _______%d m_read_cam_slav ____%d",
            ps_daqst->bh_running[SYS__collector],  ps_daqst->bh_running[SYS__transport], ps_daqst->bh_running[SYS__read_cam_slav]);
    LOUT;
    sprintf(c_line," m_read_meb   _______%d m_event_serv   ______%d m_esone_serv   _____%d",
            ps_daqst->bh_running[SYS__read_meb],   ps_daqst->bh_running[SYS__event_serv],ps_daqst->bh_running[SYS__esone_serv]);
    LOUT;
    sprintf(c_line," m_stream_serv   ____%d m_histogram   _______%d m_sbs_mon   ________%d",
            ps_daqst->bh_running[SYS__stream_serv],ps_daqst->bh_running[SYS__histogram], ps_daqst->bh_running[SYS__sbs_mon]);
    LOUT;
    sprintf(c_line," m_prompt   _________%d m_daq_rate  _________%d m_smi  _____________%d",
            ps_daqst->bh_running[SYS__prompt],ps_daqst->bh_running[SYS__daq_rate],ps_daqst->bh_running[SYS__smi]);
    LOUT;
    sprintf(c_line," m_ar   _____________%d m_rirec  ____________%d m_to  ______________%d",
            ps_daqst->bh_running[SYS__ar],ps_daqst->bh_running[SYS__rirec],ps_daqst->bh_running[SYS__to]);
    LOUT;
    sprintf(c_line," m_ds  ______________%d m_dr  _______________%d m_vme_serv  ________%d",
            ps_daqst->bh_running[SYS__ds],ps_daqst->bh_running[SYS__dr],ps_daqst->bh_running[SYS__vme_serv]);
    LOUT;

    sprintf(c_line," Tasks  ---------------------------------------------------------------------");
    LOUT;
    for(i=0; i<ps_daqst->l_procs_run; i++) {
      sprintf(c_line," %2d pid %5d pprio%3d pact %1d type %2d pname %s",
              i,ps_daqst->l_pid[i],ps_daqst->l_pprio[i],ps_daqst->bh_pact[i],ps_daqst->l_type[i],ps_daqst->c_pname[i]);
      LOUT;
    }
  }

  if(ps_setup != NULL) {
    sprintf(c_line,"S_setup *********************************************************************");
    LOUT;

    sprintf(c_line," l_version ___________________%5d l_endian ___________________%5d",
            ps_setup->l_version,ps_setup->l_endian);
    LOUT;
    sprintf(c_line," bl_struc_len ________________%5d l_fix_lw ___________________%5d",
            ps_setup->bl_struc_len,             ps_setup->l_fix_lw);
    LOUT;
    sprintf(c_line," bl_sbs__n_cr ________________%5d bl_sbs__n_trg_typ __________%5d",
            ps_setup->bl_sbs__n_cr,             ps_setup->bl_sbs__n_trg_typ);
    LOUT;
    sprintf(c_line," bl_no_crates ________________%5d bh_crate_nr ________________%5d",
            ps_setup->bl_no_crates,             ps_setup->bh_crate_nr);
    LOUT;
    sprintf(c_line," bl_se_meb_asy_len ___________%5d bh_rd_typ __________________%5d",
            ps_setup->bl_se_meb_asy_len,        ps_setup->bh_rd_typ);
    LOUT;
    sprintf(c_line," bh_meb_asy_flg ______________%5d bh_col_mode ________________%5d",
            ps_setup->bh_meb_asy_flg,           ps_setup->bh_col_mode);
    LOUT;
    sprintf(c_line," bh_meb_trig_mode ____________%5d bh_special_meb_trig_type ___%5d",
            ps_setup->bh_meb_trig_mode,         ps_setup->bh_special_meb_trig_type);
    LOUT;
    sprintf(c_line," bl_loc_esone_base _______x%08x bl_rem_esone_base ______x%08x",
            ps_setup->bl_loc_esone_base,        ps_setup->bl_rem_esone_base);
    LOUT;
    sprintf(c_line," bl_esone_off ____________x%08x bl_cvc_crr_off _________x%08x",
            ps_setup->bl_esone_off,             ps_setup->bl_cvc_crr_off);
    LOUT;
    sprintf(c_line," bl_cvc_csr_off __________x%08x bl_cvc_clb_off _________x%08x",
            ps_setup->bl_cvc_csr_off,           ps_setup->bl_cvc_clb_off);
    LOUT;
    sprintf(c_line," bl_ml_pipe_base_addr ____x%08x bl_ml_pipe_seg_len _____x%08x",
            ps_setup->bl_ml_pipe_base_addr,     ps_setup->bl_ml_pipe_seg_len);
    LOUT;
    sprintf(c_line," bl_special_meb_trig_base x%08x bl_ml_pipe_len _________x%08x",
            ps_setup->bl_special_meb_trig_base, ps_setup->bl_ml_pipe_len);
    LOUT;
    sprintf(c_line," lp_cvc_irq ______________x%08x bl_cvc_irq_len _________x%08x",
            ps_setup->lp_cvc_irq,               ps_setup->bl_cvc_irq_len);
    LOUT;
    sprintf(c_line," bl_cvc_irq_source_off ___x%08x bl_cvc_irq_mask_off ____x%08x",
            ps_setup->bl_cvc_irq_source_off,    ps_setup->bl_cvc_irq_mask_off);
    LOUT;
    sprintf(c_line," bl_ev_buf_len ________%5d bl_n_ev_buf _______%5d bl_n_stream _______%5d",
            ps_setup->bl_ev_buf_len,    ps_setup->bl_n_ev_buf,   ps_setup->bl_n_stream);
    LOUT;
    sprintf(c_line," bi_evt_typ_sy ________%5d bi_evt_typ_asy ____%5d bi_evt_subtyp_sy __%5d",
            ps_setup->bi_evt_typ_sy,    ps_setup->bi_evt_typ_asy,ps_setup->bi_evt_subtyp_sy);
    LOUT;
    sprintf(c_line," bi_evt_subtyp_asy ____%5d h_se_control ______%5d h_rd_tab_flg ______%5d",
            ps_setup->bi_evt_subtyp_asy,ps_setup->h_se_control,  ps_setup->h_rd_tab_flg);
    LOUT;
    sprintf(c_line," bl_init_read_len _____%5d bl_n_col_retry ____%5d bi_master ___%4s__%5d",
            ps_setup->bl_init_read_len, ps_setup->bl_n_col_retry,ps_master[ps_setup->bi_master-1],ps_setup->bi_master);
    LOUT;
    sprintf(c_line," Crates ---------------------------------------------------------------------");
    LOUT;
    for(i=0; i<SBS__N_CR; i++) {
      if((ps_setup->lp_rem_mem_base[i] != 0) |
          (ps_setup->lp_rem_cam_base[i] != 0) |
          (ps_setup->lp_loc_mem_base[i] != 0) |
          (ps_setup->lp_loc_pipe_base[i] != 0)) {
        sprintf(c_line," %2d rem_mem_base __x%08x rem_mem_off ___x%08x rem_mem_len ___x%08x",
                i,ps_setup->lp_rem_mem_base[i], ps_setup->bl_rem_mem_off[i], ps_setup->bl_rem_mem_len[i]);
        LOUT;
        sprintf(c_line," %2d rem_cam_base __x%08x rem_cam_off ___x%08x rem_cam_len ___x%08x",
                i,ps_setup->lp_rem_cam_base[i], ps_setup->bl_rem_cam_off[i], ps_setup->bl_rem_cam_len[i]);
        LOUT;
        sprintf(c_line," %2d loc_mem_base __x%08x loc_mem_len ___x%08x loc_pipe_base _x%08x",
                i,ps_setup->lp_loc_mem_base[i], ps_setup->bl_loc_mem_len[i], ps_setup->lp_loc_pipe_base[i]);
        LOUT;
        sprintf(c_line," %2d pipe_off ______x%08x pipe_seg_len __x%08x pipe_len __________%5d",
                i,ps_setup->bl_pipe_off[i],     ps_setup->bl_pipe_seg_len[i],ps_setup->bl_pipe_len[i]);
        LOUT;
        sprintf(c_line," %2d init_tab_off __x%08x init_tab_len __x%08x",
                i,ps_setup->bl_init_tab_off[i], ps_setup->bi_init_tab_len[i]);
        LOUT;
        sprintf(c_line," %2d controller_id _____%5d sy_asy_flg ________%5d trig_stat_nr ______%5d",
                i,ps_setup->bh_controller_id[i],ps_setup->bh_sy_asy_flg[i],  ps_setup->bh_trig_stat_nr[i]);
        LOUT;
        sprintf(c_line," %2d trig_cvt __________%5d trig_fct __________%5d rd_flg ____________%5d",
                i,ps_setup->bl_trig_cvt[i],     ps_setup->bl_trig_fct[i],    ps_setup->bh_rd_flg[i]);
        LOUT;
        sprintf(c_line," %2d i_se_typ __________%5d i_se_subtyp _______%5d i_se_procid _______%5d",
                i,ps_setup->i_se_typ[i],        ps_setup->i_se_subtyp[i],    ps_setup->i_se_procid[i]);
        LOUT;
        for(j=0; j<SBS__N_TRG_TYP; j++) {
          if(ps_setup->bi_rd_tab_len[i][j] != 0) {
            sprintf(c_line,"  %2d %2d bl_max_se_len x%08x   bl_rd_tab_off x%08x   bi_rd_tab_len x%08x",
                    i,j,ps_setup->bl_max_se_len[i][j],ps_setup->bl_rd_tab_off[i][j],ps_setup->bi_rd_tab_len[i][j]);
            LOUT;
          }
        }
      }
    }
  }

  if(ps_set_ml != NULL) {
    sprintf(c_line,"S_set_ml ********************************************************************");
    LOUT;
    sprintf(c_line," l_version ______________%5d l_endian _______________%5d",
            ps_set_ml->l_version,      ps_set_ml->l_endian);
    LOUT;
    sprintf(c_line," l_set_ml_lw ____________%5d l_fix_lw _______________%5d",
            ps_set_ml->l_set_ml_lw,    ps_set_ml->l_fix_lw);
    LOUT;
    sprintf(c_line," l_ml__n_rd_pipe ________%5d l_short_len ____________%5d",
            ps_set_ml->l_ml__n_rd_pipe,ps_set_ml->l_short_len);
    LOUT;
    sprintf(c_line," l_long_len _____________%5d l_n_rd_pipe ____________%5d",
            ps_set_ml->l_long_len,     ps_set_ml->l_n_rd_pipe);
    LOUT;
    sprintf(c_line," l_out_mode _____________%5d l_wr_pipe_base_addr x%08x",
            ps_set_ml->l_out_mode,     ps_set_ml->l_wr_pipe_base_addr);
    LOUT;
    sprintf(c_line," l_wr_pipe_len ______x%08x l_wr_pipe_n_frag _______%5d",
            ps_set_ml->l_wr_pipe_len,  ps_set_ml->l_wr_pipe_n_frag);
    LOUT;
    sprintf(c_line," l_ev_buf_len ___________%5d l_n_ev_buf _____________%5d",
            ps_set_ml->l_ev_buf_len,   ps_set_ml->l_n_ev_buf);
    LOUT;
    sprintf(c_line," l_n_stream _____________%5d",
            ps_set_ml->l_n_stream);
    LOUT;
    sprintf(c_line," c_hostname _____________%s",
            ps_set_ml->c_hostname);
    LOUT;
    sprintf(c_line," Pipes ----------------------------------------------------------------------");
    LOUT;
    for(i=0; i<ps_set_ml->l_n_rd_pipe; i++) {
      sprintf(c_line,"  %2d c_rd_hostname     %s",
              i,ps_set_ml->c_rd_hostname[i]);
      LOUT;
      sprintf(c_line,"  %2d c_sbs_setup_path  %s",
              i,ps_set_ml->c_sbs_setup_path[i]);
      LOUT;
      sprintf(c_line,"  %2d l_rd_pipe_base_addr x%08x   l_rd_pipe_len _____x%08x",
              i,ps_set_ml->l_rd_pipe_base_addr[i],ps_set_ml->l_rd_pipe_len[i]);
      LOUT;
      sprintf(c_line,"  %2d l_rd_pipe_n_frag _______%5d   l_rd_host_flg _________%5d",
              i,ps_set_ml->l_rd_pipe_n_frag[i],   ps_set_ml->l_rd_host_flg[i]);
      LOUT;
    }
  }

  if(ps_set_mo != NULL) {
    sprintf(c_line,"S_set_mo ********************************************************************");
    LOUT;
    sprintf(c_line,"ds_hostname       dr_hostname      active");
    LOUT;
    if(ps_set_mo->l_no_senders > ps_set_mo->l_no_receivers) { j = ps_set_mo->l_no_senders; }
    else { j = ps_set_mo->l_no_receivers; }
    for(i = 0; i < j ; i++) {
      sprintf(c_line,"%2d %-16s  %-16s %d",i+1,
              &ps_set_mo->c_ds_hostname[i][0],&ps_set_mo->c_dr_hostname[i][0],ps_set_mo->bl_dr_active[i]);
      LOUT;
    }
    for(i = 0; i < ps_set_mo->l_no_receivers ; i++) {
      sprintf(c_line,"%2d l_ev_buf_len ___%5d l_n_ev_buf __%5d l_n_stream __%5d",i+1,
              ps_set_mo->l_ev_buf_len[i],    ps_set_mo->l_n_ev_buf[i],   ps_set_mo->l_n_stream[i]);
      LOUT;
    }
    sprintf(c_line,"l_max_evt_size ___%8d l_n_frag ____%5d",ps_set_mo->l_max_evt_size,ps_set_mo->l_n_frag);
    LOUT;

  }
  return(0);
}
