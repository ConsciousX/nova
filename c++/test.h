#pragma once

#include <iostream>

class A{
    public:
    A() : price(20000){
	std::cout<<"Defaut constructor"<<std::endl;
    }
    A(double b):price(b*1.1){
std::cout<<"Constructor 1"<<std::endl;
}
    double price;
};

class B:public A{
    public:
    B(double b):A(b){
	std::cout<<"B constructor"<<std::endl;
}
};

class C:public B{
    public:
    C(double b):B(b){
std::cout<<"C constructor"<<std::endl;
}
};


