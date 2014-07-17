/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * N.Kurz 8-Jun-1998
 *
 * within this structure the setup information for a   n # m
 * (multiple output/collector) mbs system is specified
 */

#include "typedefs.h"
#include "mo_def.h"

typedef struct {
  INTU4 l_endian;                 /* must be 1 */
  INTU4 l_version;                /* structure version */
  INTU4 l_set_mo_lw;              /* length of structure */
  INTU4 l_swap_lw;                /* longwords to be swapped */
  INTU4 l_max_nodes;              /* set to MO__N_NODE */
  INTU4 l_no_senders;             /* actual number of senders */
  INTU4 l_no_receivers;           /* actual number of receivers */
  INTU4 bl_dr_active[MO__N_NODE]; /* active receivers */

  INTU4 l_rd_pipe_base_addr [MO__N_NODE] [MO__N_NODE];
  /* base addresses of all pipes residing on the ds nodes seen remote    */
  /* from dr nodes  l_rd_pipe_base_addr[dr_node_id][ds_node_id].         */
  /* this setup parametes are only  necessary for an address mapped      */
  /* transfer mode (l_trans_mode = 0).                                   */
  INTU4 l_rd_pipe_seg_len [MO__N_NODE];
  /* size of pipe segments on ds nodes. index is ds id. this information */
  /* is only necessary if transfer type 0 (single shot data transfer)    */
  /* from any of the ds nodes. !!!! WARNING !!!! this information is     */
  /* redundant. the size is also specified in the setup.usf or           */
  /* set_ml.usf of the ds node and must match.                           */
  INTU4 l_rd_pipe_trans_mode [MO__N_NODE] [MO__N_NODE];
  /* data transfer mode from ds nodes to dr nodes                            */
  /* l_rd_pipe_base_addr[dr_node_id][ds_node_id].                        */
  /* transfer mode: 0xxx = address mapped, dr reads data                 */
  /*                1xxx = message oriented mode ( tcp ), ds sends data  */
  /*                01xx = address mapped DMA modes (various)            */
  /*                                                                     */
  /*              0x   0 = standard singe cycle address mapped           */
  /*              0x 101 = VME DMA E7                                    */
  /*              0x 102 = VME DMA RIO2 <- RIO2                          */
  /*              0x 103 = VSB DMA RIO2 <- "any" VSB slave device        */
  /*              0x 104 = PVIC DMA RIO2                                 */
  /*              0x 105 = VME DMA RIO2 <- E7 / VME memory               */
  /*              0x1001 = TCP sockets                                   */
  INTU4 l_form_mode;
  /* two format modes have been forseen, whereas only mode 1 is imple-   */
  /* mented yet.                                                         */
  /* mode 1: ds node sends data, or dr node reads data (depending on     */
  /*         transfer type) to an intermediate event buffer of size      */
  /*         l_max_evt_size. formatting, and possible byte swapping is   */
  /*         done afterwards from the intermediate event buffer into the */
  /*         streams.                                                    */
  /* mode 2: ds node sends data, or dr node reads data and formats       */
  /*         immediately into the streams. not yet implemented           */
  INTU4 l_base_addr_evt_buf[MO__N_NODE];
  /* if l_form_mode = 1:       (intermediate formatting)                 */
  /* for transfer types where address mapped writing from ds node or dma */
  /* data transfer is done a shared segement is needed and created with  */
  /* physical base address l_base_addr_evt_buf and size l_max_evt_size.  */
  /* if l_form_mode = 2:       (direct formatting)                       */
  /* a shared segment for this buffer must also be created for           */
  /* direct formatting into streams if the ds node writes address mapped */
  /* or dma is done. this buffer will be used to hold an event if the    */
  /* actual stream has less space than l_max_evt_size since in this mode */
  /* the actual event size is not known before the transfer of the last  */
  /* fraction.                                                           */
  /*                                                                     */
  /* if l_base_addr_evt_buf != 0 an smem_create segment will be created  */
  /* if l_base_addr_evt_buf  = 0 ( or not specified) a buffer of size    */
  /* l_max_evt_size will be created with malloc and is therefore not     */
  /* contigious in the address space.                                    */
  /* MO__N_NODE runs over dr node ids.                                   */
  INTU4 l_max_evt_size;
  /* TOTAL maximum event size, which could occur within this setup.      */
  /* in bytes.                                                           */
  INTU4 l_n_frag;
  /* many subevents/fragments can be send/read in one transfer (i.e.     */
  /* tcp, vme block transfer) from m_ds to m_dr if the data is conscu-   */
  /* tive. l_n_frag specifies the number fragments sent in such a packet */
  INTU4 l_ev_buf_len [MO__N_NODE];
  INTU4 l_n_ev_buf [MO__N_NODE];
  INTU4 l_n_stream [MO__N_NODE];
  INTU4 l_base_addr_stream_seg [MO__N_NODE];
  /* only nedded if l_form mode = 2. see explanation above               */
  INTU4 l_out_mode [MO__N_NODE];
  CHARS c_ds_hostname [MO__N_NODE][16];
  /* name of ds nodes */
  CHARS c_dr_hostname [MO__N_NODE][16];
  /* name of dr nodes */

} s_set_mo;
