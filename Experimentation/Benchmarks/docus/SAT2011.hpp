// Oliver Kullmann, 26.2.2011 (Swansea)
/* Copyright 2011 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Experimentation/Benchmarks/docus/SAT2011.hpp
  \brief Benchmark packages provided for SAT 2011


  <h1> Van der Waerden instances </h1>

  General information:
  <ul>
   <li> Two generators:
    <ol>
     <li> <code>VanderWaerdenCNF-O3-DNDEBUG</code>
     (Satisfiability/Transformers/Generators/VanderWaerdenCNF.cpp) </li>
     <li> Creates ordinary vdW-instances, encoding "vdw_2(k1,k2) > n"
     (satisfiable iff the answer is yes). </li>
     <li> <code>PdVanderWaerdenCNF-O3-DNDEBUG</code>
     (Satisfiability/Transformers/Generators/PdVanderWaerdenCNF.cpp) </li>
     <li> Creates palindromic vdW-instances, encoding "vdw_2^pd(k1,k2) > n"
     (satisfiable iff the answer is yes). </li>
    </ol>
   </li>
   <li> These generators-executables, statically linked, are created by
   \verbatim
OKlib/Satisfiability/Transformers/Generators> oklib cleanall
OKlib/Satisfiability/Transformers/Generators> LDFLAGS="-static" oklib all
   \endverbatim
   and then copied from <code>OKplatform/system_directories/bin</code>.
   </li>
   <li> The Git-ID of the relevant state of the OKlibrary is
   \verbatim
9fc269649716c7a848878fe58edfbdadf11faff0
   \endverbatim
   </li>
   <li> The package-template is given by the directory
   <code>OKlib/Experimentation/Benchmarks/SAT2011_VanDerWaerden</code>. </li>
   <li> The "empty" package (the template-directory, without the instances,
   but with the generator-executables added) has md5sum
   \verbatim
fcb95d587988f266b17bd2727afffe38  SAT2011_VanDerWaerden_Empty.tar.bz2
   \endverbatim
   and 4,572,689 bytes.
   </li>
   <li> Created by
   \verbatim
OKlib/Experimentation/Benchmarks> tar -cjf SAT2011_VanDerWaerden_Empty.tar.bz2 SAT2011_VanDerWaerden
   \endverbatim
   </li>
   <li> Extracting this archive (by
   <code>tar -xjf SAT2011_VanDerWaerden_Empty.tar.bz2</code>) yields directory
   <code>SAT2011_VanDerWaerden</code>. </li>
   <li> The "full" package (additionally with the instances) has md5sum
   \verbatim
3a37725576bacb61b0b25d3adeb475df  SAT2011_VanDerWaerden.tar.bz2
   \endverbatim
   and size 42,306,960 bytes.
   </li>
   <li> Created by
   \verbatim
OKlib/Experimentation/Benchmarks> tar -cjf SAT2011_VanDerWaerden.tar.bz2 SAT2011_VanDerWaerden
   \endverbatim
   </li>
   <li> From the "empty" package the "full" package is created by running
   <code>./Create</code> in the (extracted) directory
   <code>SAT2011_VanDerWaerden</code>.
    <ol>
     <li> This script prints "SUCCESS" and returns code 0 if no error occurred.
     </li>
     <li> This includes checking of the md5sums of the two generators and all
     the benchmark files. </li>
    </ol>
   </li>
  </ul>


  <h1> Green-Tao instances </h1>

  General information:
  <ul>
   <li> One generator:
    <ol>
     <li> <code>GreenTaoCNF-O3-DNDEBUG</code>
     (Satisfiability/Transformers/Generators/GreenTaoCNF.cpp) </li>
     <li> Creates gt-instances, encoding "grt_2(k1,k2) > n"
     (satisfiable iff the answer is yes). </li>
     <li> <code>GTSat</code> is a wrapper script, which in general allows
     also to create problems using more than two colours, however this
     functionality is not available for this copy. </li>
    </ol>
   </li>
   <li> The generator-executable, statically linked, is created by
   \verbatim
OKlib/Satisfiability/Transformers/Generators> oklib cleanall
OKlib/Satisfiability/Transformers/Generators> LDFLAGS="-static" oklib all
   \endverbatim
   and then copied from <code>OKplatform/system_directories/bin</code>.
   </li>
   <li> The Git-ID of the relevant state of the OKlibrary is
   \verbatim
080a2210bf3c195fc91ab489de2640559b089f44
   \endverbatim
   </li>
   <li> The package-template is given by the directory
   <code>OKlib/Experimentation/Benchmarks/SAT2011_GreenTao</code>. </li>
   <li> The "empty" package (the template-directory, without the instances,
   but with the generator-executables added) has md5sum
   \verbatim
86073975e019fbce96a0f5bfa80a3b2a  SAT2011_GreenTao_Empty.tar.bz2
   \endverbatim
   and 2,372,999 bytes.
   </li>
   <li> Created by
   \verbatim
OKlib/Experimentation/Benchmarks> tar -cjf SAT2011_GreenTao_Empty.tar.bz2 SAT2011_GreenTao
   \endverbatim
   </li>
   <li> Extracting this archive (by
   <code>tar -xjf SAT2011_GreenTao_Empty.tar.bz2</code>) yields directory
   <code>SAT2011_GreenTao</code>. </li>
   <li> The "full" package (additionally with the instances) has md5sum
   \verbatim
a235cf7a7c88d6aeafded25ab13b993f  SAT2011_GreenTao.tar.bz2
   \endverbatim
   and size 63,872,418 bytes.
   </li>
   <li> Created by
   \verbatim
OKlib/Experimentation/Benchmarks> tar -cjf SAT2011_GreenTao.tar.bz2 SAT2011_GreenTao
   \endverbatim
   after running <code>Create</code>.
   </li>
   <li> From the "empty" package the "full" package is created by running
   <code>./Create</code> in the (extracted) directory
   <code>SAT2011_GreenTao</code>.
    <ol>
     <li> This script prints "SUCCESS" and returns code 0 if no error occurred.
     </li>
     <li> This includes checking of the md5sums of the two generator-files and
     all the benchmark files. </li>
    </ol>
   </li>
  </ul>


  <h1> AES instances </h1>

*/

