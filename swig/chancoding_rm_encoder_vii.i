GR_SWIG_BLOCK_MAGIC(chancoding,rm_encoder_vii);

chancoding_rm_encoder_vii_sptr chancoding_make_rm_encoder_vii (int r, int m);

class chancoding_rm_encoder_vii : public gr_sync_block
{
 private:
	chancoding_rm_encoder_vii (int r, int m);
 public:
	int get_vlen_in();
	int get_vlen_out();
	int get_num_bits_in();
	int get_num_bits_out();
};
