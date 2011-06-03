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

import numpy as np

from gnuradio import gr, gr_unittest
import chancoding_swig as chancoding


class qa_bsc (gr_unittest.TestCase):
    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_exceptions(self):
        """ Make sure the block fails appropriately """
        self.assertRaises(ValueError, lambda: chancoding.bsc_bb(2))
        self.assertRaises(ValueError, lambda: chancoding.bsc_bb(0.5, 9))

    def test_002_bsc (self):
        """ Test on unpacked data """
        src = gr.glfsr_source_b(32)  # Create some pseudo-random bits
        head = gr.head(1, 10000)
        bsc = chancoding.bsc_bb(0.3)
        sink1 = gr.vector_sink_b()
        sink2 = gr.vector_sink_b()

        self.tb.connect(src, head, bsc, sink1)
        self.tb.connect(head, sink2)
        self.tb.run()

        bits1 = sink1.data()
        bits2 = sink2.data()
        bit_errors = np.sum(np.abs(np.array(bits1) - np.array(bits2)))
        self.assert_(bit_errors > 2500 and bit_errors < 3500,
                 "Due to the statistical nature of the bsc, this can actually fail (though very unlikely). Try again.")

    def test_003_bsc_packed (self):
        """ Test on packed data """
        src = gr.glfsr_source_b(32)  # Create some pseudo-random bits
        packer = gr.unpacked_to_packed_bb(1, gr.GR_MSB_FIRST)
        head = gr.head(1, 8 * 1000)
        bsc = chancoding.bsc_bb(0.5, 8)
        unpacker = gr.packed_to_unpacked_bb(1, gr.GR_MSB_FIRST)
        sink1 = gr.vector_sink_b()
        sink2 = gr.vector_sink_b()

        self.tb.connect(src, head, packer, bsc, unpacker, sink1)
        self.tb.connect(head, sink2)
        self.tb.run()

        bits1 = sink1.data()
        bits2 = sink2.data()
        bit_errors = np.sum(np.abs(np.array(bits1) - np.array(bits2)))
        self.assert_(bit_errors > 3500 and bit_errors < 4500,
                 "Due to the statistical nature of the bsc, this can actually fail (though very unlikely). Try again.")


if __name__ == '__main__':
    gr_unittest.main ()

