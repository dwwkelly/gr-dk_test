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


#ifndef INCLUDED_DK_TEST_PSK_DD_EQ_CPP_H
#define INCLUDED_DK_TEST_PSK_DD_EQ_CPP_H

#include <dk_test/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace dk_test {

    /*!
     * \brief <+description of block+>
     * \ingroup dk_test
     *
     */
    class DK_TEST_API psk_dd_eq_cpp : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<psk_dd_eq_cpp> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of dk_test::psk_dd_eq_cpp.
       *
       * To avoid accidental use of raw pointers, dk_test::psk_dd_eq_cpp's
       * constructor is in a private implementation
       * class. dk_test::psk_dd_eq_cpp::make is the public interface for
       * creating new instances.
       */
      static sptr make(int M);
    };

  } // namespace dk_test
} // namespace gr

#endif /* INCLUDED_DK_TEST_PSK_DD_EQ_CPP_H */

