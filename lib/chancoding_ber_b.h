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
#ifndef INCLUDED_CHANCODING_BER_B_H
#define INCLUDED_CHANCODING_BER_B_H

#include <gr_sync_block.h>
#include <gruel/thread.h>

class chancoding_ber_b;

typedef boost::shared_ptr<chancoding_ber_b> chancoding_ber_b_sptr;

chancoding_ber_b_sptr chancoding_make_ber_b (int bits_per_byte=1);

/*!
 * \brief Compare incoming bit streams (packed or unpacked) and count the differences.
 * \ingroup chancoding
 *
 * This block can be used in two ways: either as a sink, in which case there is no
 * output and the current BER can be read asynchronously using the ber() or bit_errors()
 * methods, or as a DSP block where the current BER is constantly streamed at the
 * output as a stream of floats at the same rate bytes are fed into the inputs.
 */
class chancoding_ber_b : public gr_sync_block
{
private:
	friend chancoding_ber_b_sptr chancoding_make_ber_b (int bits_per_byte);

	chancoding_ber_b (int bits_per_byte);

	unsigned long d_bitcounter;
	unsigned long d_errorcounter;
	int d_bits_per_byte;
	gruel::mutex d_mutex;

 public:
	~chancoding_ber_b ();

	float ber(); //! Return current BER
	long bit_errors(); //! Return total number of identified bit errors

	int work (int noutput_items,
		    gr_vector_const_void_star &input_items,
		    gr_vector_void_star &output_items);
};

#endif /* INCLUDED_CHANCODING_BER_B_H */

