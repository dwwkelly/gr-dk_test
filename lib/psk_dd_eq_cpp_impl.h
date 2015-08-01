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

#ifndef INCLUDED_DK_TEST_PSK_DD_EQ_CPP_IMPL_H
#define INCLUDED_DK_TEST_PSK_DD_EQ_CPP_IMPL_H

#include <dk_test/psk_dd_eq_cpp.h>

namespace gr {
  namespace dk_test {

    class psk_dd_eq_cpp_impl : public psk_dd_eq_cpp
    {
     private:
         int d_M;
         std::vector<gr_complex> *constellations;

         void get_constellations();

         int find_closest(gr_complex input);

     public:
      psk_dd_eq_cpp_impl(int M);
      ~psk_dd_eq_cpp_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      void set_M(int M) {
          d_M = M;
      }

      int M() const {
          return d_M;
      }

      int general_work(int noutput_items,
		       gr_vector_int &ninput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items);

    };


  } // namespace dk_test
} // namespace gr

#endif /* INCLUDED_DK_TEST_PSK_DD_EQ_CPP_IMPL_H */

