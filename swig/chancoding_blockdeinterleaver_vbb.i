GR_SWIG_BLOCK_MAGIC(chancoding,blockdeinterleaver_vbb);

chancoding_blockdeinterleaver_vbb_sptr
chancoding_make_blockdeinterleaver_vbb(unsigned n_rows, unsigned n_cols, unsigned bits_per_byte=1)
	throw(std::invalid_argument);

class chancoding_blockdeinterleaver_vbb : public gr_sync_block
{
 private:
	chancoding_blockdeinterleaver_vbb (unsigned n_rows, unsigned n_cols, unsigned bits_per_byte)
		throw(std::invalid_argument);
};

