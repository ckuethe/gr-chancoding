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

#include <cppunit/TestAssert.h>
#include <qa_chancodingi_blockinterleaver.h>
#include <chancodingi_blockinterleaver.h>

// Simplest case, 2x3 block interleaving with one bit per byte
void
qa_chancodingi_blockinterleaver::t1()
{
	const int n_rows = 2;
	const int n_cols = 3;
	const unsigned bits_per_byte = 1;
	const unsigned char flag = 0x01;
	const int n_syms = n_rows * n_cols;
	const unsigned char in[n_syms] =
		{0, 1, 0,
		 1, 1, 0};
	unsigned char out[n_syms] = {0, 0, 0, 0, 0, 0};
	const unsigned char expected[n_syms] =
		{0, 1,
	     1, 1,
	     0, 0};
	chancodingi_blockinterleaver interleaver(n_rows, n_cols, bits_per_byte);

	interleaver.interleave(in, out);
	for (int i = 0; i < n_syms; i++) {
		CPPUNIT_ASSERT_EQUAL((unsigned)(out[i] & flag), (unsigned)expected[i]);
	}
}


// 2x6 block interleaving with two bits per byte
void
qa_chancodingi_blockinterleaver::t2()
{
	const int n_rows = 2;
	const int n_cols = 6;
	const unsigned bits_per_byte = 2;
	const unsigned char flag = 0x03;
	const int n_syms = n_rows * n_cols;
	const unsigned char in[n_syms] = // 2x6
		{0x00, 0x01, 0x02,  // 00 10 01 LSB first notation
		 0x03, 0x02, 0x01}; // 11 01 10
	unsigned char out[n_syms] = {0, 0, 0, 0, 0, 0};
	const unsigned char expected[n_syms] = // 6x2
		{0x02,  // 01 LSB first notation
		 0x02,  // 01
	     0x01,  // 10
		 0x02,  // 01
	     0x02,  // 01
		 0x01}; // 10
	chancodingi_blockinterleaver interleaver(n_rows, n_cols, bits_per_byte);

	interleaver.interleave(in, out);
	for (int i = 0; i < n_syms; i++) {
		CPPUNIT_ASSERT_EQUAL((unsigned)(out[i] & flag), (unsigned)expected[i]);
	}
}


// 2x3 block interleaving, symbols
void
qa_chancodingi_blockinterleaver::t3()
{
	const int n_rows = 2;
	const int n_cols = 3;
	const int n_syms = n_rows * n_cols;
	const unsigned char in[n_syms] =
		{1, 2, 3,
		 4, 5, 6};
	unsigned char out[n_syms];
	const unsigned char expected[n_syms] =
		{1, 4,
		 2, 5,
		 3, 6};
	chancodingi_blockinterleaver interleaver(n_rows, n_cols);

	interleaver.interleave_symbols(in, out);
	for (int i = 0; i < n_syms; i++) {
		CPPUNIT_ASSERT_EQUAL((unsigned)out[i], (unsigned)expected[i]);
	}
}


// 20x55 block interleaving, symbols, compare in & out
void
qa_chancodingi_blockinterleaver::t4()
{
	const int n_rows = 20;
	const int n_cols = 55;
	const int n_syms = n_rows * n_cols;
	unsigned char in[n_syms];
	unsigned char interleaved[n_syms];
	unsigned char out[n_syms];

	for (int i = 0; i < n_syms; i++) {
		in[i] = (unsigned char) i % 256;
	}
	chancodingi_blockinterleaver interleaver(n_rows, n_cols);

	interleaver.interleave_symbols(in, interleaved);
	interleaver.deinterleave_symbols(interleaved, out);
	for (int i = 0; i < n_syms; i++) {
		CPPUNIT_ASSERT_EQUAL((unsigned)out[i], (unsigned)in[i]);
	}
}


// block interleaving, 2 bits per byte, compare in & out
void
qa_chancodingi_blockinterleaver::t5()
{
	const unsigned bits_per_byte = 2;
	const int n_rows = 20;
	const int n_cols = 55 * bits_per_byte;
	const int n_syms = n_rows * n_cols / bits_per_byte;
	unsigned char flag = (1 << bits_per_byte) - 1;
	unsigned char in[n_syms];
	unsigned char interleaved[n_syms];
	unsigned char out[n_syms];

	for (int i = 0; i < n_syms; i++) {
		in[i] = (unsigned char) (i % flag);
	}
	chancodingi_blockinterleaver interleaver(n_rows, n_cols, bits_per_byte);

	interleaver.interleave(in, interleaved);
	interleaver.deinterleave(interleaved, out);
	for (int i = 0; i < n_syms; i++) {
		CPPUNIT_ASSERT_EQUAL((unsigned) out[i], (unsigned) in[i]);
	}
}

