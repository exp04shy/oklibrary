// Matthew Gwynne, 26.3.2008 (Swansea)
/* Copyright 2008, 2009 Oliver Kullmann
This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation and included in this library; either version 3 of the
License, or any later version. */

/*!
  \file ComputerAlgebra/Cryptology/Lisp/Cryptanalysis/Rijndael/plans/Translations.hpp
  \brief Plans for the translation of Rijndael into active clauses ("SAT constraints") etc in Maxima


  \todo Parameterise inclusion of inverse operation in Mixcolumn translation
  <ul>
   <li> In the initial AES translation, only the encryption direction was
   included in the translation for the Mixcolumn, however, as this operation
   involves the use of multiple xors, decryption does not follow from simple
   UCP. </li>
   <li> Therefore, to both allow decryption to follow solely via UCP and to 
   generally increase the decision power of the translation (i.e increase the
   likelyhood of cracking certain round AES variants), the inverse of the 
   Mixcolumn operation was included. </li>
   <li> To compare and contrast the different approaches, as well as to allow 
   for different translations of the encryption and inverse/decryption only
   versions of the Mixcolumns, there should be a parameter to control whether
   this inverse Mixcolumn is included in the translation. </li>
  </ul>


  \todo Rewrite tests based on rewritten translation system
  <ul>
   <li> After the translation system is rewritten (see "Fix translation system")
   the tests must be rewritten to take account of this. </li>
   <li> Also additionally tests for the following functions are necessary:
    <ul>
     <li> aes_cp </li>
     <li> aes_cnf_cs </li>
     <li> aes_cnf_fcs </li>
    </ul>
   </li>
  </ul>

  
  \todo Provide additional translation into CSP-solver format
  <ul>
   <li> A translation of the AES into a format usable by popular CSP solvers
   should be undertaken. This should allow comparison to the SAT translation.
   </li>
   <li> Is there a generic input format (like DIMACS) for CSP problems? </li>
   <li> Translating to something Minion can read seems reasonably simple, using
   constraints such as: 
   <ul>
    <li> difference (for xor) </li>
    <li> table or negativetable (for sbox, GF multiplication etc) </li>
   </ul>
   one should be able to generate a simple AES CSP problem.
   </li>
   <li> The specification of the sbox and multiplication operations are then
   separate from their instances within the constraint set. This should allow
   for a variety of different translations (including using large prime 
   implicate representations). </li>
  </ul>


  \todo Fix translation system
  <ul>
   <li> The current translation system works in the following way: 
   <ul>
    <li> The common datatype is a set of "constraint templates" of the form
    "aes_c(p_1,p_2,p_3,...p_128,k_1,...)" where: 
    <ul>
     <li> "aes_cp" is an unevaluated function. </li>
     <li> "p_1" etc represent variables within the constraint system. </li>
     <li> %Variables are associated with the underlying variables inherent in
     the constraint by their position in the function arguments. </li>
    </ul>
    </li>
    <li> The process starts off with the set with just the "aes_c" constraint
    template with the plaintext, key and ciphertext input variables as 
    arguments. </li>
    <li> For each constraint template, there are rewrite rules, for instance
    "aes_cp" which take as arguments the variables given to the constraint
    template and produce a set of new constraint templates to replace it. </li>
    <li> When a rewrite rule needs to introduce auxillary variables, to ensure
    no clashing of variables occurs over multiple uses of the rule, a function
    "aes_make_vars" is used to generate unique variables (either named or
    integer depending on how aes_make_vars is assigned). </li>
    <li> Such rewrite rules are applied across the set of constraint templates
    using "rewrite_condition". This is done by simply giving the rewrite rule
    the arguments for the template, and then replacing it in the set of
    constraint templates with the new set of templates returned by the rule. 
    </li> 
    <li> Some rewrite rules, such as "aes_sbox_cp" produce sets of clauses, 
    instead of sets of constraint templates. </li>
    <li> Rewrite rules are applied in a set order using "rewrite_all" to
    produce a final clause set. </li>
   </ul>
   </li>
   <li> This translation works and has the following advantages: 
    <ul>
     <li> It is a simple rewrite procedure. </li>
     <li> Rewrite rules are easy to replace. </li>
    </ul>
    however, it also has several disadvantages: 
    <ul>
     <li> %Clauses are injected directly into the set of constraint templates,
     requiring explicit detection of "sets" within the rewrite system, as they
     are not constraint templates to be rewritten and therefore must be treated
     differently. </li>
     <li> As there is no context for various constraints, only variable
     arguments, rewrite rules such as "aes_round" etc can't use this additional
     information, and:
      <ul>
       <li> Must resort to using "aes_make_vars" which resorts to
       use of global variables in the process. </li>
       <li> Trying to instantiate the system of constraint templates into a
       system of true constraints may result in some information lost which
       could have been used. </li>
      </ul>
     </li>
     <li> Operations such as "shiftrows" must be represented using equality
     constraints, which is a waste. </li>
    </ul>
    The main systematic disadvantage of using some "random" variables
    is that we are losing the meaning of variables.
   </li>
   <li> To improve the system, the following changes are suggested: 
    <ul>
     <li> Split the overall clause set generation process into two steps:
     <ol>
      <li> A pure constraint template rewrite system. </li>
      <li> Translation of the constraint template system into a clause set.
      </li>
     </ol>
     In this way:
     <ul>
      <li> There is no need for explicit detection of "sets" within the
      rewrite system and everything is much cleaner. </li>
      <li> The second step can be used to remove equality constraints using
      variable replacement. </li>
      <li> The second step can be replaced with other translations into
      constraint languages, or replacement of constraint templates with "true
      constraints". See
      ComputerAlgebra/Satisfiability/Lisp/ConstraintProblems/plans/Conditions.hpp. 
      </li>
     </ul>
     </li>
     <li> Alter the constraint template format to the form 
     "aes_cp([p_1,...,p_n],[namespace,...])":
     <ul>
      <li> The first argument to the template is a list of variables. </li>
      <li> The second is a list of additional information about the
      constraint, such as a namespace for auxillary variables, although other
      information
      could be added based on the type of constraint template. </li>
      <li> This allows one to provide all information associated with the
      constraint template. </li>
      <li> Also, given a namespace for auxillary variables, variables may be
      generated in the rewrite rules without the need for any global function
      like "aes_make_vars". </li>
      <li> The form of the namespace seems simplest to be a positive function,
      as then namespaces can be composed, and when auxillary variables are
      needed within a rewrite rule, the namespace can simply be "applied" to
      a localised variable name. </li>
     </ul>
     </li>
    </ul>
   </li>
   <li> Further questions are:
    <ul>
     <li> What is the best way to control the rewrite process? 
     <li> The current system works but a more precise, systematic way of 
     controlling how many rounds, or which rewrite rules are used etc is 
     needed. </li>
     <li> DONE What is the best way to handle parameters controlling the translation?
     <ul>
      <li> There are already many parameters, many of which are controlled via 
      global variables, which is potentially bad practice and underdocumented. 
      </li>
      <li> However taking these parameters as explicit parameters (which must 
      always be provided) is incredibly cumbersome. </li>
      <li> These parameters should become arguments to the constraint templates,
      as this is precisely what these additionals arguments are for, then such
      information (%e.g. that the 2 round AES variant should be considered) is 
      not hidden away. </li>
      <li> These can be considered simply by their position in the argument list,
      and if an argument is optional, then you must still provide it if one of
      the arguments appearing later in the list must be specified. </li>
      <li> For this reason, for such parameters, defaults should be provided, 
      however, they should not be changed in the global scope. </li>
     </ul>
     </li>
    </ul>
   </li>
   <li> Specification: 
    <ul> 
     <li> Concepts:
      <ul>
       <li> Constraint - A list with at least 2 arguments, the first being
       the name of the constraint, the second a list of variables in a 
       predefined order, and then any additional arguments which may
       be required for the computation of the constraints. For example:
       \verbatim
["aes_ct",[aes_ns(p,1),...,aes_ns(p,128),...,aes_ns(c,128)],rounds]
       \endverbatim
       See
       Satisfiability/Lisp/PseudoBoolean/plans/CardinalityConstraints.hpp
       for an example of similar such constraints. 
       </li>
       <li> Constraint template - A list with at least 2 arguments, the 
       first being a constraint, the second, the namespace to be used
       when rewritting the given constraint, and then any additional 
       arguments which will help uniquely identify a particular constraint 
       template instance (in general, uniquely identifying constraints
       isn't important as they just represent a given function, however,
       when rewriting them, one must distinguish them, to avoid introducing
       clashing variables etc). Consider something of the form:
       \verbatim
[["aes_ct",[aes_ns(p,1),...,aes_ns(p,128),...,aes_ns(c,128)],rounds],aes_ns]
       \endverbatim
       </li>
       <li> Namespace - An unevaluated function, where
        <ol>
         <li> The first (required) argument is a variable. </li>
	 <li> Further arguments are template-specific and are then used to 
	 further specify the namespace. </li>
	 <li> The result of the function (if it were to be evaluated) is
	 assumed to be a variable. </li>
	 <li> As the return type of the namespace
  	 function is assumed to be a variable, we may nest namespaces
	 within each other. </li>
	 <li> As the namespace is an unevaluated function, it may be
	 an unevaluated lambda expression, and so arguments may be 
	 included in a namespace in this way, that is:
	 \verbatim
lambda([a],some_namespace_x(a,1,2,3))
	 \endverbatim
	 </li>
        </ol>
       </li>
       <li> Variable - A positive noun, defined in the usual way
       (see ComputerAlgebra/Satisfiability/Lisp/Generators/Generators.mac) for
       each constraint template, where the arguments are used to indicate 
       which instance of a particular type of variable are being used (that 
       is, using nouns in the same way as is usual, see 
       ComputerAlgebra/Satisfiability/Lisp/Generators/Generators.mac). </li>
      </ul>
     </li>
     <li> Datatypes (in an abstract sense):
      <ul>
       <li> Constraint template - denoted by postfix "ct". </li>
       <li> Constraint rewrite function - denoted by "ctr" in 
       function name. </li>
       <li> Constraint list - denoted by "ctl". </li>
      </ul>
     </li>
     <li> Necessary functions and structures: 
      <ul>
       <li> Constraint rewrite bundle:
        <ul>
	 <li> Three element list containing:
	  <ol> 
           <li> A constraint template rewrite function. </li>
	   <li> A namespace used for any new variables introduced in the 
	   constraint template rule. </li>
	   <li> A function which computes a list of variables
	   introduced by the constraint template rewrite 
	   function. </li>
	  </ol>
	 </li>
	 <li> Such a structure groups together all elements relating to
	 the particular rewrite of a given constraint template. </li>
	</ul>
       </li>
       <li> Constraint template rewrite function:
        <ul>
	 <li> Take as argument, the given constraint template. </li>
	 <li> Returns a list of constraint templates representing the original
	 constraint template. </li>
	 <li> Each of the constraint templates in the returned list should 
	 have a namespace n as their 
	 namespace argument, where n is the functional composition of 
	 the namespace for this rewrite function, and the namespace given
	 as the "parent namespace" for the constraint template being
	 rewritten. </li>
	 <li> For example, given the constraint template:
	 \verbatim
[["example_ct",[ct_arg_1,ct_arg_2,ct_arg_3],ex_param],ex_namespace_parent]);
	 \endverbatim
	 a constraint rewrite function "example_ctr" with this as an argument
	 and would return:
	 \verbatim
[[["example_sub_ct",[ct_arg_1,ct_arg_2,ex_namespace(ex_namespace(ct_arg_new,ex_param))]],example_namespace],
[["example_sub_ct2",[ct_arg_3]],example_namespace]]
	 \endverbatim
	 </li>
	</ul>
       </li>
       <li> Namespace variables function:
        <ul>
	 <li> Take as the first argument the constraint 
	 template which the constraint template function associated with this
	 function rewrites. </li>
	 <li> Take as the second argument a rewrite mapping. </li>
	 <li> Return a list of variables introduced by the associated 
	 constraint template rewrite function. </li>
	 <li> Note here, that through such functions, one has immediately
	 a method of translating variables to integer values, as such
	 values are simply the index of the variable in the list. </li>
	</ul>
       </li>
       <li> Rewrite mapping:
        <ul>
	 <li> A list of mappings, where a mapping is simply a two element 
	 list, with the first element being the name of a constraint,
	 for example, "aes_ct", and the second argument being a constraint
	 template rewrite bundle, with which to rewrite this template. </li>
	 <li> Such rewrite mappings then determine which rewrite rules are to
	 be applied by global rewrite functions (see "Rewrite all constraint
	 templates function"), and also the order in which these
	 rewrites will be done. </li>
	 <li> Several default rewrite mappings can then be provided in the 
	 library for convenience. </li>
	 </li>
	</ul>
       </li>
       <li> Rewrite all constraint templates function:
        <ul>
         <li> Takes as first argument a set of constraint templates. </li>
	 <li> Takes as second argument a rewrite mapping. </li>
	 <li> Returns a list of constraint templates after applying all
	 rewrite rules. </li>
        </ul>
       </li>
       <li> Translate to CNF function:
        <ul>
	 <li> Takes as argument a list of constraint templates. </li>
	 <li> Returns a list containing:
	  <ol>
	   <li> A list of variables present in the rewritten list. </li>
	   <li> A list of clauses and constraint templates after 
	   applying all translations from constraint templates to CNF.
	   </li>
	  </ol>
	 </li>
	 <li> Call this result list a formal pseudo-constraint-template list. 
	 </li>
	 <li> The point here is that if there are only constraint templates
	 in the input, which are rewritable to CNFs, then the result is simply
	 a formal clause-list. </li>
	 <li> If it is passed constraint-templates which do not have
	 a translation to CNF then it will simply return them as they are,
	 within the list of clauses/templates. </li>
	 <li> Each specific rewrite situation, such as for instance handling
	 of equality constraints should be represented by separate functions
	 which rewrite the entire pseudo-constraint-template set, and are
	 then called by this function. </li>
	</ul>
       </li>
       <li> Constraint template list to CNF clause list mapping function:
        <ul>
	 <li> This function should take as an argument a list of constraint 
	 templates. </li>
	 <li> The result should be a formal CNF clause-list representing the 
         constraint system. </li>
	 <li> Auxilliary functions which translate individual constraint 
	 templates into clause-lists are also necessary (and exist for the
	 most part). </li>
	 <li> Additionally, constraints such as equality constraints should
	 be rewritten, to simple replace literals with their equivalent 
	 literals, although there are different options which
	 should be represented by different rewrite functions. </li>
	</ul>
       </li>
       <li> (DONE Replaced with variable generator)
       Variable count function:
        <ul>
	 <li> Takes as argument namespace arguments. </li>
	 <li> Returns the number of variables used in this namespace. </li>
	 <li> Such a function should be defined for each namespace
	 and can be recursively calculated based on sub-namespaces. </li>
	</ul>
       </li>
       <li> (DONE Replaced with variable generator) 
       Variable to integer mapping function:
        <ul>
	 <li> Take as an argument a variable. </li>
	 <li> Return the integer representing that variable. </li>
	 <li> Note that the argument may have unevaluated namespaces
	 surrounding it, and these can then be used by the mapping 
	 function to determine the correct mapping. </li>
	 <li> Such a mapping function should exist for each namespace,
	 where the mapping from the set of all variables V(N) in a namespace
	 N to the set of integers {1,...,size(V(N))} is bijective. </li>
	 <li> Mapping functions can then be defined recursively using
	 the mapping functions for sub-namespaces and variable count
	 functions. </li>
	</ul>
       </li>
       <li> (DONE Replaced with variable generator)
       Integer to variable mapping function - simply the inverse of the 
       "Variable to integer mapping function". </li>
      </ul>
     </li>
     <li> Overview of system:
     <ul>
      <li> To translate AES one would call a rewrite all constraint template
      function called "aes_rewrite_all_ctl", which would take as an argument a
      list containing only a constraint template called "aes_ct", where 
      arguments for the constraint template are the variables of AES 
      (plaintext, key and ciphertext), along with a list of arguments, which 
      would include the identity as the namespace (i.e., "lambda([a],a)"), and
      then additionally arguments specifying which translation is used for the
      Sbox, field multiplications, and whether one should include the 
      mixcolumn inverse operation etc. </li>
      <li> So for example:
      \verbatim
aes_rewrite_all_ctl([[["aes_ct",[p1,...,p128,k1,...,k128,c1,...,c128]],lambda([a],a)]]);
      \endverbatim
      </li>
      <li> "aes_rewrite_all_ctl" would then call constraint template rewrite 
      function, called for instance, "aes_ctr_ctl", which would take as an 
      argument, the constraint template, along with a rewrite mapping. </li>
      <li> aes_ctr_ctl would then translate this into a list of constraint 
      templates, such as "aes_subbytes_ct", for which all newly introduced
      variables have the namespace "aes_ns", where additional arguments to
      the namespace are additional (non-namespace) arguments to "aes_ct",
      and the namespace argument of (for instance) "aes_subbytes_ct" is
      "lambda([a],aes_ns(a,arg1,arg2,...))", and additional arguments
      to sub-constraint-templates are simply those arguments relevant
      to that sub-constraint-template. </li>
      <li> Such a rewrite procedure should continue until on newly
      produced constraint templates, and existing constraint templates
      until all constraint-template rewrite functions have been applied
      in the order specified by the given rewrite mapping. </li>
      <li> The result of "rewrite_all" is then a set of constraint
      templates which can no longer be rewritten into smaller
      constraint templates. </li>
      <li> At this point one can then call a translate to CNF function
      on this set of constraint templates to rewrite it to CNF. </li>
      <li> Within the translate to CNF function, constraint templates
      such as those representing equivalence of variables can be translated
      by replacement of variables etc, rather than adding additional clauses
      etc. </li>
      <li> (DONE) MG should see 
      Satisfiability/Lisp/PseudoBoolean/plans/CardinalityConstraints.hpp
      and replace the functional notation used in the new system with
      lists and clarify the distinction between constraint templates
      and constraints. </li>
     </ul>
     </li>
    </ul>
   </li>
  </ul>


  \todo Move notion of AES constraints to separate module/unit
  <ul>
   <li> The representation of components of the AES as constraints
   and the evaluation of these constraints is separate from the 
   rewriting of these constraints (constraints, plus additional information).
   </li>
   <li> The AES implementation at 
   Cryptology/Lisp/CryptoSystems/Rijndael/AdvancedEncryptionStandard.mac 
   should be updated to take the same arguments as each of the constraints 
   used within this system (no global variables like aes_num_rounds), so one 
   can evaluate the constraints generated by the rewrite functions. </li>
  </ul>


  \todo Write Docus
  

  \todo Partitioning into active clauses
  <ul>
   <li> This todo has to be updated according to
   ComputerAlgebra/Satisfiability/Lisp/plans/SatisfactionProblems.hpp. </li>
   <li> An overview on the possibilities of anatomising the AES-process into
   active clauses has to be gained. </li>
   <li> The roughest subdivision presents just the input-output relation (this
   shouldn't not be considered as an active clause). </li>
   <li> At the finest level we have represented the whole of AES as a boolean
   CNF. </li>
   <li> Inbetween there are many possibilities to handle the
   round-computations. </li>
  </ul>


  \todo Active clauses for field operations
  <ul>
   <li> Likely the two best first candidates for active clauses
   are the S-box (as map GF(2^8) -> GF(2^8)) and multiplication with
   some constant a in GF(2^8)^* (again, as map GF(2^8) -> GF(2^8)). </li>
   <li> Both types of functions yield boolean functions in 16 variables. </li>
   <li> As bijections, they all have trivial DNF representations (with 256
   satisfying assignments). </li>
   <li> For CNF representations see "Generate good CNF clause-sets for the AES
   Sbox" in
   ComputerAlgebra/Cryptology/Lisp/Cryptanalysis/Rijndael/plans/SboxAnalysis.hpp
   (obviously all the algorithmic techniques can be generalised to any function
   given by truth tables. </li>
   <li> Obviously also of interest are OBDD representations of these boolean
   functions.
    <ol>
     <li> One should come pretty close to finding an optimal variable
     ordering. </li>
    </ol>
   </li>
   <li> These allow efficient handling of all basic tasks for active clauses
   (see ComputerAlgebra/Satisfiability/Lisp/plans/SatisfactionProblems.hpp).
   </li>
   <li> Of course, special algorithms should be investigated. </li>
   <li> It seems, that actually the DNF representation we have, which actually
   is a full DNF, and just having 256 clauses, yields an unbeatable active
   clause:
    <ol>
     <li> Given any DNF representation D of a boolean function F,
     satisfiability of phi * F is just checked by testing whether phi * D is
     not the empty clause-set. </li>
     <li> In general, for a clause-set F, considered as CNF or DNF, the
     opposite representation is just obtained by the transversal hypergraph,
     from which non-clauses are eliminated, and which then is complemented.
     </li>
     <li> So forced literals for phi * D are literals which occur in every
     clause. This can be checked by just checking the literal degrees. </li>
     <li> And the number of satisfying assignments for a hitting D can be
     computed by the standard counting arguments. The given case is even
     simpler, since we have a full clause-set (where full clause-sets are
     stable under application of partial assignments), and so we just need
     to count the remaining clauses. </li>
     <li> Nevertheless we need to compute the prime-implicate representation,
     since the minimal size of a prime implicate tells us how many variables
     have to be set until we may obtain a contradiction --- this is important
     information for the analysis, and furthermore for the active clause it
     can be used as threshold which triggers some action (before, we are
     just lazy and don't do anything (w.r.t. updating the counters)). </li>
     <li> All these generalisations are very general, and should go to
     supermodule Satisfiability/ProblemInstances. </li>
    </ol>
    Using these active clauses should give us a good advantage over any CNF
    translation!
   </li>
   <li> We should aim at "high integration":
    <ol>
     <li> The more active clauses can manage the better. </li>
     <li> So we should have the full S-box an active clause, and not
     dividing it further. </li>
     <li> Perhaps in combination with the various permutations we can combine
     several "micro-steps" into one. Perhaps the ShiftRows step doesn't need
     to be made explicit at all. And also MixColumns operates on the bytes.
     </li>
     <li> Perhaps we create "generic active clauses" for these cases, and
     instantiate them appropriately (so that many variations of the same basic
     active clause appear). </li>
     <li> Identifying transformations of GF(2^8) seems most promising, since
     this yield active clauses with 16 bits, which can be thoroughly
     analysed. 32 bits likely is too much (since we won't have much
     exploitable structure(?)). </li>
    </ol>
   </li>
   <li> We have also the field addition, which can be broken down into binary
   xor, and perhaps a dedicated active clause(-set) handles all these equations
   over GF(2) (via Gaussian elimination). </li>
   <li> The main underlying theoretical question is whether the conditions
   "x * y = 1" and "a * x = y" are active clauses (for arbitrary GF(2^n).
    <ol>
     <li> This depends on the choice of literals (i.e., which partial
     assignments are allowed). </li>
     <li> A coarse choice is to use byte-valued variables (x, y here are just
     elements of the byte-field) and standard literals: Here we have active
     clauses, since the field operations as well as inversions can be
     performed in polynomial time. </li>
     <li> The next level (perhaps our preferred level) is the boolean level
     (now the bits of x and y can be queried). Using the natural representation
     of elements of GF(2^n) as vectors in the canonical base, we obtain
     one quadratic equation in both cases. If quadratic equations in GF(2^n)
     can be solved in polynomial time, then we are done, if not then we have
     to investigate whether the special form of equations we have matters or
     not. </li>
     <li> A fine level considers again byte-valued variables, but signed
     literals. It seems rather unlikely that this can be solved in polynomial
     time. However for n=8 perhaps we can perform heavy preprocessing? </li>
    </ol>
   </li>
  </ul>


  \todo Generate translation that allows multiple plaintext/ciphertext pairs
  <ul>
   <li> Given that a single plaintext/ciphertext pair (P,C), encrypted with AES 
   using a key K, might not be enough, on it's own, to deduce K (as there may
   be some K' which performs the same mapping for this specific (P,C)), for
   genuine experiments and understanding of AES, translations allowing
   multiple plaintext/ciphertext pairs but sharing the key variables are 
   needed. </li>
   <li> A simple method here is to perform the translation multiple times, 
   introducing distinct variables for each pair of plaintext/ciphertext, but 
   using the same key variables in each translation. The union of all such 
   translations is then the required result. </li>
  </ul>i


  \todo DONE Standardise block ordering
  <ul>
   <li> Within the translation system, any time a list of variables 
   representing a block within the AES are passed, the list is interpreted
   as the "block"/"matrix" given *row by row*. </li>
   <li> However, the standard when representing such blocks in hexidecimal etc
   is to list the block, *column by column*, which makes much more sense as
   the number of columns may increase, whereas the number of rows (i.e column
   size) remains the same. </li>
   <li> Therefore, each of the translation functions and tests should be
   rewritten to consider such list of variables *column by column*. </li>
   <li> This should make the implementation of functions such as aes_hex2pa
   etc must simpler. </li>
   <li> This has already been done for the AES implementation in
   ComputerAlgebra/Cryptology/Lisp/CryptoSystems/Rijndael/ . </li>
  </ul>


  \todo Constraint rewrite system (DONE Covered in "Fix translation system")
  <ul>
   <li> In translating AES to a CNF, one can define a rewrite system based
   around sets of constraints.
    <ol>
     <li> A "constraint" is simply a 3-tuple with a name, a set of variables
     and a function for evaluation given a partial assignment to the variables.
     OK: The notion of "constraint" is not really appropriate. And in general
     the partial assignment must be *total* w.r.t. the scope.
     MG: What would be better terminology? Active unit? Condition also doesn't
     appear to fit for similar reasons (?).
     </li>
     <li> A rewrite function "f" is defined to take a constraint, and if it is
     applicable (i.e., if "f" is a rewrite rule for that constraint), it
     returns a set of new constraints, otherwise it returns false (in some
     way). This may be handled by a unit list and empty list rather than use
     of "false". </li>
     <li> An application function is necessary to apply a given rewrite rule
     to a set of constraints. When a particular rewrite rule applies, the 
     constraints it returns must be joined to the current set of constraints
     and issues such as variable clashes etc handled. </li>
     <li> Translations may be achieved by applying such rewrite rules using
     the application functions to sets of constraints in an interative manner.
     </li>
     <li> Starting initially with a single "aes" constraint, rewrite rules 
     can then be iteratively applied to reduce the system to simpler
     sets of constraints. </li>
    </ol>
   </li>
   <li> How  to handle variables?
    <ol>
      <li> How to name variables? Seperate variable prefixes for plaintext, 
      ciphertext, key and round key bits seem sensible, as well as seperate
      input and output bits for each round, and then a variable
      prefix for each constraint? </li>
      <li> %Variables used when rewriting a particular
      constraint would then use the variables appropriate to that constraint? 
      </li>
      <li> Indices can be used to represent that a variable belongs to a 
      particular round "r" (if applicable), and then it seems sensible to 
      provide an index "i" which specifies the position of the bit in a 
      particular grouping, for instance the "ith" bit of the plaintext. </li>
      <li> Lastly, an index "n" to determine that this is the nth set of such
      variables should suffice, for situations within constraint rewriting
      where multiple sets of internal variables are needed for a single
      constraint rewrite. </li>
      <li> When applying a rewrite rule "f" to a constraint "c", given that 
      a particular rewrite rule has no knowledge of the wider set of
      constraints "S_t" (only the constraint given to it), how to rename or
      reindex the variables in the set of constraints "S_o" that "f" outputs,
      so that internal variables (i.e., variables not present in the variable
      set "S_c" for "c") do not clash with others in "S_t"? </li>
      <li> Simply take some kind of maximum index "m" derived from indices 
      used in variables in "S_t", and then rewrite any variables in "S_o"
      by taking the indices "u" used there and adding to them "m"? </li>
      <li> For instance transforming "sbox_var(r,u,i)" to "sbox_var(r,u+m,i)".
      %Variables occuring in "S_c" must obviously be exempt from this, but this
      should be trivial to achieve. </li>
      <li> How should a given rewrite rule know which variables represent which
      bits in the problem when we consider only a set of variables? Special 
      knowledge of the system works well enough for everything outside of the 
      Sbox and potentially addition within the rijndael byte field, as these
      are used in various places? </li>
      <li> Should the rewrite rules for such constraints (sbox etc) simply make
      hardcoded case distinctions based on the variables occuring in the 
      variable set? </li>
    </ol>
   </li>
  </ul>


  \todo Encoding AES (top down) (DONE Covered in "Fix Translation System")
  <ul>
   <li> Break this todo into separate todos </li>
   <li> Using the concept of a "constraint" (rather than condition), where this
   can be represented by a tuple consisting of a name, a set of variables
   and a function to evaluate it, given an assignment. </li>
   <li> Compare the discussion under "Condition" in
   ComputerAlgebra/Satisfiability/Lisp/plans/SatisfactionProblems.hpp. </li>
   <li> The following needs updating, so that from the beginning
   we consider families of encoding, using different "granularity
   levels" for the "active clauses" used; see "Partitioning into active
   clauses" above. </li>
   <li> First the formulas F_AES(p, k, c) encoding
   the encryption via AES, and F'_AES(p, k, c) encoding
   the decryption via AES have to be created, as
   plain CNF. The formulas F_AES etc. actually need a
   further parameter 0 <= r <= 10, the number of rounds.
   </li>
   <li> That is, we can consider F_AES^r(p, k, c') for 0 <= r < = 10
   which encodes that encryption of p via k in r rounds yields c',
   and F'_AES^s(p', k, c) for 0 <= s < = 10
   which encodes that decryption of c via k in s rounds yields p'. </li>
   <li> We have  F_AES(p, k, c) = F_AES^10(p, k, c) and
   F'_AES(p, k, c) = F'_AES^10(p, k, c). </li>
   <li> It seams reasonable to demand that F_AES^r(p, k, c') contains
   F_AES^r'(p, k, c') for r' <= r, and the same for F'_AES^s(p', k, c).
   </li>
   <li> The variables used in  F_AES^r(p, k, c') and F'_AES^s(p', k, c)
   must be consistently named, so that these formulas can be combined.
   </li>
   <li> (Compare the 2006-BSc-project by Gareth Thomas. The difference
   between F_AES(p, k, c) and F'_AES(p, k, c) is in the use
   of the auxiliary variables.)
   </li>
   <li> Only later should we consider a full C++ implementation, but first
   we create a prototype in the computer-algebra system. DONE </li>
   <li> (DONE Discussion reformulated in "Constraint Rewrite System")
   For an initial translation to CNF, the following seems sensible
    <ol>
     <li> Function of the form aes_cp(p1,...,p128,k1,...,k128,c1,...,c128) 
     which given the plaintext, key and ciphertext variables, produces a
     set of conditions. </li>
     <li> At the highest level, the "aes_cp" could produce a set of conditions
     in terms of an "aes_round_cd" condition, which could then later be defined
     through functions which would then be substituted for conditions in the
     set. </li>
     <li> The conditions can be replaced by functions that 
     are only *then* evaluated by use of "obsubst", providing a more
     structured intentional approach, which makes substituting different
     conditions into the final expansion far easier (without constant 
     function renaming). </li>
     <li> This methodology can be applied down to levels such as the sbox
     and field element multiplications (within reason) and then additional
     must be made of these operations. </li>
     <li> An issue that arises is the naming/production of new variables. 
     Given that these will be needed at various levels to "join" various
     result bits to input bits of different conditions, but if such a scheme
     uses function evaluations, how to produce such variables without sharing
     some kind of global state? </li>
     <li> Passing an initial variable pool (list of variables) into the 
     conditions could work, but this doesn't seem to fit well with the
     conditions being simple conditions given a set of input bits. Perhaps a
     method which evaluates a given set of conditions and condition producing
     functions and then defines this variable pool, which is then in the scope
     of the condition producing functions when they are substituted and
     evaluated? </li>
     <li> Also, if each of these functions produces a set of conditions, then
     simple substitution would yield a set of sets, and then a set of set of
     sets etc. A simple solution here seems to be, to return the union of 
     any unevaluated conditions, where this union will be applied 
     (automatically by maxima) only when the entire expression has been 
     sufficiently evaluated, such that each of these conditions yields
     a set. </li>
     <li> On second thought, it seems more natural, considering each of
     these functions can be run in isolation and should produce a set of
     conditions, that only at the substitution stage should the issue,
     of joining the set produced by a condition to the parent set, be
     considered. </li>
     <li> For the unevaluated conditions (placeholders) within the sets, 
     perhaps the postfix "_c" for condition, could be used, and for the
     functions producing the conditions, perhaps "_cp" as a postfix? </li>
     <li> (DONE yes this is precisely the intention)
     Could such condition sets also be used as a representation when
     dealing with active clauses? A generalised solver that looked for 
     operators within the set and then applied appropriate given functions
     for those operators that would determine heuristics etc? </li>
     <li> DONE (Not needed, we want a set of conditions to be produced)
     "nounify" appears to be useful here, to force functions such as
     "union" to become "nouns" rather than "verbs", which are then not 
     immediately evaluated. This is only an issue in some cases such as "union"
     where it expects it's arguments to be of the correct type and won't return
     the unevaluated expression if not, but instead returns an error. </li>
    </ol>
   </li>
  </ul>


  \todo DONE Truncate AES for reduced rounds
  <ul>
   <li> The current behaviour of the AES SAT translation when 
   the variable aes_num_rounds is specified, is to translate an
   AES variant with (aes_num_rounds - 1) full "normal" AES rounds and
   then a single instance of the final AES round (which is a special
   case in Rijndael). </li>
   <li> To truly say that AES is being "stopped" and inspected after
   aes_num_rounds rounds, the true behaviour should be that exactly
   (aes_num_rounds - 1) rounds and 1 final round are translated iff
   aes_num_rounds = 10, otherwise exactly aes_num_rounds rounds are
   translated and the special final AES round is not used. </li>
   <li> Perhaps this should somehow be an option for:
   <ul>
    <li> Truncated AES </li>
    <li> Generalised AES </li>
   </ul>
  </ul>


*/

