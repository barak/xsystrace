#undef ENABLE_NLS
#undef HAVE_CATGETS
#undef HAVE_GETTEXT
#undef HAVE_LC_MESSAGES
#undef HAVE_STPCPY
#undef HAVE_LIBSM
#undef PACKAGE_LOCALE_DIR
#undef PACKAGE_DATA_DIR
#undef PACKAGE_SOURCE_DIR

@BOTTOM@

#ifndef HAVE_STRLCAT
unsigned int strlcat(char *, const char *, unsigned int);
#endif
        
#ifndef HAVE_STRLCPY
unsigned int strlcpy(char *, const char *, unsigned int);
#endif

