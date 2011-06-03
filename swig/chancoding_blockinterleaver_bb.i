GR_SWIG_BLOCK_MAGIC(chancoding,blockinterleaver_bb);

chancoding_blockinterleaver_bb_sptr
chancoding_make_blockinterleaver_bb(
		unsigned n_rows,
		unsigned n_cols,
		unsigned bits_per_byte=1)
	throw(std::invalid_argument);

class chancoding_blockinterleaver_bb : public gr_hier_block2
{
 private:
	chancoding_blockinterleaver_bb(unsigned n_rows, unsigned n_cols, unsigned bits_per_byte)
		throw(std::invalid_argument);

 public:
	unsigned n_rows();
	unsigned n_cols();
	unsigned bits_per_byte();
};

