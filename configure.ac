AC_INIT([sfw], [1.0])
AC_CONFIG_SRCDIR([README.md])
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_MACRO_DIRS([m4])

AC_CANONICAL_HOST
AC_CANONICAL_TARGET
AM_INIT_AUTOMAKE([foreign subdir-objects])
AM_MAINTAINER_MODE

AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_CXX
AX_CXX_COMPILE_STDCXX_11
LT_INIT

OS="unknown"
ARCH="unknown"

case "$target_cpu" in
	x86_64 | amd64)
		ARCH=64
		;;
	i*86)
		ARCH=32
		;;
	arm64 | aarch64)
		ARCH=64
		;;
	arm)
		ARCH=32
		;;
  *)
	AC_MSG_ERROR([$target_cpu is not supported!])
	;;
esac

INCLUDE_PATHS="src src/sfw/includes"

CFLAGS="$CFLAGS -fPIC"
CPPFLAGS="$CPPFLAGS -fPIC"
LDFLAGS="$LDFLAGS -fPIC"

case "$target_os" in
	mingw* | cygwin*)
		OS=win
		AC_DEFINE([TARGET_WIN], [1], [ ])
		INCLUDE_PATHS="$INCLUDE_PATHS src/sfw/includes/win32"
		;;
	linux*)
		OS=linux
		AC_DEFINE([TARGET_LINUX], [1], [ ])
		INCLUDE_PATHS="$INCLUDE_PATHS src/sfw/includes/linux"
		;;
	darwin*)
		OS=mac
		AC_DEFINE([TARGET_MAC], [1], [ ])
		INCLUDE_PATHS="$INCLUDE_PATHS src/sfw/includes/osx"
		LDFLAGS="$LDFLAGS -undefined suppress -flat_namespace"
		;;
	*)
	AC_MSG_ERROR([$target_os is not supported!])
	;;
esac

case "$ARCH" in
	64)
		AC_DEFINE(OPA_SIZEOF_VOID_P, 8, [64 bit architecture detected])
	;;
	32)
		AC_DEFINE(OPA_SIZEOF_VOID_P, 4, [32 bit architecture detected])
	;;
esac

case "$OS" in
	linux | mac)
		AC_DEFINE([OPA_HAVE_GCC_INTRINSIC_ATOMICS], [1], [ ])
		AC_DEFINE([HAVE_STDDEF_H], [1], [ ])
		AC_DEFINE([HAVE_STDLIB_H], [1], [ ])
		AC_DEFINE([HAVE_UNISTD_H], [1], [ ])
		;;
esac

AM_CONDITIONAL(TARGET_32, [test x$ARCH = x32])
AM_CONDITIONAL(TARGET_64, [test x$ARCH = x64])
AM_CONDITIONAL(TARGET_WIN, [test x$OS = xwin])
AM_CONDITIONAL(TARGET_LINUX, [test x$OS = xlinux])
AM_CONDITIONAL(TARGET_MAC, [test x$OS = xmac])
AM_CONDITIONAL(TARGET_UNIX, [test x$OS = xlinux || test x$OS = xmac])

AC_SUBST(CFLAGS)
AC_SUBST(CPPFLAGS)
AC_SUBST(LDFLAGS)
AC_SUBST(INCLUDE_PATHS)

AC_CONFIG_FILES([
	Makefile
	src/Makefile
	src/sfw/Makefile
	src/bindings/Makefile
	src/bindings/sfw.net/Makefile
	tests/Makefile
	tests/test-console/Makefile
	tests/sfw.net.TestConsole/Makefile
])
AC_CONFIG_COMMANDS([default],[[ echo timestamp > stamp-h ]],[[]])
AC_OUTPUT

cat <<EOF

Configuration summary
---------------------

   * Installation prefix: ${prefix}

EOF
