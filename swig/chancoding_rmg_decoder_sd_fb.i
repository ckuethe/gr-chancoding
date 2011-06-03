GR_SWIG_BLOCK_MAGIC(chancoding,rmg_decoder_sd_fb);

chancoding_rmg_decoder_sd_fb_sptr chancoding_make_rmg_decoder_sd_fb (int m, int num_bits_precoded);

class chancoding_rmg_decoder_sd_fb : public gr_hier_block2
{
 private:
	chancoding_rmg_decoder_sd_fb (int m, int num_bits_precoded);
};
