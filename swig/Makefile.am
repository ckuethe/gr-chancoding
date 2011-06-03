#
# Copyright 2004,2005,2006,2008,2009,2010 Free Software Foundation, Inc.
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

AM_CPPFLAGS += -I$(top_srcdir)/lib

if PYTHON
###################################
# SWIG Python interface and library

TOP_SWIG_IFILES = \
	chancoding.i

# Install so that they end up available as:
#   import chancoding
# This ends up at:
#   ${prefix}/lib/python${python_version}/site-packages/$(modname)

chancoding_la_swig_libadd =		\
	$(top_builddir)/lib/libgnuradio-chancoding.la

include $(top_srcdir)/Makefile.swig

# add some of the variables generated inside the Makefile.swig.gen
BUILT_SOURCES = $(swig_built_sources)

# Do not distribute the output of SWIG
no_dist_files = $(swig_built_sources)

# additional SWIG files to be installed
chancoding_swiginclude_headers = \
	chancoding_bsc_bb.i \
	chancoding_ber_b.i \
	chancoding_industrystd_encoder_bb.i \
	chancoding_markovchan_bb.i \
	chancoding_blockinterleaver_vbb.i \
	chancoding_blockdeinterleaver_vbb.i \
	chancoding_blockinterleaver_bb.i \
	chancoding_blockdeinterleaver_bb.i \
	chancoding_unpacked_to_packed_bvi.i \
	chancoding_packed_to_unpacked_vib.i \
	chancoding_rm_encoder_vii.i \
	chancoding_rm_decoder_vii.i \
	chancoding_rmg_encoder_vii.i \
	chancoding_rmg_decoder_vii.i \
	chancoding_rm_encoder_bb.i \
	chancoding_rm_decoder_bb.i \
	chancoding_rmg_encoder_bb.i \
	chancoding_rmg_decoder_bb.i \
	chancoding_rmg_decoder_sd_fb.i \
	chancoding_rmg_decoder_sd_vfi.i

endif
