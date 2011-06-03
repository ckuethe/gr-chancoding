GR_SWIG_BLOCK_MAGIC(chancoding,packed_to_unpacked_vib);

chancoding_packed_to_unpacked_vib_sptr chancoding_make_packed_to_unpacked_vib (int bits_per_vector);

class chancoding_packed_to_unpacked_vib : public gr_sync_interpolator
{
 private:
	chancoding_packed_to_unpacked_vib (int bits_per_vector);
};
