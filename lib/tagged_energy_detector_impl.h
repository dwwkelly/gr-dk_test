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

#ifndef INCLUDED_DK_TEST_TAGGED_ENERGY_DETECTOR_IMPL_H
#define INCLUDED_DK_TEST_TAGGED_ENERGY_DETECTOR_IMPL_H

#include <dk_test/tagged_energy_detector.h>

namespace gr {
  namespace dk_test {

    class tagged_energy_detector_impl : public tagged_energy_detector
    {
     private:
      int d_fft_size;
      float d_threshold;

     public:
      tagged_energy_detector_impl(float threshold, int fft_size);
      ~tagged_energy_detector_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
		       gr_vector_int &ninput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items);

      float threshold() {
        return d_threshold;
      }

      void set_threshold(float thresh) {
        d_threshold = thresh;
      }

      int fft_size(){
        return d_fft_size;
      }

      void set_fft_size(int N) {
        d_fft_size = N;
      }

    };

  } // namespace dk_test
} // namespace gr

#endif /* INCLUDED_DK_TEST_TAGGED_ENERGY_DETECTOR_IMPL_H */

