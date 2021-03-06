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

#ifndef INCLUDED_CHANCODING_RMG_DECODER_SD_FB_H
#define INCLUDED_CHANCODING_RMG_DECODER_SD_FB_H

#include <gr_hier_block2.h>
#include <chancoding_rmg_decoder_sd_vfi.h>
#include <gr_stream_to_vector.h>
#include <chancoding_packed_to_unpacked_vib.h>

class chancoding_rmg_decoder_sd_fb;
typedef boost::shared_ptr<chancoding_rmg_decoder_sd_fb> chancoding_rmg_decoder_sd_fb_sptr;

chancoding_rmg_decoder_sd_fb_sptr chancoding_make_rmg_decoder_sd_fb (int m, int num_bits_precoded);

/*!
 * \brief Hierarchical block for Reed-Muller(-Golay) Soft-Decision-decoding (bits at the output)
 *
 * Soft-Decision-Decoder for Reed-Muller(-Golay) coding.
 * The input must be a vector of 2^\p m floats in range (0,1).
 * Only the LSB from each byte is used at the output.
 *
 * See chancoding_rmg_decoder_sd_vfi for decoding details.
 *
 * \param num_bits_precoded How many bits were used to select the golay-coset?
 * \param m Parameter for the length of the Reed-Muller Code (RM(r,m))
 *
 * \ingroup chancoding
 *
 */
class chancoding_rmg_decoder_sd_fb : public gr_hier_block2
{
	friend chancoding_rmg_decoder_sd_fb_sptr chancoding_make_rmg_decoder_sd_fb (int m, int num_bits_precoded);

	chancoding_rmg_decoder_sd_fb (int m, int num_bits_precoded);

	int d_num_codebits;
	int d_num_infobits;

	gr_stream_to_vector_sptr d_pack_vector;
	chancoding_packed_to_unpacked_vib_sptr d_unpack_bits;
	chancoding_rmg_decoder_sd_vfi_sptr d_coding_action;
 public:
	~chancoding_rmg_decoder_sd_fb ();


};

#endif /* INCLUDED_CHANCODING_RMG_DECODER_SD_FB_H */

