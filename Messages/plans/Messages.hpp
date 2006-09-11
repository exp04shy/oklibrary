// Oliver Kullmann, 29.1.2006 (Swansea)

/*!
  \file Messages/plans/Messages.hpp
  \brief Plans for the messages module (as a whole)

  \todo Directory structure:
   - To conform with the current recursive build system, we need a new sub-directory
     Messages/Basics, which contains all the files currently directly under Messages.
     This would bring another nested namespace, but since we have macro support
     anyway for creating message classes, this should not bring much user-inconvenience
     with it.
   - Under Messages we need then an makefile_recursive instance.

  \todo Update:
   - Move all relevant todos to the plans-directory.
   - Update the doxygen-documentation.
   - Especially it must be precisely documented how to use and write message classes.

  \todo Testing:
   - We need here a preliminary compiler switch, which disables
     testing of fr_CA for versions different from 4.0.3 and 4.1.1.
     Later we will request compiler version 4.1.1 or higher,
     but first we have to see that there are no performance
     problems with these later gcc-versions (regarding compilation and execution).
*/

/*!
  \namespace OKlib::Messages
  \brief Module for objects representing units of meaning
*/

namespace OKlib {
  namespace Messages {
  }
}

