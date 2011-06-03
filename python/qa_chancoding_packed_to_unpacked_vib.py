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

class qa_packed_to_unpacked_vib (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_pack4bits (self):
        """ Check unpacking 4 Bits """

	expected_data = (1,0,1,0)
	src_data = (5,)
        src1 = gr.vector_source_i(src_data,0,1)
        pack_bits = chancoding.packed_to_unpacked_vib(4)
        sink = gr.vector_sink_b()

        self.tb.connect(src1, pack_bits)
        self.tb.connect(pack_bits, sink)
        self.tb.run()

	for i in range( len(expected_data) ):
        	self.assertEqual( sink.data()[i] , expected_data[i], i)

    def test_002_pack4bits_6_elements_input (self):
        """ Check unpacking 4 Bits """

	expected_data = (1,0,0,1)
	src_data = (9,)
        src1 = gr.vector_source_i(src_data,0,1)
        pack_bits = chancoding.packed_to_unpacked_vib(4)
        sink = gr.vector_sink_b()

        self.tb.connect(src1, pack_bits)
        self.tb.connect(pack_bits, sink)
        self.tb.run()

	for i in range( len(expected_data) ):
        	self.assertEqual( sink.data()[i] , expected_data[i], i)

    def test_003_pack8bits_non_zero (self):
        """ Check unpacking 8 bits one time """

	expected_data = (1,0,1,1,0,0,0,0)
	src_data = (13,)
        src1 = gr.vector_source_i(src_data,0,1)
        pack_bits = chancoding.packed_to_unpacked_vib(8)
        sink = gr.vector_sink_b()

        self.tb.connect(src1, pack_bits)
        self.tb.connect(pack_bits, sink)
        self.tb.run()

	for i in range( len(expected_data) ):
        	self.assertEqual( sink.data()[i] , expected_data[i], i)

    def test_004_pack8bits (self):
        """ Check unpacking 8 bits multiple times """

	expected_data = (1,0,0,0,0,0,0,0,
			 1,1,0,0,0,0,0,0,
			 0,0,1,0,0,0,0,0,
			 0,0,0,0,0,0,0,0,
			 1,0,0,1,0,0,0,0,
			 0,0,0,0,0,1,0,0,
			 1,1,0,1,0,1,0,0,
			 1,1,1,1,1,1,1,1)
	src_data = (1,3,4,0,9,32,43,255)
        src1 = gr.vector_source_i(src_data,0,1)
        pack_bits = chancoding.packed_to_unpacked_vib(8)
        sink = gr.vector_sink_b()

        self.tb.connect(src1, pack_bits)
        self.tb.connect(pack_bits, sink)
        self.tb.run()

	for i in range( len(expected_data) ):
        	self.assertEqual( sink.data()[i] , expected_data[i], i)


    def test_005_pack32bits (self):
        """ Check unpacking 32 bits with an input of 2 int """

	expected_data = (1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
	src_data = (1,1)
        src1 = gr.vector_source_i(src_data,0,1)
        pack_bits = chancoding.packed_to_unpacked_vib(32)
        sink = gr.vector_sink_b()

        self.tb.connect(src1, pack_bits)
        self.tb.connect(pack_bits, sink)
        self.tb.run()

	for i in range( len(expected_data) ):
        	self.assertEqual( sink.data()[i] , expected_data[i], i)

    def test_006_pack33bits (self):
        """ Check unpacking 33 bits two times """

	expected_data = (1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1)
	src_data = (3,1,3,1)
        src1 = gr.vector_source_i(src_data,0,2)
        pack_bits = chancoding.packed_to_unpacked_vib(33)
        sink = gr.vector_sink_b()

        self.tb.connect(src1, pack_bits)
        self.tb.connect(pack_bits, sink)
        self.tb.run()

	for i in range( len(expected_data) ):
        	self.assertEqual( sink.data()[i] , expected_data[i], i)

    def test_007_pack64bits (self):
        """ Check unpacking 64 bits two times """

	expected_data = (1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
	src_data = (1,5,2,10)
        src1 = gr.vector_source_i(src_data,0,2)
        pack_bits = chancoding.packed_to_unpacked_vib(64)
        sink = gr.vector_sink_b()

        self.tb.connect(src1, pack_bits)
        self.tb.connect(pack_bits, sink)
        self.tb.run()

	for i in range( len(expected_data) ):
        	self.assertEqual( sink.data()[i] , expected_data[i], i)

    def test_008_pack65bits (self):
        """ Check unpacking 65 bits two times """

	expected_data = (1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			 0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0)
	src_data = (1,5,1,2,10,0)
        src1 = gr.vector_source_i(src_data,0,3)
        pack_bits = chancoding.packed_to_unpacked_vib(65)
        sink = gr.vector_sink_b()

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
#        pack_bits = chancoding.packed_to_unpacked_vib(32)
#        sink = gr.vector_sink_i()

#        self.tb.connect(src1, pack_bits)
#        self.tb.connect(pack_bits, sink)
#        self.tb.run()

#	for i in range( len(expected_data) ):
#       	self.assertEqual(int( sink.data()[i] ), expected_data[i], i)


if __name__ == '__main__':
    gr_unittest.main ()
