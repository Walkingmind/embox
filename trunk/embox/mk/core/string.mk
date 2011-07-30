# $Id$
#
# Extended set of functions for string analysis and manipulation.
#
#   Date: Jan 14, 2011
# Author: Eldar Abusalimov
#

ifndef __core_string_mk
__core_string_mk := 1

##
# Function: nowords
# Checks whether the specified string contains no words (nothing but
# whitespaces).
#
# Params:
#  1. The string to check
# Return:
#     True if the specified text has no non-whitespace characters,
#     false otherwise.
nowords = \
  $(call not,$(firstword $1))

##
# Function: singleword
# Checks whether the specified string contains exactly one word.
#
# Params:
#  1. The string to check
# Return:
#     The word itself if the specified string is a single-word list,
#     nothing (false) otherwise.
singleword = \
  $(if $(word 2,$1),,$(firstword $1))

##
# Function: doubleword
# Checks whether the specified string contains exactly two words.
#
# Params:
#  1. The string to check
# Return:
#     The unmodified string if it is a double-word list,
#     nothing (empty string) otherwise.
doubleword = \
  $(if $(filter 2,$(words $1)),$1)

##
# Function: firstword
# Gets the first word of the specified words list.
#
# Params:
#  1. The target list of words
# Return:
#     The first word of the list.
firstword = \
  $(firstword $1)# built-in

##
# Function: lastword
# Gets the last word of the specified words list.
#
# Params:
#  1. The target list of words
# Return:
#     The last word of the list.
ifeq ($(lastword $(false) $(true)),$(true))
lastword = \
  $(lastword $1)# built-in
else
lastword = \
  $(if $(strip $1),$(word $(words $1),$1))
endif

##
# Function: nofirstword
# Removes the first word from the specified words list.
#
# Params:
#  1. The target list of words
# Return:
#     The list of words with the first one removed.
nofirstword = \
  $(wordlist 2,2147483647,$1)

##
# Function: nolastword
# Removes the last word from the specified words list.
#
# Params:
#  1. The target list of words
# Return:
#     The list of words with the last one removed.
nolastword = \
  $(wordlist 2,$(words $1),x $1)

##
# Function: append
# Appends the second argument after the first using whitespace as a separator
# (if both of the argument are non-empty strings).
#
# Params:
#  1. The first string
#  2. The second string
# Return:
#     The result of string concatenation.
append = \
  $1$(if $2,$(if $1, )$2)

##
# Function: prepend
# Prepends the second argument before the first using whitespace as a separator
# (if both of the argument are non-empty strings).
#
# Params:
#  1. The first string
#  2. The second string
# Return:
#     The result of string concatenation.
prepend = \
  $2$(if $1,$(if $2, )$1)

##
# Function: filter-patsubst
# Strict version of patsubst. Leaves only those words that match at least
# one of the specified patterns.
#
# Params:
#  1. Pattern...
#  2. Replacement
#  3. String
# Return:
#     The result of patsubst applied to filtered string.
filter-patsubst = \
  $(foreach 1,$1,$(patsubst $1,$2,$(filter $1,$3)))

endif # __core_string_mk
