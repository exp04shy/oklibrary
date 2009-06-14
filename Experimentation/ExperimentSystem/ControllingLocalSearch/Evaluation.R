# Oliver Kullmann, 4.6.2009 (Swansea)
# Copyright 2009 Oliver Kullmann
# This file is part of the OKlibrary. OKlibrary is free software; you can redistribute
# it and/or modify it under the terms of the GNU General Public License as published by
# the Free Software Foundation and included in this library; either version 3 of the
# License, or any later version.

# Reading files created by ubcsat-okl, printing most basic statistics, and
# returning the dataframe:
read_ubcsat = function(filename) {
  E = read.table(file = filename, 
        colClasses = c("character", "factor", "integer", "integer", "integer", "character"))
 print(table(E$min))
 cat(length(E$min),"\n")
 E
}