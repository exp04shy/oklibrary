# Matthew Gwynne, 19.9.2009 (Swansea)
# Copyright 2009, 2010, 2011 Oliver Kullmann
# This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
# it and/or modify it under the terms of the GNU General Public License as published by
# the Free Software Foundation and included in this library; either version 3 of the
# License, or any later version.

# #######
# Input #
# #######

# Reading the output of a picosat913 computation from filename and returning a
# data.frame containing the statistics on the computation.
#
# Inputs:
#   stats_filename
#     The filename containing the output of the solver run.
#
# Output:
#   Statistics corresponding to the run of the solver on filename.
#   A data.frame with a single row with the following fields in the
#   following order:
#
#     filename (string)
#       Name of the DIMACS file the solver was run on.
#     n (positive integer)
#       Initial number of variables.
#     c (positive integer)
#       Initial number of clauses.
#     sat ({0,1,2})
#       Whether picosat913 found filename to be SATISFIABLE (1),
#       UNSATISFIABLE (0) or it was unable to determine satisfiability (2).
#     restarts (positive integer)
#       Number of restarts.
#     failed_lits (positive integer)
#       Number of forced assignments found using failed literal reductions.
#     conflicts (positive integer)
#       Number of conflicts found while solving filename.
#     decisions (positive integer)
#       Number of "decisions".
#     fixed_vars (positive integer)
#       Number of variables fixed to true or false during search.
#     learned_lits (positive integer)
#       Number of literals determined by conflict clause analysis.
#     deleted_lits (double)
#       Percentage of literals deleted.
#     prop (positive integer)
#       Total number of unit clause propagations.
#     simps (positive integer)
#       Total number of simplications performed.
#     mem (double)
#       Maximum amount of main memory in Megabytes used.
#     time (double)
#       Total time taken in seconds to solve.
#
# Note this function will not read the output of any of the precosat solvers.
#  
read_picosat_output = function(stats_filename, ...) {
  S = system(paste("cat ", filename," | grep \"^c\\|s\""), intern=TRUE)
  result = list()
  for (line in S) {
    line = gsub("^[cs] *", "",line)
    if (length(grep("^parsing *",line)) > 0) {
      result = c(result,list(filename = gsub("^parsing *","",line)))
    } else if (length(grep("^initialized", line)) > 0) {
      result = c(result,
        list(n = as.integer(gsub("[^0-9]","",line))))
    } else if (length(grep("trivial clauses",line)) > 0) {
      result = c(result,
        list(c = as.integer(gsub("[^0-9]","",line))))
    } else if (length(grep("decisions",line)) > 0) {
      result = c(result,
        list(decisions = as.integer(gsub("[^0-9]","",line))))
    } else if (length(grep("conflicts *$",line)) > 0) {
      result = c(result,
        list(conflicts = as.integer(gsub("[^0-9]","",line))))
    } else if (length(grep("fixed variables",line)) > 0) {
      result = c(result,
        list(fixed_vars = as.integer(gsub("[^0-9]","",line))))
    } else if (length(grep("learned literals",line)) > 0) {
      result = c(result,
        list(learned_lits = as.integer(gsub("[^0-9]","",line))))
    } else if (length(grep("failed literals",line)) > 0) {
      result = c(result,
        list(failed_lits = as.integer(gsub("[^0-9]","",line))))
    } else if (length(grep("deleted literals",line)) > 0) {
      result = c(result,
        list(deleted_lits = as.double(gsub("[^0-9\\.]","",line))))
    } else if (length(grep("propagations",line)) > 0) {
      result = c(result,
        list(prop = as.integer(gsub("[^0-9]","",line))))
    } else if (length(grep("simplifications",line)) > 0) {
      result = c(result,
        list(simps = as.integer(gsub("[^0-9]","",line))))
    } else if (length(grep("iterations",line)) > 0) {
      result = c(result,
        list(iter = as.integer(gsub("[^0-9]","",line))))
    } else if (length(grep("seconds total run time",line)) > 0) {
      result = c(result,
        list(time = as.double(gsub("[^0-9\\.]","",line))))
    } else if (length(grep("MB maximally allocated",line)) > 0) {
      result = c(result,
        list(mem = as.double(gsub("[^0-9\\.]","",line))))
    } else if (length(grep("restarts",line)) > 0) {
      result = c(result,
        list(restarts = as.integer(gsub("[^0-9\\.]","",line))))
    } else if (length(grep("SATISFIABLE",line)) > 0) {
      result = c(result, list(sat = 1))
    } else if (length(grep("UNSATISFIABLE",line)) > 0) {
      result = c(result, list(sat = 0))
    }
  }
  data.frame(result)
}
# From the following picosat913 output (in sbox.result):
# 
# c PicoSAT SAT Solver Version 913
# c Copyright (c) 2006 - 2009 Armin Biere JKU Linz
# c gcc -Wall -Wextra -m32 -static -DNDEBUG -O3 -fomit-frame-pointer -finline-limit=1000000
# c
# c parsing AES_sbox_2_4_full.cnf
# c parsed header 'p cnf 8 240'
# c initialized 8 variables
# c found 240 non trivial clauses
# c
# *snip*
# c
# s SATISFIABLE
# v -1 -2 -3 -4 -5 6 7 -8 0
# c
# c 0 iterations
# c 0 restarts
# c 0 failed literals
# c 2 conflicts
# c 8 decisions
# c 0 fixed variables
# c 13 learned literals
# c 0.0% deleted literals
# c 11 propagations
# c 100.0% variables used
# c 0.0 seconds in library
# c 0.0 megaprops/second
# c 1 simplifications
# c 0 reductions
# c 0.0 MB recycled
# c 0.0 MB maximally allocated
# c 0.0 seconds total run time
#
# we get the following data.frame:
#
# R> oklib_load_all()
# R> E = read_picosat_output("sbox.result")
# R> E
#                filename n   c sat iter restarts failed_lits conflicts decisions
# 1 AES_sbox_2_4_full.cnf 8 240   1    0        0           0         2         8
#   fixed_vars learned_lits deleted_lits prop simps mem time
# 1          0           13            0   11     1   0    0
#

# Reading multiple picosat913 output files into a data.frame.
# See read_picosat_output.
read_picosat_outputs = function(filenames) {
 result_df = NULL
 for(file in filenames) {
     result_df = rbind(result_df,read_picosat_output(file))
 }
 result_df
}

