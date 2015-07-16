#!/usr/bin/env python2
# -*- coding: utf-8 -*-
#
# Copyright 2015 <+YOU OR YOUR COMPANY+>.
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
from gnuradio import blocks
import numpy as np
import math
from phase_rotator import phase_rotator


class qa_phase_rotator (gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    def test_001_t(self):
        input_data = [0, 1, 1j]
        expected = []
        expected.append(0)
        expected.append(np.complex64(math.sqrt(2) / 2 +
                                     1j * (math.sqrt(2) / 2)))
        expected.append(np.complex64(math.sqrt(2) / 2 +
                                     1j * -(math.sqrt(2) / 2)))

        rotator = phase_rotator(3.14159 / 4.0)
        src = blocks.vector_source_c(input_data)
        sink = blocks.vector_sink_c()

        self.tb.connect(src, rotator)
        self.tb.connect(rotator, sink)
        self.tb.run()

        result_data = sink.data()
        self.assertFloatTuplesAlmostEqual(expected, result_data, 3)

    def test_002_t(self):
        input_data = [0, 1, 1j]
        expected = []
        expected.append(0)
        expected.append(np.complex64(-math.sqrt(2) / 2 +
                                     1j * (math.sqrt(2) / 2)))
        expected.append(np.complex64(math.sqrt(2) / 2 +
                                     1j * (math.sqrt(2) / 2)))

        rotator = phase_rotator(-3.14159 / 4.0)
        src = blocks.vector_source_c(input_data)
        sink = blocks.vector_sink_c()

        self.tb.connect(src, rotator)
        self.tb.connect(rotator, sink)
        self.tb.run()

        result_data = sink.data()
        self.assertFloatTuplesAlmostEqual(expected, result_data, 3)


if __name__ == '__main__':
    gr_unittest.run(qa_phase_rotator, "qa_phase_rotator.xml")
