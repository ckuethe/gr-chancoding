GR_SWIG_BLOCK_MAGIC(chancoding,blockdeinterleaver_bb);

chancoding_blockdeinterleaver_bb_sptr
chancoding_make_blockdeinterleaver_bb (unsigned n_rows, unsigned n_cols, unsigned bits_per_byte=1)
	throw(std::invalid_argument);

chancoding_blockdeinterleaver_bb_sptr
chancoding_make_blockdeinterleaver_bb (chancoding_blockinterleaver_bb_sptr interleaver);

class chancoding_blockdeinterleaver_bb : public gr_hier_block2
{
 private:
	chancoding_blockdeinterleaver_bb (unsigned n_rows, unsigned n_cols, unsigned bits_per_byte)
		throw(std::invalid_argument);

 public:
	unsigned n_rows() { return d_n_rows; };
	unsigned n_cols() { return d_n_cols; };
	unsigned bits_per_byte() { return d_bits_per_byte; };
};

