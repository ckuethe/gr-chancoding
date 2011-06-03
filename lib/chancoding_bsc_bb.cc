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

#include <chancoding_bsc_bb.h>
#include <gr_io_signature.h>

chancoding_bsc_bb_sptr
chancoding_make_bsc_bb (float ber, unsigned bits_per_byte, long seed)
{
  return chancoding_bsc_bb_sptr (new chancoding_bsc_bb (ber, bits_per_byte, seed));
}


chancoding_bsc_bb::chancoding_bsc_bb (float ber, unsigned bits_per_byte, long seed)
  : gr_sync_block ("bsc_bb",
	      gr_make_io_signature (1, 1, 1), gr_make_io_signature (1, 1, 1)),
	d_ber(ber),
	d_bits_per_byte(bits_per_byte),
	d_random(seed)
{
	if (ber < 0 || ber > 1) {
		throw std::invalid_argument("ber must be in range [0; 1]");
	}
	if (d_bits_per_byte > 8) {
		throw std::invalid_argument("a byte only has 8 bits");
	}
}


chancoding_bsc_bb::~chancoding_bsc_bb ()
{
}


void
chancoding_bsc_bb::set_ber(float ber)
{
	gruel::scoped_lock guard(d_mutex);
	d_ber = ber;
}


int
chancoding_bsc_bb::work (int noutput_items,
			       gr_vector_const_void_star &input_items,
			       gr_vector_void_star &output_items)
{

	const unsigned char *in = (const unsigned char *) input_items[0];
	unsigned char *out = (unsigned char *) output_items[0];

	gruel::scoped_lock guard(d_mutex);
	for (int i = 0; i < noutput_items; i++) {
		out[i] = in[i];
		for (int b = 0; b < d_bits_per_byte; b++) {
			if (d_random.ran1() < d_ber) {
				out[i] ^= (0x01 << b);
			}
		}
	}

	return noutput_items;
}

