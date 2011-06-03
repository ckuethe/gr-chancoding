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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gr_io_signature.h>
#include <chancoding_rm_encoder_bb.h>
#include <chancodingi_rm_coding.h>
#include <chancoding_rm_encoder_vii.h>
#include <chancoding_unpacked_to_packed_bvi.h>
#include <chancoding_packed_to_unpacked_vib.h>


chancoding_rm_encoder_bb_sptr
chancoding_make_rm_encoder_bb (int r, int m)
{
	return gnuradio::get_initial_sptr (new chancoding_rm_encoder_bb (r, m));
}


chancoding_rm_encoder_bb::chancoding_rm_encoder_bb (int r, int m)
	: gr_hier_block2 ("rm_encoder_bb",
		gr_make_io_signature (1, 1, sizeof (char)),
		gr_make_io_signature (1, 1, sizeof (char)))
{
	d_num_codebits = (1<<m);
	d_num_infobits = rm_calc_num_infobits(r,m, 0);

	d_pack_bits = chancoding_make_unpacked_to_packed_bvi(d_num_infobits);
	d_unpack_bits = chancoding_make_packed_to_unpacked_vib(d_num_codebits);
	d_coding_action = chancoding_make_rm_encoder_vii(r, m);

	connect(self(), 0, d_pack_bits, 0);
	connect(d_pack_bits, 0, d_coding_action, 0);
	connect(d_coding_action, 0, d_unpack_bits, 0);
	connect(d_unpack_bits, 0, self(), 0);
}


chancoding_rm_encoder_bb::~chancoding_rm_encoder_bb ()
{
}

