dnl Process this file with autoconf to produce a configure script.

AC_INIT([notification],[0.1])
AM_INIT_AUTOMAKE([foreign subdir-objects -Wall])
AC_CONFIG_HEADERS([config.h])

AC_SEARCH_LIBS([strerror],[cposix])
AC_PROG_CC

PKG_CHECK_MODULES([GTK],[gtk+-2.0])

AC_CHECK_HEADERS([bsd/string.h])

dnl Use -Wall if we have gcc.
changequote(,)dnl
if test "x$GCC" = "xyes"; then
  case " $CFLAGS " in
  *[\ \	]-Wall[\ \	]*) ;;
  *) CFLAGS="$CFLAGS -Wall" ;;
  esac
fi
changequote([,])dnl

AC_SEARCH_LIBS([strlcpy],[bsd])

AC_CONFIG_FILES([
Makefile
src/Makefile
])
AC_OUTPUT
