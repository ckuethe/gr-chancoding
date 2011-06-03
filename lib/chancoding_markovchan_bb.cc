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

#include <stdexcept>
#include <cmath>
#include <gr_io_signature.h>
#include <chancoding_markovchan_bb.h>

const double ftol = 1e-10;


chancoding_markovchan_bb_sptr
chancoding_make_markovchan_bb (std::vector<double> ber, std::vector<double> trans_matrix,
								unsigned bits_per_byte, unsigned init_state, long seed)
{
	return chancoding_markovchan_bb_sptr (new chancoding_markovchan_bb (ber, trans_matrix, bits_per_byte, init_state, seed));
}


chancoding_markovchan_bb::chancoding_markovchan_bb (std::vector<double> ber, std::vector<double> trans_matrix, unsigned bits_per_byte, unsigned init_state, long seed)
	: gr_sync_block ("markovchan_bb",
		gr_make_io_signature (1, 1, sizeof (char)),
		gr_make_io_signature2 (1, 2, sizeof (char), sizeof(int))),
	d_bits_per_byte(bits_per_byte),
	d_state(init_state),
	d_ber(ber),
	d_trans_matrix(trans_matrix),
	d_trans_interval_matrix(trans_matrix),
	d_random(seed)
{
	unsigned n = ber.size();

	// Sanity check
	if (d_state >= n || d_state < 0) {
		throw std::invalid_argument("Initial state is not valid.");
	}
	if (n * n != trans_matrix.size()) {
		throw std::invalid_argument("BER vector size does not match transition matrix size");
	}
	for (unsigned i = 0; i < n; i++) {
		if (ber[i] < 0 || ber[i] > 1) {
			throw std::invalid_argument("BER must be in range [0; 1]");
		}
	}
	for (unsigned i = 0; i < trans_matrix.size(); i++) {
		if (trans_matrix[i] < 0 || trans_matrix[i] > 1) {
			throw std::invalid_argument("State transition probabilities must be in range [0; 1]");
		}
	}
	if (d_bits_per_byte > 8) {
		throw std::invalid_argument("a byte only has 8 bits");
	}

	for (unsigned i = 0; i < n; i++) {
		for (unsigned j = 1; j < n; j++) {
			d_trans_interval_matrix[i * n + j] +=
					d_trans_interval_matrix[i * n + j - 1];
		}
	}

	// Every row's last column in d_trans_interval_matrix must now be one
	for (unsigned i = 0; i < ber.size(); i++) {
		if (fabs(d_trans_interval_matrix[(i+1) * n - 1] - 1) < ftol) {
			// We set it to exactly one to make sure the state change
			// is never undefined
			d_trans_interval_matrix[(i+1) * n - 1] = 1.0;
		} else {
			throw std::invalid_argument("transition matrix rows must add up to 1");
		}
	}
}


chancoding_markovchan_bb::~chancoding_markovchan_bb ()
{
}


double
chancoding_markovchan_bb::ber(int state)
{
	if (state < n_states()) {
		return d_ber[state];
	}

	return -1.0;
}


void
chancoding_markovchan_bb::set_state(int state)
{
	gruel::scoped_lock guard(d_mutex);
	if (state < n_states()) {
		d_state = state;
	} else {
		throw std::invalid_argument("set_state(): given state out of range");
	}
}


void
chancoding_markovchan_bb::set_ber(std::vector<double> ber)
{
	if (ber.size() != d_ber.size()) {
		throw std::invalid_argument("set_ber(): wrong number of BERs given");
	}

	gruel::scoped_lock guard(d_mutex);
	d_ber = ber;
}


int
chancoding_markovchan_bb::work (int noutput_items,
			gr_vector_const_void_star &input_items,
			gr_vector_void_star &output_items)
{
	const unsigned char *in = (const unsigned char *) input_items[0];
	unsigned char *out = (unsigned char *) output_items[0];
	int *out_state = NULL;
	bool relay_state = false;
	if (output_items.size() == 2) {
		relay_state = true;
		out_state = (int *) output_items[1];
	}

	gruel::scoped_lock guard(d_mutex);
	for (int i = 0; i < noutput_items; i++) {
		out[i] = in[i];
		for (unsigned b = 0; b < d_bits_per_byte; b++) {
			// Switch to new state
			double change_state = d_random.ran1();
			for (int s = 0; s < n_states(); s++) {
				if (change_state <= d_trans_interval_matrix[d_state * n_states() + s]) {
					d_state = s;
					break;
				}
			}

			// Apply current BER
			if (d_random.ran1() < d_ber[d_state]) {
				out[i] ^= (0x01 << b);
			}
		}
		if (relay_state) {
			out_state[i] = d_state;
		}
	}

	return noutput_items;
}

