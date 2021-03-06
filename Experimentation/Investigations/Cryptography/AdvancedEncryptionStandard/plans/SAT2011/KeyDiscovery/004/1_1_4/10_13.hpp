// Matthew Gwynne, 15.2.2011 (Swansea)
/* Copyright 2011 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Investigations/Cryptography/AdvancedEncryptionStandard/plans/SAT2011/KeyDiscovery/004/1_1_4/10_13.hpp
  \brief Investigations into simplest small scale AES key discovery for ten rounds AES with MixColumns


  \todo Explain sizes
  <ul>
   <li> Here and everywhere else we need precise explanations why we have so
   and so many variables and clauses. </li>
  </ul>


  \todo Problem specification
  <ul>
   <li> In this file, we collect the investigations into translations of
   10 + 1/3 round small scale AES with one rows, one columns, using the 4-bit
   field size. </li>
   <li> The AES encryption scheme we model takes a 4-bit plaintext and
   4-bit key and outputs a 4-bit ciphertext. 
   </li>
   <li> The 4-bit element (b_0,b_1,b_2,b_3) is considered as the polynomial
   b_0 * x^3 + b_1 * x^2 + b_2 * x + b_3. Addition and multiplication
   on these polynomials is defined as usual, modulo the polynomial x^4+x+1. 
   </li>
   <li> The encryption scheme applies the following operations:
   <ol>
    <li> Key schedule which takes the key and generates eleven 4-bit round 
    keys. </li>
    <li> Application of the following operation (the "round") ten times:
     <ol>
      <li> Addition of round key n-1. </li>
      <li> Application of Sbox operation. </li>
     </ol>
    </li>
    <li> Addition of round key n. </li>
    <li> The result of the last round key addition is then the ciphertext. 
    </li>
   </ol>
   </li>
   <li> The Sbox is non-linear permutation over the set of 4-bit elements,
   defined as inversion within the 4-bit field composed with an affine
   transformation. </li>
  </ul>


  \todo Using the canonical translation
  <ul>
   <li> Generating simplest small scale AES for 10 rounds (with MixColumns):
   \verbatim
num_rounds : 10$
num_columns : 1$
num_rows : 1$
exp : 4$
final_round_b : false$
box_tran : aes_ts_box$
seed : 1$
mc_tran : aes_mc_bidirectional$
output_ss_fcl_std(num_rounds, num_columns, num_rows, exp, final_round_b, box_tran, mc_tran)$

shell> cat ssaes_r10_c1_rw1_e4_f0.cnf | ExtendedDimacsFullStatistics-O3-DNDEBUG n
 n non_taut_c red_l taut_c orig_l comment_count finished_bool
572 3436 9688 0 9688 573 1
 length count
1 40
2 2720
3 336
9 320
16 20
   \endverbatim
   </li>
   <li> In this translation, we have:
   <ul>
    <li> Ten full rounds (Key Addition, SubBytes, and diffusion operation).
    </li>
    <li> 10 Sboxes in the SubBytes operation 
    (1 rows * 1 columns * 10 rounds = 10). </li>
    <li> 124 additions within the round and key additions, coming from:
     <ul>
      <li> 44 additions of arity 2 from key additions 
      (11 round keys * 4-bit additions = 44). </li>
      <li> 80 additions of arity one from the identity matrix multiplication
      in the diffusion operation 
      (1 rows * 1 columns * 2 directions * 4 bits * 10 rounds = 80).
      </li>
     </ul>
    </li>
    <li> 10 Sboxes in the AES key schedule 
    (1 rows * 10 rounds = 10). </li>
    <li> 40 additions in the key schedule:
    <ul>
     <li> 40 additions of arity two
     (1 row * 1 column * 4 bits * 10 rounds = 40). </li>
    </ul>
    </li>
    <li> 40 bits for the constant in the key schedule
    (4 bits * 10 rounds = 40).
    </li>
   </ul>
   </li>
   <li> The number of clauses of each length in the translation, computed by:
   \verbatim
maxima> ncl_list_ss(10,1,1,4,false,aes_ts_box,aes_mc_bidirectional);
[[1,40],[2,2720],[3,336],[9,320],[16,20]]
maxima> ncl_list_ss_gen(10,1,1,4,ss_mixcolumns_matrix(2,4,1),[[2,'s2],[9,'s9],[16,'s16]],[],false,aes_mc_bidirectional);
[[1,40],[2,20*s2+160],[3,336],[9,20*s9],[16,20*s16]]
maxima> ncl_list_full_dualts(8,16);
[[2,128],[9,16],[16,1]]
   \endverbatim
   are comprised of:
   <ul>
    <li> 40 unit clauses for the 4-bit constant in the key expansion. </li>
    <li> 2720 binary clauses, coming from 20 Sboxes and 80 additions of arity
    one (20 * 128 + 80 * 2 = 2720). </li>
    <li> 336 ternary clauses, coming from 84 additions of arity two
    (84 * 4 = 336). </li>
    <li> 320 clauses of length nine, coming from 20 Sboxes
    (20 * 16 = 320). </li>
    <li> 20 clauses of length sixteen, coming from from 20 Sboxes
    (20 * 1 = 20). </li>
   </ul>
   </li>
   <li> Then we can generate a random assignment with the plaintext and 
   ciphertext, leaving the key unknown:
   \verbatim
maxima> output_ss_random_pc_pair(seed,num_rounds,num_columns,num_rows,exp,final_round_b);
   \endverbatim
   and the merging the assignment with the translation:
   \verbatim
shell> AppendDimacs-O3-DNDEBUG ssaes_r10_c1_rw1_e4_f0.cnf ssaes_pkpair_r10_c1_rw1_e4_f0_s1.cnf > r10_keyfind.cnf
   \endverbatim
   </li>
   <li> OKsolver solves this with no decisions:
   \verbatim
shell> OKsolver_2002-O3-DNDEBUG r10_keyfind.cnf
s SATISFIABLE
c sat_status                            1
c initial_maximal_clause_length         16
c initial_number_of_variables           572
c initial_number_of_clauses             3444
c initial_number_of_literal_occurrences 9696
c number_of_initial_unit-eliminations   48
c reddiff_maximal_clause_length         0
c reddiff_number_of_variables           48
c reddiff_number_of_clauses             144
c reddiff_number_of_literal_occurrences 432
c number_of_2-clauses_after_reduction   2816
c running_time(sec)                     0.0
c number_of_nodes                       1
c number_of_single_nodes                0
c number_of_quasi_single_nodes          0
c number_of_2-reductions                148
c number_of_pure_literals               0
c number_of_autarkies                   1
c number_of_missed_single_nodes         0
c max_tree_depth                        0
c number_of_table_enlargements          0
c number_of_1-autarkies                 0
c number_of_new_2-clauses               0
c maximal_number_of_added_2-clauses     0
c file_name                             r10_keyfind.cnf
   \endverbatim
   </li>
   <li> However, minisat-2.2.0 and glucose need to branch:
   \verbatim
shell> minisat-2.2.0 r10_keyfind.cnf 
<snip>
restarts              : 1
conflicts             : 22             (inf /sec)
decisions             : 41             (0.00 % random) (inf /sec)
propagations          : 6095           (inf /sec)
conflict literals     : 295            (41.93 % deleted)
Memory used           : 19.00 MB
CPU time              : 0 s

shell> minisat2 r10_keyfind.cnf 
<snip>
restarts              : 1
conflicts             : 29             (1450 /sec)
decisions             : 67             (0.00 % random) (3350 /sec)
propagations          : 5397           (269850 /sec)
conflict literals     : 364            (37.67 % deleted)
Memory used           : 15.18 MB
CPU time              : 0.02 s
shell> glucose r10_keyfind.cnf 
c restarts              : 1
c nb ReduceDB           : 0
c nb learnts DL2        : 15
c nb learnts size 2     : 8
c nb learnts size 1     : 1
c conflicts             : 48             (inf /sec)
c decisions             : 168            (2.38 % random) (inf /sec)
c propagations          : 5738           (inf /sec)
c conflict literals     : 714            (15.40 % deleted)
c Memory used           : 2.00 MB
c CPU time              : 0 s
   \endverbatim
   </li>
   <li> We can check we get the right result with:
   \verbatim
shell> OKsolver_2002-O3-DNDEBUG -O r10_keyfind.cnf | grep "^v" | $OKlib/Experimentation/Investigations/Cryptography/AdvancedEncryptionStandard/validate_aes_assignment 10 1 1 4 0 && echo "VALID"
VALID
   \endverbatim
   </li>
  </ul>


  \todo DONE Update description
  <ul>
   <li> Now the key-addition happens at the beginning of each round. </li>
   <li> This update must be performed here and everywhere else. </li>
  </ul>

*/
