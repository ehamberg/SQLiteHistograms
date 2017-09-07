/*

cl /Fohelpers.obj /c helpers.cpp  /EHsc
 && cl /Foratiohistogram.obj /c ratiohistogram.cpp /EHsc
 && cl /Fohistogram.obj /c histogram.cpp /EHsc
 && cl /FoRegistExt.obj /c RegistExt.cpp /EHsc
 && link /DLL /OUT:myextensions.sqlext RegistExt.obj histogram.obj /export:sqlite3_myextensions_init

With debug info:

cl /Fohelpers.obj /c helpers.cpp  /DDEBUG  /ZI /EHsc
 && cl /Foratiohistogram.obj /c ratiohistogram.cpp /DDEBUG  /ZI /EHsc
 && cl /Fohistogram.obj /c histogram.cpp /DDEBUG  /ZI /EHsc
 && cl /FoRegistExt.obj /c RegistExt.cpp  /DDEBUG  /ZI /EHsc
 && link /DLL /DEBUG /debugtype:cv /OUT:myextensions.sqlext helpers.obj RegistExt.obj histogram.obj ratiohistogram.obj /export:sqlite3_myextensions_init

*/

#include "RegistExt.h"




#ifdef __cplusplus
extern "C" {
#endif

SQLITE_EXTENSION_INIT1



sqlite3 *thisdb = NULL;


int sqlite3_myextensions_init( // always use lower case
  sqlite3 *db,
  char **pzErrMsg,
  const sqlite3_api_routines *pApi
  )
{
  int rc = SQLITE_OK;
  SQLITE_EXTENSION_INIT2(pApi);
#ifndef SQLITE_OMIT_VIRTUALTABLE
  if (sqlite3_libversion_number()<3008012)
  {
    *pzErrMsg = sqlite3_mprintf(
      "RegistExt requires SQLite 3.8.12 or later");
    return SQLITE_ERROR;
  }
  rc = sqlite3_create_module(db, "HISTO", &histoModule, 0);
  rc = sqlite3_create_module(db, "RATIOHISTO", &ratiohistoModule, 0);

#endif
  return rc;
}



#ifdef __cplusplus
}
#endif