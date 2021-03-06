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
#include <chancoding_rm_encoder_vii.h>
#include <chancodingi_rm_coding.h>

const int BITS_PER_INT = sizeof(int) * 8;

chancoding_rm_encoder_vii_sptr
chancoding_make_rm_encoder_vii (int r, int m)
{
	return chancoding_rm_encoder_vii_sptr (new chancoding_rm_encoder_vii (r, m));
}


chancoding_rm_encoder_vii::chancoding_rm_encoder_vii (int r, int m)
	: gr_sync_block ("rm_encoder_vii",
		gr_make_io_signature (1, 1, sizeof (int) * rm_calc_num_int(rm_calc_num_infobits(r,m, 0)) ),
		gr_make_io_signature (1, 1, sizeof (int) * rm_calc_num_int(1<<m))),
	d_m(m),
	d_r(r),
	d_num_int_uncoded(rm_calc_num_int(rm_calc_num_infobits(r,m, 0))),
	d_num_int(rm_calc_num_int(1<<m)),
	d_num_rows(rm_calc_rows(r,m)),
	d_gen_mat(d_num_rows * d_num_int, 0)
{
	rm_generate_gen_mat(r, m, &d_gen_mat[0], d_num_rows, d_num_int);
}


chancoding_rm_encoder_vii::~chancoding_rm_encoder_vii ()
{
}

int chancoding_rm_encoder_vii::get_vlen_in() {
	return rm_calc_num_int(rm_calc_num_infobits(d_r,d_m, 0));
}

int chancoding_rm_encoder_vii::get_vlen_out() {
	return rm_calc_num_int(1<<d_m);
}

int chancoding_rm_encoder_vii::get_num_bits_in() {
	return rm_calc_num_infobits(d_r,d_m, 0);
}

int chancoding_rm_encoder_vii::get_num_bits_out() {
	return (1<<d_m);
}

int
chancoding_rm_encoder_vii::work (int noutput_items,
			gr_vector_const_void_star &input_items,
			gr_vector_void_star &output_items)
{
	const unsigned int *uncoded = (const unsigned int *) input_items[0];
	unsigned int *encoded = (unsigned int *) output_items[0];
	memset((void *) encoded, 0, noutput_items * d_num_int * sizeof(int));

	for(int i = 0; i < noutput_items; i++) {
		rm_encode(&d_gen_mat[0], d_num_rows, d_num_int, uncoded, encoded);

		uncoded += d_num_int_uncoded;
		encoded += d_num_int;
	}

	return noutput_items;
}

