// Oliver Kullmann, 6.6.2009 (Swansea)
/* Copyright 2009, 2011 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Interfaces/InputOutput/plans/ExtendedDimacsStatistics.hpp
  \brief Plans on the application extracting statistics from files in (extended) Dimacs format


  \todo Better output for InputOutput/ExtendedDimacsStatistics.cpp
  <ul>
   <li> DONE
   The output description should be more descriptive. </li>
   <li> Also the maximal index and the real number of variables is needed.
   </li>
   <li> DONE
   The output should be in a R-table-like form. </li>
   <li> DONE (not needed; if needed, just remove the first line)
   And via a command-line parameter "raw output" (just the numbers,
   separated by spaces) are output. </li>
   <li> Compare with InputOutput/ExtendedDimacsFullStatistics.cpp. </li>
   <li> Likely Messages should be used. </li>
  </ul>


  \todo More convenient input
  <ul>
   <li> We should provide some standard parameters ("--help" etc.). </li>
   <li> Perhaps also something like "--file=", where then the input
   comes from a file. </li>
  </ul>


  \todo Improving efficiency
  <ul>
   <li> On the AES Sbox-subsumption hypergraph, created by
   \verbatim
> QuineMcCluskeySubsumptionHypergraph-n16-O3-DNDEBUG AES_Sbox_full.cnf | ExtendedDimacsFullStatistics-O3-DNDEBUG AES_PK.cnf
   \endverbatim
   the computation takes 3m41s on csltok. </li>
   <li> Parsing should be possible in 30s (precosat570 only needs that), and
   the rest of the computation shouldn't take much longer. </li>
   <li> There is somewhere a todo related to inefficient parsing. </li>
   <li> One also needs to check the effect of replacing boost::size by
   boost::distance. </li>
  </ul>


  \todo Generalising the computation
  <ul>
   <li> We also need a component for performing the computation of the
   statistics directly on a data structure. </li>
   <li> Somehow code duplication should be minimised. </li>
   <li> At least the components should be kept close together. </li>
  </ul>


  \todo Improving output
  <ul>
   <li> See "Better output for InputOutput/ExtendedDimacsStatistics.cpp"
   above. </li>
   <li> DONE (lines need to be removed if needed)
   Additionally we now have the problem that we have two types of output,
   and that seems not directly handable by R. </li>
   <li> DONE (that's how we handle it)
   Though one could handle it by skipping initial and trailing parts of
   the file. </li>
   <li> We should write a little R helper function. </li>
   <li> DONE
   Likely in general our output shot be easily R-readable, at least by
   some option. </li>
   <li> We should standardise this option: perhaps "--R-friendly". </li>
  </ul>

*/

