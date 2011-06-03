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

#include <chancoding_ber_b.h>
#include <gr_io_signature.h>

chancoding_ber_b_sptr
chancoding_make_ber_b (int bits_per_byte)
{
	return chancoding_ber_b_sptr (new chancoding_ber_b (bits_per_byte));
}


chancoding_ber_b::chancoding_ber_b (int bits_per_byte)
  : gr_sync_block ("ber_b",
	      gr_make_io_signature (2, 2, 1), gr_make_io_signature (0, 1, sizeof(float))),
	d_bitcounter(0),
	d_errorcounter(0),
	d_bits_per_byte(bits_per_byte)
{
	if (d_bits_per_byte > 8) {
		throw std::invalid_argument("a byte does not have more than 8 bits.");
	}
}


chancoding_ber_b::~chancoding_ber_b ()
{
}


float
chancoding_ber_b::ber()
{
	gruel::scoped_lock guard(d_mutex);
	return ((float) d_errorcounter) / d_bitcounter;
}


long
chancoding_ber_b::bit_errors()
{
	gruel::scoped_lock guard(d_mutex);
	return d_errorcounter;
}


int
chancoding_ber_b::work (int noutput_items,
			       gr_vector_const_void_star &input_items,
			       gr_vector_void_star &output_items)
{
	const unsigned char *in1 = (const unsigned char *) input_items[0];
	const unsigned char *in2 = (const unsigned char *) input_items[1];
	float *out = NULL;
	bool output_ber = (bool) output_items.size();
	if (output_ber) {
		out = (float *) output_items[0];
	}

	gruel::scoped_lock guard(d_mutex);
	for (int i = 0; i < noutput_items; i++) {
		unsigned char byte1 = in1[i];
		unsigned char byte2 = in2[i];
		for (int b = 0; b < d_bits_per_byte; b++) {
			if ((byte1 & (1 << b)) != (byte2 & (1 << b))) {
				d_errorcounter++;
			}
			d_bitcounter++;
		}

		if (output_ber) {
			out[i] = ((float) d_errorcounter) / d_bitcounter;
		}
	}

	return noutput_items;
}

