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

#ifndef INCLUDED_CHANCODING_PACKED_TO_UNPACKED_VIB_H
#define INCLUDED_CHANCODING_PACKED_TO_UNPACKED_VIB_H

#include <gr_sync_interpolator.h>

class chancoding_packed_to_unpacked_vib;
typedef boost::shared_ptr<chancoding_packed_to_unpacked_vib> chancoding_packed_to_unpacked_vib_sptr;

chancoding_packed_to_unpacked_vib_sptr chancoding_make_packed_to_unpacked_vib (int bits_per_vector);

/*!
 * \brief Bit-Unpacker
 *
 * Unpacks \p bits_per_vector from a given vector of integers at the input.
 * The vectorlength is given by the minimum number of integers needed to store \p bits_per_vector.  
 * At the output it generates a byte for each unpacked bit in which the bit itself is represented by the LSB.
 *
 * \param bits_per_vector How many bits should be unpacked from the vector of integers?
 *
 * \ingroup chancoding 
 *
 */
class chancoding_packed_to_unpacked_vib : public gr_sync_interpolator
{
	friend chancoding_packed_to_unpacked_vib_sptr chancoding_make_packed_to_unpacked_vib (int bits_per_vector);

	chancoding_packed_to_unpacked_vib (int bits_per_vector);

	int d_bits_per_vector;
	int d_vector_length;

 public:
	~chancoding_packed_to_unpacked_vib ();


	void bit_unpacker(const unsigned int*, unsigned char*);

	int work (int noutput_items,
		gr_vector_const_void_star &input_items,
		gr_vector_void_star &output_items);
};

#endif /* INCLUDED_CHANCODING_PACKED_TO_UNPACKED_VIB_H */

