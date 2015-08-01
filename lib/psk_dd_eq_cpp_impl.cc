/* -*- c++ -*- */
/*
 * Copyright 2015 Devin Kelly
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


#include <cmath>
#include <cfloat>
#include <vector>
#include <gnuradio/io_signature.h>
#include "psk_dd_eq_cpp_impl.h"

#define PI 3.141592623589

namespace gr {
  namespace dk_test {

    psk_dd_eq_cpp::sptr
    psk_dd_eq_cpp::make(int M)
    {
      return gnuradio::get_initial_sptr (new psk_dd_eq_cpp_impl(M));
    }

    /*
     * The private constructor
     */
    psk_dd_eq_cpp_impl::psk_dd_eq_cpp_impl(int M)
      : gr::block("psk_dd_eq_cpp",
              gr::io_signature::make(1, 8192, sizeof(gr_complex)),
              gr::io_signature::make(1, 8192, sizeof(gr_complex)))
    {
        constellations = NULL;
        set_M(M);
        get_constellations();
    }

    /*
     * Our virtual destructor.
     */
    psk_dd_eq_cpp_impl::~psk_dd_eq_cpp_impl()
    {
    }

    void
    psk_dd_eq_cpp_impl::get_constellations()
    {
        if(constellations != NULL) {
            delete constellations;
            constellations = NULL;
        }
        constellations = new std::vector<gr_complex>(M());

        int ii = 0;
        float a, b, theta;
        for (ii=0; ii < M(); ii++){
            theta = 2.0 * PI * ((float) ii) / ((float) M());

            a = cos(theta);
            b = sin(theta);

            constellations->assign(ii, gr_complex(a, b));
        }
    }

    int
    psk_dd_eq_cpp_impl::find_closest(gr_complex input)
    {
        float d_min = FLT_MAX;
        int ii = 0;
        float a, b, dist;
        for (ii=0; ii<M(); ii++){
            a = pow(constellations->at(ii).real() - input.real(), 2);;
            b = pow(constellations->at(ii).imag() - input.imag(), 2);
            dist = sqrt(a + b);
            if (dist < d_min) {
                d_min = dist;
            }
        }

        return d_min;
    }


    void
    psk_dd_eq_cpp_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
    }


    int
    psk_dd_eq_cpp_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const gr_complex *in = (const gr_complex *) input_items[0];
        gr_complex *out = (gr_complex *) output_items[0];

        consume_each (noutput_items);

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace dk_test */
} /* namespace gr */

