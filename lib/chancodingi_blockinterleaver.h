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

#ifndef INCLUDED_CHANCODINGI_BLOCKINTERLEAVER_H
#define INCLUDED_CHANCODINGI_BLOCKINTERLEAVER_H

/*!
 * \brief Block (de-)interleaver, implementation stuff.
 *
 * Performs the actual (de-)interleaving.
 */
class chancodingi_blockinterleaver
{
 public:
	chancodingi_blockinterleaver(int n_rows, int n_cols, int bits_per_byte=1);
	~chancodingi_blockinterleaver();

	void interleave_symbols(const unsigned char *in, unsigned char *out);
	void deinterleave_symbols(const unsigned char *in, unsigned char *out);
	void interleave(const unsigned char *in, unsigned char *out);
	void deinterleave(const unsigned char *in, unsigned char *out);

 private:
	unsigned d_n_rows;
	unsigned d_n_cols;
	unsigned d_bits_per_byte;

};

#endif /* INCLUDED_CHANCODINGI_BLOCKINTERLEAVER_H */

