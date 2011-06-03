GR_SWIG_BLOCK_MAGIC(chancoding,unpacked_to_packed_bvi);

chancoding_unpacked_to_packed_bvi_sptr chancoding_make_unpacked_to_packed_bvi (int bits_per_vector);

class chancoding_unpacked_to_packed_bvi : public gr_sync_decimator
{
 private:
	chancoding_unpacked_to_packed_bvi (int bits_per_vector);
};
