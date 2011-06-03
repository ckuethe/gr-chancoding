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


class qa_rmg_decoder_vii (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_codeallr2m3 (self):
        """ Check Golay-decoding m=3 for all possible inputs """

	src_data = (18,237,29,226,33,222,46,209,71,184,72,183,116,139,123,132,20,235,27,228,39,216,40,215,65,190,78,177,114,141,125,130)
	expected_data = (0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31)
        src1 = gr.vector_source_i(src_data)
        coding_action = chancoding.rmg_decoder_vii(3,1)
        sink = gr.vector_sink_i()

        self.tb.connect(src1, coding_action)
        self.tb.connect(coding_action, sink)
        self.tb.run()

        self.assertEqual( coding_action.get_vlen_in(), 1)
        self.assertEqual( coding_action.get_vlen_out(), 1)
        self.assertEqual( coding_action.get_num_bits_in(), 8)
        self.assertEqual( coding_action.get_num_bits_out(), 5)

	for i in range( len(expected_data) ):
        	self.assertEqual( sink.data()[i] , expected_data[i], i)

    def test_002_codear5m5 (self):
        """ Check Golay-decoding m5 for 5 possible inputs """

	src_data = (2027768814, -487726574, -290184584, 1195919287, -1220065209, -763895484, -507784568, 1220065208, 487776786, -303895267)
	expected_data = (1084,9,1027,32,47,1053,1033,46,10,1)

        src1 = gr.vector_source_i(src_data)
        coding_action = chancoding.rmg_decoder_vii(5,5)
        sink = gr.vector_sink_i()

        self.tb.connect(src1, coding_action)
        self.tb.connect(coding_action, sink)
        self.tb.run()

	for i in range( len(expected_data) ):
        	self.assertEqual( sink.data()[i] , expected_data[i], i)

    def test_003_coder3m7 (self):
        """ Check Golay-decoding m=7 for 5 possible inputs """

	expected_data = (121,
			 9,
			 235,
			 32,
			 492,
			 194,
			 342,
			 100,
			 10,
			 1)
	src_data = (	786312737, -786354655, -786312738, -786354655,
			303895266, -303951134, -303895267, -303951134,
			-2071231372, 2071233652, -2071231372, -2071233653,
			-487776787, 487726573, 487776786, 487726573,
			2104655245, 2104656498, -2104655246, 2104656498,
			1954253691, -1954247813, 1954253691, 1954247812,
			-668457176, -668411689, -668457176, 668411688,
			773968161, 773926622, -773968162, 773926622,
			303895266, -303951134, 303895266, 303951133,
			303951133, -303895267, -303951134, -303895267)

        src1 = gr.vector_source_i(src_data,0,4)
        coding_action = chancoding.rmg_decoder_vii(7,11)
        sink = gr.vector_sink_i()

        self.tb.connect(src1, coding_action)
        self.tb.connect(coding_action, sink)
        self.tb.run()

	for i in range( len(expected_data) ):
        	self.assertEqual( sink.data()[i] , expected_data[i], i)

if __name__ == '__main__':
    gr_unittest.main ()
