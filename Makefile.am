SUBDIRS=mordor

ACLOCAL_AMFLAGS=-I m4 -I mordor/m4
AUTOMAKE_OPTIONS=nostdinc subdir-objects
AM_CPPFLAGS=$(BOOST_CPPFLAGS) -I$(srcdir)/mordor -I$(top_srcdir)
AM_CXXFLAGS=-Wall -Werror -fno-strict-aliasing
#AM_LDFLAGS=-rdynamic

sbin_PROGRAMS=			\
	pghottub/pghottub

nobase_include_HEADERS=		\
	pghottub/client.h	\
	pghottub/connection.h	\
	pghottub/hot_tub.h	\
	pghottub/listener.h	\
	pghottub/tcp_listener.h

pghottub_pghottub_SOURCES=	\
	pghottub/client.cpp	\
	pghottub/connection.cpp	\
	pghottub/hot_tub.cpp	\
	pghottub/listener.cpp	\
	pghottub/main.cpp	\
	pghottub/tcp_listener.cpp
pghottub_pghottub_LDADD=			\
	mordor/mordor/libmordor.la		\
	$(COREFOUNDATION_FRAMEWORK_LIBS)

