GR_SWIG_BLOCK_MAGIC(chancoding,bsc_bb);

chancoding_bsc_bb_sptr chancoding_make_bsc_bb (float ber, unsigned bits_per_byte=1, long seed=3021)
	throw(std::invalid_argument);

class chancoding_bsc_bb : public gr_sync_block
{
private:
	chancoding_bsc_bb (float ber, unsigned bits_per_byte, long seed)
		throw(std::invalid_argument);

 public:
	float ber();
	void set_ber(float ber);
};

