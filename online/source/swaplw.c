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
 * created  6.12.1995 by Ralph S. Mayer
 ****************************+***************************************
 * makes 4byte swap
 ****************************+***************************************
 */

long swaplw(pp_source, l_len, pp_dest)
long *pp_source, *pp_dest;
long l_len;
{

    char unsigned *p_source, *p_dest, *p_s, *p_d;
    //   char              c_modnam[] = "f_swaplw";
    long unsigned lu_save;

    /* +++ action +++ */
    p_source = (unsigned char *)pp_source;
    p_dest = (unsigned char *)pp_dest;

    if (p_dest) {
        /* source != destination */
        for (p_s = (unsigned char *)p_source, p_d = (unsigned char *)p_dest; p_s < p_source + (l_len * 4); p_s += 4) {
            p_s += 4; /* increment source      */
            *(p_d++) = *(--p_s);
            *(p_d++) = *(--p_s);
            *(p_d++) = *(--p_s);
            *(p_d++) = *(--p_s);
        }
    } else {
        /* source == destination */
        for (p_d = (unsigned char *)p_source, p_s = (unsigned char *)&lu_save; p_d < p_source + (l_len * 4);) {
            lu_save = *((long *)p_d);
            p_s += 4; /* increment source      */
            *(p_d++) = *(--p_s);
            *(p_d++) = *(--p_s);
            *(p_d++) = *(--p_s);
            *(p_d++) = *(--p_s);
        }
    }

    return (1);

} /* swaplw */
