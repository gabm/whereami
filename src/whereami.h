// (‑●‑●)> dual licensed under the WTFPL v2 and MIT licenses
//   without any warranty.
//   by Gregory Pakosz (@gpakosz)
// https://github.com/gpakosz/whereami

#ifndef WHEREAMI_H
#define WHEREAMI_H

#ifdef __cplusplus
extern "C" {
#endif


#ifndef WAI_FUNCSPEC
#ifdef _WIN32
#ifdef WAI_EXPORT
#define WAI_FUNCSPEC __declspec(dllexport)
#else
#define WAI_FUNCSPEC __declspec(dllimport)
#endif
#else
#define WAI_FUNCSPEC
#endif
#endif

#ifndef WAI_PREFIX
#define WAI_PREFIX(function) wai_##function
#endif
    
    /**
     * Returns the path to the current executable.
     *
     * Usage:
     *  - first call `int length = wai_getExecutablePath(NULL, 0, NULL);` to
     *    retrieve the length of the path
     *  - allocate the destination buffer with `path = (char*)malloc(length + 1);`
     *  - call `wai_getExecutablePath(path, length, NULL)` again to retrieve the
     *    path
     *  - add a terminal NUL character with `path[length] = '\0';`
     *
     * @param out destination buffer, optional
     * @param capacity destination buffer capacity
     * @param dirname_length optional recipient for the length of the dirname part
     *   of the path.
     *
     * @return the length of the executable path on success (without a terminal NUL
     * character), otherwise `-1`
     */
    WAI_FUNCSPEC
    int WAI_PREFIX(getExecutablePath)(char* out, int capacity, int* dirname_length);
    
    /**
     * Returns the path to the current module
     *
     * Usage:
     *  - first call `int length = wai_getModulePath(NULL, 0, NULL);` to retrieve
     *    the length  of the path
     *  - allocate the destination buffer with `path = (char*)malloc(length + 1);`
     *  - call `wai_getModulePath(path, length, NULL)` again to retrieve the path
     *  - add a terminal NUL character with `path[length] = '\0';`
     *
     * @param out destination buffer, optional
     * @param capacity destination buffer capacity
     * @param dirname_length optional recipient for the length of the dirname part
     *   of the path.
     *
     * @return the length of the module path on success (without a terminal NUL
     * character), otherwise `-1`
     */
    WAI_FUNCSPEC
    int WAI_PREFIX(getModulePath)(char* out, int capacity, int* dirname_length);
    
#ifdef __cplusplus
}

#include <string>
#include <vector>
#define CPP_FUNCTION(function)     inline std::string function() { \
int length, dirname_length; \
length = WAI_PREFIX(function)(NULL, 0, &dirname_length); \
if (length <= 0) return ""; \
    std::vector<char> path; \
    path.resize(length + 1); \
    WAI_PREFIX(function)(path.data(), length, &dirname_length); \
    path[dirname_length + 1] = '\0'; \
    return std::string(path.data()); \
}

namespace wai {
    CPP_FUNCTION(getExecutablePath);
    CPP_FUNCTION(getModulePath);
}
#endif

#endif // #ifndef WHEREAMI_H
