GR_SWIG_BLOCK_MAGIC(chancoding,rm_decoder_vii);

chancoding_rm_decoder_vii_sptr chancoding_make_rm_decoder_vii (int r, int m);

class chancoding_rm_decoder_vii : public gr_sync_block
{
 private:
	chancoding_rm_decoder_vii (int r, int m);
 public:
	int get_vlen_in();
	int get_vlen_out();
	int get_num_bits_in();
	int get_num_bits_out();
};
