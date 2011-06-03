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
#include <gr_stream_to_vector.h>
#include <gr_vector_to_stream.h>
#include <chancoding_blockdeinterleaver_bb.h>


chancoding_blockdeinterleaver_bb_sptr
chancoding_make_blockdeinterleaver_bb (
		unsigned n_rows,
		unsigned n_cols,
		unsigned bits_per_byte)
{
	if (n_rows % bits_per_byte || n_cols % bits_per_byte) {
		throw std::invalid_argument("n_cols and n_bits must be integer multiples of bits_per_byte!");
	}
	return gnuradio::get_initial_sptr (new chancoding_blockdeinterleaver_bb (n_rows, n_cols, bits_per_byte));
}


chancoding_blockdeinterleaver_bb_sptr
chancoding_make_blockdeinterleaver_bb (chancoding_blockinterleaver_bb_sptr interleaver)
{
	return chancoding_make_blockdeinterleaver_bb(
			interleaver->n_rows(),
			interleaver->n_cols(),
			interleaver->bits_per_byte());
}


chancoding_blockdeinterleaver_bb::chancoding_blockdeinterleaver_bb (unsigned n_rows, unsigned n_cols, unsigned bits_per_byte)
	: gr_hier_block2 ("blockdeinterleaver_bb",
		gr_make_io_signature (1, 1, sizeof (char)),
		gr_make_io_signature (1, 1, sizeof (char))),
	d_deinterleaver(chancoding_make_blockdeinterleaver_vbb(n_rows, n_cols, bits_per_byte))
{
	gr_stream_to_vector_sptr s2v(gr_make_stream_to_vector(sizeof(char), n_rows * n_cols / bits_per_byte));
	gr_vector_to_stream_sptr v2s(gr_make_vector_to_stream(sizeof(char), n_rows * n_cols / bits_per_byte));

	connect(self(), 0, s2v, 0);
	connect(s2v, 0, d_deinterleaver, 0);
	connect(d_deinterleaver, 0, v2s, 0);
	connect(v2s, 0, self(), 0);
}


chancoding_blockdeinterleaver_bb::~chancoding_blockdeinterleaver_bb ()
{
}

