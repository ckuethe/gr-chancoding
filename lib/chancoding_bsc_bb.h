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
#ifndef INCLUDED_CHANCODING_BSC_BB_H
#define INCLUDED_CHANCODING_BSC_BB_H

#include <gr_sync_block.h>
#include <gr_random.h>
#include <gruel/thread.h>

class chancoding_bsc_bb;

typedef boost::shared_ptr<chancoding_bsc_bb> chancoding_bsc_bb_sptr;

/*!
 * \param ber Bit error rate induced by the BSC
 * \param bits_per_byte Number of info bits per input byte
 */
chancoding_bsc_bb_sptr chancoding_make_bsc_bb (float ber, unsigned bits_per_byte=1, long seed=3021);

/*!
 * \brief A binary, symmetric channel for simulating bit errors.
 * \ingroup chancoding
 */
class chancoding_bsc_bb : public gr_sync_block
{
private:
	friend chancoding_bsc_bb_sptr chancoding_make_bsc_bb (float ber, unsigned bits_per_byte, long seed);

	chancoding_bsc_bb (float ber, unsigned bits_per_byte, long seed=3021);

	float d_ber;
	int d_bits_per_byte;
	gr_random d_random;
	gruel::mutex d_mutex;

 public:
	~chancoding_bsc_bb ();

	float ber() { return d_ber; };
	void set_ber(float ber);

	int work (int noutput_items,
		    gr_vector_const_void_star &input_items,
		    gr_vector_void_star &output_items);
};

#endif /* INCLUDED_CHANCODING_BSC_BB_H */

