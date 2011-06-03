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
#include <qa_chancoding_blockinterleaver_vbb.h>
#include <chancoding_blockinterleaver_vbb.h>


void
qa_chancoding_blockinterleaver_vbb::t1()
{
	chancoding_blockinterleaver_vbb_sptr
		interleaver(chancoding_make_blockinterleaver_vbb(2, 3, 1));
}


void
qa_chancoding_blockinterleaver_vbb::t2()
{
	CPPUNIT_ASSERT_THROW(
			chancoding_blockinterleaver_vbb_sptr
					interleaver(chancoding_make_blockinterleaver_vbb(20, 20, 3)),
			std::invalid_argument);
}

