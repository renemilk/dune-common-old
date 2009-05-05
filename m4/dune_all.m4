# $Id$

# this meta-check calls everything needed for Dune to work and all
# possible components. Applications should use this so that
# Dune-updates enable new features automagically

# the entries are more or less copied from an "autoscan"-run in the
# dune-directory

#
# There are two test available:
# 1) DUNE_CHECK_ALL
#    This test is for people writing an application based on dune
# 2) DUNE_CHECK_ALL_M
#    This test is for dune modules.
#    In addition to DUNE_CHECK_ALL it run some additional tests
#    and sets up some things needed for modules (i.e. the 'dune' symlink)

AC_DEFUN([DUNE_CHECK_ALL],[
  # doxygen and latex take a lot of time...
  AC_REQUIRE([DUNE_DOCUMENTATION])
  AC_REQUIRE([DUNE_WEB])

  AC_ARG_ENABLE(enabledist,
    AC_HELP_STRING([--enable-dist],
                 [go into create-tarballs-mode [[default=no]]]),
    [enabledist=$enableval],
    [enabledist=no]
  )
  AM_CONDITIONAL(MAKEDIST, test x$enabledist = xyes)
  if test x$enabledist = xyes; then
    AM_CONDITIONAL(DUNEWEB, false)
  fi

  dnl check dependencies of this module
  dnl this test is autogenerated for each module
  AC_REQUIRE([DUNE_CHECK_MOD_DEPENDENCIES])

  # convenience-variables if every found package should be used
  AC_SUBST(ALL_PKG_LIBS, "$LIBS $DUNE_PKG_LIBS")
  AC_SUBST(ALL_PKG_LDFLAGS, "$LDFLAGS $DUNE_PKG_LDFLAGS")
  AC_SUBST(ALL_PKG_CPPFLAGS, "$CPPFLAGS $DUNE_PKG_CPPFLAGS")

  AC_SUBST(ACLOCAL_AMFLAGS, "$ACLOCAL_AMFLAGS")

  AC_SUBST(am_dir, $DUNE_COMMON_ROOT/am)
])

AC_DEFUN([DUNE_ADD_SUMMARY_ENTRY],[
  indentlen=24
  txt="$1"
  while test `echo "$txt" | tr -d '\n' | wc -c` -lt $indentlen; do txt="$txt."; done
  txt="$txt: $2"
  [DUNE_SUMMARY="$DUNE_SUMMARY echo '$txt';"]
])

AC_DEFUN([DUNE_ADD_SUMMARY_MOD_ENTRY],[
  indentlen=24
  txt=$1
  while test `echo $txt | tr -d '\n' | wc -c` -lt $indentlen; do txt=$txt.; done
  txt="$txt: $2"
  [DUNE_MODULES_SUMMARY="$DUNE_MODULES_SUMMARY echo '$txt';"]
])

AC_DEFUN([DUNE_SUMMARY_ALL],[
  # show search results

  echo
  echo "Found the following Dune-components: "
  echo
  echo "----------------------------------------"
  echo  
  [(eval $DUNE_MODULES_SUMMARY) | sort]
  [(eval $DUNE_SUMMARY) | sort]
  echo
  echo "----------------------------------------"
  echo
  echo "See ./configure --help and config.log for reasons why a component wasn't found"
  echo

])

AC_DEFUN([DUNE_CHECK_ALL_M],[
  AC_REQUIRE([DUNE_SYMLINK])
  AC_REQUIRE([DUNE_CHECK_ALL])
  AC_REQUIRE([DUNE_AUTOBUILD_FLAGS])
])
