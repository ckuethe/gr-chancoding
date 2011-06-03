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


class qa_rm_decoder_vii (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_decodeallr2m3 (self):
        """ Check decoding r=2 m=3 for all possible inputs """

	src_data = 	(0,255,15,240,51,204,60,195,85,170,90,165,102,153,105,150,3,252,12,243,48,207,63,192,86,169,89,166,101,154,106,149,5,250,10,245,54,201,57,198,80,175,95,160,99,156,108,147,6,249,9,246,53,202,58,197,83,172,92,163,96,159,111,144,17,238,30,225,34,221,45,210,68,187,75,180,119,136,120,135,18,237,29,226,33,222,46,209,71,184,72,183,116,139,123,132,20,235,27,228,39,216,40,215,65,190,78,177,114,141,125,130,23,232,24,231,36,219,43,212,66,189,77,178,113,142,126,129)
	expected_data = (0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127)
        src1 = gr.vector_source_i(src_data)
        coding_action = chancoding.rm_decoder_vii(2,3)
        sink = gr.vector_sink_i()

        self.tb.connect(src1, coding_action)
        self.tb.connect(coding_action, sink)
        self.tb.run()

        self.assertEqual( coding_action.get_vlen_in(), 1)
        self.assertEqual( coding_action.get_vlen_out(), 1)
        self.assertEqual( coding_action.get_num_bits_in(), 8)
        self.assertEqual( coding_action.get_num_bits_out(), 7)

	for i in range( len(expected_data) ):
        	self.assertEqual( sink.data()[i] , expected_data[i], i)

    def test_002_decodear5m5 (self):
        """ Check decoding r=5 m=5 for 10 possible inputs """

	src_data = (-1771465066, 1721341545, 252654387, 858993459, -1431672471)
	expected_data = (125,182,392,16,419)
        src1 = gr.vector_source_i(src_data)
        coding_action = chancoding.rm_decoder_vii(5,5)
        sink = gr.vector_sink_i()

        self.tb.connect(src1, coding_action)
        self.tb.connect(coding_action, sink)
        self.tb.run()

	for i in range( len(expected_data) ):
        	self.assertEqual( sink.data()[i] , expected_data[i], i)

    def test_003_decoder3m7 (self):
        """ Check decoding r=3 m=7 for 10 possible inputs """

	src_data = (	-571585657, 756958344, 506300235, 517113780,
			84238240, 919170156, 184180560, 959868060,
			858993459, -859032781, -1717986919, 1718000025,
			-1431677611, 1431677610, 1515890085, 1515890085,
			-65536, 65535, -65536, 65535)
	expected_data = (	1902679864,3,
				147491936,6,
				24782,0,
				2472,0,
				12,0)
        src1 = gr.vector_source_i(src_data,0,4)
        coding_action = chancoding.rm_decoder_vii(3,7)
        sink = gr.vector_sink_i(2)

        self.tb.connect(src1, coding_action)
        self.tb.connect(coding_action, sink)
        self.tb.run()

	for i in range( len(expected_data) ):
        	self.assertEqual( sink.data()[i] , expected_data[i], i)

if __name__ == '__main__':
    gr_unittest.main ()
