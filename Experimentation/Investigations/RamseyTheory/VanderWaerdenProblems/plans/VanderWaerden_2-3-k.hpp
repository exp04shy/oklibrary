// Oliver Kullmann, 10.4.2009 (Swansea)
/* Copyright 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Experimentation/Investigations/RamseyTheory/VanderWaerdenProblems/plans/VanderWaerden_2-3-k.hpp
  \brief On investigations into vdW-numbers vdw_2(3,k)
  
  
  \todo Literature overview
  <ul>
   <li> A conjecture seems to be that vdw_2(3,k) <= k^2 for k >= 3. </li>
   <li> The known values with k=1, ..., 16 are available via
   vanderwaerden3k(k):
   \verbatim
create_list(vanderwaerden3k(k),k,1,17);
 [3,6,9,18,22,32,46,58,77,97,114,135,160,186,218,238,unknown]
   \endverbatim
   </li>
   <li> Via R we get the prediction f(k) ~ 0.8132032 * k^2.0602760 when
   excluding the first 4 points:
   \verbatim
d = c(3,6,9,18,22,32,46,58,77,97,114,135,160,186,218,238)
plot(d)
x = log((1:length(d))[-(1:4)])
y : log(d[-(1:4)])
plot(x,y)
L = lm(y ~ x)
summary(L)
Coefficients:
            Estimate Std. Error t value Pr(>|t|)
(Intercept) -0.20677    0.04173  -4.955 0.000574 ***
x            2.06028    0.01799 114.495  < 2e-16 ***
lines(x,predict(L))
C = coefficients(L)
f = function(k){exp(C[1]) * k^C[2]}
plot(d)
lines(f(1:length(d)))
   \endverbatim
   </li>
  </ul>


  \todo Performance of OKsolver-2002
  <ul>
   <li> k=4, n=17,18: 7 resp. 9 nodes. </li>
   <li> k=5, n=21,22: 6 resp. 19 nodes. </li>
   <li> k=6, n=31,32: 24 resp. 51 nodes. </li>
   <li> k=7, n=45,46: 11 resp. 139 nodes. </li>
   <li> k=8, n=57,58: 109 resp. 479 nodes. </li>
   <li> k=9, n=76,77: 702 resp. 1591 nodes. </li>
   <li> k=10, n=96,97: 129 resp. 10545 nodes. </li>
   <li> k=11, n=113,114:
    <ol>
     <li> 37374 resp. 41563 nodes. </li>
     <li> With minisat2-preprocessor: identical results (so apparently
     the preprocessor does nothing). </li>
    </ol>
   </li>
   <li> k=12, n=134, 135: 283568 resp. 281381 nodes (~ 7 minutes). </li>
   <li> k=13, n=159,160:
   \verbatim
s SATISFIABLE
c sat_status=1 initial_maximal_clause_length=13 initial_number_of_variables=159 initial_number_of_clauses=7216 initial_number_of_literal_occurrences=31398 running_time(s)=4187.7 number_of_nodes=1590137 number_of_single_nodes=0 number_of_quasi_single_nodes=0 number_of_2-reductions=13477703 number_of_pure_literals=455 number_of_autarkies=0 number_of_missed_single_nodes=1 max_tree_depth=43 number_of_table_enlargements=0 reduced_maximal_clause_length=0 reduced_number_of_variables=0 reduced_number_of_clauses=0 reduced_number_of_literal_occurrences=0 number_of_1-autarkies=12836 number_of_initial_unit-eliminations=0 number_of_new_2-clauses=0 maximal_number_of_added_2-clauses=0 initial_number_of_2-clauses=0 file_name=VanDerWaerden_2-3-13_159.cnf
s UNSATISFIABLE
c sat_status=0 initial_maximal_clause_length=13 initial_number_of_variables=160 initial_number_of_clauses=7308 initial_number_of_literal_occurrences=31804 running_time(s)=7514.8 number_of_nodes=2970721 number_of_single_nodes=0 number_of_quasi_single_nodes=0 number_of_2-reductions=25434723 number_of_pure_literals=706 number_of_autarkies=0 number_of_missed_single_nodes=0 max_tree_depth=43 number_of_table_enlargements=0 reduced_maximal_clause_length=0 reduced_number_of_variables=0 reduced_number_of_clauses=0 reduced_number_of_literal_occurrences=0 number_of_1-autarkies=24074 number_of_initial_unit-eliminations=0 number_of_new_2-clauses=0 maximal_number_of_added_2-clauses=0 initial_number_of_2-clauses=0 file_name=VanDerWaerden_2-3-13_160.cnf
   \endverbatim
   </li>
   <li> k=16, n=238: Running it with monitoring level 20 appears hopeless.
   And using the m2pp-variant doesn't make a difference, since the
   preprocessor has no effect. </li>
  </ul>


  \todo Performance of march_pl
  <ul>
   <li> k=13, n=160:
   \verbatim
c main():: nodeCount: 279674
c main():: dead ends in main: 531
c main():: lookAheadCount: 71792373
c main():: unitResolveCount: 1830566
c main():: time=5111.450195
   \endverbatim
   </li>
  </ul>


  \todo Performance of satz215
  <ul>
   <li> k=13, n=160:
   \verbatim
> satz215 VanDerWaerden_2-3-13_160.cnf
****the instance is unsatisfiable *****
NB_MONO= 316, NB_UNIT= 38903958, NB_BRANCHE= 1699870, NB_BACK= 864253
Program terminated in 1308.930 seconds.
satz215 VanDerWaerden_2-3-13_160.cnf 1308.930 1699870 864253 214884364 8337569 0 160 7308 0 3878431 1563013
   \endverbatim
   So satz215 seems best-performing here.
   </li>
   <li> k=14, n=186:
   \verbatim
****the instance is unsatisfiable *****
NB_MONO= 1011, NB_UNIT= 275097539, NB_BRANCHE= 10842443, NB_BACK= 5511751
Program terminated in 11507.900 seconds.
satz215 VanDerWaerden_2-3-14_186.cnf 11507.900 10842443 5511751 1544946578 56724610 0 186 9795 0 26796344 10549534
   \endverbatim
   </li>
   <li> k=15, n=218:
   \verbatim
****the instance is unsatisfiable *****
NB_MONO= 2544, NB_UNIT= 1879235364, NB_BRANCHE= 66642611, NB_BACK= 33796681
Program terminated in 99407.850 seconds.
satz215 VanDerWaerden_2-3-15_218.cnf 99407.850 66642611 33796681 10812633494 373672422 0 218 13362 0 305553394 82352337
   \endverbatim
   </li>
   <li> k=16, n=238:
   \verbatim
****the instance is unsatisfiable *****
NB_MONO= 62751, NB_UNIT= 17632939133, NB_BRANCHE= 600383827, NB_BACK= 304409259
Program terminated in 990144.910 seconds.
satz215 VanDerWaerden_2-3-16_238.cnf 990144.910 600383827 304409259 99369777769 3501709276 0 238 15812 0 3305729737 824297599
   \endverbatim
   Stably a factor of 10. So with some parallelisation k=17 should be feasible
   (the unsatisfiable case; around 3 months on a single processor). </li>
  </ul>


  \todo Performance of minisat2
  <ul>
   <li> k=13, n=160: 19681930 conflicts, 19 restarts (4500s). </li>
   <li> k=16, n=238: Apparently after 30 restarts and 36906145 conflicts
   no progress was made. </li>
  </ul>


  \todo Local search for the satisfiable instances
  <ul>
   <li> The first impression is that ubcsat::samd is best. </li>
   <li> For k=16, n=237 a local minimum of 1 is easily found (even with just
   100000 steps), while to find a solution one should use, say, 10^7 steps
   (and then solutions seem to be found often, e.g., seed=370833091). </li>
  </ul>

*/

