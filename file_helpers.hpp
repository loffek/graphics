#ifndef FILE_HELPERS_HPP
#define FILE_HELPERS_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>       /* string */
#include <stdlib.h>     /* atof */
#include <vector>
#include <cstddef> /* size_t */

typedef struct{
    int length;
    size_t element_size;
    void* buffer;
}BufferContainer;

BufferContainer
getBufferFromFloatFile(const char* const filename);

BufferContainer
getBufferFromIntFile(const char* const filename);


#endif
