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


#ifndef INCLUDED_DK_TEST_TAGGED_ENERGY_DETECTOR_H
#define INCLUDED_DK_TEST_TAGGED_ENERGY_DETECTOR_H

#include <dk_test/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace dk_test {

    /*!
     * \brief <+description of block+>
     * \ingroup dk_test
     *
     */
    class DK_TEST_API tagged_energy_detector : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<tagged_energy_detector> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of dk_test::tagged_energy_detector.
       *
       * To avoid accidental use of raw pointers, dk_test::tagged_energy_detector's
       * constructor is in a private implementation
       * class. dk_test::tagged_energy_detector::make is the public interface for
       * creating new instances.
       */
      static sptr make(float threshold, int fft_size);

      /*!
       * \brief Get the threshold in dB
       */
      virtual float threshold() = 0;

      /*!
       * \brief Set the threshold in dB
       */
      virtual void set_threshold(float thresh) = 0;

      /*!
       * \brief Get the FFT size
       */
      virtual int fft_size() = 0;

      /*!
       * \brief Set the FFT Size
       */
      virtual void set_fft_size(int N) = 0;

    };

  } // namespace dk_test
} // namespace gr

#endif /* INCLUDED_DK_TEST_TAGGED_ENERGY_DETECTOR_H */

