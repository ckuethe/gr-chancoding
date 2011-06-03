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

#ifndef INCLUDED_CHANCODINGI_RM_CODING_H
#define INCLUDED_CHANCODINGI_RM_CODING_H

#include <complex>

//calc functions
/*!
 * \brief Calculate binomial coefficient
 */
int rm_binom_coeff(int, int);
/*!
 * \brief Calculate number of rows of the generator-matrix
 */
int rm_calc_rows(int, int);
/*!
 * \brief Calculate greatest common divisor
 */
unsigned long long rm_gcd(unsigned long long, unsigned long long);
/*!
 * \brief Calculate maximum number of bits that can be used to select the golay-coset
 */
unsigned int rm_calc_num_bits_precoded(int);
/*!
 * \brief Calculate the dot-product of two vectors with given length
 */
int rm_calc_dot_product(unsigned int*, unsigned int*, int);
/*!
 * \brief Count number of elements which are one in a vector with given length
 */
int rm_count_ones_in_vec(unsigned int*, int);
/*!
 * \brief Calculate the number of bits to be encoded
 */
unsigned int rm_calc_num_infobits(int, int, bool);
/*!
 * \brief Calculate the number of integers needed to store a given number of bits
 */
int rm_calc_num_int(int);

//help functions
/*!
 * \brief Change an element in a matrix with given dimensions
 */
void rm_change_matrix_element(unsigned int*, int, int, int, bool);
/*!
 * \brief Add two vectors with given length
 */
void rm_vector_add(unsigned int*, unsigned int*, unsigned int*, int, int, int, int);
/*!
 * \brief Add a negated vector to another vector with given length of both vectors (must be the same length)
 */
void rm_vector_add_neg(unsigned int*, unsigned int*, unsigned int*, int, int, int, int);
/*!
 * \brief XOR-combining of two vectors with given lengths
 */
void rm_vector_xor(unsigned int*, unsigned int*, unsigned int*, int, int, int, int);
/*!
 * \brief Fast-Hadamard-Transformation (Hard-Decision -> no complex values)
 */
void rm_fht(float*, int);
/*!
 * \brief Fast-Hadamard-Transformation (Soft-Decision -> complex values possible)
 */
void rm_fht_sd(std::complex<float>*, int);

//RM Coding functions
/*!
 * \brief Generates the generator-matrix for a Reed-Muller Code
 */
void rm_generate_gen_mat(short, short, unsigned int*, int, int);
/*!
 * \brief Generates the precode-matrix used to select a golay-coset
 */
void rmg_generate_precode_mat(short, unsigned int*, unsigned int, unsigned int);
/*!
 * \brief Reed-Muller Encoder
 */
void rm_encode(unsigned int*, int, int, const unsigned int*, unsigned int*);
/*!
 * \brief Reed-Muller Decoder
 */
void rm_decode(unsigned int*, int, int, int, int, unsigned int*, unsigned int*, unsigned int*, const unsigned int*, int, unsigned int*);
/*!
 * \brief Reed-Muller(-Golay) Encoder
 */
void rmg_encode(unsigned int*, int, int, const unsigned int*, unsigned int*, unsigned int*, int, int, int, unsigned int*, int, int);
/*!
 * \brief Reed-Muller(-Golay) Hard-Decision-Decoder
 */
void rmg_decode(unsigned int*, float*, unsigned int*, unsigned int*, const unsigned int*, unsigned int*, int, int, int, int, int, int, int, int);
/*!
 * \brief Reed-Muller(-Golay) Soft-Decision-Decoder
 */
void rmg_decode_sd(unsigned int*, std::complex<float>*, unsigned int*, unsigned int*, const float*, unsigned int*, int, int, int, int, int, int, int, int);

#endif /* INCLUDED_CHANCODINGI_RM_CODING_H */

