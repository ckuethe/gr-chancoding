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
import chancoding_swig as chancoding


class qa_bercount (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_berout (self):
        """ Check the float output and the ber() function with unpacked data """
        src1 = gr.vector_source_b((1,1,1,1,1,1,1,1,1,1))
        src2 = gr.vector_source_b((1,1,1,1,1,1,1,1,1,0))
        ber = chancoding.ber_b()
        sink = gr.vector_sink_f()

        self.tb.connect(src1, (ber, 0))
        self.tb.connect(src2, (ber, 1))
        self.tb.connect(ber, sink)
        self.tb.run()

        self.assertAlmostEqual(ber.ber(), 0.1)
        self.assertEqual(ber.bit_errors(), 1)
        self.assertFloatTuplesAlmostEqual(sink.data(), (0,0,0,0,0,0,0,0,0,0.1), 8)

    def test_002_packeddata (self):
        """ Pack 4 bits into a byte and run the check again """
        src1 = gr.vector_source_b((0b1111, 0b1111, 0b1111))
        src2 = gr.vector_source_b((0b1111, 0b1111, 0b1110))
        ber = chancoding.ber_b(4)
        sink = gr.vector_sink_f()

        self.tb.connect(src1, (ber, 0))
        self.tb.connect(src2, (ber, 1))
        self.tb.connect(ber, sink)
        self.tb.run()

        self.assertAlmostEqual(ber.ber(), 1./12)
        self.assertEqual(ber.bit_errors(), 1)
        self.assertFloatTuplesAlmostEqual(sink.data(), (0,0,1./12), 8)


if __name__ == '__main__':
    gr_unittest.main ()

