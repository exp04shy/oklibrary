// Oliver Kullmann, 26.9.2008 (Swansea)
/* Copyright 2008, 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Experimentation/Investigations/RamseyTheory/GreenTaoProblems/plans/AdditiveNumberTheory.hpp
  \brief On investigations into additive number theory
  
  
  \todo The distribution of arithmetic progressions amongst primes
  <ul>
   <li> The task is to find a nice (thus very likely approximated) law for
   the values in the list ln_arithprog_primes_c(k,n) (see
   ComputerAlgebra/NumberTheory/Lisp/PrimeNumbers.mac) for fixed k >= 1. </li>
   <li> Ploted via %e.g.
   \verbatim
plot2d([discrete,create_list(i,i,1,1000),ln_arithprog_primes_c(3,1000)]);
   \endverbatim
   </li>
   <li> For k = 1,2 this is trivial. </li>
   <li> For k >= 3 regression is to be performed; most powerful is using R,
   but for initial considerations also simple_linear_regression (use
   'load("stats")') can be used. </li>
   <li> There are role models for the regression function in the literature.
   </li>
   <li> One can also consider n_arithprog_primes_nc[k,n] (the non-cumulative
   data, i.e., as list the difference list of the above list):
   \verbatim
plot2d([discrete,create_list(i,i,1,1000),create_list(n_arithprog_primes_nc[3,n],n,1,1000)]);
   \endverbatim
   Though it seems that the accumulated data is easier to handle (since being
   smoother). </li>
   <li> Perhaps it is more appropriate to consider only changes here, that
   is, skipping n-values where no new arithmetic progression is added).
   This is plotted in non-cumulative resp. cumulative form by
   \verbatim
plot2d([discrete, sizes_strata_indmon_ohg(arithprog_primes_ohg(3,1000))]);
plot2d([discrete, sizes_cstrata_indmon_ohg(arithprog_primes_ohg(3,1000))]);
   \endverbatim
   </li>
   <li> Using Applications/RamseyTheory/CountProgressions_GreenTao.cpp
   and non-linear regression in R:
   \verbatim
> f = fit_greentao(3,10000)
Number of observations (changes) =  9995
Max nhyp =  3091531
Non-linear model nhyp = a * n^b:
         a          b
0.08330711 1.89230541
Residual range:  -1936.854 1003.250
   \endverbatim
   So f_3(n) = 0.08330711 * n^1.89230541 seems to be a good model. </li>
   <li> For N=100000 we need a C++ program which doesn't store the
   progressions. For N=30000 we obtain:
   \verbatim
> f = fit_greentao(3,30000)
Number of observations (changes) =  29995
Max nhyp =  25000740
Non-linear model nhyp = a * n^b:
         a          b
0.07487019 1.90377210
Residual range:  -12970.68 6619.329
   \endverbatim
   so f_3'(n) = 0.07487019 * n^1.90377210. We should consider larger n. </li>
   <li> For k=4:
   \verbatim
> f = fit_greentao(4,20000)
Number of observations (changes) =  19975
Max nhyp =  1462656
Non-linear model nhyp = a * n^b:
         a          b
0.02662577 1.79946138
Residual range:  -1194.638 1049.931

> f = fit_greentao(4,40000)
Number of observations (changes) =  39975
Max nhyp =  5148933
Non-linear model nhyp = a * n^b:
         a          b
0.02317292 1.81359675
Residual range:  -5417.02 3489.321
   \endverbatim
   So f_4(n) = 0.02317292 * n^1.81359675 is a good model (for n <= 40000).
   </li>
   <li> For k=5:
   \verbatim
> f = fit_greentao(5,40000)
Number of observations (changes) =  39346
Max nhyp =  462281
Non-linear model nhyp = a * n^b:
          a           b
0.005413189 1.723282665
Residual range:  -855.3122 516.4819

> f = fit_greentao(5,80000)
Number of observations (changes) =  79346
Max nhyp =  1545856
Non-linear model nhyp = a * n^b:
          a           b
0.004561643 1.739623162
Residual range:  -1959.498 1117.054
   \endverbatim
   So f_5(n) = 0.004561643 * n^1.739623162 is a good model (for n <= 80000).
   </li>
   <li> For k=6:
   \verbatim
> f = fit_greentao(6,80000)
Number of observations (changes) =  70976
Max nhyp =  234774
Non-linear model nhyp = a * n^b:
          a           b
0.001841092 1.653029200
Residual range:  -360.6184 351.3982

80000 - 70976
  9024

> f = fit_greentao(6,160000)
Number of observations (changes) =  150810
Max nhyp =  749499
Non-linear model nhyp = a * n^b:
          a           b
0.001491893 1.671835433
Residual range:  -1185.398 669.2617

160000 - 150810
  9190
   \endverbatim
   So f_6(n) = 0.001491893 * n^1.671835433 is a good model (for n <= 160000).
   </li>
   <li> For k=7:
   \verbatim
> f = fit_greentao(7,160000)
Number of observations (changes) =  59909
Max nhyp =  78058
Non-linear model nhyp = a * n^b:
           a            b
0.0003991339 1.5930359517
Residual range:  -200.6960 197.7186

160000 -  59909
  100091

> f = fit_greentao(7,500000)
Number of observations (changes) =  298388
Max nhyp =  497046
Non-linear model nhyp = a * n^b:
           a            b
0.0002711559 1.6253012589
Residual range:  -730.2256 322.508

500000 - 298388
  201612

> f = fit_greentao(7,1000000)
Number of observations (changes) =  736449
Max nhyp =  1558942
Non-linear model nhyp = a * n^b:
           a            b
0.0002054541 1.6465780527
Residual range:  -2338.546 1748.609

1000000 -  736449
  263551
   \endverbatim
   So f_7(n) = 0.0002054541 * n^1.6465780527 is a good model
   (for n <= 1000000). </li>
   <li> For k=8:
   \verbatim
> f = fit_greentao(8,1000000)
Number of observations (changes) =  230866
Max nhyp =  268082
Non-linear model nhyp = a * n^b:
           a            b
0.0001012130 1.5703794794
Residual range:  -478.4431 327.3195

1000000 - 230866
  769134

> f = fit_greentao(8,2000000)
Number of observations (changes) =  649644
Max nhyp =  812685
Non-linear model nhyp = a * n^b:
           a            b
6.999855e-05 1.597307e+00
Residual range:  -1618.485 1040.744

2000000 - 649644
  1350356

> f = fit_greentao(8,4000000)
Number of observations (changes) =  1781803
Max nhyp =  2491439
Non-linear model nhyp = a * n^b:
           a            b
5.514205e-05 1.613797e+00
Residual range:  -3534.482 2613.697

4000000 -  1781803
  2218197

> f = fit_greentao(8,8000000)
Number of observations (changes) =  4688545
Max nhyp =  7728990
Non-linear model nhyp = a * n^b:
           a            b
4.218958e-05 1.631506e+00
Residual range:  -10123.48 6262.802

8000000 - 4688545
  3311455
   \endverbatim
   So f_8(n) = 4.218958e-05 * n^1.631506 is a good model
   (for n <= 8*10^6). </li>
   <li> A natural conjecture here is that for every k there exists some
   index i_k >= 1 such that for every j >= i_k there exists an arithmetic
   progression of length k ending with p_j. For k <= 5 we can already
   conjecture the smallest such i_k, and this should also be possible for
   k=6, while then it becomes more difficult. </li>
   <li> One can consider the densities
   ln_arithprog_primes_c(k,n) / create_list(i,i,1,n). </li>
   <li> Hard to believe that there is nothing in the literature / on the
   Internet: We should enter for example ln_arithprog_primes_c(3,30) =
   [0,0,0,1,2,2,3,5,7,9,11,11,13,16,17,20,23,24,26,30,32,36,40,44,46,49,53,56,59,64]
   into that database of integer sequences and see whether there is information
   in it. </li>
   <li> Yes, this sequence is A125505 in
   http://www.research.att.com/~njas/sequences/Seis.html. </li>
   <li> There it is only listed for n=64; this we can easily extend, and
   perhaps we should do so. </li>
   <li> And apparently for k >= 4 there is nothing entered there --- we
   should change this.
    <ol>
     <li> Say, up to k=10. </li>
     <li> For k=10 for example the first 315 values are 0, and then
     at least until index 3000 the value is constant 1; for such sequences
     we need a compressed representation. </li>
    </ol>
   </li>
   <li> Of interest is also
   http://www.research.att.com/~njas/sequences/Sindx_Pri.html#primes_AP
   which gives an overview. It contains for given k the smallest starting
   term, smallest difference and smallest end term for arithmetical
   progressions of primes of length k. However I do not understand
   these sequences (strange explanations). </li>
  </ul>


  \todo Finding the first arithmetic progression
  <ul>
   <li> What seems very natural to me is k -> how many first primes are
   needed to get an progression of length k; this is greentao_1(k). </li>
   <li> See http://users.cybercity.dk/~dsl522332/math/aprecords.htm for
   current information around this subject; the related sequence is (now
   showing p_i instead of i):
   \verbatim
L : [
2, 3, 7, 23, 29, 157, 907, 1669, 1879, 2089, 
249037, 262897, 725663, 36850999, 173471351, 198793279, 4827507229, 17010526363, 83547839407, 572945039351,
6269243827111
];
   \endverbatim
   </li>
   <li> This is available as A005115. </li>
   <li> From this sequence S via map(rank_primes,S) we obtain the sequence:
   \verbatim
for p in L do print(rank_primes(p));
1,2,4,9,10,37,155,263,289,316,
21966,23060,58464,2253121,9686320,11015837,227225515,755752809,3466256932,22009064470,
220525414079
   \endverbatim
   where starting with k=12 actually "RankPrimes" was used. </li>
   <li> Plot the data (using R) suggests that (log,log(log))-transformation
   for (x,y) might be appropriate (that is, a model y = exp(a * x^b)):
   \verbatim
y = c(4,9,10,37,155,263,289,316,21966,23060,58464,2253121,9686320,11015837,227225515,755752809,3466256932,22009064470,220525414079)
x = 3:21
plot(log(x),log(log(y)))

m0 = lm(log(log(y)) ~ log(x))
summary(m0)
            Estimate Std. Error t value Pr(>|t|)
(Intercept) -1.48793    0.11902  -12.50 5.37e-10 ***
log(x)       1.54569    0.04925   31.38  < 2e-16 ***
Residual standard error: 0.1191 on 17 degrees of freedom
Multiple R-squared: 0.983,      Adjusted R-squared: 0.982
F-statistic: 984.9 on 1 and 17 DF,  p-value: < 2.2e-16

exp(coefficients(m0)[1])
0.2258395
coefficients(m0)[2]
1.545693
s = c(a = 0.2258395, b = 1.545693)
m = nls(y ~ exp(a * x^b), start = s)

summary(m)
  Estimate Std. Error t value Pr(>|t|)
a 0.084184   0.002663   31.61   <2e-16 ***
b 1.884508   0.010393  181.32   <2e-16 ***
Residual standard error: 273300000 on 17 degrees of freedom
Number of iterations to convergence: 18
Achieved convergence tolerance: 7.111e-06

plot(x,log(y))
lines(x,log(predict(m)))
lines(x,exp(predict(m0)))
   \endverbatim
   </li>
  </ul>


  \todo The first arithmetic progression allowing a missing number
  <ul>
   <li> greentao_2(2,k) has still a "mostly number theoretical touch". </li>
   <li> greentao_2(2,0) = 0, greentao_2(2,1) = 2, greentao(2,2) = 3. </li>
   <li> greentao_2(2,3) = 7. </li>
   <li> greentao_2(2,4) = 14. </li>
   <li> greentao_2(2,5) = 31. </li>
   <li> This sequence is apparently not in that "online encyclopedia" (also
   not after applying unrank_primes to it, obtaining [3,5,17,43,127]). </li>
  </ul>

*/

