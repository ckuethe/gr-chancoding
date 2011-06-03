GR_SWIG_BLOCK_MAGIC(chancoding,ber_b);

chancoding_ber_b_sptr chancoding_make_ber_b (int bits_per_byte=1);

class chancoding_ber_b : public gr_sync_block
{
 private:
	chancoding_ber_b (int bits_per_byte);

 public:
	~chancoding_ber_b ();

	float ber();
	long bit_errors();
};

