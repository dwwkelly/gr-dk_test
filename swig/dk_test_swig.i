/* -*- c++ -*- */

#define DK_TEST_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "dk_test_swig_doc.i"

%{
#include "dk_test/phase_rotator_2.h"
%}


%include "dk_test/phase_rotator_2.h"
GR_SWIG_BLOCK_MAGIC2(dk_test, phase_rotator_2);
