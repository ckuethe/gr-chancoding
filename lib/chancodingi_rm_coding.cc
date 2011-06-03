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


#include <chancodingi_rm_coding.h>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <complex>
#include <cstring>

void rmg_decode_sd(unsigned int* d_gen_mat, std::complex<float>* d_y, unsigned int* d_precode_mat, unsigned int* d_coset, const float* received_values, unsigned int* decoded, int d_num_rows_precode_mat, int d_num_int, int d_num_bits_precoded, int d_num_lin_comb_order_2, int d_num_int_precode_mat, int d_m, int d_num_int_decoded, int d_num_bits)
{
	memset((void *) decoded, 0, d_num_int_decoded * sizeof(int) );

	int bits_per_int = sizeof(d_num_int) * 8;
	int current_int = 0;
	int L = 0;
	std::complex<float> Y = 0;
	int J = 0;

	for(int l = 0; l < d_num_rows_precode_mat; l++)
	{
		// Build d_coset:
		memset((void *) &d_coset[0], 0, d_num_int * sizeof(int) );
	
		current_int = 0;
		for(int a = 0; a < d_num_lin_comb_order_2; a++)
		{
			if(a > 0 && a % bits_per_int == 0)
				current_int++;
			if(d_precode_mat[l * d_num_int_precode_mat + current_int] & (1<<(a-(current_int * bits_per_int))))
				rm_vector_xor(&d_coset[0], &d_gen_mat[0], &d_coset[0], 0, a+d_m+1, 0, d_num_int);
		}	

		current_int = 0;
		for(int a = 0; a < d_num_bits; a++)
		{
			if(a > 0 && a % bits_per_int == 0)
				current_int++;
			if(d_coset[current_int] & (1<<(a-(current_int * bits_per_int))))
				d_y[d_num_bits - a - 1] = received_values[a] + 1;
			if(d_y[d_num_bits - a - 1].real() == 2)
				d_y[d_num_bits - a - 1] = 0;
			if(!(d_coset[current_int] & (1<<(a-(current_int * bits_per_int)))))
				d_y[d_num_bits - a - 1] = received_values[a];
		}

		const std::complex<float> base = -1;
		for(int a = 0; a < d_num_bits; a++)
		{
			d_y[a] = pow(base, d_y[a]);
		}

		rm_fht_sd(&d_y[0], d_m);

		for(int j = 0; j < d_num_bits; j++)
		{
			if(abs(d_y[j]) > abs(Y) )
			{
				Y = d_y[j];
				L = l;
				J = j;
			}
		} 
	}

	// Build decoded Bitstring:
	for(int a = 0; a <= d_m + d_num_bits_precoded; a++)
	{
		if((L & (1<<(d_num_bits_precoded - a - 1))) && (a < d_num_bits_precoded))
			rm_change_matrix_element(decoded, d_num_int_decoded, 0, d_m + d_num_bits_precoded - a, 1);
		if((J & (1<<(a-d_num_bits_precoded))) && (d_num_bits_precoded <= a) && (a < d_m + d_num_bits_precoded))
			rm_change_matrix_element(decoded, d_num_int_decoded, 0, d_m + d_num_bits_precoded - a, 1);
		if((Y.real() < 0) && (a == d_m + d_num_bits_precoded))
			rm_change_matrix_element(decoded, d_num_int_decoded, 0, d_m + d_num_bits_precoded - a, 1);
	}
}

void rmg_decode(unsigned int* d_gen_mat, float* d_y, unsigned int* d_precode_mat, unsigned int* d_coset, const unsigned int* encoded, unsigned int* decoded, int d_num_rows_precode_mat, int d_num_int, int d_num_bits_precoded, int d_num_lin_comb_order_2, int d_num_int_precode_mat, int d_m, int d_num_int_decoded, int d_num_bits)
{
	memset((void *) decoded, 0, d_num_int_decoded * sizeof(int) );

	int bits_per_int = sizeof(d_num_int) * 8;
	int current_int = 0;
	int L = 0;
	float Y = 0;
	int J = 0;

	for(int l = 0; l < d_num_rows_precode_mat; l++)
	{
		// Build d_coset:
		memset((void *) &d_coset[0], 0, d_num_int * sizeof(int) );

		current_int = 0;
		for(int a = 0; a < d_num_lin_comb_order_2; a++)
		{
			if(a > 0 && a % bits_per_int == 0)
				current_int++;
			if(d_precode_mat[l * d_num_int_precode_mat + current_int] & (1<<(a-(current_int * bits_per_int))))
				rm_vector_xor(&d_coset[0], &d_gen_mat[0], &d_coset[0], 0, a+d_m+1, 0, d_num_int);
		}	

		//Build d_y for FHT -> floats
		rm_vector_xor(&d_coset[0], (unsigned int*)encoded, &d_coset[0], 0, 0, 0, d_num_int);
		current_int = 0;
		for(int a = 0; a < d_num_bits; a++)
		{
			if(a > 0 && a % bits_per_int == 0)
				current_int++;
			if(d_coset[current_int] & (1<<(a-(current_int * bits_per_int))))
				d_y[d_num_bits - a - 1] = -0.5;
			if(!(d_coset[current_int] & (1<<(a-(current_int * bits_per_int)))))
				d_y[d_num_bits - a - 1] = 0.5;
		}

		rm_fht(&d_y[0], d_m);

		for(int j = 0; j < d_num_bits; j++)
		{
			if(fabs(d_y[j]) > fabs(Y) )
			{
				Y = d_y[j];
				L = l;
				J = j;
			}
		} 
	}

	// Build decoded Bitstring:
	for(int a = 0; a <= d_m + d_num_bits_precoded; a++)
	{
		if((L & (1<<(d_num_bits_precoded - a - 1))) && (a < d_num_bits_precoded))
			rm_change_matrix_element(decoded, d_num_int_decoded, 0, d_m + d_num_bits_precoded - a, 1);
		if((J & (1<<(a-d_num_bits_precoded))) && (d_num_bits_precoded <= a) && (a < d_m + d_num_bits_precoded))
			rm_change_matrix_element(decoded, d_num_int_decoded, 0, d_m + d_num_bits_precoded - a, 1);
		if((Y < 0) && (a == d_m + d_num_bits_precoded))
			rm_change_matrix_element(decoded, d_num_int_decoded, 0, d_m + d_num_bits_precoded - a, 1);
	}
}

void rmg_encode(unsigned int* d_gen_mat, int d_num_rows, int d_num_int, const unsigned int* uncoded, unsigned int* encoded, unsigned int* d_uncoded_temp, int d_num_bits_precoded, int d_num_lin_comb_order_2, int d_num_int_precode_mat, unsigned int* d_precode_mat, int d_m, int d_num_int_uncoded)
{
	int coset_selector = 0;
	int bits_per_int = sizeof(int) * 8;
	int current_int = 0;
	int bit_in_int = 0;

	for(int a = 0; a < d_num_int_uncoded; a++)
		d_uncoded_temp[a] = uncoded[a];	

	// Take the last "d_num_bits_precoded" from uncoded as decimal number to choose the coset:
	for(int a = d_m + 1; a <= d_m + d_num_bits_precoded; a++)
	{
		current_int = rm_calc_num_int(a) - 1;
		bit_in_int = a % bits_per_int;
		if(d_uncoded_temp[current_int] & (1<<bit_in_int))
		{
			coset_selector += (1<<(a-d_m-1));
		}
	}

	current_int = 0;
	for(int a = 0; a < d_num_lin_comb_order_2; a++)
	{
		if((a > 0) && (a % bits_per_int == 0))
		{
			current_int++;
		}
		if(d_precode_mat[coset_selector * d_num_int_precode_mat + current_int] & (1<<(a-current_int * bits_per_int)))
			rm_change_matrix_element(&d_uncoded_temp[0], d_num_int_uncoded, 0, a+d_m+1, 1);
		else
			rm_change_matrix_element(&d_uncoded_temp[0], d_num_int_uncoded, 0, a+d_m+1, 0);
	}

	rm_encode(&d_gen_mat[0], d_num_rows, d_num_int, &d_uncoded_temp[0],  encoded);
}

void rm_decode(unsigned int* d_gen_mat, int d_num_rows, int d_num_int, int d_m, int d_r, unsigned int* d_zero_columns, unsigned int* d_char_vec, unsigned int* d_order_decoded, const unsigned int* encoded, int d_num_int_decoded, unsigned int* decoded)
{
	int decoded_bit_counter = 0;
	unsigned int i = (1<<d_m);
	unsigned int encoded_temp[d_num_int];
	for(int a = 0; a < d_num_int; a++)
		encoded_temp[a] = encoded[a];

	for(int a = d_r; a >=1; a--)
	{
		for(int b = 0; b < d_m; b++)
		{
			for(unsigned int c=i; c >= 1; c--)
			{
				bool abort = 0;
				int num_ones = 0;
				for(short k = 0; k < d_m; k++)
				{
					if(c & (1<<(d_m-k-1)))
					{
						num_ones++;
					}
				}
				if(num_ones == a)
				{
					for(int d = b+1; d <= d_m-1; d++)
					{
						if(c & (1<<(d_m-d-1)))
							abort = 1;
					}
					if(c & (1<<(d_m-b-1)) && abort == 0)
					{
						int dot_products_sum = 0;
						int num_zeros_row_c = d_m-num_ones;

						int zero_columns_counter = 0;
						for(int g = 0; g < d_m; g++)
						{
							if(!(c & (1<<g)))
							{
								d_zero_columns[zero_columns_counter] = g+1;
								zero_columns_counter++;
							}
						}
						for(int e = 0; e <= ((1<<num_zeros_row_c) -1); e++)
						{
							for(int f = 0; f < d_num_int; f++)
								d_char_vec[f] = d_gen_mat[f];
							for(int f = 0; f < num_zeros_row_c; f++)
							{
								if(e & (1<<f))
								{
									rm_vector_add(&d_char_vec[0], &d_gen_mat[0], &d_char_vec[0], 0, d_zero_columns[f], 0, d_num_int);
								}
								else
									rm_vector_add_neg(&d_char_vec[0], &d_gen_mat[0], &d_char_vec[0], 0, d_zero_columns[f], 0, d_num_int);
							}
							dot_products_sum += rm_calc_dot_product(encoded_temp, &d_char_vec[0], d_num_int);
						}
						if(dot_products_sum > (1<<(num_zeros_row_c - 1)) && num_zeros_row_c > 0)
						{
							rm_change_matrix_element(decoded, d_num_int_decoded, 0, d_num_rows - decoded_bit_counter - 1, 1);
							rm_vector_xor(&d_order_decoded[0], &d_gen_mat[0], &d_order_decoded[0], 0, d_num_rows - decoded_bit_counter - 1, 0, d_num_int);
						}
						decoded_bit_counter++;
					}
				}
			}
		}
		rm_vector_xor((unsigned int*) encoded, &d_order_decoded[0], encoded_temp, 0, 0, 0, d_num_int);
	}
	if(rm_count_ones_in_vec(encoded_temp, d_num_int) > (1<<(d_m-1)))
	{
		rm_change_matrix_element(decoded, d_num_int_decoded, 0, d_num_rows - decoded_bit_counter - 1, 1);
	}
}

void rm_encode(unsigned int* gen_mat, int num_rows, int num_int, const unsigned int* uncoded, unsigned int* encoded)
{
	memset((void *) encoded, 0, num_int * sizeof(int) );

	int bits_per_int = sizeof(num_rows) * 8;
	int current_int = 0;
	for(int a = 0; a < num_rows; a++)
	{
		if(a > 0 && a % bits_per_int == 0)
			current_int++;
		if(uncoded[current_int] & (1<<(a-(current_int * bits_per_int))))
			rm_vector_xor(encoded, gen_mat, encoded, 0, a, 0, num_int);
	}
}

void rm_fht_sd(std::complex<float>* y, int m)
{
	for(int a = m-1; a >= 0; a--)
	{
		for(int b = 0; b < (1<<m); b += (1<<(a+1)))
		{
			for(int c = 0; c < (1<<a); c++)
			{
				std::complex<float> tmp = y[b + c];
				y[b + c] += y[b + c + (1<<a)];
				y[b + c + (1<<a)] = tmp - y[b + c + (1<<a)];
			}
		}
	}
}

void rm_fht(float* y, int m)
{
	for(int a = m-1; a >= 0; a--)
	{
		for(int b = 0; b < (1<<m); b += (1<<(a+1)))
		{
			for(int c = 0; c < (1<<a); c++)
			{
				float tmp = y[b + c];
				y[b + c] += y[b + c + (1<<a)];
				y[b + c + (1<<a)] = tmp - y[b + c + (1<<a)];
			}
		}
	}
}

unsigned int rm_calc_num_bits_precoded(int m)
{
	unsigned int num_rows_precode_mat = 0;
	unsigned long factorial = 1;
	int num_bits_precoded = 0;
	for(int a = 3; a <=m; a++)
		factorial *= a; //Will be a problem for big m (datatype overflow)

	for(int a = 0; num_rows_precode_mat <= factorial; a++)
	{
		num_rows_precode_mat = (1<<a);
		num_bits_precoded = a-1;
	}

	return num_bits_precoded;
}

void rmg_generate_precode_mat(short m, unsigned int* precode_mat, unsigned int num_rows_precode_mat, unsigned int num_int_precode_mat)
{
	memset((void *) precode_mat, 0, num_int_precode_mat * num_rows_precode_mat * sizeof(int) );
	int permutation[m];
	memset((void *) permutation, 0, m * sizeof(int) );
	for(int a = 0; a < m; a++)
		permutation[a] = a+1;
	
	for(unsigned int a = 0; a < num_rows_precode_mat; a++)
	{
		//The last element must be bigger than the first one
		while(permutation[m-1] <= permutation[0])
			std::next_permutation(permutation, permutation+m);

		//Pass through the patterns of linear combinations and compare it with the current permutation
		int counter = 0;
		for(int b = 1; b <= m; b++)
		{
			for(int c = b+1; c <= m; c++)
			{
				//Search for the pattern b,c in current permutation, if it exists -> 1
				for(int d = 0; d < (m-1); d++)
				{
					if(permutation[d] == b || permutation[d] == c)
					{
						if(permutation[d+1] == b || permutation[d+1] == c)
							rm_change_matrix_element(precode_mat, num_int_precode_mat, a, counter, 1);
					}
				}
				counter++;
			}
		}

		std::next_permutation(permutation, permutation+m);
	}
}

int rm_calc_dot_product(unsigned int* vec1, unsigned int* vec2, int num_int)
{
	int dot_product = 0;

	rm_vector_add(vec1, vec2, vec2, 0, 0, 0, num_int);
	dot_product = rm_count_ones_in_vec(vec2, num_int) % 2;

	return dot_product;
}

int rm_count_ones_in_vec(unsigned int* vec, int num_int)
{
	int bits_per_int = sizeof(num_int) * 8;
	int num_ones = 0;

	for(int a = 0; a < num_int; a++)
	{
		for(int b = 0; b < bits_per_int; b++)
		{
			if(vec[a] & (1<<b))
				num_ones++;
		}
	}

	return num_ones;
}

void rm_generate_gen_mat(short r, short m, unsigned int* gen_mat, int num_rows, int num_int)
{
	memset((void *) gen_mat, 0, num_int * num_rows * sizeof(int) );
	unsigned int i = 1;
	i = (1<<m);

	//Build monoms (order r=1)

	if(r >=1)
	{
		for(int a = 0; a <= ((1<<m) - 1); a++)
			rm_change_matrix_element(gen_mat, num_int, 0, a, 1);
		for(int a = 1; a <= m; a++)
		{
			for(int b = 1; b <= (1<<a); b++)
			{
				for(int c = 1; c <= (1<<(m-a)); c++)
				{
					if(b % 2 != 0)
						rm_change_matrix_element(gen_mat, num_int, a, ((b-1) * (1<<(m-a)) + c-1), 1);
				}
			}
		}
	}	

	//Set all rows after the monoms to 1 (prepare for linear combinations)
	for(int a = m+1; a < num_rows; a++)
		for(int b = 0; b < num_int; b++)
			gen_mat[a * num_int + b] = gen_mat[0];

	//rearrange so that the orders are together at the right place
	int gen_mat_row_counter = 0;
	for(int a = 2; a <= r; a++)
	{
		for(int b = m-1; b >= 0; b--)
		{	
			for(unsigned int c=1; c <= i; c++)
			{
				bool abort = 0;
				int num_ones = 0;
				for(short k = 0; k < m; k++)
				{
					if(c & (1<<(m-k-1)))
					{
						num_ones++;
					}
				}
				if(num_ones == a)
				{
					for(int d = b+1; d <= m-1; d++)
					{
						if(c & (1<<(m-d-1)))
							abort = 1;
					}
					if(c & (1<<(m-b-1)) && abort == 0)
					{
						for(int e = 0; e < m; e++)
						{
							if(c & (1<<(m-e-1)))
								rm_vector_add(gen_mat, gen_mat, gen_mat, m+1+gen_mat_row_counter, m-e, m+1+gen_mat_row_counter, num_int);
						}
						gen_mat_row_counter++;
					}
				}
			}
		}
	}			
}

void rm_change_matrix_element(unsigned int* matrix, int num_int, int row, int column, bool value)
{
	//in which integer is the element?
	int bits_per_int = sizeof(num_int) * 8;
	int current_integer = column / bits_per_int; //results directly to the integer

	//Bit in current integer
	int element_in_int =  column % bits_per_int;

	//Insert the value
	if(!(matrix[row * num_int + current_integer] & (1<<element_in_int)) && value == 1)
		matrix[row * num_int + current_integer] += (1<<element_in_int);

	if((matrix[row * num_int + current_integer] & (1<<element_in_int)) && value == 0)
		matrix[row * num_int + current_integer] -= (1<<element_in_int);
}

int rm_calc_rows(int r, int m)
{
	int num_rows = 1;

	for(int k = 1; k <=r; k++)
	{
		num_rows += rm_binom_coeff(m,k);
	}

	return num_rows;
}

unsigned long long rm_gcd (unsigned long long a, unsigned long long b) 
{
	unsigned long long tmp;

	while (b)
	{
		tmp = a;
		a = b;
		b = tmp % b;
	}

	return a;
}

int rm_binom_coeff(int m, int r)
{
	unsigned long long n = m;
	unsigned long long k = r;
	unsigned long long fac,tmp;
	unsigned long long res = 1;
	if(k > (n-k))
		k = n-k;
	for (unsigned long long a=1; a<=k; a++)
	{     
		fac = n-a+1;
		tmp = rm_gcd(fac, a);
		res /= a/tmp;
		res *= fac/tmp;
	}

	return res;
}

void rm_vector_add(unsigned int* matrix1, unsigned int* matrix2, unsigned int* result_matrix, int row1, int row2, int result_row, int num_int)
{
	for(int a = 0; a < num_int; a++)
	{
		result_matrix[result_row * num_int + a] = matrix1[row1 * num_int + a] & matrix2[row2 * num_int + a];
	}
}

void rm_vector_add_neg(unsigned int* matrix1, unsigned int* matrix2, unsigned int* result_matrix, int row1, int row2, int result_row, int num_int)
{
	for(int a = 0; a < num_int; a++)
	{
		result_matrix[result_row * num_int + a] = matrix1[row1 * num_int + a] & ~matrix2[row2 * num_int + a];
	}
}

void rm_vector_xor(unsigned int* matrix1, unsigned int* matrix2, unsigned int* result_matrix, int row1, int row2, int result_row, int num_int)
{
	for(int a = 0; a < num_int; a++)
	{
		result_matrix[result_row * num_int + a] = matrix1[row1 * num_int + a] ^ matrix2[row2 * num_int + a];
	}
}

unsigned int rm_calc_num_infobits(int r, int m, bool golay)
{
	unsigned int num_infobits;

	if(!golay)
		num_infobits = rm_calc_rows(r, m);
	else
		num_infobits = 1 + m + rm_calc_num_bits_precoded(m);

	return num_infobits;
}

int rm_calc_num_int(int num_bits)
{
	int bits_per_int = sizeof(num_bits) * 8;
	int modulo_helper = 0;

	if(num_bits % bits_per_int != 0)
		modulo_helper = bits_per_int - num_bits % bits_per_int;
	int num_int = (num_bits + modulo_helper) / bits_per_int;

	return num_int;
}
