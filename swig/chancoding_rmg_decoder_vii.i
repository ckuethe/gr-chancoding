GR_SWIG_BLOCK_MAGIC(chancoding,rmg_decoder_vii);

chancoding_rmg_decoder_vii_sptr chancoding_make_rmg_decoder_vii (int m, int num_bits_precoded);

class chancoding_rmg_decoder_vii : public gr_sync_block
{
 private:
	chancoding_rmg_decoder_vii (int m, int num_bits_precoded);
 public:
	int get_vlen_in();
	int get_vlen_out();
	int get_num_bits_in();
	int get_num_bits_out();
};
