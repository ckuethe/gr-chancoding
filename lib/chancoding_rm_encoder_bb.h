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

#ifndef INCLUDED_CHANCODING_RM_ENCODER_BB_H
#define INCLUDED_CHANCODING_RM_ENCODER_BB_H

#include <gr_hier_block2.h>
#include <chancoding_rm_encoder_vii.h>
#include <chancoding_unpacked_to_packed_bvi.h>
#include <chancoding_packed_to_unpacked_vib.h>

class chancoding_rm_encoder_bb;
typedef boost::shared_ptr<chancoding_rm_encoder_bb> chancoding_rm_encoder_bb_sptr;

chancoding_rm_encoder_bb_sptr chancoding_make_rm_encoder_bb (int r, int m);

/*!
 * \brief Hierarchical block for Reed-Muller encoding (bits at the in- & output)
 *
 * Encoder for standard Reed-Muller coding.
 * Only the LSB from each byte is used at the in- & output.
 *
 * See chancoding_rm_encoder_vii for decoding details.
 *
 * \param r Parameter for the order of the Reed-Muller Code (RM(r,m))
 * \param m Parameter for the length of the Reed-Muller Code (RM(r,m))
 *
 * \ingroup chancoding
 *
 */
class chancoding_rm_encoder_bb : public gr_hier_block2
{
	friend chancoding_rm_encoder_bb_sptr chancoding_make_rm_encoder_bb (int r, int m);

	chancoding_rm_encoder_bb (int r, int m);

	int d_num_codebits;
	int d_num_infobits;

	chancoding_unpacked_to_packed_bvi_sptr d_pack_bits;
	chancoding_packed_to_unpacked_vib_sptr d_unpack_bits;
	chancoding_rm_encoder_vii_sptr d_coding_action;

 public:
	~chancoding_rm_encoder_bb ();


};

#endif /* INCLUDED_CHANCODING_RM_ENCODER_BB_H */

