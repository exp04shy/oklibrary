/* Oliver Kullmann, 18.12.2010 (Swansea) */
/* Copyright 2010, 2011 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file ComputerAlgebra/Satisfiability/Lisp/Reductions/plans/RBases.hpp
  \brief Plans for removing redundancies from the set of prime implicates


  \todo Relations to other parts
  <ul>
   <li> See
   Experimentation/Investigations/BooleanFunctions/plans/ReductionBasedRepresentations.hpp
   for considerations regarding representing boolean functions. </li>
   <li> See
   Satisfiability/Reductions/Bases/plans/general.hpp for the C++ level. </li>
  </ul>


  \todo Organisation
  <ul>
   <li> DONE The concept of r-bases can be applied to arbitrary clause-sets,
   not just to the set of all prime-clauses of some boolean function. </li>
   <li> DONE
   So likely this module should be moved from Lisp/Primality to module
   Lisp/Reductions. </li>
   <li> What remains there is the application to compute "interesting" subsets
   of the set of all prime-clauses. </li>
  </ul>


  \todo The notion of a base of a clause-set relative to some reduction
  <ul>
   <li> Consider some reduction r (i.e., r: CLS -> CLS with r(F)
   satisfiability-equivalent to F). </li>
   <li> A sub-clause-set F' of a clause-set F is an "r-base of F" if
   for every clause D in F and for the corresponding partial assignment
   phi_D^0 the empty clause is element of r(phi_D^0 * F'), while this is not
   true for any strict subset of F'. </li>
   <li> That means that all missing clauses D can be derived from F' by means
   of r. </li>
   <li> Using additional assumptions for r one can derive more efficient
   algorithms. </li>
   <li> An "r-generating" clause-set drops the requirement that no clause
   can be removed. </li>
   <li> Both notions of generating clause-sets and base-clause-sets actually
   make sense regarding the relation between arbitrary clause-sets F and F'
   (F is r-generating resp. an r-base for F'). </li>
   <li> As with Satisfiability/Reductions/Bases/RUcpGen.cpp, we need also
   the form of rbase_cl(F,red_) using some given stock F0 of clauses to be
   used. </li>
  </ul>


  \todo Considering special reductions
  <ul>
   <li> There is exactly one r_0-base of every F, namely the result of
   subsumption elimination in F. </li>
  </ul>


  \todo Application to the representation of boolean functions
  <ul>
   <li> If F is the set of prime implicates of some boolean function, which is
   too big to be included in some CNF-representation, then the hope is that
   r_1-bases or r_2-bases might be much smaller, while still having enough
   inference power. </li>
   <li> The reasoning is that if r is too strong (for example if r detects
   every unsatisfiability, then the bases of (any) F are exactly the
   irredundant cores) then we get smaller F', however we possibly gave up
   too much inference power, and SAT-solving might be much harder. </li>
   <li> The r_k-bases of such F are exactly the minimal (w.r.t
   subset-inclusion) r_k-based representation via CNFs not using additional
   variables (see "Investigating conditions and their representations" in
   Investigations/Cryptography/AdvancedEncryptionStandard/plans/general.hpp)
   of the underlying boolean function. </li>
  </ul>


  \todo Sampling of r-bases
  <ul>
   <li> DONE (we have rand_rbase_cs in
   ComputerAlgebra/Satisfiability/Lisp/Reductions/RBases.mac)
   First we just need the natural randomised algorithm for producing some
   r-base.
    <ol>
     <li> We start with F' = F, while G = {} is the set of clauses which are
     necessary. </li>
     <li> Choose C at random from F' - G, and let F'' := F' - {C}. </li>
     <li> If for all D in F - F'' we have {} in r(phi_D * F''), then let
     F' := F'', and repeat with choosing another C. </li>
     <li> Otherwise G := G + {C}, and another C is tried. </li>
     <li> The algorithm stops once F' = G, and then F' is an r-basis of F.
     </li>
    </ol>
   </li>
   <li> The remaining problem here is to precisely specify the random
   permutation.
    <ol>
     <li> See "Random r_1-bases" in
     Satisfiability/Reductions/Bases/plans/UcpBase.hpp. </li>
    </ol>
   </li>
  </ul>


  \todo Computing minimum r-bases
  <ul>
   <li> Searching for minimum bases (that is, of minimum size) might be very
   expensive, but, of course, should be implemented. </li>
  </ul>

*/
