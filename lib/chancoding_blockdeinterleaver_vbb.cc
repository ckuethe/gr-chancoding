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

#include <gr_io_signature.h>
#include <chancoding_blockdeinterleaver_vbb.h>


chancoding_blockdeinterleaver_vbb_sptr
chancoding_make_blockdeinterleaver_vbb (
		unsigned n_rows,
		unsigned n_cols,
		unsigned bits_per_byte)
{
	return chancoding_blockdeinterleaver_vbb_sptr (new chancoding_blockdeinterleaver_vbb (n_rows, n_cols, bits_per_byte));
}


chancoding_blockdeinterleaver_vbb_sptr
chancoding_make_blockdeinterleaver_vbb(chancoding_blockinterleaver_vbb_sptr interleaver)
{
	return chancoding_make_blockdeinterleaver_vbb(
				interleaver->n_rows(),
				interleaver->n_cols(),
				interleaver->bits_per_byte());
}

chancoding_blockdeinterleaver_vbb::chancoding_blockdeinterleaver_vbb(
		unsigned n_rows,
		unsigned n_cols,
		unsigned bits_per_byte)
	: gr_sync_block ("blockdeinterleaver_vbb",
		gr_make_io_signature (1, 1, sizeof(char) * n_rows * n_cols / bits_per_byte),
		gr_make_io_signature (1, 1, sizeof(char) * n_rows * n_cols / bits_per_byte)),
	d_n_rows(n_rows),
	d_n_cols(n_cols),
	d_bits_per_byte(bits_per_byte),
	d_vlen(n_rows * n_cols / bits_per_byte),
	d_interleaver(n_rows, n_cols, bits_per_byte)
{
}


chancoding_blockdeinterleaver_vbb::~chancoding_blockdeinterleaver_vbb ()
{
}


int
chancoding_blockdeinterleaver_vbb::work (int noutput_items,
			gr_vector_const_void_star &input_items,
			gr_vector_void_star &output_items)
{
	const unsigned char *in = (const unsigned char *) input_items[0];
	unsigned char *out = (unsigned char *) output_items[0];

	if (d_bits_per_byte == 1) {
		for (int i = 0; i < noutput_items; i++) {
			d_interleaver.deinterleave_symbols(&in[i * d_vlen], &out[i * d_vlen]);
		}
	} else {
		for (int i = 0; i < noutput_items; i++) {
			d_interleaver.deinterleave(&in[i * d_vlen], &out[i * d_vlen]);
		}
	}

	return noutput_items;
}

