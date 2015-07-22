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
    def __init__(self,
                 start_sample=0,
                 start_tag='tx_sob',
                 end_sample=2500,
                 end_tag='tx_eob'):
        gr.basic_block.__init__(self,
                                name="burster",
                                in_sig=[numpy.float],
                                out_sig=[numpy.float])

        self.set_start_sample(start_sample)
        self.set_start_tag(start_tag)
        self.set_end_sample(end_sample)
        self.set_end_tag(end_tag)

        self.forward = False
        self.offset = 0
        self.last_tagged_sample = 0

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
            if ii % self.start_sample() == 0 and self.forward:
                k = pmt.string_to_symbol(self.start_tag())
                v = pmt.PMT_T
                src = pmt.string_to_symbol('burster')
                self.add_item_tag(0, self.offset, k, v, src)
                self.offset += self.start_sample()
                self.forward = not self.forward
            elif ii % self.end_sample() == 0 and not self.forward:
                k = pmt.string_to_symbol(self.end_tag())
                v = pmt.PMT_T
                src = pmt.string_to_symbol('burster')
                self.add_item_tag(0, self.offset, k, v, src)
                self.forward = not self.forward
                self.offset += self.end_sample()

        nitems_to_consume = min(ninput_items, noutput_items)
        out0[:nitems_to_consume] = in0[:nitems_to_consume]
        self.consume(0, nitems_to_consume)
        return noutput_items

    def set_start_sample(self, samp_num):
        if samp_num == 0:
            samp_num = 1
        self.start_samp_num = samp_num

    def start_sample(self):
        return self.start_samp_num

    def set_start_tag(self, tag):
        self.d_start_tag = tag

    def start_tag(self):
        return self.d_start_tag

    def set_end_sample(self, samp_num):
        if samp_num <= self.start_sample():
            samp_num = self.start_sample() + 1
        self.end_samp_num = samp_num

    def end_sample(self):
        return self.end_samp_num

    def set_end_tag(self, tag):
        self.d_end_tag = tag

    def end_tag(self):
        return self.d_end_tag
