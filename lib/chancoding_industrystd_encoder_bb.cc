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
#include <chancoding_industrystd_encoder_bb.h>
#include <gr_unpacked_to_packed_bb.h>
#include <gr_packed_to_unpacked_bb.h>
#include <gr_unpack_k_bits_bb.h>


const std::vector<int>
chancodingi_make_G()
{
	std::vector<int> G(2);
	G[0] = 0133;
	G[1] = 0171;

	return (const std::vector<int>) G;
}


chancoding_industrystd_encoder_bb_sptr
chancoding_make_industrystd_encoder_bb (unsigned bits_per_input_byte, unsigned bits_per_output_byte, int ST)
{
	return gnuradio::get_initial_sptr (new chancoding_industrystd_encoder_bb (bits_per_input_byte, bits_per_output_byte, ST));
}


chancoding_industrystd_encoder_bb::chancoding_industrystd_encoder_bb (unsigned bits_per_input_byte, unsigned bits_per_output_byte, int ST)
	: gr_hier_block2 ("industrystd_encoder_bb",
		gr_make_io_signature (1, 1, sizeof(char)),
		gr_make_io_signature (1, 1, sizeof(char))),
	d_encoder(trellis_make_encoder_bb(fsm(1, 2, chancodingi_make_G()), ST))

{
	if (bits_per_input_byte > 8 || bits_per_output_byte > 8) {
		throw std::invalid_argument("A byte does not have more than 8 bits.");
	}

	connect_input_alignment(bits_per_input_byte);
	connect_output_alignment(bits_per_output_byte);
}


/**
 * \brief Ensure the trellis gets connected in a manner that it always gets 1 Bit at a time.
 */
void
chancoding_industrystd_encoder_bb::connect_input_alignment(int bits_per_input_byte)
{
	if (bits_per_input_byte == 1) {
		connect(self(), 0, d_encoder, 0);
	} else {
		gr_unpack_k_bits_bb_sptr unpacker(gr_make_unpack_k_bits_bb(bits_per_input_byte));
		connect(self(), 0, unpacker, 0);
		connect(unpacker, 0, d_encoder, 0);
	}
}


/**
 * \brief Connect the CC in a manner that every output byte has the right number of bits.
 */
void
chancoding_industrystd_encoder_bb::connect_output_alignment(int bits_per_output_byte)
{
	if (bits_per_output_byte == 2) {
		connect(d_encoder, 0, self(), 0);
	} else {
		gr_unpacked_to_packed_bb_sptr out_packer = gr_make_unpacked_to_packed_bb(2, GR_MSB_FIRST);
		connect(d_encoder, 0, out_packer, 0);
		if (bits_per_output_byte == 8) {
			connect(out_packer, 0, self(), 0);
		} else {
			gr_packed_to_unpacked_bb_sptr out_unpacker = gr_make_packed_to_unpacked_bb(bits_per_output_byte, GR_MSB_FIRST);
			connect(out_packer, 0, out_unpacker, 0);
			connect(out_unpacker, 0, self(), 0);
		}
	}
}


chancoding_industrystd_encoder_bb::~chancoding_industrystd_encoder_bb ()
{
}

