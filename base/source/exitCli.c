/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/********************************************************************
 * Copyright:
 *   GSI, Gesellschaft fuer Schwerionenforschung mbH
 *   Planckstr. 1
 *   D-64291 Darmstadt
 *   Germany
 ********************************************************************
 * exitCli.c
 * handles CTL C in ROOT clients of remote event server
 * created 12. 3.1999 by Horst Goeringer
 *
 * 22. 4.1999, H.G.: close TCP connection in client, not here
 * 10. 6.1999, H.G.: call sleep only if required
 ********************************************************************
 */
#include <stdio.h>    // for printf
#include <unistd.h>   // for sleep

extern int imySig;
extern int iTimeOut;
extern int iOutMode;

void exitCli() /* handles Ctl C */
{
    // int iRC;
    int iSleep; /* sleep time here */
    int iSocket;
    // int iMode = 2;
    // char cMsg[128] = "";

    iSocket = imySig;
    imySig = -1;
    iSleep = iTimeOut;

    printf("\n-I- user specified CTL C: ");

    if (iSocket > 0) {
        if (iOutMode) {
            printf("close connection (socket %d), hold client for %d s\n", iSocket, iSleep);
        } else {
            printf("close connection\n");
        }

        if (iSleep) {
            sleep(iSleep);
        }
    } else {
        printf("\n");
    }
} /* exitCli */
