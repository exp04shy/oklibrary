// Oliver Kullmann, 23.3.2011 (Swansea)
/* Copyright 2011 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Experimentation/Investigations/RamseyTheory/VanderWaerdenProblems/plans/5-k/13.hpp
  \brief On investigations into vdw_2(5,13)


  \todo Best complete solver for palindromic problems


  \todo Best local-search solver for palindromic problems


  \todo vdw_2^pd(5,13) >= (1176,1187)
  <ul>
   <li> Certificates:
    <ol>
     <li> n=1175:
     \verbatim
13,14,16,17,18,20,27,30,33,37,
43,45,49,56,58,65,75,76,80,82,
86,87,89,91,92,99,101,102,110,118,
119,120,122,123,125,127,129,135,144,145,
146,149,152,156,157,158,160,161,162,171,
174,182,187,188,189,196,198,200,208,209,
210,214,216,222,226,227,232,237,238,239,
247,248,253,260,262,263,265,267,268,270,
271,277,279,280,286,288,290,295,298,306,
317,324,335,337,338,339,341,345,351,352,
354,355,357,359,361,367,369,370,377,379,
382,389,393,395,401,403,404,406,407,410,
414,415,419,422,424,427,434,436,438,443,
453,454,456,457,460,464,465,472,474,476,
479,484,486,489,492,498,501,504,507,508,
512,525,528,531,533,534,535,536,539,543,
545,546,548,552,553,564,565,567,568,572,
585,586
     \endverbatim
     </li>
     <li> n=1186:
     \verbatim
4,7,10,17,20,24,31,43,44,45,
48,54,61,62,64,68,69,73,79,83,
93,94,95,96,98,99,104,105,107,112,
124,126,129,130,132,134,135,140,142,143,
146,147,148,150,151,152,161,164,174,175,
177,181,193,195,200,202,207,210,212,213,
215,217,218,221,225,238,239,241,242,248,
249,258,259,260,263,265,276,282,285,287,
291,298,299,301,303,304,305,310,312,314,
315,318,320,322,327,333,335,342,348,349,
350,351,355,359,369,373,376,382,383,385,
386,398,404,407,408,409,410,415,418,420,
421,422,423,426,436,437,443,446,454,456,
461,464,465,467,468,471,473,478,479,481,
486,487,490,492,493,494,496,501,505,507,
508,519,528,533,534,536,538,539,540,548,
561,562,565,566,569,571,572,574,579,583,
585,590,591
     \endverbatim
    </ol>
   </li>
   <li> "RunPdVdWk1k2 5 13 adaptg2wsat 100 80000000" yields
   \verbatim
Break point 1: 1176
Break point 2: 1187
   \endverbatim
   using at most 14 runs.
   </li>
   <li> "RunPdVdWk1k2 5 13 adaptg2wsat 100 160000000" yields
   \verbatim
Break point 1: 1154
   \endverbatim
    before being aborted, using at most 79 runs.
   </li>
  </ul>

*/
