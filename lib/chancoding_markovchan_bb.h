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

#ifndef INCLUDED_CHANCODING_MARKOVCHAN_BB_H
#define INCLUDED_CHANCODING_MARKOVCHAN_BB_H

#include <gr_sync_block.h>
#include <gr_random.h>
#include <gruel/thread.h>

class chancoding_markovchan_bb;
typedef boost::shared_ptr<chancoding_markovchan_bb> chancoding_markovchan_bb_sptr;

/*!
 * \param ber Vector containing the BER for every state. Elements must be in [0, 1].
 * \param trans_matrix A vector representing the transition matrix for the BER states.
 *                     The length of this vector must be the square of length of the ber
 *                     vector.
 * \param bits_per_byte The number of information bits stored in every byte.
 * \param init_state The initial state.
 */
chancoding_markovchan_bb_sptr
chancoding_make_markovchan_bb (
		std::vector<double> ber,
		std::vector<double> trans_matrix,
		unsigned bits_per_byte=1,
		unsigned init_state=0,
		long seed=3021);

/*! \brief A Markov-modeled binary channel.
 * \ingroup chancoding
 *
 * This binary channel has several states, each with an individual bit error rate.
 * A common way to configure this channel is with two states: one with a very small
 * BER, and one with a very large BER. This models a transmission system which
 * normally works quite well, but if it doesn't, crushes many bits at once (burst
 * errors).
 *
 * State changes can occur after every bit, according to a probability given in the
 * transmission matrix.
 *
 * For debugging purposes, the current state can be read at the second output.
 */
class chancoding_markovchan_bb : public gr_sync_block
{
	friend chancoding_markovchan_bb_sptr chancoding_make_markovchan_bb (std::vector<double> ber, std::vector<double> trans_matrix, unsigned bits_per_byte, unsigned init_state, long seed);

	chancoding_markovchan_bb (std::vector<double> ber, std::vector<double> trans_matrix, unsigned bits_per_byte, unsigned init_state, long seed);

	unsigned d_bits_per_byte; //! Bits per byte, in [1,8]
	unsigned d_state; //! Current state, in [0, ber.size())
	std::vector<double> d_ber; //! BER per state
	std::vector<double> d_trans_matrix; //! State transition matrix as a vector, read row-wise
	std::vector<double> d_trans_interval_matrix;

	gr_random d_random;
	gruel::mutex d_mutex;


 public:
	~chancoding_markovchan_bb ();

	double ber(int state);
	std::vector<double> ber() { return d_ber; };
	std::vector<double> transition_matrix() { return d_trans_matrix; };
	int n_states() { return d_ber.size(); };

	void set_state(int state);
	void set_ber(std::vector<double> ber);

	int work (int noutput_items,
		gr_vector_const_void_star &input_items,
		gr_vector_void_star &output_items);
};

#endif /* INCLUDED_CHANCODING_MARKOVCHAN_BB_H */

