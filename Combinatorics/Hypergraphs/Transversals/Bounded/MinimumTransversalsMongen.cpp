// Oliver Kullmann, 13.6.2009 (Swansea)
/* Copyright 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file Combinatorics/Hypergraphs/Transversals/Bounded/MinimumTransversalsMongen.cpp
  \brief Application for computing all minimum transversals of a monotone series of hypergraphs

  Function Transversals::Bounded::generator needs to be provided in another
  compilation unit.
*/

#include <iostream>
#include <set>
#include <vector>

#include <boost/lexical_cast.hpp>

#include <OKlib/Programming/Utilities/OrderRelations/OrderConstructions.hpp>
#include <OKlib/Combinatorics/Hypergraphs/Transversals/Bounded/VertexBranching.hpp>


namespace {
  typedef unsigned int vertex_type;
  typedef std::set<vertex_type> hyperedge_type;
  typedef std::vector<hyperedge_type> hyperedge_list_type;
  typedef hyperedge_list_type::size_type size_type;
}

namespace OKlib {
 namespace Combinatorics {
  namespace Hypergraphs {
   namespace Transversals {
    namespace Bounded {
      extern hyperedge_list_type generator(const size_type n);
    }
   }
  }
 }
}

namespace {

  template <class> struct GeneratorWrapper {
    typedef ::size_type size_type;
    typedef ::hyperedge_list_type hyperedge_list_type;
    hyperedge_list_type operator() (const size_type n) const {
      return ::OKlib::Combinatorics::Hypergraphs::Transversals::Bounded::generator(n);
    }
  };

  enum {
    error_parameters = 1
  };

  const std::string version = "0.0.1";

}

int main(const int argc, const char* const argv[]) {

  if (argc != 2) {
    std::cerr << "ERROR[MinimumTransversalsMongen]:\n"
      " Exactly one parameter is required, the maximal number of vertices.\n"
      " However, the actual number of input parameters was " << argc-1 << ".\n";
    return error_parameters;
  }

  const size_type N = boost::lexical_cast<size_type>(argv[1]);

  typedef OKlib::OrderRelations::SizeLessThan<std::less<hyperedge_type> > hyperedge_ordering_type;
  typedef std::set<hyperedge_type, hyperedge_ordering_type> set_system_type;

  using namespace OKlib::Combinatorics::Hypergraphs::Transversals;
  typedef Bounded::Minimum_transversals_mongen<set_system_type, GeneratorWrapper, Bounded::TrivialOutput> mtrans_mongen_type;
  typedef mtrans_mongen_type::generator_type generator_type;
  typedef mtrans_mongen_type::output_type output_type;
  output_type out(std::cout);

  mtrans_mongen_type()(N, generator_type(), out);

}

