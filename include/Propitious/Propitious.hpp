#if defined( PROPITIOUS_EXPORTS )
#define useful __declspec(dllexport)
#else
#define useful __declspec(dllimport)
#endif