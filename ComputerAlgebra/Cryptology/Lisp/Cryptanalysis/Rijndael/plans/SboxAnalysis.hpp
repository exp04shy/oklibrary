// Matthew Gwynne, 26.3.2008 (Swansea)
/* Copyright 2008, 2009, 2010, 2011 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file ComputerAlgebra/Cryptology/Lisp/Cryptanalysis/Rijndael/plans/SboxAnalysis.hpp
  \brief Plans for the Cryptanalysis of the Rijndael Sbox in Maxima/Lisp


  \todo Connections
  <ul>
   <li> See Experimentation/Investigations/Cryptography/AdvancedEncryptionStandard/plans/SboxInvestigations.hpp
   for experimental investigations. </li>
  </ul>


  \todo Add decomposed Sbox operations
  <ul>
   <li> In "Rearranging linear components of Sbox and MixColumns " in
   Cryptology/Lisp/Cryptanalysis/Rijndael/plans/Translations.hpp
   we wish to translate the AES by splitting the various parts of the Sbox
   (inversion, linear multiplication) and moving them into the MixColumns by
   combining them with the field multiplications. </li>
   <li> Therefore we need CNF translations for each of the following
   functions:
   <ol>
    <li> Inversion with the field - tseitin translation as translation 
    function. </li>
    <li> Linear multiplication by a GF(b) matrix - tseitin translation as 
    translation function. </li>
    <li> Linear multiplication by a GF(b) matrix followed by multiplication in
    the field - tseitin translation as translation function. </li>
    <li> Linear multiplication by a GF(b) matrix followed by multiplication in
    the field - CNF translation : DONE. </li>
    <li> Linear multiplication by a GF(b) matrix - CNF translation : DONE. 
    </li>
    <li> DONE Inversion with the field - CNF translation. </li>
   </ol>
   </li>
   <li> All operations are now available in theory using 
   ss_field_op_fulldnf_gen_fcl etc in 
   ComputerAlgebra/Cryptology/Lisp/Cryptanalysis/Rijndael/FieldOperationsAnalysis.mac .
   </li>
  </ul>

  
  \todo Representations of the Sbox using additional variables
  <ul>
   <li> Compare with "Investigating conditions and their representations"
   in 
   Experimentation/Investigations/Cryptography/AdvancedEncryptionStandard/plans/general.hpp. 
   </li>
   <li> When using (only) CNF, likely the use of additional variables is
   crucial. </li>
   <li> One should also consider the various arithmetical representations
   of the Sbox. </li>
   <li> DONE Most natural is to consider the Tseitin translation of the
   DNF-representation.
    <ol>
     <li> See
     Satisfiability/Lisp/FiniteFunctions/plans/TseitinTranslation.hpp. </li>
     <li> Most natural should be to use dualts_fcl in
     Satisfiability/Lisp/FiniteFunctions/TseitinTranslation.mac. </li>
    </ol>
   </li>
  </ul>

  
  \todo Other software systems offering Sbox translations
  <ul>
   <li> In the 4.2.1 version of the Sage computer algebra system, there is a
   module which offers functions related to the cryptanalysis and translation
   of various substitution boxes to CNF and SymbolicLogic (see 
   http://www.sagemath.org/doc/reference/sage/crypto/mq/sbox.html). </li>
   <li> In this system, one can create any substitution box, which is 
   considered as a permutation of the set of numbers 0 to n, and such
   an SBox object can be generated by specifying the mapping in the same
   manner as we specify permutations using lists in the Maxima system 
   (modulo the fact that we start with 1).
OK: WHERE? LINK?
   For example, the cyclic shift of the elements {0,...,3} can be generated
   by
   \verbatim
S = sage.crypto.mq.SBox(1,2,3,0)
   \endverbatim
   and then a CNF for this permutation can be generated using
   \verbatim
S.cnf()
   \endverbatim
   or 
   \verbatim
S.cnf(format='dimacs')
   \endverbatim
OK: What is the corresponding presentation in our system?
   for DIMACS, where there are 2 * (log_2(k)+1) variables and k is the number
   of arguments to SBox, the first log_2(k) + 1 variables are used to 
   represent the big endian representation of the input to the permutation, and
   the last log_2(k) + 1 variables represent the big endian representation of 
   the output. The CNF generated has (log_2(k)+1) * 2^k clauses, where these
   clauses are the direct translation of (i_1 /\ ... i_(log_2(k)+1)) => 
   (o_1 /\ ... /\ o_(log_2(k)+1)). </li>
OK: What is the "direct translation"? What does this mean for our cases?
   <li> There is also a separate module which implements each of the different 
   small scale variations of the AES given in [Algebraic Aspects of the 
   Advanced Encryption Standard], see 
   http://www.sagemath.org/doc/reference/sage/crypto/mq/sr.html#module-sage.crypto.mq.sr).
   </li>
  </ul>


  \todo Determine *all* prime implicates (for the purpose of analysis)
  <ul>
   <li> The task here is to try to *understand* the structure of the
   prime implicates. </li>
   <li> See
   Satisfiability/Lisp/Resolution/plans/PrimeImplicatesImplicants.hpp
   </li>
   <li> For a permutation of GF(2^8) we have 2 * 2^8 * 8 = 2^12 = 4096
   potential prime implicates, given by fixing 8 bit in either the input or
   the output, and one further bit to the wrong value. As one can see by
   the identity, these are not necessarily prime, since the identify
   just has 16 prime implicates (of length 2). </li>
   <li> One should test these. </li>
   <li> If the Maxima computation, via
   \verbatim
min_2resolution_closure_cs(rijnsbox_fullcnf_fcs()[2]);
   \endverbatim
   takes too long, then we need a C++ implementation; see
   OKlib/Satisfiability/FiniteFunctions/plans/general.hpp,
   "Prime implicants and implicates". A simple implementation should
   suffice here. </li>
   <li> Brute-force approaches:
    <ol>
     <li> There are 3^16 = 43,046,721 clauses with 16 variables altogether,
     so with a C++ implementation it is even no problem to run through
     all clauses and determine in this brute-force way the prime implicates. 
     </li>
     <li> We should write a little Maxima function which searches for prime 
     implicates (of length up to k) of a clause-set via this brute-force 
     approach (using some input SAT solver). This would need as input one of 
     the CNF-representations; since they are hitting clause-sets, we can then
     use a specialised SAT solver. </li>
     <li> We should also write a Maxima function for brute-force determination
     of all dual prime implicates (up to a given length), that is, the minimal 
     satisfying (partial) assignments. This is even simpler and doesn't need a 
     SAT solver. </li>
     <li> Perhaps we should write this function then also in C++ --- it's the 
     most simple function imaginable here, just run through all partial 
     assignments and check whether they satisfy the given clause-set. </li>
     <li> The only thing to think about is subsumption-elimination. But the
     simple implementation just does it at the end (since we have already a
     function for that!). As a side result, we obtain here the number of all
     satisfying partial assignments (which otherwise is actually not so easy to
     compute?!?). </li>
     <li> This would belong to module Satisfiability/Algorithms/AllSolutions;
     see Algorithms/AllSolutions/plans/MinimalAssignments.hpp. </li>
    </ol>
   </li>
   <li> However, since the S-box has a perfectly regular structure, it
   should also be possible to analytically determine all prime implicates:
    <ol>
     <li> Extract from the above results prime implicates, determine
     their structure, and generalise. </li>
     <li> See the 4096 candidates above. </li>
    </ol>
   </li>
  </ul>

*/

