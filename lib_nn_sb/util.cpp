#include "util.h"
#include <fstream>
#include <iostream>

util::util()
{

}

int reverseInt (int i)
{
    unsigned char c1, c2, c3, c4;

    c1 = i & 255;
    c2 = (i >> 8) & 255;
    c3 = (i >> 16) & 255;
    c4 = (i >> 24) & 255;

    return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}

Tensor util::read_idx(std::string file_path)
{
    std::ifstream file;
    file.open(file_path,std::ios::binary);

    if(!file){
        std::cout <<"Could not open file \n";
        return Tensor(0,0);
    }
    int magic_number;
    int num_images;
    int num_cols;
    int num_rows;

    file.read((char*)&magic_number,sizeof(magic_number));
    magic_number = reverseInt(magic_number);

    file.read((char*)&num_images,sizeof(num_images));
    num_images = reverseInt(num_images);

    file.read((char*)&num_cols,sizeof(num_cols));
    num_cols = reverseInt(num_cols);

    file.read((char*)&num_rows,sizeof(num_rows));
    num_rows = reverseInt(num_rows);

    unsigned int i;
    for (i = 0; i < num_images; i++) {
        unsigned int j;
        for (j = 0; j < num_cols; j++) {
            unsigned int k;
            for (k = 0; k< num_rows; k++) {


            }

        }

    }









}
