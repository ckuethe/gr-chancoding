/* -*- c++ -*- */
/* 
 * Copyright 2011 Communications Engineering Lab, KIT
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdexcept>
#include <gr_io_signature.h>
#include <chancoding_blockinterleaver_vbb.h>

chancoding_blockinterleaver_vbb_sptr
chancoding_make_blockinterleaver_vbb (unsigned n_rows, unsigned n_cols, unsigned bits_per_byte)
{
	return chancoding_blockinterleaver_vbb_sptr (new chancoding_blockinterleaver_vbb (n_rows, n_cols, bits_per_byte));
}


chancoding_blockinterleaver_vbb::chancoding_blockinterleaver_vbb (
		unsigned n_rows,
		unsigned n_cols,
		unsigned bits_per_byte)
	: gr_sync_block ("blockinterleaver_vbb",
		gr_make_io_signature (1, 1, sizeof(char) * n_rows * n_cols / bits_per_byte),
		gr_make_io_signature (1, 1, sizeof(char) * n_rows * n_cols / bits_per_byte)),
	d_n_rows(n_rows),
	d_n_cols(n_cols),
	d_bits_per_byte(bits_per_byte),
	d_vlen(n_rows * n_cols / bits_per_byte),
	d_interleaver(n_rows, n_cols, bits_per_byte)
{
}


chancoding_blockinterleaver_vbb::~chancoding_blockinterleaver_vbb ()
{
}


int
chancoding_blockinterleaver_vbb::work (int noutput_items,
			gr_vector_const_void_star &input_items,
			gr_vector_void_star &output_items)
{
	const unsigned char *in = (const unsigned char *) input_items[0];
	unsigned char *out = (unsigned char *) output_items[0];

	if (d_bits_per_byte == 1) {
		for (int i = 0; i < noutput_items; i++) {
			d_interleaver.interleave_symbols(&in[i * d_vlen], &out[i * d_vlen]);
		}
	} else {
		for (int i = 0; i < noutput_items; i++) {
			d_interleaver.interleave(&in[i * d_vlen], &out[i * d_vlen]);
		}
	}

	return noutput_items;
}

