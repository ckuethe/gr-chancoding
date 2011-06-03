GR_SWIG_BLOCK_MAGIC(chancoding,industrystd_encoder_bb);

chancoding_industrystd_encoder_bb_sptr
chancoding_make_industrystd_encoder_bb (unsigned bits_per_input_byte=1, unsigned bits_per_output_byte=1, int ST=0);

class chancoding_industrystd_encoder_bb : public gr_hier_block2
{
	fsm FSM() const;
	int ST() const;

 private:
	chancoding_industrystd_encoder_bb (unsigned bits_per_input_byte, unsigned bits_per_output_byte, int ST);
};

