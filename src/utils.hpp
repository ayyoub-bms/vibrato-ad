#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <memory>
#include <fstream>
#include "helper.hpp"

using namespace std;

// Quick and dirty way to export data to csv
template<template <class> class C, typename T>
void data2csv(string name, shared_ptr<C<T>> v, string header="") {
    ofstream myfile(name + ".csv");
    if (myfile.is_open()) {
    	if (!header.empty()){
    		myfile << header << endl;
    	}
    	try {
    		myfile << v->headers() << endl;
		} catch (const std::exception& e) {
			cout << "WARNING:  " << e.what();
		}
    	for (const auto& i: *v) {
            myfile << i << endl;
        }
        myfile.close();
        cout << "Writing to file " << name << ".csv....Done! " << endl;
    } else {
        cout << "Unable to open file " << name << ".csv" << endl;
    }
}

#endif  // UTILS_HPP
