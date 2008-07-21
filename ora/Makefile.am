# Copyright (C) 2005 Florian Uhlig <f.uhlig@gsi.de>
#  
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without 
# modifications, as long as this notice is preserved.
# 
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

PROCFLAGS 	= oraca=yes code=cpp parse=partial sqlcheck=semantics	\
		  userid=$(ORA_USER) ireclen=130 oreclen=130 \
		  sys_include=(${ORACLE_HOME}/precomp/public,/usr/include/,/usr/local/gcc3.2.3/lib/gcc-lib/i686-pc-linux-gnu/3.2.3/include,/usr/local/gcc3.2.3/lib/gcc-lib/i686-pc-linux-gnu,/usr/include/g++-3,/usr/include/c++/3.2/backward,/usr/include/c++/3.2) \
		  include=$(ORACLE_HOME)/precomp/public \
		  include=$(ORACLE_HOME)/rdbms/public \
		  include=$(ORACLE_HOME)/rdbms/demo \
		  include=$(ORACLE_HOME)/plsql/public \
		  include=$(ORACLE_HOME)/network/public	\
		  include=$(ROOTSYS)/include \
		  include=$(top_srcdir)/base	\
		  include=$(top_srcdir)/ora	\
                  include=.

INCLUDES		= $(ROOTCFLAGS) -I$(top_srcdir)/ora -I$(top_srcdir)/base  -I$(ORACLE_HOME)/precomp/public  \
			  -I$(ORACLE_HOME)/rdbms/public -I$(ORACLE_HOME)/rdbms/demo -I$(ORACLE_HOME)/plsql/public  -I$(ORACLE_HOME)/network/public  
                                                              
lib_LTLIBRARIES		= libOra.la

libOra_la_LDFLAGS 	= -version-info 0:0:0

libOra_la_LIBADD	= -L$(ROOTLIBDIR) $(ROOTLIBS) -L$(top_srcdir)/base/ 

include_HEADERS		= CbmDetParOraIo.h CbmOraConn.h CbmOraRunInfo.h	\
			  CbmGenericParOraIo.h CbmOraInfo.h CbmParOraIo.h

noinst_HEADERS		= OraLinkDef.h 

libOra_la_SOURCES	= CbmDetParOraIo.cxx CbmGenericParOraIo.cxx	\
			  CbmOraConn.cxx CbmOraInfo.cxx	\
			  CbmOraDict.cxx  

CLEANFILES		= CbmOraDict.cxx CbmOraDict.h *~ libOra.la

CbmOraDict.cxx: $(include_HEADERS) OraLinkDef.h
	$(ROOTCINT) -f $@ -c -DHAVE_CONFIG_H $(INCLUDES) $^

SUFFIXES = .cxx .pc
.pc.cxx:
	$(ORACLE_HOME)/bin/proc $(PROCFLAGS) iname=$< oname=$*.cxx

