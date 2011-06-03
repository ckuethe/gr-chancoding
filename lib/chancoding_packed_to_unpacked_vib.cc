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
#include <chancoding_packed_to_unpacked_vib.h>
#include <chancodingi_rm_coding.h>


chancoding_packed_to_unpacked_vib_sptr
chancoding_make_packed_to_unpacked_vib (int bits_per_vector)
{
	return chancoding_packed_to_unpacked_vib_sptr (new chancoding_packed_to_unpacked_vib (bits_per_vector));
}


chancoding_packed_to_unpacked_vib::chancoding_packed_to_unpacked_vib (int bits_per_vector)
	: gr_sync_interpolator ("packed_to_unpacked_vib",
		gr_make_io_signature (1, 1, sizeof(int) * rm_calc_num_int(bits_per_vector)),
		gr_make_io_signature (1, 1, sizeof (char)), bits_per_vector )
{
	d_bits_per_vector = bits_per_vector;
	d_vector_length = rm_calc_num_int(bits_per_vector);
}


chancoding_packed_to_unpacked_vib::~chancoding_packed_to_unpacked_vib ()
{
}

void
chancoding_packed_to_unpacked_vib::bit_unpacker(const unsigned int* in_int_vec, unsigned char* out_char)
{
	int num_bits_per_int = sizeof(int) * 8;
	memset((void *) out_char, 0, d_bits_per_vector * sizeof(char) );

	int current_integer = 0;
	for(int bit_counter = 0; bit_counter < d_bits_per_vector; bit_counter++)
	{
		if(bit_counter % num_bits_per_int == 0 && bit_counter > 0)
			current_integer++;
		if(in_int_vec[current_integer] & (1<<(bit_counter - current_integer * num_bits_per_int)))
			out_char[bit_counter] = (1<<0);
	}
}

int
chancoding_packed_to_unpacked_vib::work (int noutput_items,
			gr_vector_const_void_star &input_items,
			gr_vector_void_star &output_items)
{
	const unsigned int *in = (const unsigned int *) input_items[0];
	unsigned char *out = (unsigned char *) output_items[0];

	for(int i = 0; i < noutput_items / d_bits_per_vector; i++)
	{
		bit_unpacker(in, out);

		in += d_vector_length;
		out += d_bits_per_vector;
	}

	return noutput_items;
}

