/**
 * File Handler main module. @jpvanegasc/FileHandler
 * 
 * @author: Juan Vanegas. git: jpvanegasc
 * 
 * Last modification: Dec 8, 2020.
 */
#ifndef __FILE_HANDLER_H
#define __FILE_HANDLER_H

#include<iostream>
#include<cmath>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<exception>

#define vector(type) std::vector<type>
#define vector2D(type) std::vector<vector(type)>

struct FileNotOpened: public std::exception{
    const char * what() const throw () {
        return "Unable to open file";
    }
};

namespace fh{
    void vec_load_file(std::string filename, vector2D(double) &data, char delim=',', char comment='#');
    void load_file(std::string filename, double **&data, int &rows, int &columns, char delim=',', char comment='#');

    void clear(double **&data, int rows, bool set_null=true);
    void __check_vec(vector2D(double) &data);
    std::string get_full_file(std::ifstream f);
}

#endif