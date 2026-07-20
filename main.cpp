#include "NumPattern.h"
#include <iostream>
#include "Controller.h"

void testEquivlenceOperator(NumPattern x, NumPattern y);

void testIncrementNumPattern(NumPattern x);

void testDecrementNumPattern(NumPattern y) {
    std::cout << y.returnObjectSize() << std::endl; // 8

    y--;
    --y;

    std::cout << y.returnObjectSize() << std::endl; //4
}

void testingAddition(NumPattern x, NumPattern y);

int main() {

    //Num Pattern tests
    NumPattern x(5,4,3);
    NumPattern y(5,4,4);

    testEquivlenceOperator(x,y);

    testIncrementNumPattern(x);

    testDecrementNumPattern(y);

    NumPattern z(5,1,1);
    NumPattern alpha(4,1,1);

    testingAddition(alpha,z);

    // testing addition
    WildPattern n1(5,4,3);
    WildPattern n2(5,4,4);

    NumPattern n3 = n1 + n2;
    std::cout << "n3 size: " << n3.returnObjectSize() << std::endl;

    n3 += 5;
    std::cout << "n3 size: " << n3.returnObjectSize() << std::endl;

    try {
        n3[1000];
    }catch(std::exception& e){ std::cout << e.what() << std::endl;}

    if (n1+ 5 == 5 + n1) std::cout << "(n1 +5) same as (5+ n1)" << std::endl; //true

     std::cout << "trackUtlity array status for n1: "<< n1;

    //Testing Controller overloading
    std::unique_ptr<std::unique_ptr<NumPattern>[]> p1;
    uint size  = 3;

    p1 = std::make_unique<std::unique_ptr<NumPattern>[]>(size);

    p1[0] = std::make_unique<NumPattern>(5,4,2);
    p1[1] = std::make_unique<WildPattern>(5,4,3);
    p1[2] = std::make_unique<DubPattern>(5,4,4);

    Controller c1(size, std::move(p1));

    std::unique_ptr<std::unique_ptr<NumPattern>[]> p2;
    size = 2;

    p2 = std::make_unique<std::unique_ptr<NumPattern>[]>(size);
    p2[0] = std::make_unique<NumPattern>(5,4,2);
    p2[1] = std::make_unique<WildPattern>(5,4,3);

    Controller c2(size, std::move(p2));

    if (c1 == c2) {
        std::cout << "(c1 == c2): true" << std::endl;
    }else std::cout << "(c1 == c2): false" << std::endl;;

    if (c1 != c2) {
        std::cout << "(c1 != c2): true" << std::endl;
    }else std::cout << "(c1 != c2): false" << std::endl;;

    ++c2;

    std::cout <<"c2 index 0 object: " << c2.kthObjectSize(0) << std::endl; //8
    std::cout << "c2 index 1 object: " << c2.kthObjectSize(1) << std::endl;

    --c2;

    std::cout << "c2 index 0 object: " << c2.kthObjectSize(0) << std::endl; //6
    std::cout << "c2 index 1 object: " << c2.kthObjectSize(1) << std::endl;

    std::cout << c2 << std::endl; //0,0

    c2.queryUnrestrictedNumber(0);

    std::cout << c2 << std::endl; //span should be set

    return 0;
}

void testingAddition(NumPattern x, NumPattern y) {
    NumPattern beta = x + y;
    std::cout << "beta object size: " << beta.returnObjectSize() << std::endl; //4

    for (int i = 0; i < beta.returnObjectSize(); i++) {
        std::cout << beta.generateRandomValue() << std::endl;
    }

    try {
        beta.generateRandomValue();
    }catch(std::exception& e){std::cout << e.what() << std::endl;}
}

void testIncrementNumPattern(NumPattern x) {
    ++x;
    x++;

    std::cout << x.returnObjectSize() << std::endl; //12
}

void testEquivlenceOperator(NumPattern x, NumPattern y) {
    if (x != y) std::cout << "true" << std::endl; //true
    else std::cout << "false" << std::endl;

    if (x == y) std::cout << "true" << std::endl; //true
    else std::cout << "false" << std::endl;

    x = y; //assignment

    if (x == y ) std::cout << "x and y are equal after deep copy" << std::endl;
}