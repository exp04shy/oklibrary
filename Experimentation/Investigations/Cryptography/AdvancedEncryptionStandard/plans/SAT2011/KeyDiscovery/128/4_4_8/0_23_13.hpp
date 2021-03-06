// Matthew Gwynne, 15.2.2011 (Swansea)
/* Copyright 2011 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Investigations/Cryptography/AdvancedEncryptionStandard/plans/SAT2011/KeyDiscovery/128/4_4_8/0_23_13.hpp
  \brief Investigations into AES key discovery for one round AES without MixColumns (0+2/3+1/3)


  \todo Show and explain sizes of minimum-translations
  <ul>
   <li> To show the "minimum-size" translation, its sizes need to be discussed
   everywhere. </li>
   <li> This must include explanations of the numbers of different boxes and
   their contributions to the overall size (explained, in each case). </li>
  </ul>


  \todo Problem specification
  <ul>
   <li> In this file, we collect the investigations into translations of
   0 + 2/3 + 1/3 round small scale AES with four rows, two columns, using the
   8-bit field size. </li>
   <li> The AES encryption scheme we model takes a 128-bit plaintext and
   128-bit key and outputs a 128-bit ciphertext. The plaintext, key and 
   ciphertext are all considered, column by column, as 4x4 matrices of 8-bit 
   elements. </li>
   <li> In other words, in the AES blocks (plaintext, key, ciphertext etc), 
   the 8-bit element at position (i,j) in the matrix is the ((i-1)*4 + j)-th 
   8-bit word of the 128-bits. </li>
   <li> The 8-bit element (b_0,b_1,b_2,b_3,b_4,b_5,b_6,b_7) is considered as 
   the polynomial b_0 * x^7 + b_1 * x^6 + b_2 * x^5 + b_4 * x^3 + b_5 * x^2 + 
   b^6 * x + b_7. Addition and multiplication on these polynomials is defined
   as usual, modulo the polynomial x^8+x^4+x^3+x+1. </li>
   <li> The encryption scheme applies the following operations:
   <ol>
    <li> Addition of round key 0 (input key) to plaintext. </li>
    <li> Application of SubBytes (Sbox to each 8-bit element) operation. </li>
    <li> A shift of row i by i-1 to the left for all i from 1 to the number of
    rows. </li>
    <li> Addition of round key 1, resulting in the ciphertext. </li>
   </ol>
   </li>
   <li> The Sbox is non-linear permutation over the set of 8-bit elements,
   defined as inversion within the 8-bit field composed with an affine
   transformation. </li>
  </ul>


  \todo Using the canonical box translation
  <ul>
   <li> Translating the AES cipher treating Sboxes and field multiplications 
   as whole boxes and translating these boxes using the canonical translation.
   </li>
   <li> Generating AES-instance for 0 + 2/3 + 1/3 round:
   \verbatim
num_rounds : 1;
num_columns : 4;
num_rows : 4;
exp : 8;
final_round_b : true;
box_tran : aes_ts_box;
seed : 1;
mc_tran : aes_mc_bidirectional;
output_ss_fcl_std(num_rounds, num_columns, num_rows, exp, final_round_b, box_tran, mc_tran);

shell> cat ssaes_r1_c4_rw4_e8_f1.cnf | ExtendedDimacsFullStatistics-O3-DNDEBUG n
 n non_taut_c red_l taut_c orig_l comment_count finished_bool
5928 88636 260776 0 260776 5929 1
 length count
1 8
2 81920
3 1504
4 64
17 5120
256 20
   \endverbatim
   </li>
   <li> In this translation, we have:
   <ul>
    <li> One special round (Key Addition, SubBytes, and ShiftRows).
    </li>
    <li> 16 Sboxes in the SubBytes operation (4 rows * 4 columns = 16). </li>
    <li> 256 additions within the round and key additions, coming from:
     <ul>
      <li> 256 additions from key additions 
      (2 round keys * 128-bit additions = 256). </li>
     </ul>
    </li>
    <li> 4 Sboxes in the AES key schedule (4 rows). </li>
    <li> 128 additions in the key schedule:
    <ul>
     <li> 8 additions of arity three 
     (1 row * 1 column * 8 bits = 8). </li>
     <li> 120 additions of arity two 
     ((3 rows * 4 columns + 1 rows * 3 columns) * 8 bits = 120). </li>
    </ul>
    </li>
    <li> 8 bits for the constant in the key schedule. </li>
   </ul>
   </li>
   <li> The number of clauses of each length in the translation, computed by:
   \verbatim
maxima> ncl_list_ss(1,4,4,8,true,aes_ts_box,aes_mc_bidirectional);
[[1,8],[2,81920],[3,1504],[4,64],[17,5120],[256,20]]
maxima> ncl_list_ss_gen(1,4,4,8,ss_mixcolumns_matrix(2,8,4),[[2,'s2],[9,'s9],[16,'s16]],[],true,aes_mc_bidirectional);
[[1,8],[2,20*s2],[3,1504],[4,64],[9,20*s9],[16,20*s16]]
maxima> ncl_list_full_dualts(16,256);
[[2,4096],[17,256],[256,1]]
   \endverbatim
   are comprised of:
   <ul>
    <li> 8 unit clauses for the 8-bit constant in the key expansion. </li>
    <li> 81920 binary clauses, coming from 20 Sboxes 
    (20 * 4096 = 81920). </li>
    <li> 1504 ternary clauses, coming from 376 additions of arity two
    (376 * 4 = 1504). </li>
    <li> 64 clauses of length four, coming from 8 additions of arity three
    (8 * 8 = 64). </li>
    <li> 5120 clauses of length seventeen, coming from 20 Sboxes
    (20 * 256 = 5120). </li>
    <li> 20 clauses of length 256, coming from from 20 Sboxes
    (20 * 1 = 20). </li>
   </ul>
   </li>
   <li> Then we generate a random assignment with the plaintext and 
   ciphertext, leaving the key unknown:
   \verbatim
output_ss_random_pc_pair(seed,num_rounds,num_columns,num_rows,exp,final_round_b);

> cat ssaes_pcpair_r1_c4_rw4_e8_f1_s1.cnf | ExtendedDimacsFullStatistics-O3-DNDEBUG 
 n non_taut_c red_l taut_c orig_l comment_count finished_bool
256 256 256 0 256 1 1
 length count
1 256
   \endverbatim
   </li>
   <li> Finally we merge the assignment with the basic instance:
   \verbatim
shell> AppendDimacs-O3-DNDEBUG ssaes_r1_c4_rw4_e8_f1.cnf ssaes_pcpair_r1_c4_rw4_e8_f1_s1.cnf > ssaes_r1_c4_rw4_e8_f1_keyfind.cnf
    \endverbatim
   </li>
   <li> Overall, most of the solvers in the OKlibrary solve the problem in
   either < 30s or < 6m. </li>
   <li> Using the OKsolver:
   \verbatim
shell> OKsolver_2002-O3-DNDEBUG -D15 -M ssaes_r1_c4_rw4_e8_f1_keyfind.cnf
s SATISFIABLE
c sat_status                            1
c initial_maximal_clause_length         256
c initial_number_of_variables           5928
c initial_number_of_clauses             88892
c initial_number_of_literal_occurrences 261032
c number_of_initial_unit-eliminations   264
c reddiff_maximal_clause_length         0
c reddiff_number_of_variables           264
c reddiff_number_of_clauses             808
c reddiff_number_of_literal_occurrences 2472
c number_of_2-clauses_after_reduction   82432
c running_time(sec)                     362.9
c number_of_nodes                       646
c number_of_single_nodes                1
c number_of_quasi_single_nodes          0
c number_of_2-reductions                120548
c number_of_pure_literals               0
c number_of_autarkies                   0
c number_of_missed_single_nodes         0
c max_tree_depth                        14
c number_of_table_enlargements          0
c number_of_1-autarkies                 0
c number_of_new_2-clauses               0
c maximal_number_of_added_2-clauses     0
c file_name                             ssaes_r1_c4_rw4_e8_f1_keyfind.cnf
   \endverbatim
   </li>
   <li> Using precosat236:
   \verbatim
shell> precosat236 ssaes_r1_c4_rw4_e8_f1_keyfind.cnf
   \endverbatim
   returns the correct result in 5.2 seconds.
   </li>
   <li> Glucose finishes in 131.55 seconds:
   \verbatim
shell> precosat236 ssaes_r1_c4_rw4_e8_f1_keyfind.cnf
c restarts              : 721
c nb ReduceDB           : 14
c nb learnts DL2        : 5363
c nb learnts size 2     : 4463
c nb learnts size 1     : 55
c conflicts             : 402591         (3060 /sec)
c decisions             : 1562100        (1.58 % random) (11875 /sec)
c propagations          : 57405015       (436374 /sec)
c conflict literals     : 91153560       (39.04 % deleted)
c Memory used           : 66.94 MB
c CPU time              : 131.55 s
   \endverbatim
   </li>
   <li> MiniSAT-2.2.0 finishes in 60s:
   \verbatim
shell> minisat-2.2.0 test_keyfind.cnf
<snip>
restarts              : 382
conflicts             : 143515         (2413 /sec)
decisions             : 801345         (0.00 % random) (13473 /sec)
propagations          : 25615653       (430660 /sec)
conflict literals     : 40285635       (26.74 % deleted)
Memory used           : 295.00 MB
CPU time              : 59.48 s

shell> minisat2 ssaes_r1_c4_rw4_e8_f1_keyfind.cnf
Verified 87756 original clauses.
Verified 1128 eliminated clauses.
restarts              : 13
conflicts             : 33963          (346 /sec)
decisions             : 214258         (1.39 % random) (2181 /sec)
propagations          : 5270395        (53637 /sec)
conflict literals     : 9386723        (16.92 % deleted)
Memory used           : 66.55 MB
CPU time              : 98.26 s
  \endverbatim
  </li>
  <li> march_pl solves it in 19.92s:
  \verbatim
shell> march_pl ssaes_r1_c4_rw4_e8_f1_keyfind.cnf
c main():: nodeCount: 5
c main():: dead ends in main: 0
c main():: lookAheadCount: 133012
c main():: unitResolveCount: 5664
c main():: time=19.920000
c main():: necessary_assignments: 364
c main():: bin_sat: 0, bin_unsat 0
c main():: doublelook: #: 410, succes #: 369
c main():: doublelook: overall 0.313 of all possible doublelooks executed
c main():: doublelook: succesrate: 90.000, average DL_trigger: 172.997
c main():: SOLUTION VERIFIED :-)
   \endverbatim
   It apparently does this in only 5 nodes??!?
   </li>
   <li> Picosat solves it in 18 seconds:
   \verbatim
shell> picosat913 ssaes_r1_c4_rw4_e8_f1_keyfind.cnf
c 29 iterations
c 439 restarts
c 0 failed literals
c 94325 conflicts
c 783798 decisions
c 293 fixed variables
c 30468079 learned literals
c 18.6% deleted literals
c 35170202 propagations
c 100.0% variables used
c 17.7 seconds in library
c 2.0 megaprops/second
c 13 simplifications
c 15 reductions
c 109.4 MB recycled
c 18.9 MB maximally allocated
c 17.7 seconds total run time
   \endverbatim
   </li>
   <li> survey_propagation doesn't converge:
   \verbatim
shell> survey_propagation ssaes_r1_c4_rw4_e8_f1_keyfind.cnf
<snip>
fixed 1 biased var (+49 ucp)
.:-)
<bias>:-nan
fixed 1 biased var (+17 ucp)
.:-)
<bias>:-nan
contradiction
   \endverbatim
   </li>
   <li> Grasp says "RESOURCES EXCEEDED":
   \verbatim
shell> sat-grasp ssaes_r1_c4_rw4_e8_f1_keyfind.cnf
Registering switches
	Done creating structures. Elapsed time: 0.12
	Done searching.... RESOURCES EXCEEDED. Elapsed time: 2256.6
   \endverbatim
   </li>
   <li> With "seed : 2$" and "seed : 3$", these runtimes and statistics
   seem stable. </li>
   <li> DONE (merge_cnf.sh replaced with AppendDimacs)
   Finally we merge the assignment with the basic instance:
   \verbatim
shell> $OKlib/Experimentation/Investigations/Cryptography/AdvancedEncryptionStandard/merge_cnf.sh ssaes_r1_c4_rw4_e8_f1.cnf ssaes_pcpair_r1_c4_rw4_e8_f1_s1.cnf > ssaes_r1_c4_rw4_e8_f1_keyfind.cnf

> cat ssaes_r1_c4_rw4_e8_f1_keyfind.cnf | ExtendedDimacsFullStatistics-O3-DNDEBUG 
terminate called after throwing an instance of 'OKlib::InputOutput::ClauseInputError'
  what():  OKlib::InputOutput::StandardDIMACSInput::read_clauses:
  literal 5929 has variable index larger than the specified upper bound 5928
line 94566, column 2, total characters read 21231687
   \endverbatim
   </li>
  </ul>


  \bug DONE (merging now handled by AppendDimacs)
  Merging deficient
  <ul>
   <li> See below for error-report. </li>
   <li> This merging-tool shouldn't exist in this form; see
   "Elementary file-surgery" in
   Interfaces/InputOutput/plans/general.hpp. </li>
   <li> There is now a specific C++ application for this with
   tests. See "AppendDimacs". </li>
   <li> The plans files must be updated to use "AppendDimacs"
   instead of this merge script. </li>
  </ul>


  \todo DONE Problems sizes
  <ul>
   <li> For each such file, we need the complete information about the instance
   sizes. </li>
   <li> Both measured, and as a result of general formulas. </li>
  </ul>

*/
