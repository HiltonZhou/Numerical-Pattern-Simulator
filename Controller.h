#ifndef Controller_h
#define Controller_h

#include "NumPattern.h"
#include <memory>
#include <iostream>
#include <ostream>

class Controller {

private:

    unsigned int s;
    std::unique_ptr<std::unique_ptr<NumPattern>[]> x;

    int prevNum;
    int currentNum;

    int span;
    int spanLeftVal;
    int spanRightVal;

    void setSpanValues(int currentVal);
    int queryValue(unsigned kthObject);
    int valueAwayFromSpan(unsigned kthObject);
    int getValueWithSpan(unsigned kthObject);

    Controller& increment();

    Controller& decrement();

public:
    Controller(unsigned int s, std::unique_ptr<std::unique_ptr<NumPattern>[]> p);

    Controller& operator=(Controller &&src);

    Controller(Controller &&src);

    // Pre: size > 0, p cannot be null
    // Post: x is replaced by the injected p returns true. if p is null returns false
    bool inject(unsigned int size, std::unique_ptr<std::unique_ptr<NumPattern>[]> p);

    // Pre: kthObject < s
    // Post: returns generated value, sets currentNum, prevNum, span, spanLeft, spanRight
    int queryUnrestrictedNumber(unsigned kthObject);

    // Pre: kthObject < s, span > 0
    // Post: returns generated value outside of span, sets currentNum, prevNum, span, spanLeft, spanRight
    int queryValueAwayFromSpan(unsigned kthObject);

    // Pre: m > 0
    // Post: finds first object >= m, returns the queried value from such object
    //       sets currentNum, prevNum, span, spanLeft, spanRight.
    //       If no objects exist, throws exception.
    int queryValueFromAtLeastM(int m);

    // Pre: objectNumber < s, kthTerm must be less than size of that NumPattern
    // Post: sets that object kth term to disabled status
    void disableKthTermOfObject(unsigned objectNumber, unsigned kthTerm);

    // Pre: objectNumber < s, kthTerm must be less than size of that NumPattern
    // Post: sets that object kth term to enabled status
    void enableKthTermOfObject(unsigned objectNumber, unsigned kthTerm);

    // Pre: objectNumber < s, kthTerm must be less than size of that NumPattern
    // Post: returns the status 1 (Enabled) or 0 (Disabled).
    int statusKthTermOfObject(unsigned int objectNumber, unsigned int kthTerm);

    // Pre: objectNumber < s
    // Post: returns number of disabled in that object
    int numberOfDisable(unsigned int objectNumber);

    // Pre: objectNumber < s, newObject not null
    // Post: if disabledAmount >= size/2 replace object return true, else no change
    bool replaceNumPatternObject(unsigned int objectNumber, std::unique_ptr<NumPattern> object);

    // Pre: objectNumber < s
    // Post: returns size of kth object
    int kthObjectSize(unsigned int objectNumber);

    // Pre: objectNumber < s
    // Post: kth NumPattern object is reseted
    void resetKthObject(unsigned int objectNumber);

    //Post: returns controller size;
    int getControllerSize() const;

    //Post: return true of Controller == Controller else false
    bool operator==(const Controller& objB);

    //Post: returns trye if Controller != Controller else false
    bool operator!=(const Controller& objB);

    //Pre: increments all NumPattern by 1
    Controller& operator++();

    //Pre: decrements all NumPattern by 1
    Controller& operator--();

    //Post: prints span range
    friend std::ostream& operator<<(std::ostream&, const Controller&);
};

#endif
