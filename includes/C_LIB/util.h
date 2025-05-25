#ifndef __UTIL_H
#define __UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TYPE.h"


#ifdef __cplusplus
extern "C"
{
#endif

#ifdef CLIB_EXPORTS
#define CLIB_API __declspec(dllexport)
#else
#define CLIB_API __declspec(dllimport)
#endif

/*******pOut->value �����Ҵ��Ͽ� �����ϴ� �Լ� �ܺο��� free�� �� �������*******/
CLIB_API int readFile(const char* filePath, UString* pOut);

//���ϰ�ο� ��ǲ���� Write
CLIB_API int writeFile(const UString* pIn, const char* filePath);

#ifdef __cplusplus
}
#endif

#endif