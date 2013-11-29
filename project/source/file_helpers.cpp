#include "file_helpers.hpp"

BufferContainer
getBufferFromFloatFile(const char* const filename){

    std::vector <float> data;
    int length = 0;
    std::ifstream infile( filename );

    while (infile){
        std::string str_line;
        if (!getline( infile, str_line ))
            break;
        std::istringstream ss( str_line );

        while (ss)
        {
            std::string str_number;
            float number;
            if (!getline( ss, str_number, ',' ))
                break;
            number = atof(str_number.c_str());
            data.push_back( number );
            length ++;
        }

    }
    if (!infile.eof()){
        fprintf( stderr, "Fooey!\n");
    }

    float* buffer = new float[length]();
    std::copy(data.begin(), data.end(), buffer);

    BufferContainer ret;
    ret.length = length;
    ret.element_size = sizeof(float);
    ret.buffer = (void*)buffer;

    return ret;
}

BufferContainer
getBufferFromIntFile(const char* const filename){

    std::vector <unsigned short> data;
    int length = 0;
    std::ifstream infile( filename );

    while (infile){
        std::string str_line;
        if (!getline( infile, str_line ))
            break;
        std::istringstream ss( str_line );

        while (ss)
        {
            std::string str_number;
            int number;
            if (!getline( ss, str_number, ',' ))
                break;
            number = (unsigned short)atoi(str_number.c_str());
            data.push_back( number );
            length ++;
        }

    }
    if (!infile.eof()){
        fprintf( stderr, "Fooey!\n");
    }

    unsigned short* buffer = new unsigned short[length]();
    std::copy(data.begin(), data.end(), buffer);

    BufferContainer ret;
    ret.length = length;
    ret.element_size = sizeof(unsigned short);
    ret.buffer = (void*)buffer;

    return ret;
}
