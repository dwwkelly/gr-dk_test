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

import numpy
from gnuradio import gr


class phase_rotator(gr.basic_block):
    """
    docstring for block phase_rotator
    """
    def __init__(self, angle):
        gr.basic_block.__init__(self,
                                name="phase_rotator",
                                in_sig=[numpy.complex64],
                                out_sig=[numpy.complex64])

        self.angle = angle  # radians

    def forecast(self, noutput_items, ninput_items_required):
        # setup size of input_items[i] for work call
        for i in range(len(ninput_items_required)):
            ninput_items_required[i] = noutput_items

    def general_work(self, input_items, output_items):
        nread = self.nitems_read(0)  # number of items read on port 0
        ninput_items = len(input_items[0])
        noutput_items = len(output_items[0])
        nitems_to_consume = min(ninput_items, noutput_items)
        in0 = input_items[0]
        out0 = output_items[0]

        for ii in range(nitems_to_consume):
            x = in0[ii].real
            y = in0[ii].imag

            if x == 0 and y == 0:
                out0[ii] = numpy.complex(0)
            else:
                r = numpy.sqrt(numpy.square(x) + numpy.square(y))
                theta = numpy.arctan2(x, y) - self.angle

                a = r * numpy.cos(theta)
                b = r * numpy.sin(theta)

                out0[ii] = numpy.complex(a, b)

        self.consume(0, nitems_to_consume)
        return nitems_to_consume

    def get_angle(self):
        return self.angle

    def set_angle(self, angle):
        self.angle = angle
