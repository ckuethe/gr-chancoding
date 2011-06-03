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

#ifndef INCLUDED_CHANCODING_UNPACKED_TO_PACKED_BVI_H
#define INCLUDED_CHANCODING_UNPACKED_TO_PACKED_BVI_H

#include <gr_sync_decimator.h>

class chancoding_unpacked_to_packed_bvi;
typedef boost::shared_ptr<chancoding_unpacked_to_packed_bvi> chancoding_unpacked_to_packed_bvi_sptr;

chancoding_unpacked_to_packed_bvi_sptr chancoding_make_unpacked_to_packed_bvi (int bits_per_vector);

/*!
 * \brief Bit-packer
 *
 * Packs \p bits_per_vector from a stream of bytes at the input (only the LSB of each byte is used) into a vector of integers (bitwise).
 * The vectorlength is given by the minimum number of integers needed to store \p bits_per_vector.  
 *
 * \param bits_per_vector How many bits should be packed into the vector of integers?
 *
 * \ingroup chancoding 
 *
 */
class chancoding_unpacked_to_packed_bvi : public gr_sync_decimator
{
	friend chancoding_unpacked_to_packed_bvi_sptr chancoding_make_unpacked_to_packed_bvi (int bits_per_vector);

	chancoding_unpacked_to_packed_bvi (int bits_per_vector);

	int d_bits_per_vector;
	int d_vector_length;


 public:
	~chancoding_unpacked_to_packed_bvi ();

	void bit_packer(const unsigned char*, unsigned int*);

	int work (int noutput_items,
		gr_vector_const_void_star &input_items,
		gr_vector_void_star &output_items);
};

#endif /* INCLUDED_CHANCODING_UNPACKED_TO_PACKED_BVI_H */

