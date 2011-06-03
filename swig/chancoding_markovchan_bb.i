GR_SWIG_BLOCK_MAGIC(chancoding, markovchan_bb);

chancoding_markovchan_bb_sptr chancoding_make_markovchan_bb (std::vector<double> ber, std::vector<double> trans_matrix, unsigned bits_per_byte=1, unsigned init_state=0, long seed=3021)
	throw(std::invalid_argument);

class chancoding_markovchan_bb : public gr_sync_block
{
 public:
	double ber(int state);
	std::vector<double> ber();
	std::vector<double> transition_matrix();
	int n_states();
	void set_state(int state)
		throw(std::invalid_argument);
	void set_ber(std::vector<double> ber)
		throw(std::invalid_argument);

 private:
	chancoding_markovchan_bb (std::vector<double> ber, std::vector<double> trans_matrix, unsigned bits_per_byte, unsigned init_state, long seed)
		throw(std::invalid_argument);
};

