/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "typedefs.h"
/*
 *   definitons of the port numbers used
 */

#define PORT__TRANSPORT 6000
#define PORT__ESONE_SERV 6001
#define PORT__STREAM_SERV 6002
#define PORT__EVENT_SERV 6003
#define PORT__PROMPT 6004
#define PORT__MSG_LOG 6005
#define PORT__PROMPT_R 6006
#define PORT__MSG_REM 6007
#define PORT__STAT_SERV 6008
#define PORT__HIST_SERV 6009
#define MO__PORT_BASE                                                                                                  \
    6100 /* m_ds and m_dr processes construct their                                                                    \
          * necessary ports from this base. It requires,                                                               \
          * that ports 6100 - 6256 are reserved (if max                                                                \
          * nr of m_ds and m_dr nodes is defined to 16.*/
