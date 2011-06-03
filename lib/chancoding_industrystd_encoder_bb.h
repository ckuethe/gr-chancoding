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

#ifndef INCLUDED_CHANCODING_INDUSTRYSTD_ENCODER_BB_H
#define INCLUDED_CHANCODING_INDUSTRYSTD_ENCODER_BB_H

#include <gr_hier_block2.h>
#include <trellis_encoder_bb.h>

class chancoding_industrystd_encoder_bb;
typedef boost::shared_ptr<chancoding_industrystd_encoder_bb> chancoding_industrystd_encoder_bb_sptr;

chancoding_industrystd_encoder_bb_sptr
chancoding_make_industrystd_encoder_bb (unsigned bits_per_input_byte=1, unsigned bits_per_output_byte=1, int ST=0);

/*!
 * \brief Industry-standard convolutional code, as used in 802.11a.
 *
 * This is a CC of rate 1/2, k = 7. It's generator polynomials are
 *
 * g_1(x) = 1 + x^2 + x^3 + x^5 + x^6
 * g_2(x) = 1 + x   + x^2 + x^3 + x^6
 *
 * (0133 0171 in octal representation). This is a transparent code. It is used in many
 * applications, such as 802.11a and is the best known CC for k=7.
 *
 * \param bits_per_input_byte Number of bits from every input byte which are relevant.
 *        In most cases, the values 1 (only one bit per byte) or 8 (every bit is relevant)
 *        will be used, but any other value should work, too.
 * \param bits_per_output_byte Number of bits which are coded to every output byte. E.g.,
 *        if a 8-PSK encoder follows directly afterwards, using '3' makes it possible to use
 *        gr_chunks_to_symbols as the next block.
 * \param ST Initial state of FSM
 *
 */
class chancoding_industrystd_encoder_bb : public gr_hier_block2
{
	friend chancoding_industrystd_encoder_bb_sptr
		chancoding_make_industrystd_encoder_bb (unsigned bits_per_input_byte, unsigned bits_per_output_byte, int ST);

	chancoding_industrystd_encoder_bb (unsigned bits_per_input_byte, unsigned bits_per_output_byte, int ST);

	trellis_encoder_bb_sptr d_encoder;

	void connect_input_alignment(int bits_per_input_byte);
	void connect_output_alignment(int bits_per_output_byte);

 public:
	~chancoding_industrystd_encoder_bb ();

	fsm FSM() const { return d_encoder->FSM(); };
	int ST() const { return d_encoder->ST(); };
};

#endif /* INCLUDED_CHANCODING_INDUSTRYSTD_ENCODER_BB_H */

