#
# Copyright 2004,2010 Free Software Foundation, Inc.
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

EXTRA_DIST = run_tests.in
TESTS = run_tests

modpython_PYTHON = \
	__init__.py

noinst_PYTHON = \
	qa_bercount.py \
	qa_bsc.py \
	qa_chancoding_industrystd_bb.py \
	qa_chancoding_markovchan_bb.py \
	qa_chancoding_blockinterleaver.py \
	qa_chancoding_unpacked_to_packed_bvi.py \
	qa_chancoding_packed_to_unpacked_vib.py \
	qa_chancoding_rm_encoder_vii.py \
	qa_chancoding_rm_decoder_vii.py \
	qa_chancoding_rmg_encoder_vii.py \
	qa_chancoding_rmg_decoder_vii.py \
	qa_chancoding_rmg_decoder_sd_vii.py \
	qa_chancoding_rmg_decoder_sd_vfi.py

