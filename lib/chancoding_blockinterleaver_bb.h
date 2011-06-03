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

#ifndef INCLUDED_CHANCODING_BLOCKINTERLEAVER_BB_H
#define INCLUDED_CHANCODING_BLOCKINTERLEAVER_BB_H

#include <gr_hier_block2.h>
#include <chancoding_blockinterleaver_vbb.h>


class chancoding_blockinterleaver_bb;
typedef boost::shared_ptr<chancoding_blockinterleaver_bb> chancoding_blockinterleaver_bb_sptr;

chancoding_blockinterleaver_bb_sptr chancoding_make_blockinterleaver_bb (unsigned n_rows, unsigned n_cols, unsigned bits_per_byte=1);

/*!
 * \brief Block interleaver.
 *
 * Input 0: A stream of bytes
 * Output 0: A stream of interleaved bytes
 */
class chancoding_blockinterleaver_bb : public gr_hier_block2
{
	friend chancoding_blockinterleaver_bb_sptr chancoding_make_blockinterleaver_bb (unsigned n_rows, unsigned n_cols, unsigned bits_per_byte);
	chancoding_blockinterleaver_bb (unsigned n_rows, unsigned n_cols, unsigned bits_per_byte);

	chancoding_blockinterleaver_vbb_sptr d_interleaver;

	unsigned d_n_rows;
	unsigned d_n_cols;
	unsigned d_bits_per_byte;

 public:
	unsigned n_rows() { return d_n_rows; };
	unsigned n_cols() { return d_n_cols; };
	unsigned bits_per_byte() { return d_bits_per_byte; };

	~chancoding_blockinterleaver_bb ();
};

#endif /* INCLUDED_CHANCODING_BLOCKINTERLEAVER_BB_H */

