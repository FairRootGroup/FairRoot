/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "f_stccomm.h"

CHARS c_msg[80];
/*#define DEBUG 1*/

/* %%+HEAD: */
/*****************+***********+****************************************/
/*                                                                    */
/*   GSI, Gesellschaft fuer Schwerionenforschung mbH                  */
/*   Postfach 11 05 41                                                */
/*   D-6100 Darmstadt 11                                              */
/*                                                                    */
/*1+ PLI Main ****************+****************************************/
/*                                                                    */
/*+ Module      : f_stc_read                                          */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_stc_read( INTS1 p_buffer  , INTS4 i_buflen ,         */
/*                            INTS4  i_channel , INTS4 i_timeout )        */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : f_stc_read  read bytes from a connected socket      */
/*                            and places them in a buffer (p_buffer). */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+ p_buffer    : Pointer to free data buffer.                        */
/*                                                                    */
/*+ i_buflen    : buffer length.                                      */
/*                                                                    */
/*+ i_channel   : Id from the connected socket.                       */
/*                                                                    */
/*+ i_timeout   : Timeout value ( seconds ) for read from socket.     */
/*-        i_timeout = 0  : Return immediately after           */
/*                                  checking the connected socket.    */
/*-        i_timeout > 0  : Return when the specified socket   */
/*                                  is ready for I/O, but don't wait  */
/*                                  beyond a fixed amount of time.    */
/*-        i_timeout = -1 : Return only when the specified     */
/*                                  socket is ready for I/O.          */
/*                                                                    */
/*+ Return type : integer.                                            */
/*                                                                    */
/*2+DESCRIPTION***+***********+****************************************/
/*                                                                    */
/*+ CALLING     : f_stc_read  ( INTS1 p_buffer  , INTS4 i_buflen ,       */
/*                              INTS4  i_channel , INTS4 i_timeout )      */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+ p_buffer    : Pointer to free data buffer.                        */
/*                                                                    */
/*+ i_buflen    : buffer length.                                      */
/*                                                                    */
/*+ i_channel   : Id from the connected socket.                       */
/*                                                                 */
/*+ i_timeout   : Timeout value ( seconds ) for read from socket.     */
/*                                                                    */
/*-        i_timeout = 0 :  Return immediately after checking  */
/*                                  the connected socket.             */
/*-        i_timeout > 0 :  Return when the specified socket   */
/*                                  is ready for I/O, but don't wait  */
/*                                  beyond a fixed amount of time.    */
/*-        i_timeout = -1 : Return only when the specified     */
/*                                  socket is ready for I/O.          */
/*                                                                    */
/*+ FUNCTION    : Read bytes from a connected socket and places them  */
/*                in a buffer (p_buffer)                              */
/*                The procedure f_stc_read wait max timeout seconds   */
/*                getting data from the socket.                       */
/*                                                                    */
/*+ REMARKS     : -                                                   */
/*                                                                    */
/*2+IMPLEMENTATION************+****************************************/
/*                                                                    */
/*+ Input/Output: SYS$INPUT, SYS$OUTPUT                               */
/*+ Return type : INTEGER                                             */
/*+ Status codes:                                                     */
/*-        STC__SUCCESS   : success.                           */
/*-        STC__FAIlURE   : failure.                           */
/*-        STC__INVSOCK   : invalid socket number.             */
/*-        STC__INVBUF    : buffer points outside allocated    */
/*                                  adress space.                     */
/*-        STC__NGBUFSIZE : buffer length is negative.         */
/*-        STC__INVTIME   : time limit is unacceptable negativ */
/*                                  or to long.                       */
/*-        STC__TIMEOUT   : timeout read from socket.          */
/*+ File name   :                                                     */
/*+ Version     : 1.01                                                */
/*+ Author      : R.Fritzsche                                         */
/*+ Last Update : 17-Jul-1995                                         */
/*                                                                    */
/*2+UPDATES*******+***********+*********************************************/
/*                                                                         */
/*+ Updates     : Date        Purpose                                      */
/*-               17-Jul-1995 : f_stc_connectserver         H.G.           */
/*                              close socket in case of failure to avoid   */
/*                              hanging sockets                            */
/*-               17-Jul-1995 : f_stc_discclient           H.G.            */
/*                              remove shutdown (which didn't work and     */
/*                              inibited close) and make close in any case */
/*-               17-Jul-1995 : f_stc_disperror             H.G.           */
/*                              new message no.: STC__ECONNREF             */
/*                                                                         */
/*2+INTERNALS*****+***********+*********************************************/
/*                                                                    */
/*+ Utility     : EXAMPLES                                            */
/*+ Compile lib.: GOOINC.TLB                                          */
/*+ Home direct.: GOO$EXAMPLES                                        */
/*+ Created     : 25-Jan-1994                                         */
/*                                                                    */
/*1- PLI Main ****************+****************************************/
/* %%-HEAD:  */

INTS4 f_stc_read(p_buffer, i_buflen, i_channel, i_timeout) INTS1* p_buffer;
INTS4 i_buflen;
INTS4 i_channel;
INTS4 i_timeout;
{
    INTS4 retval, buflen_tmp;
    INTS1* p_buffer_tmp;
    //   INTS4                rmask , wmask , emask;
    INTS4 i_retry = 0;
    struct timeval read_timeout;
    fd_set xrmask, xwmask, xemask;
    INTS4 num_of_bytes_read = 0;

    buflen_tmp = i_buflen;
    p_buffer_tmp = p_buffer; /* actual pointer to buffer      */

    FD_ZERO(&xrmask);
    FD_ZERO(&xemask);
    FD_ZERO(&xwmask);
    FD_SET(i_channel, &xrmask);
    read_timeout.tv_sec = i_timeout;
    read_timeout.tv_usec = 0;
#ifdef DEBUG
    printf("STC: read %6d bytes channel %d ", i_buflen, i_channel);
    fflush(stdout);
#endif
    while (num_of_bytes_read < i_buflen && buflen_tmp > 0) {
        if (i_timeout >= 0) {
            /*
      #ifdef GSI__AIX
           retval = select(32,&xrmask,&xwmask,&xemask,&read_timeout);
      #else
           retval = select(32,&rmask,&wmask,&emask,&read_timeout);
      #endif
      */

            /* Changed by S.Linev, 18.09.2007 */
            //        retval = select(32,(fd_set*) &rmask, (fd_set*) &wmask, (fd_set*) &emask,&read_timeout);
            retval = select(i_channel + 1, &xrmask, &xwmask, &xemask, &read_timeout);

            switch (retval) {
                case -1:
                    switch (errno) {
                        case EBADF:
                            return STC__INVSOCK;
                        case EINVAL:
                            return STC__INVTIME;
                        case EINTR:
                            continue;
                        case ECONNRESET:
                            return STC__ECONNRES;
                        default:
                            sprintf(c_msg, "STC select error channel %d", i_channel);
                            perror(c_msg);
                            return STC__FAILURE;
                    }
                case 0:
                    return STC__TIMEOUT;
            }
        }
        /* ------------------------------------------------------- */
        /*   read data from the connect socket.                    */
        /* ------------------------------------------------------- */
#ifdef DEBUG
        printf("read ");
        fflush(stdout);
#endif
#ifdef GSI__WINNT
        retval = recv(i_channel, p_buffer_tmp, buflen_tmp, 0); /* Mohammad Al-Turany 31.07.00 */
#else
        retval = read(i_channel, p_buffer_tmp, buflen_tmp);
#endif
        if (retval == -1) {
            switch (errno) {
                case EBADF:
                    return STC__INVSOCK;
                case EFAULT:
                    return STC__INVBUF;
                case EINVAL:
                    return STC__NGBUFSIZE;
                case EINTR:
                    return STC__EINTR;
                case ECONNRESET:
                    return STC__ECONNRES;
                default:
                    sprintf(c_msg, "STC read error channel %d", i_channel);
                    perror(c_msg);
                    return STC__FAILURE;
            } /* switch( errno )  */

        } /* if( retval == -1 )  */

        /* ------------------------------------------------------- */
        /*       set the num of bytes to read in the next          */
        /*       read statement.                                   */
        /* ------------------------------------------------------- */

        num_of_bytes_read += retval;
        buflen_tmp -= retval;
        p_buffer_tmp += retval; /* calc actual pointer   */
        if (i_retry == 100000) {
            printf("Request %d bytes, read %d, timeout after 100000 retries\n", i_buflen, num_of_bytes_read);
            return STC__NODATA;
        }
        ++i_retry;

        read_timeout.tv_sec = 100;
        read_timeout.tv_usec = 0;

    } /* end while */

#ifdef DEBUG
    printf("done\n");
    fflush(stdout);
#endif
    if (num_of_bytes_read == i_buflen) {
        return STC__SUCCESS;
    }

    return STC__FAILURE;
} /* f_stc_read()  */

/* ------------------------------------------------------------------------- */

/* %%+HEAD: */
/*****************+***********+****************************************/
/*                                                                    */
/*   GSI, Gesellschaft fuer Schwerionenforschung mbH                  */
/*   Postfach 11 05 41                                                */
/*   D-6100 Darmstadt 11                                              */
/*                                                                    */
/*1+ PLI Main ****************+****************************************/
/*                                                                    */
/*+ Module      : f_stc_write                                         */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_stc_write( INTS1 p_buffer , INTS4 i_buflen ,         */
/*                             INTS4  i_channel )                       */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : f_stc_write.    write a buffer to a connected       */
/*                                socket.                             */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+ p_buffer    : Pointer to buffer.                                  */
/*                                                                    */
/*+ i_buflen    : length of buffer.                                   */
/*                                                                    */
/*+ i_channel   : Id from the connected socket.                       */
/*                                                                    */
/*+ Return type : integer.                                            */
/*                                                                    */
/*2+DESCRIPTION***+***********+****************************************/
/*                                                                    */
/*+ CALLING     : f_stc_write( INTS1 p_buffer , INTS4 i_buflen ,         */
/*                             INTS4  i_channel )                       */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+ p_buffer    : Pointer to buffer.                                  */
/*                                                                    */
/*+ i_buflen    : length of buffer.                                   */
/*                                                                    */
/*+ i_channel   : Id from the connected socket.                       */
/*                                                                    */
/*+ FUNCTION    : Write a specified buffer to a connected socket      */
/*                                                                    */
/*+ REMARKS     : -                                                   */
/*                                                                    */
/*2+IMPLEMENTATION************+****************************************/
/*                                                                    */
/*+ Input/Output: SYS$INPUT, SYS$OUTPUT                               */
/*+ Return type : INTEGER                                             */
/*+ Status codes:                                                     */
/*-        STC__SUCCESS : success.                             */
/*-        STC__FAILURE : failure.                             */
/*-        STC__INVSOCK : invalid socket number.               */
/*-        STC__NOTSOCK : socket number points to a file       */
/*                                not a socket.                       */
/*-        STC__INVADDR : invalid address specified in         */
/*                                parameter.                          */
/*+ File name   :                                                     */
/*+ Version     : 1.01                                                */
/*+ Author      : R.Fritzsche                                         */
/*+ Last Update : 27-Jan-1994                                         */
/*                                                                    */
/*2+UPDATES*******+***********+****************************************/
/*                                                                    */
/*+ Updates     : Date        Purpose                                 */
/*                                                                    */
/*2+INTERNALS*****+***********+****************************************/
/*                                                                    */
/*+ Utility     : EXAMPLES                                            */
/*+ Compile lib.: GOOINC.TLB                                          */
/*+ Home direct.: GOO$EXAMPLES                                        */
/*+ Created     : 25-Jan-1994                                         */
/*                                                                    */
/*1- PLI Main ****************+****************************************/
/* %%-HEAD: */

INTS4 f_stc_write(p_buffer, i_buflen, i_channel) INTS1* p_buffer;
INTS4 i_buflen;
INTS4 i_channel;
{
    INTS4 l_retval;

    /* ---------------------------------------------------------- */
    /*   send data to server.                                     */
    /* ---------------------------------------------------------- */

#ifdef DEBUG
    printf("STC: write %5d bytes channel %d ", i_buflen, i_channel);
    fflush(stdout);
#endif
    l_retval = send(i_channel, p_buffer, i_buflen, 0);

    switch (l_retval) {
        case -1:
            switch (errno) {
                case EBADF:
                    return STC__INVSOCK;
                case ENOTSOCK:
                    return STC__NOTSOCK;
                case EFAULT:
                    return STC__INVADDR;
                default:
                    sprintf(c_msg, "STC write error channel %d", i_channel);
                    perror(c_msg);
                    return STC__FAILURE;
            } /*  switch( errno )  */

    } /* switch( l_retval )  */

        /* ---------------------------------------------------------- */
        /*   send() returns the number of bytes sent.                 */
        /* ---------------------------------------------------------- */

#ifdef DEBUG
    printf("done\n");
    fflush(stdout);
#endif
    if (l_retval == i_buflen) {
        return STC__SUCCESS;
    }

    return STC__FAILURE;
} /* end f_stc_write()  */

/* %%+HEAD: */
/*****************+***********+****************************************/
/*                                                                    */
/*   GSI, Gesellschaft fuer Schwerionenforschung mbH                  */
/*   Postfach 11 05 41                                                */
/*   D-6100 Darmstadt 11                                              */
/*                                                                    */
/*1+ PLI Main ****************+****************************************/
/*                                                                    */
/*+ Module      : f_stc_connectserver                                 */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_stc_connectserver( CHARS c_node    , INTS4 l_port , */
/*                                     INTS4  pi_channel ,              */
/*                                     struct s_tcpcomm ps_client )   */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : f_stc_connectserver. connect a client process to a  */
/*                                     server process.                */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+ c_node      : Name of server node                                 */
/*                                                                    */
/*+ l_port      : Portnumber from server                              */
/*                                                                    */
/*+ pi_channel  : Pointer to channel number.                          */
/*                i_channel specifies the address that will be filled */
/*                in with the actual socket Id.                       */
/*                                                                    */
/*+ pc_client   : Pointer to structure s_tcpcomm.                     */
/*                s_client specifies the address that will be filled  */
/*                in with the actual communication values.            */
/*                                                                    */
/*                                                                    */
/*+ Return type : integer.                                            */
/*                                                                    */
/*2+DESCRIPTION***+***********+****************************************/
/*                                                                    */
/*+ CALLING     : f_stc_connectserver( CHARS c_node , INTS4 l_port ,    */
/*                                     INTS4  pi_channel ,              */
/*                                     struct s_tcpcomm ps_client )   */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+ c_node      : Name of server node                                 */
/*                                                                    */
/*+ l_port      : Portnumber from server                              */
/*                                                                    */
/*+ pi_channel  : Pointer to channel number.                          */
/*                i_channel specifies the address that will be filled */
/*                in with the actual socket Id.                       */
/*                                                                    */
/*+ ps_client   : Pointer to structure s_tcpcomm.                     */
/*                s_client specifies the address that will be filled  */
/*                in with the actual communication values.            */
/*                                                                    */
/*+ FUNCTION    : f_stc_connectserver. connect a client process to a  */
/*                                     server process on node "c_node"*/
/*                                     and port "l_port".             */
/*                                     f_stc_connectserver() modify   */
/*                                     the channel number and fill the*/
/*                                     structure s_tcpcomm.           */
/*                                     The channel number is required */
/*                                     to read and write data, to the */
/*                                     connected server.              */
/*+ REMARKS     : -                                                   */
/*                                                                    */
/*2+IMPLEMENTATION************+****************************************/
/*                                                                    */
/*+ Input/Output: SYS$INPUT, SYS$OUTPUT                               */
/*+ Return type : INTEGER                                             */
/*+ Status codes:                                                     */
/*-        STC__SUCCESS : success.                             */
/*-        STC__FAILURE : failure.                             */
/*-        STC__INVADDRF: The specified address family is not  */
/*                                supported.                          */
/*-        STC__SOCKNSUP: The specified socket type is not     */
/*                                supported.                          */
/*-        STC__INVPROTO: The specified protocol is not        */
/*                                supported.                          */
/*-        STC__SOCKTABF: The per-process descriptor table     */
/*                                is full.                            */
/*-        STC__SOCKSPAF: No buffer space is available. The    */
/*                                socket can't be created.            */
/*-        STC__INVSOCK : invalid socket number.               */
/*-        STC__NOTSOCK : socket number points to a file not a */
/*                                socket.                             */
/*-        STC__SOCKISC : socket is already connected.         */
/*-        STC__CONNTOUT: connection timed out without         */
/*                                establishing a connection.          */
/*-        STC__NETUNREA: The network is not reachable from    */
/*                                this host.                          */
/*-        STC__PORTINUS: The specified Internet Address and   */
/*                                port is already in use.             */
/*+ File name   :                                                     */
/*+ Version     : 1.01                                                */
/*+ Author      : R.Fritzsche                                         */
/*+ Last Update : 24-Jan-1994                                         */
/*                                                                    */
/*2+UPDATES*******+***********+****************************************/
/*                                                                    */
/*+ Updates     : Date        Purpose                                 */
/*                                                                    */
/*2+INTERNALS*****+***********+****************************************/
/*                                                                    */
/*+ Utility     : EXAMPLES                                            */
/*+ Compile lib.: GOOINC.TLB                                          */
/*+ Home direct.: GOO$EXAMPLES                                        */
/*+ Created     : 24-Jan-1994                                         */
/*                                                                    */
/*1- PLI Main ****************+****************************************/
/* %%-HEAD: */

INTS4 f_stc_connectserver(c_node, l_port, pi_channel, ps_client) CHARS* c_node;
INTS4 l_port;
INTS4* pi_channel;
struct s_tcpcomm* ps_client;
{

    INTS4 /*shut,*/ retval;
    //  INTS4 thirty = 30;
    struct s_tcpcomm s_client;
    memset(&s_client, 0, sizeof(s_client));

    /* ----------------------------------------------------------------------- */
    /*           init communication socket.              */
    /* ----------------------------------------------------------------------- */

#ifdef GSI__WINNT
    WORD wVersionRequested;
    WSADATA wsaData;
    char message1[512];
    wVersionRequested = MAKEWORD(2, 2);
    // err = WSAStartup( wVersionRequested, &wsaData );
    if (WSAStartup(wVersionRequested, &wsaData) != 0) {
        printf("WinSock NOT found");
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.                                  */
    }

    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.
         */
        printf("WinSock %d.%d", LOBYTE(wsaData.wVersion), HIBYTE(wsaData.wVersion));
        WSACleanup();
    }

#endif

    s_client.socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    *ps_client = s_client;
    *pi_channel = s_client.socket; /* save channel also in case of error */
    /* 17.7.95, H.G. */
    switch (s_client.socket) {
        case -1:
            switch (errno) {
                case EAFNOSUPPORT:
                    return STC__INVADDRF;
                case ESOCKTNOSUPPORT:
                    return STC__SOCKNSUP;
                case EPROTONOSUPPORT:
                    return STC__INVPROTO;
                case EMFILE:
                    return STC__SOCKTABF;
                case ENOBUFS:
                    return STC__SOCKSPAF;
                default:
                    return STC__FAILURE;
            } /* switch( errno )  */
    }         /* switch( s_client.socket)  */

    if ((s_client.hostentptr = gethostbyname(c_node)) == NULL) {

#ifdef GSI__WINNT
        closesocket(s_client.socket); /* Mohammad Al-Turany 31.07.00*/
#else
        close(s_client.socket); /* close socket here and in any case! */
        /* H.G., 17.7.95      */
#endif
        /* printf("--E--f_stc_connectserver(): error gethostbyname: >%s<\n",c_node);*/
        return STC__FAILURE;
    }

    s_client.hostentstruct = *s_client.hostentptr;
    s_client.sock.sin_family = s_client.hostentstruct.h_addrtype;
    s_client.sock.sin_port = htons(l_port);
    s_client.sock.sin_addr = *((struct in_addr*)s_client.hostentstruct.h_addr);

    retval = connect(s_client.socket, (struct sockaddr*)&s_client.sock, sizeof(s_client.sock));
    if (retval == -1) {
#ifdef GSI__WINNT
        closesocket(s_client.socket); /* Mohammad Al-Turany 31.07.00*/
#else
        close(s_client.socket); /* close socket here and in any case! */
                                /* H.G., 17.7.95      */
#endif
        switch (errno) {
            case EBADF:
                return STC__INVSOCK;
            case ENOTSOCK:
                return STC__NOTSOCK;
            case EISCONN:
                return STC__SOCKISC;
            case ETIMEDOUT:
                return STC__CONNTOUT;
            case ENETUNREACH:
                return STC__NETUNREA;
            case EADDRINUSE:
                return STC__PORTINUS;
            case ECONNREFUSED:
                return STC__ECONNREF;
            default:
                return STC__FAILURE;
        } /* switch( errno )  */
    }

    *ps_client = s_client;

    return STC__SUCCESS;

} /* f_stc_connectserver()  */

/* %%+HEAD: */
/*****************+***********+****************************************/
/*                                                                    */
/*   GSI, Gesellschaft fuer Schwerionenforschung mbH                  */
/*   Postfach 11 05 41                                                */
/*   D-6100 Darmstadt 11                                              */
/*                                                                    */
/*1+ PLI Main ****************+****************************************/
/*                                                                    */
/*+ Module      : f_stc_acceptclient                                  */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_stc_acceptclient( struct s_tcpcomm s_server ,     */
/*                                    INTS4    pi_channel )             */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : f_stc_acceptclient. completes a connection between  */
/*                                    server and client.              */
/*                                    f_stc_acceptclient() modify the */
/*                                    channel Id from the accepted    */
/*                                    client. The channel Id  is      */
/*                                    required to read and write data */
/*                                    to the client.                  */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+ s_server    : Pointer to structure s_tcpcomm.                     */
/*                                                                    */
/*+ pi_channel  : Id from the connected client.                       */
/*                i_channel specifies the address that will be filled */
/*                in with the actual client socket Id.                */
/*                                                                    */
/*+ Return type : integer.                                            */
/*                                                                    */
/*2+DESCRIPTION***+***********+****************************************/
/*                                                                    */
/*+ CALLING     : f_stc_acceptclient( struct s_tcpcomm s_server ,     */
/*                                    INTS4    pi_channel )             */
/*                                                                    */
/*+ PURPOSE     : f_stc_acceptclient. completes a connection between  */
/*                                    server and client.              */
/*                                    f_stc_acceptclient() modify the */
/*                                    channel Id from the accepted    */
/*                                    client. The channel Id is       */
/*                                    required to read and write data */
/*                                    to the client.                  */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+ s_server    : Pointer to structure s_tcpcomm.                     */
/*                                                                    */
/*+ pi_channel  : Id from the connected client.                       */
/*                i_channel specifies the address that will be filled */
/*                in with the actual client socket id.                */
/*                                                                    */
/*+ Return type : integer.                                            */
/*                                                                    */
/*+ REMARKS     : -                                                   */
/*                                                                    */
/*2+IMPLEMENTATION************+****************************************/
/*                                                                    */
/*+ Input/Output: SYS$INPUT, SYS$OUTPUT                               */
/*+ Return type : INTEGER                                             */
/*+ Status codes: Status of last command                              */
/*-        STC__SUCCESS : success.                             */
/*-        STC__FAILURE : failure.                             */
/*-        STC__INVSOCK : invalid socket number.               */
/*-        STC__NOTSOCK : socket number points to a file not   */
/*                                a socket.                           */
/*+ File name   : GOO$EXAMPLES:                                       */
/*+ Version     : 1.01                                                */
/*+ Author      : R.Fritzsche                                         */
/*+ Last Update : 25-Jan-1994                                         */
/*                                                                    */
/*2+UPDATES*******+***********+****************************************/
/*                                                                    */
/*+ Updates     : Date        Purpose                                 */
/*                                                                    */
/*2+INTERNALS*****+***********+****************************************/
/*                                                                    */
/*+ Utility     : EXAMPLES                                            */
/*+ Compile lib.: GOOINC.TLB                                          */
/*+ Home direct.: GOO$EXAMPLES                                        */
/*+ Created     : 15-Jan-1994                                         */
/*                                                                    */
/*1- PLI Main ****************+****************************************/
/* %%-HEAD: */

INTS4 f_stc_acceptclient(ps_server, pi_channel) struct s_tcpcomm* ps_server;
INTS4* pi_channel;
{
    //  INTS4 i_socket;
    //  struct hostent*  he;

#ifdef GSI__AIX
    *pi_channel =
        accept(ps_server->sock_rw, (struct sockaddr*)&ps_server->sock_name, (socklen_t*)&ps_server->namelength);
#else
    *pi_channel = accept(ps_server->sock_rw, (struct sockaddr*)&ps_server->sock_name, (uint*)&ps_server->namelength);
#endif
    if (*pi_channel == -1) {
        switch (errno) {
            case EBADF:
                return STC__INVSOCK;
            case ENOTSOCK:
                return STC__NOTSOCK;
            default:
                return STC__FAILURE;
        } /* switch( errno )  */
    }

    /*
     hostname of remote node.
     he = gethostbyaddr( ps_server->sock_name.sin_addr.s_addr,
               sizeof(ps_server->sock_name.sin_addr.s_addr),
               AF_INET );

          if( he != NULL )
            printf("name of client: %s\n",he->h_name);
  */

    return STC__SUCCESS;

} /* end f_stc_acceptclient()  */

/* %%+HEAD: */
/*****************+***********+****************************************/
/*                                                                    */
/*   GSI, Gesellschaft fuer Schwerionenforschung mbH                  */
/*   Postfach 11 05 41                                                */
/*   D-6100 Darmstadt 11                                              */
/*                                                                    */
/*1+ PLI Main ****************+****************************************/
/*                                                                    */
/*+ Module      : f_stc_createserver                                  */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_stc_createserver( INTS4 pl_port ,                  */
/*                                    struct s_tcpcomm ps_server )    */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : f_stc_createserver  creates an endpoint for         */
/*                                    client-server communications.   */
/*                                    The endpoint of communication   */
/*                                    data is not the process name.   */
/*                                    The client-server communication */
/*                                    use portnumbers as endpoints of */
/*                                    communications.                 */
/*                                    The port numbers in the range   */
/*                                    1 to 1023 are privileged ports. */
/*                                    User can use ports in the range */
/*                                    1024 to 65535.                  */
/*                                    also you can use portnumber  0, */
/*                                    then f_stc_createserver() search*/
/*                                    for a free portnumber and modify*/
/*                                    the value from l_port,          */
/*                                    else f_stc_createserver()       */
/*                                    returns 0                       */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+ l_port      : Pointer to Portnumber. ( 1024 - 65535 ) or ( 0 ).   */
/*                                                                    */
/*+ s_server    : Pointer to structure s_tcpcomm                      */
/*                s_server specifies the address that will be filled  */
/*                in with the actual communication values.            */
/*                                                                    */
/*+ Return type : integer.                                            */
/*                                                                    */
/*2+DESCRIPTION***+***********+****************************************/
/*                                                                    */
/*+ CALLING     : f_stc_createserver( INTS4 l_port ,                   */
/*                                    struct s_tcpcomm s_server)      */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+ l_port      : Pointer to Portnumber. ( 1024 - 65535 ) or ( 0 ).   */
/*                l_port specifies the address that will be filled    */
/*                in with the actual server portnumber.               */
/*                                                                    */
/*+ S_SERVER    : Pointer to structure s_tcpcomm                      */
/*                s_server specifies the address that will be filled  */
/*                in with the actual communication values.            */
/*                                                                    */
/*+ FUNCTION    : f_stc_createserver  creates an endpoint for         */
/*                                  client - server communications.   */
/*                                  The endpoint of communication for */
/*                                  data is not the a process name.   */
/*                                  The client - server communication */
/*                                  use portnumbers as endpoints of   */
/*                                  communications.                   */
/*                                  The port numbers in the range     */
/*                                  1 to 1023 are privileged ports.   */
/*                                  User can use ports in the range   */
/*                                  1024 to 65535.                    */
/*                                  also you can use portnumber  0,   */
/*                                  then f_stc_createserver() search  */
/*                                  for a free portnumber and write   */
/*                                  the free portnumber to l_port,    */
/*                                  else f_stc_createserver()         */
/*                                  returns 0                         */
/*                                                                    */
/*+ REMARKS     : -                                                   */
/*                                                                    */
/*2+IMPLEMENTATION************+****************************************/
/*                                                                    */
/*+ Input/Output: SYS$INPUT, SYS$OUTPUT                               */
/*+ Return type : INTEGER                                             */
/*+ Status codes:                                                     */
/*-        STC__SUCCESS  : success.                            */
/*-        STC__FAILURE  : failure.                            */
/*-        STC__INVADDRF : The specified address family is not */
/*                               supported.                           */
/*-        STC__SOCKNSUP : The specified socket type is not    */
/*                               supported.                           */
/*-        STC__INVPROTO : The specified protocol is not       */
/*                               supported.                           */
/*-        STC__SOCKTABF : The per-process descriptor table    */
/*                               is full.                             */
/*-        STC__SOCKSPAF : No buffer space is available.       */
/*                               The socket can't be created.         */
/*-        STC__INVSOCK  : invalid socket number.              */
/*-        STC__NOTSOCK  : socket number points to a file not  */
/*                               a socket.                            */
/*-        STC__PORTINUS : The specified Internet Address      */
/*                               and port is already in use.          */
/*-        STC__SOCKISC  : socket is already connected.        */
/*-        STC__SOCKISP  : socket address is protected and the */
/*                               current user has inadequate          */
/*                       permission to access it.             */
/*+ File name   :                                                     */
/*+ Version     : 1.01                                                */
/*+ Author      : R.Fritzsche                                         */
/*+ Last Update : 25-Jan-1994                                         */
/*                                                                    */
/*2+UPDATES*******+***********+****************************************/
/*                                                                    */
/*+ Updates     : Date        Purpose                                 */
/*                                                                    */
/*2+INTERNALS*****+***********+****************************************/
/*                                                                    */
/*+ Utility     : EXAMPLES                                            */
/*+ Compile lib.: GOOINC.TLB                                          */
/*+ Home direct.: GOO$EXAMPLES                                        */
/*+ Created     : 25-Jan-1994                                         */
/*                                                                    */
/*1- PLI Main ****************+****************************************/
/* %%-HEAD: */

INTS4 f_stc_createserver(pl_port, ps_server) INTS4* pl_port;
struct s_tcpcomm* ps_server;

{

    INTS4 retval, /*i,*/ retry, on;
    //  struct protoent* p;
    struct s_tcpcomm s_server;
    memset(&s_server, 0, sizeof(s_server));

#ifdef GSI__WINNT
    WORD wVersionRequested;
    WSADATA wsaData;
    char message1[512];
    wVersionRequested = MAKEWORD(2, 2);
    // err = WSAStartup( wVersionRequested, &wsaData );
    if (WSAStartup(wVersionRequested, &wsaData) != 0) {
        printf("WinSock NOT found");
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.                                  */
    }

    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.
         */
        printf("WinSock %d.%d", LOBYTE(wsaData.wVersion), HIBYTE(wsaData.wVersion));
        WSACleanup();
    }

#endif

    on = 1;

    if (*pl_port == 0) {
        retry = 1;
        *pl_port = 1024;
    } else {
        retry = 0;
    }

    s_server.sock_rw = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    switch (s_server.sock_rw) {
        case -1:
            switch (errno) {
                case EAFNOSUPPORT:
                    return STC__INVADDRF;
                case ESOCKTNOSUPPORT:
                    return STC__SOCKNSUP;
                case EPROTONOSUPPORT:
                    return STC__INVPROTO;
                case EMFILE:
                    return STC__SOCKTABF;
                case ENOBUFS:
                    return STC__SOCKSPAF;
                default:
                    return STC__FAILURE;
            } /* switch( errno )  */
    }         /* switch( s_server.sock_rw)  */

    retval = gethostname(s_server.hostname, sizeof(s_server.hostname));
    if (retval) {
        printf("--E--f_stc_createserver() error get local hostname\n");
        return STC__FAILURE;
    }

    if ((s_server.hostentptr = gethostbyname(s_server.hostname)) == NULL) {
        printf("--E--f_stc_createserver() error get local Internet address\n");
        return STC__FAILURE;
    }

    bzero((CHARS*)&s_server.sock_name, sizeof(s_server.sock_name));
    s_server.sock_name.sin_family = AF_INET;
    s_server.sock_name.sin_addr.s_addr = htonl(INADDR_ANY);
    s_server.sock_name.sin_port = htons(*pl_port);

    retval = bind(s_server.sock_rw, (struct sockaddr*)&s_server.sock_name, sizeof(s_server.sock_name));

    if (retval == -1 && retry == 0) {

        close(s_server.sock_rw);

        switch (errno) {
            case EBADF:
                return STC__INVSOCK;
            case ENOTSOCK:
                return STC__NOTSOCK;
            case EADDRINUSE:
                return STC__PORTINUS;
            case EINVAL:
                return STC__SOCKISC;
            case EACCES:
                return STC__SOCKISP;
            default:
                return STC__FAILURE;
        }
    }

    retval = -1;

    while (retval == -1 && retry == 1) {

        s_server.sock_rw = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        switch (s_server.sock_rw) {
            case -1:
                switch (errno) {
                    case EAFNOSUPPORT:
                        return STC__INVADDRF;
                    case ESOCKTNOSUPPORT:
                        return STC__SOCKNSUP;
                    case EPROTONOSUPPORT:
                        return STC__INVPROTO;
                    case EMFILE:
                        return STC__SOCKTABF;
                    case ENOBUFS:
                        return STC__SOCKSPAF;
                    default:
                        return STC__FAILURE;
                }
        }

        retval = gethostname(s_server.hostname, sizeof(s_server.hostname));
        if (retval) {
            printf("--E--f_stc_createserver() error get local hostname\n");
            return STC__FAILURE;
        }

        if ((s_server.hostentptr = gethostbyname(s_server.hostname)) == NULL) {
            printf("--E--f_stc_createserver() error get local Internet address\n");
            return STC__FAILURE;
        }

        retval = -1;

        bzero((CHARS*)&s_server.sock_name, sizeof(s_server.sock_name));
        s_server.sock_name.sin_family = AF_INET;
        s_server.sock_name.sin_addr.s_addr = htonl(INADDR_ANY);
        s_server.sock_name.sin_port = htons(*pl_port);

        retval = bind(s_server.sock_rw, (struct sockaddr*)&s_server.sock_name, sizeof(s_server.sock_name));
        if (retval == -1) {
            close(s_server.sock_rw);

            *pl_port += 1;

            if (*pl_port > 65535) {
                printf("--E--f_stc_createserver() portnumber exceeded > 655535\n");

                switch (errno) {
                    case EBADF:
                        return STC__INVSOCK;
                    case ENOTSOCK:
                        return STC__NOTSOCK;
                    case EADDRINUSE:
                        return STC__PORTINUS;
                    case EINVAL:
                        return STC__SOCKISC;
                    case EACCES:
                        return STC__SOCKISP;
                    default:
                        return STC__FAILURE;
                } /* end switch( errno )   */

            } /* end if *pl_port > ... )   */

        } /* end if (retval == -1 )  */
    }

    retval = listen(s_server.sock_rw, 5);
    if (retval == -1) {
        switch (errno) {
            case EBADF:
                return STC__INVSOCK;
            case ENOTSOCK:
                return STC__NOTSOCK;
            default:
                return STC__FAILURE;
        }
    }

    s_server.namelength = sizeof(s_server.sock_name);

    *ps_server = s_server;

    return STC__SUCCESS;
} /* end f_stc_createserver()  */

/* %%+HEAD: */
/*****************+***********+****************************************/
/*                                                                    */
/*   GSI, Gesellschaft fuer Schwerionenforschung mbH                  */
/*   Postfach 11 05 41                                                */
/*   D-6100 Darmstadt 11                                              */
/*                                                                    */
/*1+ PLI Main ****************+****************************************/
/*                                                                    */
/*+ Module      : f_stc_close                                         */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_stc_close( struct s_tcpcomm ps_tcp )              */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : f_stc_close       close the client server           */
/*                                communication.                      */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+ S_TCP       : Pointer to structure s_tcpcomm.                     */
/*                                                                    */
/*+ Return type : integer.                                            */
/*                                                                    */
/*2+DESCRIPTION***+***********+****************************************/
/*                                                                    */
/*+ CALLING     : f_stc_close( struct s_tcpcomm ps_tcp )              */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+ FUNCTION    : f_stc_close       close the client server           */
/*                                communication.                      */
/*                                                                    */
/*+ S_TCP       : Pointer to structure s_tcpcomm.                     */
/*                                                                    */
/*+ REMARKS     : -                                                   */
/*                                                                    */
/*2+IMPLEMENTATION************+****************************************/
/*                                                                    */
/*+ Input/Output: SYS$INPUT, SYS$OUTPUT                               */
/*+ Return type : INTEGER                                             */
/*+ File name   :                                                     */
/*+ Version     : 1.01                                                */
/*+ Author      : R.Fritzsche                                         */
/*+ Last Update : 25-Jan-1994                                         */
/*                                                                    */
/*2+UPDATES*******+***********+****************************************/
/*                                                                    */
/*+ Updates     : Date        Purpose                                 */
/*                                                                    */
/*2+INTERNALS*****+***********+****************************************/
/*                                                                    */
/*+ Utility     : EXAMPLES                                            */
/*+ Compile lib.: GOOCINC.TLB                                         */
/*+ Home direct.: GOO$EXAMPLES                                        */
/*+ Created     : 25-Jan-1994                                         */
/*                                                                    */
/*1- PLI Main ****************+****************************************/
/* %%-HEAD: */

INTS4 f_stc_close(ps_tcp) struct s_tcpcomm* ps_tcp;
{
    INTS4 retval;

    if (ps_tcp->socket) {
        retval = shutdown(ps_tcp->socket, 2);
        if (retval == -1) {
            return STC__FAILURE;
        }
        retval = close(ps_tcp->socket);
        if (retval == -1) {
            return STC__FAILURE;
        }

        return STC__SUCCESS;
    }

    return STC__FAILURE;
} /* f_stc_close()  */

/* %%+HEAD: */
/*****************+***********+****************************************/
/*                                                                    */
/*   GSI, Gesellschaft fuer Schwerionenforschung mbH                  */
/*   Postfach 11 05 41                                                */
/*   D-6100 Darmstadt 11                                              */
/*                                                                    */
/*1+ PLI Main ****************+****************************************/
/*                                                                    */
/*+ Module      : f_stc_discclient                                    */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_stc_discclient( INTS4 i_channel )                   */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : f_stc_discclient       close the specified client   */
/*                                       server communication.        */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+ I_CHANNEL   : Channel Id from the specified client.               */
/*                                                                    */
/*+ Return type : integer.                                            */
/*                                                                    */
/*2+DESCRIPTION***+***********+****************************************/
/*                                                                    */
/*+ CALLING     : f_stc_discclient( INTS4 i_channel )                   */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+ FUNCTION    : f_stc_discclient  close the specified client        */
/*                                  server communication.             */
/*                                                                    */
/*+ I_CHANNEL   : Channel Id from the specified client.               */
/*                                                                    */
/*+ REMARKS     : -                                                   */
/*                                                                    */
/*2+IMPLEMENTATION************+****************************************/
/*                                                                    */
/*+ Input/Output: SYS$INPUT, SYS$OUTPUT                               */
/*+ Return type : INTEGER                                             */
/*+ File name   :                                                     */
/*+ Version     : 1.01                                                */
/*+ Author      : R.Fritzsche                                         */
/*+ Last Update : 01-Mar-1994                                         */
/*                                                                    */
/*2+UPDATES*******+***********+****************************************/
/*                                                                    */
/*+ Updates     : Date        Purpose                                 */
/*                                                                    */
/*2+INTERNALS*****+***********+****************************************/
/*                                                                    */
/*+ Utility     : EXAMPLES                                            */
/*+ Compile lib.:                                                     */
/*+ Home direct.:                                                     */
/*+ Created     : 01-Mar-1994                                         */
/*                                                                    */
/*1- PLI Main ****************+****************************************/
/* %%-HEAD: */

INTS4 f_stc_discclient(i_channel) INTS4 i_channel;
{
    INTS4 retval;

    /* call of shutdown removed 17.7.95, H.G. */
    retval = close(i_channel);
    if (retval == -1) {
        return STC__FAILURE;
    } else {
        return STC__SUCCESS;
    }
} /* f_stc_discclient()  */

/* %%+HEAD: */
/*****************+***********+****************************************/
/*                                                                    */
/*   GSI, Gesellschaft fuer Schwerionenforschung mbH                  */
/*   Postfach 11 05 41                                                */
/*   D-6100 Darmstadt 11                                              */
/*                                                                    */
/*1+ PLI Main ****************+****************************************/
/*                                                                    */
/*+ Module      : f_stc_listenserver                                  */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_stc_listenserver( struct s_tcpcomm ps_server )    */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : f_stc_listenserver look for a pending client        */
/*                                 connection on the specified        */
/*                                 server.                            */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+ PS_SERVER   : Pointer to structure s_tcpcomm.                     */
/*                                                                    */
/*+ Return type : integer.                                            */
/*                                                                    */
/*2+DESCRIPTION***+***********+****************************************/
/*                                                                    */
/*+ CALLING     : f_stc_listenserver( struct s_tcpcomm ps_server )    */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+ FUNCTION    : f_stc_listenserver  look for a pending client       */
/*                                  connection on the specified       */
/*                                  server.                           */
/*                                                                    */
/*+ PS_SERVER   : Pointer to structure s_tcpcomm.                     */
/*                                                                    */
/*+ REMARKS     : -                                                   */
/*                                                                    */
/*2+IMPLEMENTATION************+****************************************/
/*                                                                    */
/*+ Input/Output: SYS$INPUT, SYS$OUTPUT                               */
/*+ Return type : INTEGER                                             */
/*+ Status codes:                                                     */
/*-          STC__SUCCESS   : success.                         */
/*-          STC__FAIlURE   : failure.                         */
/*-          STC__INVSOCK   : invalid socket number.           */
/*-          STC__TIMEOUT   : timeout.                         */
/*-          STC__INVTIME   : time limit is unacceptable       */
/*                                    negativ or to long.             */
/*+ File name   :                                                     */
/*+ Version     : 1.01                                                */
/*+ Author      : R.Fritzsche                                         */
/*+ Last Update : 25-Jan-1994                                         */
/*                                                                    */
/*2+UPDATES*******+***********+****************************************/
/*                                                                    */
/*+ Updates     : Date        Purpose                                 */
/*                                                                    */
/*2+INTERNALS*****+***********+****************************************/
/*                                                                    */
/*+ Utility     : EXAMPLES                                            */
/*+ Compile lib.: GOOCINC.TLB                                         */
/*+ Home direct.: GOO$EXAMPLES                                        */
/*+ Created     : 25-Jan-1994                                         */
/*                                                                    */
/*1- PLI Main ****************+****************************************/
/* %%-HEAD: */

INTS4 f_stc_listenserver(ps_server) struct s_tcpcomm* ps_server;
{
    struct timeval read_timeout;
    fd_set rset, allset, wset, eset;
    INTS4 listenfd, maxfd, sts;

    read_timeout.tv_sec = 0;
    read_timeout.tv_usec = 0;

    listenfd = ps_server->sock_rw;

    FD_ZERO(&rset);
    FD_ZERO(&wset);
    FD_ZERO(&eset);
    FD_ZERO(&allset);
    FD_SET(listenfd, &rset);
    FD_SET(listenfd, &wset);
    FD_SET(listenfd, &eset);
    maxfd = listenfd;

    sts = select(maxfd + 1, &rset, &wset, &eset, &read_timeout);
    switch (sts) {
        case -1:
            switch (errno) {
                case EBADF:
                    return STC__INVSOCK;
                case EINVAL:
                    return STC__INVTIME;
                default:
                    return STC__FAILURE;
            } /* switch( errno )  */

        case 0:
            return STC__TIMEOUT;

    } /* end switch( sts )  */

    if (FD_ISSET(listenfd, &eset)) {
        return STC__SUCCESS;
    }

    if (FD_ISSET(listenfd, &rset)) {
        return STC__SUCCESS;
    }

    if (FD_ISSET(listenfd, &wset)) {
        return STC__SUCCESS;
    }

    return STC__FAILURE;
}

/* %%+HEAD: */
/*****************+***********+****************************************/
/*                                                                    */
/*   GSI, Gesellschaft fuer Schwerionenforschung mbH                  */
/*   Postfach 11 05 41                                                */
/*   D-6100 Darmstadt 11                                              */
/*                                                                    */
/*1+ PLI Main ****************+****************************************/
/*                                                                    */
/*+ Module      : f_stc_disperror                                     */
/*                                                                    */
/*--------------------------------------------------------------------*/
/*+ CALLING     : f_stc_disperror( INTS4 i_error , CHARS c_string[256],  */
/*                                 INTS4 i_out )                       */
/*--------------------------------------------------------------------*/
/*                                                                    */
/*+ PURPOSE     : f_stc_disperror  displays the error message for the */
/*                               error id ( i_error )                 */
/*                               if i_out = 1  the error message is   */
/*                               copied into c_string, else           */
/*                               f_stc_disperror() print the message  */
/*                               on the terminal.                     */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+ I_ERROR     : The error id.                                       */
/*                                                                    */
/*+ C_STRING    : The string into f_stc_disperror() copies the        */
/*                message.                                            */
/*                                                                    */
/*+ I_OUT       : specifies the output device for the error message.  */
/*                                                                    */
/*-          I_OUT = 1 : the error message is copied into      */
/*                              the string.                           */
/*-          I_OUT = 0 : the error message is printed on       */
/*                              the terminal.                         */
/*                                                                    */
/*+ Return type : integer.                                            */
/*                                                                    */
/*2+DESCRIPTION***+***********+****************************************/
/*                                                                    */
/*+ CALLING     : f_stc_disperror( INTS4 i_error , CHARS c_string[256], */
/*                               INTS4 i_out )                         */
/*                                                                    */
/*+ ARGUMENTS   :                                                     */
/*                                                                    */
/*+ I_ERROR     : The error id.                                       */
/*                                                                    */
/*+ C_STRING    : The string into f_stc_disperror() copies the        */
/*                message.                                            */
/*                                                                    */
/*+ I_OUT       : specifies the output device for the error message.  */
/*                                                                    */
/*-        I_OUT = 1 : the error message is copied into the    */
/*                            string.                                 */
/*-        I_OUT = 0 : the error message is printed on the     */
/*                            terminal.                               */
/*                                                                    */
/*+ FUNCTION    : f_stc_disperror  displays the error message for the */
/*                               error id ( i_error )                 */
/*                               if i_out = 1  the error message is   */
/*                               copied into c_string, else           */
/*                               f_stc_disperror() print the message  */
/*                               on the terminal.                     */
/*                                                                    */
/*+ REMARKS     : -                                                   */
/*                                                                    */
/*2+IMPLEMENTATION************+****************************************/
/*                                                                    */
/*+ Input/Output: SYS$INPUT, SYS$OUTPUT                               */
/*+ Return type : INTEGER                                             */
/*+ Status codes:                                                     */
/*-        STC__SUCCESS   : success.                           */
/*-        STC__FAIlURE   : failure.                           */
/*+ File name   :                                                     */
/*+ Version     : 1.01                                                */
/*+ Author      : R.Fritzsche                                         */
/*+ Last Update : 28-Jan-1994                                         */
/*                                                                    */
/*2+UPDATES*******+***********+****************************************/
/*                                                                    */
/*+ Updates     : Date        Purpose                                 */
/*                                                                    */
/*2+INTERNALS*****+***********+****************************************/
/*                                                                    */
/*+ Utility     : EXAMPLES                                            */
/*+ Compile lib.: GOOCINC.TLB                                         */
/*+ Home direct.: GOO$EXAMPLES                                        */
/*+ Created     : 28-Jan-1994                                         */
/*                                                                    */
/*1- PLI Main ****************+****************************************/
/* %%-HEAD: */

INTS4 f_stc_disperror(i_error, c_dest, i_out) INTS4 i_error;
CHARS* c_dest;
INTS4 i_out;
{
    CHARS c_line[80];

    switch (i_error) {
        case STC__FAILURE:
            sprintf(c_line, "-I- f_stc failure");
            break;
        case STC__SUCCESS:
            sprintf(c_line, "-I- f_stc failure");
            break;
        case STC__INVSOCK:
            sprintf(c_line, "-I- f_stc invalid socket number");
            break;
        case STC__INVBUF:
            sprintf(c_line, "-I- f_stc buffer points outside allocated address space");
            break;
        case STC__NGBUFSIZE:
            sprintf(c_line, "-I- f_stc buffer length is negative");
            break;
        case STC__INVTIME:
            sprintf(c_line, "-I- f_stc time limit is negativ or to long");
            break;
        case STC__TIMEOUT:
            sprintf(c_line, "-I- f_stc timeout read data from socket");
            break;
        case STC__NOTSOCK:
            sprintf(c_line, "-I- f_stc socket number points to a file not a socket");
            break;
        case STC__INVADDR:
            sprintf(c_line, "-I- f_stc invalid address specified in parameter");
            break;
        case STC__INVADDRF:
            sprintf(c_line, "-I- f_stc the specified address family is not supported");
            break;
        case STC__SOCKNSUP:
            sprintf(c_line, "-I- f_stc The specified socket type is not supported.");
            break;
        case STC__INVPROTO:
            sprintf(c_line, "-I- f_stc The specified protocol is not supported.");
            break;
        case STC__SOCKTABF:
            sprintf(c_line, "-I- f_stc The per-process descriptor table is full.");
            break;
        case STC__SOCKSPAF:
            sprintf(c_line, "-I- f_stc No buffer space is available. The socket can't be created");
            break;
        case STC__SOCKISC:
            sprintf(c_line, "-I- f_stc socket is already connected.");
            break;
        case STC__CONNTOUT:
            sprintf(c_line, "-I- f_stc connection timed out without establishing a connection.");
            break;
        case STC__NETUNREA:
            sprintf(c_line, "-I- f_stc The network is not reachable from this host.");
            break;
        case STC__PORTINUS:
            sprintf(c_line, "-I- f_stc The specified Internet Address and port is already in use.");
            break;
        case STC__SOCKISP:
            sprintf(c_line, "-I- f_stc socket address is protected.");
            break;
        case STC__ECONNREF: /* added 17.7.95, H.G. */
            sprintf(c_line, "-I- f_stc connection refused.");
            break;
        case TPS__ECPORTS:
            sprintf(c_line, "-I- f_stc error connect portserver");
            break;
        case TPS__EREGSERV:
            sprintf(c_line, "-I- f_stc error register service at portserver");
            break;
        case TPS__EWTOPORTS:
            sprintf(c_line, "-I- f_stc error write buffer to portserver");
            break;
        case TPS__ERMFRPORTS:
            sprintf(c_line, "-I- f_stc error read status message from portserver");
            break;
        case TPS__EGSERVICE:
            sprintf(c_line, "-I- f_stc error get spec. info from  portserver");
            break;
        default:
            sprintf(c_line, "-I- f_stc unknown message id %d", i_error);
            if (i_out == 0) {
                printf("%s\n", c_line);
            }
            if (i_out == 1) {
                strcpy(c_dest, c_line);
            }
            return STC__FAILURE;
    } /* end switch( i_error )   */

    if (i_out == 0) {
        printf("%s\n", c_line);
    }
    if (i_out == 1) {
        strcpy(c_dest, c_line);
    }

    return STC__SUCCESS;
} /* f_stc_disperror()  */
