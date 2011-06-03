#!/usr/bin/env python
#
# Copyright 2011 Communications Engineering Lab, KIT
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
import chancoding_swig as cc

class qa_industrystd_bb (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_zeros (self):
        """ Check the right number of zeros is output for n input zeros. """
        in_len = 8
        src = gr.vector_source_b((0,) * in_len, False)
        enc = cc.industrystd_encoder_bb(1, 1)
        dst = gr.vector_sink_b()

        self.tb.connect(src, enc, dst)
        self.tb.run ()
        self.assertEqual(dst.data(), (0,) * (in_len * 2))


    def test_002_data(self):
        """ Check on real data """
        in_data = (1, 1, 0, 1, 1, 0, 0, 1)
        out_data = (1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1)

        src = gr.vector_source_b(in_data, False)
        enc = cc.industrystd_encoder_bb(1, 1)
        dst = gr.vector_sink_b()

        self.tb.connect(src, enc, dst)
        self.tb.run ()
        self.assertEqual(out_data, dst.data())

    def test_003_packeddata(self):
        """ Run test on packed input data. """
        in_data = (0b11011001,)
        out_data = (0b11101011, 0b01000111)

        src = gr.vector_source_b(in_data, False)
        enc = cc.industrystd_encoder_bb(8, 8)
        dst = gr.vector_sink_b()

        self.tb.connect(src, enc, dst)
        self.tb.run ()
        self.assertEqual(out_data, dst.data())

    def test_004_halfpackeddata(self):
        """ Run test on sparsely packed data """
        in_data = (0b1101 ,0b1001)
        out_data = (0b1110, 0b1011, 0b0100, 0b0111)

        src = gr.vector_source_b(in_data, False)
        enc = cc.industrystd_encoder_bb(4, 4)
        dst = gr.vector_sink_b()

        self.tb.connect(src, enc, dst)
        self.tb.run ()
        self.assertEqual(out_data, dst.data())

if __name__ == '__main__':
    gr_unittest.main ()
