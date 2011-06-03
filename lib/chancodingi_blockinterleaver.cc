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

#include <cstring>
#include <stdexcept>
#include <chancodingi_blockinterleaver.h>


///// Number crunching routines /////////////////////////////////////////////
//! Add a bit to a given buffer and increase counters
inline void
add_bit_to_out_buffer(unsigned char *buf,
		unsigned char val,
		unsigned &byte_idx, unsigned &bit_idx,
		unsigned bits_per_byte)
{
	buf[byte_idx] |= ((val & 0x01) << bit_idx); // Copy new bit onto bit position
	(bit_idx = ++bit_idx % bits_per_byte)
		|| ++byte_idx; // Increment counters
}


//! Shorthand for reading a single bit value from the input buffer
inline unsigned char
get_bit_from_in_buffer(
		const unsigned char *in,
		unsigned row_idx,
		unsigned bit_idx,
		unsigned col_idx,
		unsigned n_cols)
{
	return (unsigned char)
		(in[row_idx * n_cols + col_idx] >> bit_idx) // Shift my bit to LSB
		& 0x01; // And kill the rest
}


//! Perform actual (de-)interleaving
void
chancodingi_do_interleave_symbols(
		const unsigned char *in, unsigned char *out,
		unsigned rows, unsigned cols)
{
	unsigned out_byte_idx = 0;

	// c: current column-index of input buffer
	// r: current row-index of input buffer
	for (unsigned c = 0; c < cols; c++) {
		for (unsigned r = 0; r < rows; r++) {
			out[out_byte_idx++] = in[r * cols + c];
		}
	}
}


//! Perform actual (de-)interleaving, on bit-level
// \param cols The number of bytes one row takes (i.e., number of logical
//             columns/bits per byte).
void
chancodingi_do_interleave_bits(
		const unsigned char *in,
		unsigned char *out,
		unsigned rows, unsigned cols,
		unsigned bits_per_byte)
{
	unsigned out_byte_idx = 0;
	unsigned out_bit_idx = 0;

	memset((void *) out, 0, rows * cols);

	// c: current column-index of input buffer
	// b: current bit-index of input buffer
	// r: current row-index of input buffer
	for (unsigned c = 0; c < cols; c++) {
		for (unsigned b = 0; b < bits_per_byte; b++) {
			for (unsigned r = 0; r < rows; r++) {
				add_bit_to_out_buffer(out,
						get_bit_from_in_buffer(in, r, b, c, cols),
						out_byte_idx, out_bit_idx, bits_per_byte);
			}
		}
	}
}


//// Class definitions //////////////////////////////////////////////////////
chancodingi_blockinterleaver::chancodingi_blockinterleaver(
		int n_rows, int n_cols, int bits_per_byte) :
	d_n_rows(n_rows),
	d_n_cols(n_cols),
	d_bits_per_byte(bits_per_byte)
{
	if (bits_per_byte != 1 &&
			((n_rows % bits_per_byte) || (n_cols % bits_per_byte))) {
		throw std::invalid_argument("n_rows and n_cols must be integer multiples of bits_per_byte!");
	}
}


chancodingi_blockinterleaver::~chancodingi_blockinterleaver()
{
}


void
chancodingi_blockinterleaver::interleave_symbols(const unsigned char *in, unsigned char *out)
{
	chancodingi_do_interleave_symbols(in, out, d_n_rows, d_n_cols);
}


void
chancodingi_blockinterleaver::deinterleave_symbols(const unsigned char *in, unsigned char *out)
{
	chancodingi_do_interleave_symbols(in, out, d_n_cols, d_n_rows);
}


void
chancodingi_blockinterleaver::interleave(const unsigned char *in, unsigned char *out)
{
	chancodingi_do_interleave_bits(in, out, d_n_rows, d_n_cols/d_bits_per_byte, d_bits_per_byte);
}


void
chancodingi_blockinterleaver::deinterleave(const unsigned char *in, unsigned char *out)
{
	chancodingi_do_interleave_bits(in, out, d_n_cols, d_n_rows/d_bits_per_byte, d_bits_per_byte);
}

