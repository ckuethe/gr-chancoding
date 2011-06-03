#!/usr/bin/env python
# 
# Copyright 2011 Communications Engineering Lab, KIT
# 
# This is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this software; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

#

from gnuradio import gr, gr_unittest
import chancoding_swig as cc

class qa_blockinterleaver(gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_exceptions (self):
        self.assertRaises(ValueError,
                            lambda: cc.blockinterleaver_vbb(2, 1, 3))
        self.assertRaises(ValueError,
                            lambda: cc.blockinterleaver_vbb(20, 20, 3))
        self.assertRaises(ValueError,
                            lambda: cc.blockinterleaver_bb(20, 20, 3))
        self.assertRaises(ValueError,
                            lambda: cc.blockdeinterleaver_vbb(2, 1, 3))
        self.assertRaises(ValueError,
                            lambda: cc.blockdeinterleaver_vbb(20, 20, 3))
        self.assertRaises(ValueError,
                            lambda: cc.blockdeinterleaver_bb(20, 20, 3))


    def test_stream_interleaving_symbols(self):
        n_rows = 32
        n_cols = 128
        src = gr.glfsr_source_b(32)
        head = gr.head(gr.sizeof_char, n_rows * n_cols * 3)
        interleaver = cc.blockinterleaver_bb(n_rows, n_cols)
        deinterleaver = cc.blockdeinterleaver_bb(n_rows, n_cols)
        ber = cc.ber_b(8)

        self.tb.connect(src, head, interleaver, deinterleaver, ber)
        self.tb.connect(head, (ber, 1))
        self.tb.run()
        self.assertEqual(ber.ber(), 0)


    def test_stream_interleaving_bits(self):
        n_rows = 32
        n_cols = 128
        bits_per_byte = 2
        src = gr.glfsr_source_b(32)
        head = gr.head(gr.sizeof_char, n_rows * n_cols * 3)
        interleaver = cc.blockinterleaver_bb(n_rows, n_cols, bits_per_byte)
        deinterleaver = cc.blockdeinterleaver_bb(n_rows, n_cols, bits_per_byte)
        ber = cc.ber_b(bits_per_byte)

        self.tb.connect(src, head, interleaver, deinterleaver, ber)
        self.tb.connect(head, (ber, 1))
        self.tb.run()
        self.assertEqual(ber.ber(), 0)


    def test_stream_interleaving_multibits(self):
        pass


if __name__ == '__main__':
    gr_unittest.main ()

