#ifndef PROPITIOUS_COMMON_CHARSETS
#define PROPITIOUS_COMMON_CHARSETS

namespace Propitious
{
#if defined(UNICODE)
#define PROPITIOUS_CHARSET_UNICODE
#else
#define PROPITIOUS_CHARSET_ANSI
#endif
}

#endif