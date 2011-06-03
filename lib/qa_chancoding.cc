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

#include <qa_chancoding.h>
#include <qa_industrystd_bb.h>
#include <qa_chancoding_markovchan_bb.h>
#include <qa_chancoding_blockinterleaver_vbb.h>
#include <qa_chancodingi_blockinterleaver.h>
#include <qa_chancoding_blockdeinterleaver_vbb.h>
#include <qa_chancoding_blockinterleaver_bb.h>
#include <qa_chancoding_blockdeinterleaver_bb.h>
#include <qa_chancodingi_rm_coding.h>

CppUnit::TestSuite *
qa_chancoding::suite()
{
	CppUnit::TestSuite *s = new CppUnit::TestSuite("chancoding");

	s->addTest(qa_industrystd_bb::suite());
	s->addTest(qa_chancoding_markovchan_bb::suite());
	s->addTest(qa_chancoding_blockinterleaver_vbb::suite());
	s->addTest(qa_chancodingi_blockinterleaver::suite());
	s->addTest(qa_chancoding_blockdeinterleaver_vbb::suite());
	s->addTest(qa_chancoding_blockinterleaver_bb::suite());
	s->addTest(qa_chancoding_blockdeinterleaver_bb::suite());
	s->addTest(qa_chancodingi_rm_coding::suite());

	return s;
}

