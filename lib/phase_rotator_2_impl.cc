/* -*- c++ -*- */
/*
 * Copyright 2015 <+YOU OR YOUR COMPANY+>.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <math.h>
#include <gnuradio/io_signature.h>
#include "phase_rotator_2_impl.h"

namespace gr {
  namespace dk_test {

    phase_rotator_2::sptr
    phase_rotator_2::make(float angle)
    {
      return gnuradio::get_initial_sptr
        (new phase_rotator_2_impl(angle));
    }

    /*
     * The private constructor
     */
    phase_rotator_2_impl::phase_rotator_2_impl(float angle)
      : gr::block("phase_rotator_2",
              gr::io_signature::make(1, 8192, sizeof(gr_complex)),
              gr::io_signature::make(1, 8192, sizeof(gr_complex)))
    {
        this->angle = angle;
    }

    /*
     * Our virtual destructor.
     */
    phase_rotator_2_impl::~phase_rotator_2_impl()
    {
    }

    void
    phase_rotator_2_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
    }

    int
    phase_rotator_2_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const gr_complex *in = (const gr_complex *) input_items[0];
        gr_complex *out = (gr_complex *) output_items[0];

        float x = 0.0;
        float y = 0.0;
        float r = 0.0;
        float theta = 0.0;
        float a = 0.0;
        float b = 0.0;

        int ii = 0;
        for (ii=0; ii < ninput_items.size(); ii++){
            x = in[ii].real();
            y = in[ii].imag();
            if (x == 0 && y == 0.0) {
                out[ii] = gr_complex(0.0, 0.0);
            } else {

                // Get polar co-ordinates
                r = sqrt(pow(x, 2) + pow(y, 2));
                theta = atan2(x, y);

                // Add the phase offset
                theta -= theta - this->angle;

                // Back to rectangular co-ordinates
                a = r * cos(theta);
                b = r * sin(theta);

                out[ii] = gr_complex(a, b);
            }
        }

        consume_each (noutput_items);
        return noutput_items;
    }

  } /* namespace dk_test */
} /* namespace gr */

