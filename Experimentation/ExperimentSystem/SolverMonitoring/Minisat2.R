# Matthew Gwynne, 18.9.2009 (Swansea)
# Copyright 2009, 2010, 2011 Oliver Kullmann
# This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
# it and/or modify it under the terms of the GNU General Public License as published by
# the Free Software Foundation and included in this library; either version 3 of the
# License, or any later version.

# #######
# Input #
# #######

# Reading the output of a minisat-like solver. Solver output is read from
# stats_filename. A data.frame containing the statistics on the computation is
# returned.
#
# Inputs:
#   stats_filename
#     The filename containing the output of the solver run.
#
# Output:
#   Statistics corresponding to the run of the solver on some DIMACS file.
#   A data.frame with a single row with the following fields in the
#   following order:
#
#     n (positive integer)
#       Initial number of variables.
#     c (positive integer)
#       Initial number of clauses.
#     parse_time (double)
#       Time taken in seconds to parse the DIMACS file.
#     restarts (positive integer)
#       Number of restarts.
#     conflicts (positive integer)
#       Number of conflicts.
#     decisions (positive integer)
#       Number of "decisions".
#     propagations (positive integer)
#       Number of unit clause propagations.
#     mem (double)
#       Maximum amount of main memory in Megabytes used.
#     time (double)
#       Total time taken in seconds to solve the instance.
#     sat ({0,1,2})
#       Whether minisat2 found filename to be SATISFIABLE (1),
#       UNSATISFIABLE (0) or it was unable to determine satisfiability (2).
#     filename (string)
#       Name of the file the output statistics were written to. Note that
#       this is not the DIMACS file input to the solver. Minisat-like solvers
#       do not print the input filename as part of their output.
#  
read_minisat_output = function(stats_filename) {
  S = system(paste("cat ", stats_filename,
    " | grep \"\\(restarts\\|conflicts\\|decisions\\|propagations\\|",
    "conflict\\|Memory\\|CPU\\|variables\\|clauses\\|time\\|",
    "SATISFIABLE\\|UNSATISFIABLE\\|INTERRUPTED\\|INDETERMINATE\\)\"", sep=""),
    intern=TRUE)
  result = list()
  for (line in S) {
    line = gsub("^[cs] *", "",line)
    name_value = unlist(strsplit(line," *: *"))
    name_value[1] = gsub("^\\| *","",name_value[1])
    if (name_value[1] == "restarts") {
      result = c(result, list(restarts = as.integer(name_value[2])))
    } else if (name_value[1] == "conflicts") {
      temp = unlist(strsplit(name_value[2], " *\\("))
      result = c(result, list(conflicts = as.integer(temp[1])))
    } else if (name_value[1] == "propagations") {
      temp = unlist(strsplit(name_value[2], " *\\("))
      result = c(result,
        list(propagations = as.integer(temp[1])))
    } else if (name_value[1] == "Memory used") {
      result = c(result,
        list(mem = as.double(gsub(" *MB *$","",name_value[2]))))
    } else if (name_value[1] == "CPU time") {
      result = c(result,
        list(time = as.double(gsub(" *s *","",name_value[2]))))
    } else if (name_value[1] == "decisions") {
      temp = unlist(strsplit(name_value[2], " *\\("))
      result = c(result, list(decisions = as.integer(temp[1])))
    } else if (name_value[1] == "Number of variables") {
      result = c(result,
        list(n = as.integer(gsub(" *\\|","",name_value[2]))))
    } else if (name_value[1] == "Number of clauses") {
      result = c(result,
        list(c = as.integer(gsub(" *\\|","",name_value[2]))))
    } else if (name_value[1] == "Parsing time") {
      result = c(result,
        list(parse_time = as.double(gsub(" *s *\\|","",name_value[2]))))
    } else if (name_value[1] == "SATISFIABLE") {
      result = c(result, list(sat = 1))
    } else if (name_value[1] == "UNSATISFIABLE") {
      result = c(result, list(sat = 0))
    } else if (name_value[1] == "*** INTERRUPTED ***") {
      if (is.null(result$sat)) {
        result = c(result, list(sat = 2))
      }
    } else if (name_value[1] == "INDETERMINATE") {
      result = c(result, list(sat = 2))
    }
  }
  result = c(result,list(filename = stats_filename))
  data.frame(result)
}
# From the following minisat-2.2.0 output (in sbox.result):
#
# WARNING: for repeatability, setting FPU to use double precision
# ============================[ Problem Statistics ]=============================
# |                                                                             |
# |  Number of variables:             8                                         |
# |  Number of clauses:             240                                         |
# |  Parse time:                   0.00 s                                       |
# |  Simplification time:          0.00 s                                       |
# |                                                                             |
# =============================[ Search Statistics ]==============================
# | Conflicts  |          ORIGINAL         |          LEARNT          | Progress |
# |            |    Vars  Clauses Literals |    Limit  Clauses Lit/Cl |          |
# ================================================================================
# ===============================================================================
# restarts              : 1
# conflicts             : 4              (inf /sec)
# decisions             : 9              (0.00 % random) (inf /sec)
# propagations          : 19             (inf /sec)
# conflict literals     : 14             (12.50 % deleted)
# Memory used           : 18.00 MB
# CPU time              : 0 s
#
# SATISFIABLE
#
# we get the following data.frame:
#
# R> oklib_load_all()
# R> E = read_minisat2_output("sbox.result")
# R> E
#   n   c parse_time restarts conflicts decisions propagations   mem time sat
# 1 8 240          0        1         4         9           19 14.63 0.01   1
#      filename
# 1 sbox.result
#

# Reading multiple minisat-like solver output files into a data.frame.
# See read_minisat_output.
read_minisat_outputs = function(filenames) {
  result_df = NULL
  for(file in filenames) {
    result_df = rbind(result_df,read_minisat2_output(file))
  }
  result_df
}
