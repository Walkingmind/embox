# $Id: rules.mk 9 2010-03-12 19:00:31Z Eldar.Abusalimov $
#
# Author: Eldar Abusalimov
#

.DELETE_ON_ERROR:

# Disable some annoying builtin rules. These speeds up the build a bit.
.SUFFIXES:
% : RCS/%
% : %,v
% : RCS/%,v
% : %,w
% : RCS/%,w
% : s.%
% : SCCS/s.%
% : %.w
%.c : %.y
%.c : %.l
%.c : %.w
