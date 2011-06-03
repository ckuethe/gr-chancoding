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

#ifndef INCLUDED_CHANCODING_RM_ENCODER_VII_H
#define INCLUDED_CHANCODING_RM_ENCODER_VII_H

#include <gr_sync_block.h>

class chancoding_rm_encoder_vii;
typedef boost::shared_ptr<chancoding_rm_encoder_vii> chancoding_rm_encoder_vii_sptr;

chancoding_rm_encoder_vii_sptr chancoding_make_rm_encoder_vii (int r, int m);

/*!
 * \brief Reed-Muller Encoder
 *
 * Encodes \f$ \sum_{i=0}^{r} {m \choose i} \f$ bits from the vector of integers at the input, starting with the LSB of the first element. 
 * The 2^\p m encoded bits are bitwise put into a vector of integers, starting with the LSB of the first element.
 *
 * \param r Parameter for the order of the Reed-Muller Code (RM(r,m))
 * \param m Parameter for the length of the Reed-Muller Code (RM(r,m))
 *
 * \ingroup chancoding 
 *
 */

class chancoding_rm_encoder_vii : public gr_sync_block
{
	friend chancoding_rm_encoder_vii_sptr chancoding_make_rm_encoder_vii (int r, int m);

	chancoding_rm_encoder_vii (int r, int m);
	int d_m;
	int d_r;
	int d_num_int_uncoded;
	int d_num_int;
	int d_num_rows;
	std::vector<unsigned int> d_gen_mat;

 public:
	~chancoding_rm_encoder_vii ();

	/*!
	 * Returns the length of the vector at the input
	*/
	int get_vlen_in();

	/*!
	 * Returns the length of the vector at the output
	*/
	int get_vlen_out();

	/*!
	 * Returns the number of bits taken from the input
	*/
	int get_num_bits_in();

	/*!
	 * Returns the number of bits produced at the output
	*/
	int get_num_bits_out();
	int work (int noutput_items,
		gr_vector_const_void_star &input_items,
		gr_vector_void_star &output_items);
};

#endif /* INCLUDED_CHANCODING_RM_ENCODER_VII_H */

