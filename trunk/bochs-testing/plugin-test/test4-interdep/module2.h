#if defined(WIN32) || defined(__CYGWIN__)
#  if defined(MODULE2_DLL_EXPORT) && defined(DLL_EXPORT)
#    warning case 1
#    define MODULE2API(type) __declspec(dllexport) type
#  endif
#  ifdef MODULE2_DLL_IMPORT
#    warning case 2
#    define MODULE2API(type) __declspec(dllimport) type
#  endif
#endif
#ifndef MODULE2API
#  warning case 3
#  define MODULE2API(type) type
#endif

MODULE2API(extern int) n_operations;
MODULE2API(void) operation_occurred ();
