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

#ifndef INCLUDED_CHANCODING_BLOCKDEINTERLEAVER_VBB_H
#define INCLUDED_CHANCODING_BLOCKDEINTERLEAVER_VBB_H

#include <gr_sync_block.h>
#include <chancoding_blockinterleaver_vbb.h>

class chancoding_blockdeinterleaver_vbb;
typedef boost::shared_ptr<chancoding_blockdeinterleaver_vbb> chancoding_blockdeinterleaver_vbb_sptr;

chancoding_blockdeinterleaver_vbb_sptr
chancoding_make_blockdeinterleaver_vbb (
		unsigned n_rows,
		unsigned n_cols,
		unsigned bits_per_byte=1);

//! Create a matching deinterleaver to a given interleaver
chancoding_blockdeinterleaver_vbb_sptr
chancoding_make_blockdeinterleaver_vbb (
		chancoding_blockinterleaver_vbb_sptr interleaver);

/*!
 * \brief Block deinterleaver.
 *
 * Inverse operation to chancoding_blockinterleaver_vbb.
 */
class chancoding_blockdeinterleaver_vbb : public gr_sync_block
{
	friend chancoding_blockdeinterleaver_vbb_sptr chancoding_make_blockdeinterleaver_vbb (unsigned n_rows, unsigned n_cols, unsigned bits_per_byte);
	chancoding_blockdeinterleaver_vbb (unsigned n_rows, unsigned n_cols, unsigned bits_per_byte);

	unsigned d_n_rows;
	unsigned d_n_cols;
	unsigned d_bits_per_byte;
	int d_vlen;

	chancodingi_blockinterleaver d_interleaver;

 public:
	~chancoding_blockdeinterleaver_vbb ();

	unsigned n_rows() { return d_n_rows; };
	unsigned n_cols() { return d_n_cols; };
	unsigned bits_per_byte() { return d_bits_per_byte; };

	int work (int noutput_items,
		gr_vector_const_void_star &input_items,
		gr_vector_void_star &output_items);
};

#endif /* INCLUDED_CHANCODING_BLOCKDEINTERLEAVER_VBB_H */

