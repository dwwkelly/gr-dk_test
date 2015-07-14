#!/usr/bin/env python2
# -*- coding: utf-8 -*-
#
# Copyright 2015 Devin Kelly
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
import pmt
from gnuradio import gr


class burster(gr.basic_block):
    """
    docstring for block burster
    """
    def __init__(self):
        gr.basic_block.__init__(self,
                                name="burster",
                                in_sig=[numpy.float],
                                out_sig=[numpy.float])

        self.forward = True
        self.offset = 0

    def forecast(self, noutput_items, ninput_items_required):
        # setup size of input_items[i] for work call
        for i in range(len(ninput_items_required)):
            ninput_items_required[i] = noutput_items

    def general_work(self, input_items, output_items):
        nread = self.nitems_read(0)  # number of items read on port 0
        ninput_items = len(input_items[0])
        noutput_items = len(output_items[0])
        in0 = input_items[0]
        out0 = output_items[0]

        for ii in range(noutput_items):
            if ii % 2500 == 0 and self.forward:
                k = pmt.string_to_symbol('tx_sob')
                v = pmt.PMT_T
                src = pmt.string_to_symbol('burster')
                self.add_item_tag(0, self.offset, k, v, src)
                self.offset += 2500
                self.forward = not self.forward
            elif ii % 2500 == 0 and not self.forward:
                k = pmt.string_to_symbol('tx_eob')
                v = pmt.PMT_T
                src = pmt.string_to_symbol('burster')
                self.add_item_tag(0, self.offset, k, v, src)
                self.forward = not self.forward
                self.offset += 2500

        nitems_to_consume = min(ninput_items, noutput_items)
        out0[:nitems_to_consume] = in0[:nitems_to_consume]
        self.consume(0, nitems_to_consume)
        return noutput_items
