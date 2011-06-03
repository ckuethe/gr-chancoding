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
#include <qa_chancodingi_rm_coding.h>
#include <chancodingi_rm_coding.h>
#include <complex>

void
qa_chancodingi_rm_coding::t1()
{
	int num_bits = 33;
	int num_int = rm_calc_num_int(num_bits);

	CPPUNIT_ASSERT_EQUAL(num_int, 2);
}

void
qa_chancodingi_rm_coding::t2()
{
	int r = 4;
	int m = 7;
	int num_infobits = rm_calc_num_infobits(r,m,0);

	CPPUNIT_ASSERT_EQUAL(num_infobits, 99);
}

void
qa_chancodingi_rm_coding::t3()
{
	unsigned int* matrix1 = new unsigned int[2];
	matrix1[0] = 231;
	matrix1[1] = 5732;
	unsigned int* matrix2 = new unsigned int[2];
	matrix2[0] = 73;
	matrix2[1] = 2294;
	unsigned int* result_matrix = new unsigned int[2];
	int row1 = 0;
	int row2 = 0;
	int result_row = 0;
	int num_int = 2;
	unsigned int* expected_result_matrix = new unsigned int[2];
	expected_result_matrix[0] = 174;
	expected_result_matrix[1] = 7826;

	rm_vector_xor(matrix1, matrix2, result_matrix, row1, row2, result_row, num_int);

	for(int i = 0; i < num_int; i++)
		CPPUNIT_ASSERT_EQUAL(result_matrix[i], expected_result_matrix[i]);
}

void
qa_chancodingi_rm_coding::t4()
{
	unsigned int* matrix1 = new unsigned int[2];
	matrix1[0] = 231;
	matrix1[1] = 5732;
	unsigned int* matrix2 = new unsigned int[2];
	matrix2[0] = 73;
	matrix2[1] = 2294;
	unsigned int* result_matrix = new unsigned int[2];
	int row1 = 0;
	int row2 = 0;
	int result_row = 0;
	int num_int = 2;
	unsigned int* expected_result_matrix = new unsigned int[2];
	expected_result_matrix[0] = 166;
	expected_result_matrix[1] = 5632;

	rm_vector_add_neg(matrix1, matrix2, result_matrix, row1, row2, result_row, num_int);

	for(int i = 0; i < num_int; i++)
		CPPUNIT_ASSERT_EQUAL(result_matrix[i], expected_result_matrix[i]);
}

void
qa_chancodingi_rm_coding::t5()
{
	unsigned int* matrix1 = new unsigned int[2];
	matrix1[0] = 231;
	matrix1[1] = 5732;
	unsigned int* matrix2 = new unsigned int[2];
	matrix2[0] = 73;
	matrix2[1] = 2294;
	unsigned int* result_matrix = new unsigned int[2];
	int row1 = 0;
	int row2 = 0;
	int result_row = 0;
	int num_int = 2;
	unsigned int* expected_result_matrix = new unsigned int[2];
	expected_result_matrix[0] = 65;
	expected_result_matrix[1] = 100;

	rm_vector_add(matrix1, matrix2, result_matrix, row1, row2, result_row, num_int);

	for(int i = 0; i < num_int; i++)
		CPPUNIT_ASSERT_EQUAL(result_matrix[i], expected_result_matrix[i]);
}

void
qa_chancodingi_rm_coding::t6()
{
	int m = 29;
	int r = 19;

	int binom_coeff = rm_binom_coeff(m, r);

	CPPUNIT_ASSERT_EQUAL(binom_coeff, 20030010);
}

void
qa_chancodingi_rm_coding::t7()
{
	unsigned long long a = 384181;
	unsigned long long b = 2582957125;

	unsigned long long gcd = rm_gcd(a, b);
	unsigned long long expected_gcd = 7;

	CPPUNIT_ASSERT_EQUAL(gcd, expected_gcd);
}

void
qa_chancodingi_rm_coding::t8()
{
	int m = 13;
	int r = 5;

	int rows = rm_calc_rows(r,m);

	CPPUNIT_ASSERT_EQUAL(rows, 2380);
}

void
qa_chancodingi_rm_coding::t9()
{
	unsigned int* matrix = new unsigned int[4];
	matrix[0] = 0;
	matrix[1] = 0;
	matrix[2] = 0;
	matrix[3] = 5;
	int num_int = 2;
	int row = 1;
	int column = 33;
	bool value = true;

	rm_change_matrix_element(matrix, num_int, row, column, value);
	unsigned int* expected_matrix = new unsigned int[4];
	expected_matrix[0] = 0;
	expected_matrix[1] = 0;
	expected_matrix[2] = 0;
	expected_matrix[3] = 7;

	for(int i = 0; i < 4; i++)
		CPPUNIT_ASSERT_EQUAL(matrix[i], expected_matrix[i]);
}

void
qa_chancodingi_rm_coding::t10()
{
	short r = 3;
	short m = 3;
	unsigned int* gen_mat = new unsigned int[8];
	int num_rows = 8;
	int num_int = 1;

	rm_generate_gen_mat(r, m, gen_mat, num_rows, num_int);
	unsigned int* gen_mat_expected = new unsigned int[8];
	gen_mat_expected[0] = 255;
	gen_mat_expected[1] = 15;
	gen_mat_expected[2] = 51;
	gen_mat_expected[3] = 85;
	gen_mat_expected[4] = 3;
	gen_mat_expected[5] = 5;
	gen_mat_expected[6] = 17;
	gen_mat_expected[7] = 1;

	for(int i = 0; i < 8; i++)
		CPPUNIT_ASSERT_EQUAL(gen_mat[i], gen_mat_expected[i]);
}

void
qa_chancodingi_rm_coding::t11()
{
	unsigned int* vec = new unsigned int[2];
	vec[0] = 423;
	vec[1] = 3281948;
	int num_int = 2;

	int num_ones = rm_count_ones_in_vec(vec, num_int);

	CPPUNIT_ASSERT_EQUAL(num_ones, 14);
}

void
qa_chancodingi_rm_coding::t12()
{
	unsigned int* vec1 = new unsigned int[2];
	vec1[0] = 231;
	vec1[1] = 5732;
	unsigned int* vec2 = new unsigned int[2];
	vec2[0] = 5897;
	vec2[1] = 182;
	int num_int = 2;

	int dot_product = rm_calc_dot_product(vec1, vec2, num_int);

	CPPUNIT_ASSERT_EQUAL(dot_product, 1);
}

void
qa_chancodingi_rm_coding::t13()
{
	short m = 4;
	unsigned int* precode_mat = new unsigned int[8];
	int num_rows_precode_mat = 8;
	int num_int_precode_mat = 1;

	rmg_generate_precode_mat(m, precode_mat, num_rows_precode_mat, num_int_precode_mat);
	unsigned int* precode_mat_expected = new unsigned int[8];
	precode_mat_expected[0] = 41;
	precode_mat_expected[1] = 49;
	precode_mat_expected[2] = 26;
	precode_mat_expected[3] = 50;
	precode_mat_expected[4] = 28;
	precode_mat_expected[5] = 44;
	precode_mat_expected[6] = 35;
	precode_mat_expected[7] = 37;

	for(int i = 0; i < 8; i++)
		CPPUNIT_ASSERT_EQUAL(precode_mat[i], precode_mat_expected[i]);
}

void
qa_chancodingi_rm_coding::t14()
{
	int m = 12;

	int num_bits_precoded = rm_calc_num_bits_precoded(m);

	CPPUNIT_ASSERT_EQUAL(num_bits_precoded, 27);
}

void
qa_chancodingi_rm_coding::t15()
{
	int m = 3;
	float* y = new float[8];
	y[0] = 4;
	y[1] = 3;
	y[2] = 43;
	y[3] = 53;
	y[4] = 0;
	y[5] = 4;
	y[6] = 19;
	y[7] = 92;

	rm_fht(y, m);
	float* y_expected = new float[8];
	y_expected[0] = 27.25*8;
	y_expected[1] = -10.75*8;
	y_expected[2] = -24.5*8;
	y_expected[3] = 10.0*8;
	y_expected[4] = -1.5*8;
	y_expected[5] = 8.5*8;
	y_expected[6] = 2.25*8;
	y_expected[7] = -7.25*8;

	for(int i = 0; i < 8; i++)
		CPPUNIT_ASSERT_EQUAL(y[i], y_expected[i]);
}

void
qa_chancodingi_rm_coding::t16()
{
	int m = 3;
	std::complex<float>* y = new std::complex<float>[8];
	y[0] = std::complex<float>(1.0,2.0);
	y[1] = std::complex<float>(0.0,3.0);
	y[2] = std::complex<float>(4.0,0.0);
	y[3] = std::complex<float>(6.0,0.0);
	y[4] = std::complex<float>(32.0,0.0);
	y[5] = std::complex<float>(53.0,53.0);
	y[6] = std::complex<float>(0.0,53.0);
	y[7] = std::complex<float>(14.0,-5.0);

	rm_fht_sd(y, m);
	std::complex<float>* y_expected = new std::complex<float>[8];
	y_expected[0] = std::complex<float>(13.75*8, 13.25*8);
	y_expected[1] = std::complex<float>(-4.5*8, 0.5*8);
	y_expected[2] = std::complex<float>(7.75*8, 1.25*8);
	y_expected[3] = std::complex<float>(-0.5*8, -14.0*8);
	y_expected[4] = std::complex<float>(-11.0*8, -12.0*8);
	y_expected[5] = std::complex<float>(4.25*8, -0.75*8);
	y_expected[6] = std::complex<float>(-10.0*8, 0.0);
	y_expected[7] = std::complex<float>(1.25*8, 13.75*8);

	for(int i = 0; i < 8; i++)
		CPPUNIT_ASSERT_EQUAL(y[i], y_expected[i]);
}

void
qa_chancodingi_rm_coding::t17()
{
	short r = 4;
	short m = 6;
	unsigned int* gen_mat = new unsigned int[114];
	int num_rows = 57;
	int num_int = 2;
	unsigned int* encoded = new unsigned int[2];
	unsigned int* uncoded = new unsigned int[2];
	uncoded[0] = 152;
	uncoded[1] = 231;

	unsigned int* encoded_expected = new unsigned int[57];
	encoded_expected[0] = 267837991;
	encoded_expected[1] = 267787736;
	rm_generate_gen_mat(r, m, gen_mat, num_rows, num_int);

	rm_encode(gen_mat, num_rows, num_int, uncoded, encoded);

	for(int i = 0; i < 2; i++)
		CPPUNIT_ASSERT_EQUAL(encoded[i], encoded_expected[i]);
}
