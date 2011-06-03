#
# Copyright 202010 Free Software Foundation, Inc.
# 
# This file is part of GNU Radio
# 
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

include $(top_srcdir)/Makefile.common

# list of programs run by "make check" and "make distcheck"
TESTS = test_all

# ----------------------------------------------------------------
# chancoding C++ library: libgnuradio-chancoding.so
# ----------------------------------------------------------------

# C/C++ headers get installed in ${prefix}/include/$(modname)
modinclude_HEADERS = \
	chancoding_ber_b.h \
	chancoding_bsc_bb.h \
	chancoding_industrystd_encoder_bb.h \
	chancoding_markovchan_bb.h \
	chancoding_blockinterleaver_vbb.h \
	chancodingi_blockinterleaver.h \
	chancoding_blockdeinterleaver_vbb.h \
	chancoding_blockinterleaver_bb.h \
	chancoding_blockdeinterleaver_bb.h \
	chancoding_unpacked_to_packed_bvi.h \
	chancoding_packed_to_unpacked_vib.h \
	chancodingi_rm_coding.h \
	chancoding_rm_encoder_vii.h \
	chancoding_rm_decoder_vii.h \
	chancoding_rmg_encoder_vii.h \
	chancoding_rmg_decoder_vii.h \
	chancoding_rm_encoder_bb.h \
	chancoding_rm_decoder_bb.h \
	chancoding_rmg_encoder_bb.h \
	chancoding_rmg_decoder_bb.h \
	chancoding_rmg_decoder_sd_fb.h \
	chancoding_rmg_decoder_sd_vfi.h

lib_LTLIBRARIES = libgnuradio-chancoding.la

libgnuradio_chancoding_la_SOURCES = \
	chancoding_ber_b.cc \
	chancoding_bsc_bb.cc \
	chancoding_industrystd_encoder_bb.cc \
	chancoding_markovchan_bb.cc \
	chancoding_blockinterleaver_vbb.cc \
	chancodingi_blockinterleaver.cc \
	chancoding_blockdeinterleaver_vbb.cc \
	chancoding_blockinterleaver_bb.cc \
	chancoding_blockdeinterleaver_bb.cc \
	chancoding_unpacked_to_packed_bvi.cc \
	chancoding_packed_to_unpacked_vib.cc \
	chancodingi_rm_coding.cc \
	chancoding_rm_encoder_vii.cc \
	chancoding_rm_decoder_vii.cc \
	chancoding_rmg_encoder_vii.cc \
	chancoding_rmg_decoder_vii.cc \
	chancoding_rm_encoder_bb.cc \
	chancoding_rm_decoder_bb.cc \
	chancoding_rmg_encoder_bb.cc \
	chancoding_rmg_decoder_bb.cc \
	chancoding_rmg_decoder_sd_fb.cc \
	chancoding_rmg_decoder_sd_vfi.cc

libgnuradio_chancoding_la_LIBADD = \
	$(GNURADIO_CORE_LA)

libgnuradio_chancoding_la_LDFLAGS = \
	$(NO_UNDEFINED) \
	-lgnuradio-trellis

# ----------------------------------------------------------------
# chancoding C++ QA library: libgnuradio-chancoding-qa.so (not installed)
# ----------------------------------------------------------------

noinst_LTLIBRARIES = libgnuradio-chancoding-qa.la

libgnuradio_chancoding_qa_la_SOURCES = \
	qa_chancoding.cc \
	qa_industrystd_bb.cc \
	qa_chancoding_markovchan_bb.cc \
	qa_chancoding_blockinterleaver_vbb.cc \
	qa_chancodingi_blockinterleaver.cc \
	qa_chancoding_blockdeinterleaver_vbb.cc \
	qa_chancoding_blockinterleaver_bb.cc \
	qa_chancoding_blockdeinterleaver_bb.cc \
	qa_chancodingi_rm_coding.cc

libgnuradio_chancoding_qa_la_LDFLAGS = \
	$(NO_UNDEFINED) -version-info 0:0:0 \
	-lgnuradio-trellis

libgnuradio_chancoding_qa_la_LIBADD = \
	libgnuradio-chancoding.la \
	$(CPPUNIT_LIBS)

# ----------------------------------------------------------------
# headers that don't get installed
# ----------------------------------------------------------------
noinst_HEADERS = \
	qa_chancoding.h \
	qa_industrystd_bb.h \
	qa_chancoding_markovchan_bb.h \
	qa_chancoding_blockinterleaver_vbb.h \
	qa_chancodingi_blockinterleaver.h \
	qa_chancoding_blockdeinterleaver_vbb.h \
	qa_chancoding_blockinterleaver_bb.h \
	qa_chancoding_blockdeinterleaver_bb.h \
	qa_chancodingi_rm_coding.h


# ----------------------------------------------------------------
# test program
# ----------------------------------------------------------------
noinst_PROGRAMS = \
	test_all

test_all_SOURCES = test_all.cc
test_all_LDADD   = libgnuradio-chancoding-qa.la

