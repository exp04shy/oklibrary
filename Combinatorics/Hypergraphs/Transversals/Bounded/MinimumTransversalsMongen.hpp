// Oliver Kullmann, 17.11.2009 (Swansea)
/* Copyright 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Combinatorics/Hypergraphs/Transversals/Bounded/MinimumTransversalsMongen.hpp
  \brief Header file for creating instances of this application for computing all minimum transversals of a monotone series of hypergraphs

*/

#ifndef MINIMUMTRANSVERSALSMONGEN_jNbckpq5q20
#define MINIMUMTRANSVERSALSMONGEN_jNbckpq5q20

#include <set>
#include <vector>

namespace OKlib {
 namespace Combinatorics {
  namespace Hypergraphs {
   namespace Transversals {
    namespace Bounded {

      typedef unsigned int vertex_type;
      typedef std::set<vertex_type> hyperedge_type;
      typedef std::vector<hyperedge_type> hyperedge_list_type;
      typedef std::vector<vertex_type> parameter_type;

      void initialise(const vertex_type N, const parameter_type& P);
      hyperedge_list_type generator(const vertex_type n);

    }
   }
  }
 }
}


#endif
