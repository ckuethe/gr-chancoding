#!/usr/bin/env python
#
# Copyright 2011 Communications Engineering Lab, KIT
# 
# This file is part of GNU Radio
# 
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

from gnuradio import gr, gr_unittest
import chancoding_swig as chancoding


class qa_unpack_bits (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_pack4bits (self):
        """ Check packing 1 vector from 4 Bits """

	src_data = 	(1,0,1,0)
	expected_data = (5,)
        src1 = gr.vector_source_b(src_data)
        pack_bits = chancoding.unpacked_to_packed_bvi(4)
        sink = gr.vector_sink_i()

        self.tb.connect(src1, pack_bits)
        self.tb.connect(pack_bits, sink)
        self.tb.run()

        self.assertEqual( sink.data() , expected_data)

    def test_002_pack4bits_6_elements_input (self):
        """ Check packing 4 Bits when an 6 Bits are available """

	src_data = 	(1,0,0,1,1,0)
	expected_data = (9,)
        src1 = gr.vector_source_b(src_data)
        pack_bits = chancoding.unpacked_to_packed_bvi(4)
        sink = gr.vector_sink_i()

        self.tb.connect(src1, pack_bits)
        self.tb.connect(pack_bits, sink)
        self.tb.run()

        self.assertEqual( sink.data() , expected_data)

    def test_003_pack8bits_non_zero (self):
        """ Check that only the first 8 bits are used to build the int """

	src_data = 	(1,0,1,1,0,0,0,0,1,0,0,1,0,0,0)
	expected_data = (13,)
        src1 = gr.vector_source_b(src_data)
        pack_bits = chancoding.unpacked_to_packed_bvi(8)
        sink = gr.vector_sink_i()

        self.tb.connect(src1, pack_bits)
        self.tb.connect(pack_bits, sink)
        self.tb.run()

        self.assertEqual( sink.data() , expected_data)

    def test_004_pack8bits (self):
        """ Check packing 8 bits multiple times """

	src_data = 	(1,0,0,0,0,0,0,0,
			 1,1,0,0,0,0,0,0,
			 0,0,1,0,0,0,0,0,
			 0,0,0,0,0,0,0,0,
			 1,0,0,1,0,0,0,0,
			 0,0,0,0,0,1,0,0,
			 1,1,0,1,0,1,0,0,
			 1,1,1,1,1,1,1,1)
	expected_data = (1,3,4,0,9,32,43,255)
        src1 = gr.vector_source_b(src_data)
        pack_bits = chancoding.unpacked_to_packed_bvi(8)
        sink = gr.vector_sink_i()

        self.tb.connect(src1, pack_bits)
        self.tb.connect(pack_bits, sink)
        self.tb.run()

	for i in range( len(expected_data) ):
        	self.assertEqual( sink.data()[i] , expected_data[i], i)


    def test_005_pack32bits (self):
        """ Check packing 32 bits with an input of 64 bits """

	src_data = 	(1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
	expected_data = (1,1)
        src1 = gr.vector_source_b(src_data)
        pack_bits = chancoding.unpacked_to_packed_bvi(32)
        sink = gr.vector_sink_i()

        self.tb.connect(src1, pack_bits)
        self.tb.connect(pack_bits, sink)
        self.tb.run()

	for i in range( len(expected_data) ):
        	self.assertEqual( sink.data()[i] , expected_data[i], i)

    def test_006_pack33bits (self):
        """ Check packing 33 bits two times """

	src_data = 	(1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1)
	expected_data = (3,1,3,1)
        src1 = gr.vector_source_b(src_data)
        pack_bits = chancoding.unpacked_to_packed_bvi(33)
        sink = gr.vector_sink_i(2)

        self.tb.connect(src1, pack_bits)
        self.tb.connect(pack_bits, sink)
        self.tb.run()

	for i in range( len(expected_data) ):
        	self.assertEqual( sink.data()[i] , expected_data[i], i)

    def test_007_pack64bits (self):
        """ Check packing 64 bits two times """

	src_data = 	(1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
	expected_data = (1,5,2,10)
        src1 = gr.vector_source_b(src_data)
        pack_bits = chancoding.unpacked_to_packed_bvi(64)
        sink = gr.vector_sink_i(2)

        self.tb.connect(src1, pack_bits)
        self.tb.connect(pack_bits, sink)
        self.tb.run()

	for i in range( len(expected_data) ):
        	self.assertEqual( sink.data()[i] , expected_data[i], i)

    def test_008_pack65bits (self):
        """ Check packing 65 bits two times """

	src_data = 	(1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
	expected_data = (1,5,1,2,10,0)
        src1 = gr.vector_source_b(src_data)
        pack_bits = chancoding.unpacked_to_packed_bvi(65)
        sink = gr.vector_sink_i(3)

        self.tb.connect(src1, pack_bits)
        self.tb.connect(pack_bits, sink)
        self.tb.run()

	for i in range( len(expected_data) ):
        	self.assertEqual( sink.data()[i] , expected_data[i], i)

#    def test_009_packing_unpacking_random1000 (self):
#        """ Check packing 32 bits randomly created 1000 times """

#	src_data = 	(1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
#			 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
#	expected_data = (1,5,2,10)
#       src1 = gr.glfsr_source_b(int degree, 0, int mask, int seed)
#        pack_bits = chancoding.unpacked_to_packed_bvi(32)
#        sink = gr.vector_sink_i()

#        self.tb.connect(src1, pack_bits)
#        self.tb.connect(pack_bits, sink)
#        self.tb.run()

#	for i in range( len(expected_data) ):
#       	self.assertEqual(int( sink.data()[i] ), expected_data[i], i)


if __name__ == '__main__':
    gr_unittest.main ()
