// Oliver Kullmann, 14.12.2009 (Swansea)
/* Copyright 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Satisfiability/Reductions/UnitClausePropagation/plans/UnitClausePropagation.hpp
  \brief Plans regarding the specific algorithms used in UnitClausePropagation.cpp


  \todo Better names
  <ul>
   <li> Instead of "UnitClausePropagation.cpp" we should use some more specific
   name. </li>
   <li> The algorithms in this application should perhaps be centred around
   usage of the concept of "binary clauses with removal", and using the
   full clause-literal graph. </li>
   <li> And also UnitClausePropagation/ClsAdaptorUCP.hpp should have some
   more specific name. </li>
  </ul>


  \todo Move todos from UnitClausePropagation/ClsAdaptorUCP.hpp here.


  \todo Improve efficiency of UnitClausePropagation.cpp
  <ul>
   <li> One class of testcases can be generated by
   \verbatim
Smusat_Horn-O3-DNDEBUG k > Smusat_Horn_k.cnf
   \endverbatim
   </li>
   <li> For k=20000 the file is 1229 MB. </li>
   <li> The set-version seems to be a bit faster for k, say, up to 5000,
   but then it needs a lot of memory, and this seems to kill performance. </li>
   <li> The vector-version gets faster than the set-version for k, say,
   more than 6000, and it uses only 50% of the memory. </li>
   <li> The OKsolver_2002 is definitely slower than both version, but it
   uses somewhat less memory. </li>
   <li> minisat2 is much faster; for k=20000 on csltok it takes only 26 seconds
   for the whole computation, and also the memory usage is much smaller
   (maximum usage seems to be around 230 MB). </li>
   <li> satz215 creates a core dump (memory access error) for k=20000. </li>
   <li> march_pl for k=20000 needs about 120 s for parsing, and uses about 800
   MB (that's not too bad, quite a bit less than OKsolver_2002). However
   aborted after more than 3 hours (with succeeding). </li>
   <li> So there seems to be a lot to gain. Since we have very long
   clauses here, the advantage of using just two watched literals per
   clause becomes very big. </li>
   <li> Perhaps we should use a memory pool; and using only vectors should
   minimise memory usage. </li>
   <li> And, of course, we need to experiment with watched literals; perhaps
   making an exception for binary clauses, where we can simplify the
   implementation. Though not in this sub-module; see "Implement initial UCP
   based on head-tail clauses" in
   Reductions/UnitClausePropagation/plans/general.hpp. </li>
   <li> It seems that also parsing is rather slow (compared to minisat2). </li>
   <li> We need also test-cases with small clause-sizes. Perhaps the Musat(2)
   cases with one additional unit-clause (then most of the clauses are
   binary, and we just have two full clauses). </li>
   <li> Generator at Maxima-level:
   \verbatim
musatd2p1_fcl(n) := block([FF:musatd2_fcl(n)], [FF[1], endcons({1},FF[2])]);
output_musatd2p1(n) := outputext_fcl(sconcat("SMU(2) with ",n," variables, plus one unit-clause."), musatd2p1_fcl(n), sconcat("Smusatd2p1_",n,".cnf"))$
   \endverbatim
   Just writing to file is very slow. </li>
   <li> The same at C++ level:
   \verbatim
n=5; Musatd2-O3-DNDEBUG ${n} 1 > Musatd2p1_${n}.cnf
   \endverbatim
   </li>
   <li> Using n=1000000: Here the vector-version seems slightly faster than
   the set-version (12s versus 11s on csltok). </li>
   <li> OKsolver_2002 is extremely slow (7300 s); what's going on here? </li>
   <li> minisat2 is also very slow (5200 s); again, why is this? </li>
   <li> We should also consider random clause-sets with some added
   unit-clause(s). </li>
   <li> Sudoku puzzles can also be used. </li>
   <li> Experiments on 32-bit machines as well as on 64-bit machines. </li>
   <li> We need some tools for time-measurement, recording and evaluation
   (the last of course by R) of applications. </li>
   <li> Perhaps in this context we concentrate on "one-off" applications of
   UCP, that is, just reading a file, computing the simplification, and
   outputting it (as in UnitClausePropagation.cpp). </li>
   <li> Then we don't need to worry about reversing information stored in
   clauses (since pure UCP itself does not involve any form of backtracking).
   </li>
  </ul>

*/