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
 * rclose.c
 * shutdown and close of socket
 * created 23. 4.1999 by Horst Goeringer
 ********************************************************************
 */
// IWYU pragma: no_include <secure/_stdio.h>
#include <stdio.h>        // for printf, perror
#include <sys/socket.h>   // for shutdown
#include <unistd.h>       // for close

int rclose(int *piSocket, int iMode)
{
    int iSocket;
    int iRC;
    //   int iDebug = 0;
    int iError = 0;
    int iClose = 1;
    char cModule[32] = "rclose";
    char cMsg[128] = "";

    if (iMode < 0) {
        iMode = -iMode;
        iClose = 0; /* no shutdown, only close */
    }
    if ((iMode < 0) || (iMode > 3)) {
        if (iClose == 0)
            iMode = -iMode;
        printf("-E- %s: invalid shutdown mode: %d\n", cModule, iMode);
        iError = 2;
    }

    iSocket = *piSocket;
    if (iSocket > 0) {
        if (iMode < 3) {
            iRC = shutdown(iSocket, iMode);
            if (iRC) {
                sprintf(cMsg, "-E- %s: shutdown(%d) rc = %d", cModule, iMode, iRC);
                perror(cMsg);
                iError = -1;
            }
            /*
         else if (iDebug)
            printf("    %s: shutdown(%d) successfull\n",
                   cModule, iMode);
*/
        }

        if (iClose) {
            iRC = close(iSocket);
            if (iRC) {
                sprintf(cMsg, "-E- %s: close rc = %d", cModule, iRC);
                perror(cMsg);
                iError = -2;
            }
            /*
         else if (iDebug)
            printf("    %s: connection closed\n", cModule);

*/
        } /* (iClose) */

    } /* (iSocket > 0) */
    else {
        printf("-E- %s: invalid socket: %d\n", cModule, iSocket);
        iError = 1;
    }

    *piSocket = 0;
    return (iError);

} /* rclose */
