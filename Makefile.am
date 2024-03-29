## Process this file with automake to produce Makefile.in.
##
##  	Copyright (C) 1998, 1999, 2000, 2001, 2002, 2006, 2007,
##        2008, 2009, 2010, 2011, 2012, 2013,
##        2014, 2015, 2016, 2022 Free Software Foundation, Inc.
##
##   This file is part of GUILE.
##
##   GUILE is free software; you can redistribute it and/or modify it
##   under the terms of the GNU Lesser General Public License as
##   published by the Free Software Foundation; either version 3, or
##   (at your option) any later version.
##
##   GUILE is distributed in the hope that it will be useful, but
##   WITHOUT ANY WARRANTY; without even the implied warranty of
##   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##   GNU Lesser General Public License for more details.
##
##   You should have received a copy of the GNU Lesser General Public
##   License along with GUILE; see the file COPYING.LESSER.  If not,
##   write to the Free Software Foundation, Inc., 51 Franklin Street,
##   Fifth Floor, Boston, MA 02110-1301 USA

# want automake 1.10 or higher so that AM_GNU_GETTEXT can tell automake that
# config.rpath is needed
#
AUTOMAKE_OPTIONS = 1.10

SUBDIRS =					\
	lib					\
	meta					\
	libguile				\
	module					\
	stage0					\
	stage1					\
	stage2					\
	guile-readline				\
	examples				\
	emacs					\
	test-suite				\
	benchmark-suite				\
	gc-benchmarks				\
	am					\
	doc

DIST_SUBDIRS = $(SUBDIRS) prebuilt

libguileincludedir = $(pkgincludedir)/$(GUILE_EFFECTIVE_VERSION)
libguileinclude_HEADERS = libguile.h

schemelibdir = $(pkgdatadir)/$(GUILE_EFFECTIVE_VERSION)
schemelib_DATA = libguile/guile-procedures.txt

# Our own implementation of Gnulib's lock interface.
noinst_HEADERS = lib/glthread/lock.h

# Our lib/glthreads/lock.h header indirectly includes
# libguile/scmconfig.h.  Make sure it is built before we recurse into
# lib/.
BUILT_SOURCES = libguile/scmconfig.h
libguile/scmconfig.h:
	$(MAKE) -C libguile scmconfig.h

# Build it from here so that all the modules are compiled by the time we
# build it.
libguile/guile-procedures.txt: libguile/guile-procedures.texi
	$(AM_V_GEN)						\
	$(top_builddir)/meta/guile --no-auto-compile		\
	  "$(srcdir)/libguile/texi-fragments-to-docstrings"	\
	  "$(builddir)/libguile/guile-procedures.texi"		\
	  > $@.tmp
	@mv $@.tmp $@

EXTRA_DIST = LICENSE HACKING GUILE-VERSION			\
	     m4/ChangeLog-2008					\
	     m4/gnulib-cache.m4					\
	     ChangeLog-2008					\
	     .version						\
	     gnulib-local/lib/localcharset.h.diff		\
	     gnulib-local/lib/localcharset.c.diff		\
	     gnulib-local/m4/clock_time.m4.diff			\
	     gnulib-local/build-aux/git-version-gen.diff	\
	     libguile/texi-fragments-to-docstrings		\
	     gdbinit

TESTS = check-guile
TESTS_ENVIRONMENT = @LOCALCHARSET_TESTS_ENVIRONMENT@

ACLOCAL_AMFLAGS = -I m4

CLEANFILES = libguile/guile-procedures.txt
DISTCLEANFILES = check-guile.log

DISTCHECK_CONFIGURE_FLAGS = --enable-error-on-warning

dist-hook: gen-ChangeLog gen-tarball-version assert-no-store-file-names

clean-local:
	rm -rf cache/

CONFIG_STATUS_DEPENDENCIES = GUILE-VERSION

gen_start_rev = 61db429e251bfd2f75cb4632972e0238056eb24b
.PHONY: gen-ChangeLog
gen-ChangeLog:
	if test -d .git; then						\
	  $(top_srcdir)/build-aux/gitlog-to-changelog			\
	    $(gen_start_rev)..HEAD > $(distdir)/cl-t;			\
	  rm -f $(distdir)/ChangeLog;					\
	  mv $(distdir)/cl-t $(distdir)/ChangeLog;			\
	fi

# Make sure we're not shipping a file that embeds a /gnu/store file
# name, for maintainers who use Guix.
.PHONY: assert-no-store-file-names
assert-no-store-file-names:
	if grep -rE "/gnu/store/[a-z0-9]{32}-" $(distdir) ;			\
	then									\
	  echo "error: store file names embedded in the distribution" >&2 ;	\
	  exit 1 ;								\
	fi

BUILT_SOURCES += $(top_srcdir)/.version
$(top_srcdir)/.version:
	echo $(VERSION) > $@-t && mv $@-t $@
gen-tarball-version:
	echo $(VERSION) > $(distdir)/.tarball-version

# Makefile.am ends here
