GR_SWIG_BLOCK_MAGIC(chancoding,rmg_decoder_bb);

chancoding_rmg_decoder_bb_sptr chancoding_make_rmg_decoder_bb (int m, int num_bits_precoded);

class chancoding_rmg_decoder_bb : public gr_hier_block2
{
 private:
	chancoding_rmg_decoder_bb (int m, int num_bits_precoded);
};
