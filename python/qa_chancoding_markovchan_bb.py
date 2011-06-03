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

import numpy as np
from gnuradio import gr, gr_unittest
import chancoding_swig as cc

class qa_markovchan_bb (gr_unittest.TestCase):

    def setUp (self):
        self.tb = gr.top_block ()

    def tearDown (self):
        self.tb = None

    def test_001_exceptions (self):
        """ check it fails for invalid input """
        valid_ber = (0.5,) * 3
        invalid_ber1 = (0.5,) * 4 # Too long
        invalid_ber2 = (0.5, 0.5, 2) # BER=2
        valid_trans_matrix =   (0.8, 0.15, 0.05,
                                0.1, 0.6, 0.3,
                                0.2, 0.1, 0.7)
        invalid_trans_matrix1= (0.8, 0.15, 0.2, # Doesn't add up to one
                                0.1, 0.6, 0.3,
                                0.2, 0.1, 0.7)
        invalid_trans_matrix2= (0.8, 0.15, 0.05,
                                0.1, 0.6, 0.3) # Wrong size
        self.assertRaises(ValueError,
                            lambda: cc.markovchan_bb(invalid_ber1, valid_trans_matrix))
        self.assertRaises(ValueError,
                            lambda: cc.markovchan_bb(invalid_ber2, valid_trans_matrix))
        self.assertRaises(ValueError,
                            lambda: cc.markovchan_bb(invalid_ber1, invalid_trans_matrix1))
        self.assertRaises(ValueError,
                            lambda: cc.markovchan_bb(valid_ber, invalid_trans_matrix1))
        self.assertRaises(ValueError,
                            lambda: cc.markovchan_bb(valid_ber, invalid_trans_matrix2))
        self.assertRaises(ValueError,
                            lambda: cc.markovchan_bb(valid_ber, valid_trans_matrix, 9))
        self.assertRaises(ValueError,
                            lambda: cc.markovchan_bb(valid_ber, valid_trans_matrix, 8, 5))
        try:
            m = cc.markovchan_bb(valid_ber, valid_trans_matrix)
            m = cc.markovchan_bb(valid_ber, valid_trans_matrix, 8, 0)
        except ValueError:
            self.fail("An error was raised, but shouldn't have.")


    def test_002_t (self):
        """ two state: one errorless, and the other can never be reached """
        n_bytes = 10000
        ber = (0, 0.5)
        trans_matrix = (1.0, 0.0,
                        1.0, 0.0)

        src = gr.glfsr_source_b(32)  # Create some pseudo-random bits
        head = gr.head(1, n_bytes)
        chan = cc.markovchan_bb(ber, trans_matrix, 8)
        ber = cc.ber_b(8)
        sink_state = gr.vector_sink_i()

        self.tb.connect(src, head, chan, (ber, 0))
        self.tb.connect(head, (ber, 1))
        self.tb.connect((chan, 1), sink_state)
        self.tb.run ()

        self.assertEqual(ber.ber(), 0)
        self.assertEqual(sink_state.data(), (0,) * n_bytes, "State was not always 0!")


    def test_003_t (self):
        """ two states, random switching """
        n_bytes = 10000
        ber = (0, 0.5)
        trans_matrix = (0.5, 0.5,
                        0.5, 0.5)
        src = gr.glfsr_source_b(32)  # Create some pseudo-random bits
        head = gr.head(1, n_bytes)
        chan = cc.markovchan_bb(ber, trans_matrix, 8)
        ber = cc.ber_b(8)
        sink_state = gr.vector_sink_i()

        self.tb.connect(src, head, chan, (ber, 0))
        self.tb.connect(head, (ber, 1))
        self.tb.connect((chan, 1), sink_state)
        self.tb.run ()

        n_times_in_state_1 = np.sum(sink_state.data())
        print "\nNumber of times in state 1 = " + str(n_times_in_state_1)
        print "            Expected value = " + str(n_bytes/2)
        self.assertTrue(n_times_in_state_1 > 3500 and n_times_in_state_1 < 6500,
                 "Due to the statistical nature of the bsc, this can actually fail (though very unlikely). Try again.")
        print "  Measured BER = " + str(ber.ber())
        print "Expected value = 0.25"
        self.assertTrue(abs(ber.ber()- 0.25) < 0.05,
                 msg="Due to the statistical nature of the bsc, this can actually fail (though very unlikely). Try again.")


if __name__ == '__main__':
    gr_unittest.main ()

