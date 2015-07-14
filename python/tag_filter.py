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
from gnuradio import gr


class tag_filter(gr.basic_block):
    """
    docstring for block tag_filter
    """
    def __init__(self):
        gr.basic_block.__init__(self,
                                name="tag_filter",
                                in_sig=[numpy.float],
                                out_sig=[numpy.float])
        self.forward_samples = True

    def forecast(self, noutput_items, ninput_items_required):
        # setup size of input_items[i] for work call
        for i in range(len(ninput_items_required)):
            ninput_items_required[i] = noutput_items

    def general_work(self, input_items, output_items):
        nread = self.nitems_read(0)  # number of items read on port 0
        in0 = input_items[0]
        out0 = output_items[0]
        ninput_items = len(in0)
        noutput_items = len(out0)

        nread = self.nitems_read(0)

        start = nread
        end = nread + ninput_items

        tags = self.get_tags_in_range(0, start, end)
        tags = sorted(tags, key=lambda tag: tag.offset)
        offsets = [ii.offset for ii in tags]

        for ind, val in enumerate(in0[0: noutput_items]):
            if self.forward_samples:
                out0[ind] = val
            else:
                out0[ind] = 0

            if ind + nread in offsets:
                # FIXME - this is cheating
                self.forward_samples = not self.forward_samples

        self.consume(0, noutput_items)
        return noutput_items
