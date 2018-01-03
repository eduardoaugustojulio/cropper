#include <iostream>

#include "cropper.h"

int main(const int argc, const char **argv)
{
    if(argc < 2){
        std::cout << "usage: " << argv[0] << " {image} " << std::endl;
        return EXIT_FAILURE;
    }

    Cropper cropper(argv[1]);
}
