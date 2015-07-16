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

#ifndef INCLUDED_DK_TEST_PHASE_ROTATOR_2_IMPL_H
#define INCLUDED_DK_TEST_PHASE_ROTATOR_2_IMPL_H

#include <dk_test/phase_rotator_2.h>

namespace gr {
  namespace dk_test {

    class phase_rotator_2_impl : public phase_rotator_2
    {
     private:
         float d_angle;

     public:
      phase_rotator_2_impl(float angle);
      ~phase_rotator_2_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      void set_angle(float angle) {
          d_angle = angle;
      }

      float angle() const {
          return d_angle;
      }

      int general_work(int noutput_items,
		       gr_vector_int &ninput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items);
    };

  } // namespace dk_test
} // namespace gr

#endif /* INCLUDED_DK_TEST_PHASE_ROTATOR_2_IMPL_H */

