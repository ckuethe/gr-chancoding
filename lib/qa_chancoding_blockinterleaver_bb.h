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

#ifndef INCLUDED_QA_CHANCODING_BLOCKINTERLEAVER_BB_H
#define INCLUDED_QA_CHANCODING_BLOCKINTERLEAVER_BB_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestCase.h>

class qa_chancoding_blockinterleaver_bb : public CppUnit::TestCase {

	CPPUNIT_TEST_SUITE (qa_chancoding_blockinterleaver_bb);
	CPPUNIT_TEST (t1);
	CPPUNIT_TEST (t2);
	CPPUNIT_TEST_SUITE_END ();

 private:
	void t1 ();
	void t2 ();
};

#endif /* INCLUDED_QA_CHANCODING_BLOCKINTERLEAVER_BB_H */

