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

#ifndef INCLUDED_CHANCODING_RMG_DECODER_SD_VFI_H
#define INCLUDED_CHANCODING_RMG_DECODER_SD_VFI_H

#include <gr_sync_block.h>
#include <complex>

class chancoding_rmg_decoder_sd_vfi;
typedef boost::shared_ptr<chancoding_rmg_decoder_sd_vfi> chancoding_rmg_decoder_sd_vfi_sptr;

chancoding_rmg_decoder_sd_vfi_sptr chancoding_make_rmg_decoder_sd_vfi (int m, int num_bits_precoded);

/*!
 * \brief Reed-Muller(-Golay) Soft-Decision-Decoder
 *
 * Decodes a codeword with a length of 2^m bits from the vector of floats at the input.
 * The floats have to be in the range (0,1). Each floats includes information on the reliability of the corresponding bit.    
 * The 1 + \p m + \p num_bits_precoded decoded bits are bitwise put into a vector of integers, starting with the LSB of the first element.
 * 
 * The algorithm used is based on the method of supercode decoding (modified version of algorithm 17 introduced in  DAVIS , J.A. and J. JEDWAB: "Peak-to-mean power control in OFDM, Golay comple-
 * mentary sequences, and Reed-Muller codes". Information Theory, IEEE Transactions
 * on, 45(7):2397 –2417, November 1999.)
 *
 * \param num_bits_precoded How many bits were used to select the golay-coset?
 * \param m Parameter for the length of the Reed-Muller Code (RM(r,m))
 *
 * \ingroup chancoding 
 *
 */

class chancoding_rmg_decoder_sd_vfi : public gr_sync_block
{
	friend chancoding_rmg_decoder_sd_vfi_sptr chancoding_make_rmg_decoder_sd_vfi (int m, int num_bits_precoded);

	chancoding_rmg_decoder_sd_vfi (int m, int num_bits_precoded);

	int d_m;
	int d_num_bits;
	int d_num_int;
	int d_num_int_decoded;
	int d_num_bits_precoded;
	int d_num_lin_comb_order_2;
	int d_num_int_precode_mat;
	int d_num_rows_precode_mat;

	std::vector<unsigned int> d_gen_mat;
	std::vector<std::complex<float> > d_y;
	std::vector<unsigned int> d_coset;
	std::vector<unsigned int> d_precode_mat;

 public:
	~chancoding_rmg_decoder_sd_vfi ();

	/*!
	 * Returns the length of the vector at the input
	*/
	int get_vlen_in();

	/*!
	 * Returns the length of the vector at the output
	*/
	int get_vlen_out();

	/*!
	 * Returns the number of bits produced at the output
	*/
	int get_num_bits_out();
	int work (int noutput_items,
		gr_vector_const_void_star &input_items,
		gr_vector_void_star &output_items);
};

#endif /* INCLUDED_CHANCODING_RMG_DECODER_SD_VFI_H */

