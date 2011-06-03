GR_SWIG_BLOCK_MAGIC(chancoding,blockinterleaver_vbb);

chancoding_blockinterleaver_vbb_sptr
chancoding_make_blockinterleaver_vbb (int n_rows, int n_cols, unsigned bits_per_byte=1)
	throw(std::invalid_argument);

class chancoding_blockinterleaver_vbb : public gr_sync_block
{
 private:
	chancoding_blockinterleaver_vbb (int n_rows, int n_cols, unsigned bits_per_byte)
		throw(std::invalid_argument);
};

