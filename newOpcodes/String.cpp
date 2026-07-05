#include "String.h"

// 0D49=3, %3d% = compare_strings %1s% %2s% // IF and SET
// 0D49: 0@ = compare_strings "yes" "no" // IF and SET
// STRING_CMP
OpcodeResult WINAPI String::StrCmp(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	char strA[100], strB[100]; int result;
	params >> strA >> strB;
	result = strcmp(strA, strB);
	params << result << (result? orFalse : orTrue);
	return OR_CONTINUE;
}

// 0D4C=2,%2d% = string %1s% length
// 0D4C: 0@ = string "string" length
// STRING_LEN
OpcodeResult WINAPI String::StrLen(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	char str[100];
	params >> str;
	params << strlen(str);
	return OR_CONTINUE;
}

// 0D4D=2,copy_string %1s% to %2s%
// 0D4D: copy_string "yes" to 0@
// STRING_CPY
OpcodeResult WINAPI String::StrCpy(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	char src[100];
	params >> src;
	params << src;
	return OR_CONTINUE;
}

// 0D4A=2,concatenate_strings %1s% %2s%
// 0D4A: concatenate_strings 0@ " or no"
// STRING_CAT
OpcodeResult WINAPI String::StrCat(CScriptThread* thread)
{
	OpcodeParams params(thread, 2);
	char src[100]; unsigned int dst;
	params >> dst >> src;
	strcat((char *)dst, src);
	return OR_CONTINUE;
}

// 0D4B=3, %3d% = locate_substring %1s% %2s% // IF and SET
// 0D4B: 1@ = locate_substring 0@ ".bmp" // IF and SET
// STRING_STR
OpcodeResult WINAPI String::StrStr(CScriptThread* thread)
{
	OpcodeParams params(thread, 3);
	char str[100], sub[100]; unsigned int result;
	params >> str >> sub;
	result = (unsigned int)strstr(str, sub);
	params << result << (result? orTrue : orFalse);
	return OR_CONTINUE;
}