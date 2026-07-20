#include <memory>
#include <ostream>

#ifndef NumPattern_h
#define NumPattern_h

class NumPattern {
private:
    int x;
    int a;
    int c;
    int x0;
    int kIndex;
    int disabledAmount;
    int m;
    std::unique_ptr<int[]>trackUtility;

    int computeRandomValue(int x, int a, int c, int m);

    void copy(const NumPattern &src);

    NumPattern IncNumPattern();

    NumPattern DecNumPattern();

public:
    NumPattern(int xIn, int aIn, int cIn);

    NumPattern(const NumPattern& src);

    NumPattern& operator=(const NumPattern& src);

    NumPattern(NumPattern&& src);

    NumPattern& operator=(NumPattern&& src);

    //Post: returns true if equal false if not
    bool operator==(const NumPattern& objB);

    //Post: return true if not equal false if equal
    bool operator!=(const NumPattern& objB);

    //Pre:increments x,a,c by 1
    NumPattern operator++();

    //Post:increments x,a,c by 1
    NumPattern operator++(int);

    //Pre:decrements x,a,c by 1
    NumPattern operator--();

    //Post:decrements x,a,c by 1
    NumPattern operator--(int);

    //Post: if index is valid returns trackutlity[index]
    int& operator[](int index);

    //Post: Adds two NumPatternObjects and returns newObject
    NumPattern operator+(const NumPattern& objB);

    //Post: NumPattern object + int returns new object
    NumPattern operator+(int increment);

    //Post: NumPattern += NumPattern shortcut
    NumPattern& operator+=(const NumPattern& objB);

    //Post: NumPattern += int shortcut
    NumPattern& operator+=(int increment);

    //Post: prints trackUtility array
    friend std::ostream& operator<<(std::ostream&, const NumPattern&);

    // Returns next value (k+1)
    // if current term is disabled or current index is last on array, return -1 throw exception
    // Postcondition: KIndex is incremented by 1 and return queried value
    virtual int generateRandomValue();

    // Precondition: k >= 0 and k < m
    // Postcondition: Kth term is disabled and disabledAmount gets incremented by 1
    // final check if disabledAmount >= m, object resets to initial state
    virtual void disableKthTerm(unsigned int k);

    // Precondition: k >= 0 and k < m
    // Postcondition: Kth term is enabled and disabledAmount gets decremented by 1
    virtual void enableKthTerm(unsigned int k);

    // Precondition: k >= 0 and k < m
    // Post: returns status of kth index
    int kthTermStatus(unsigned int k);

    // Postcondition: x, kIndex, disabledAmount gets set back to initial state
    //                All kIndex are back to state Enabled
    virtual void resetObject();

    //Post: disabledAmount is returned
    int returnDisabledAmount() const;

    //Post: size of object is returned
    int returnObjectSize() const;

    //Post returns remaining number of generates allowed (m-kIndex)
    int remainingGenerates() const;

};

class DubPattern : public NumPattern {
private:

    bool isActive;
    int maxDisableAmount;

public:

    DubPattern(int xIn, int aIn, int cIn);

    // Pre: Object must be active
    // Post: return generated random value
    int generateRandomValue() override;

    // Pre: k >=0, k < m, must be active, maxDisableAmount != 0
    // Post: disables kth term and maxDisableAmount -1
     void disableKthTerm(unsigned int k) override;

    // Pre: k >= 0, k < m, must be active
    // Post: enabled kth term
    void enableKthTerm(unsigned int k) override;
};

class WildPattern : public NumPattern {

private:
    int resetAmountLeft;
    int mapKtoEnabledIndex(unsigned int k);
public:

    WildPattern(int xIn, int aIn, int cIn);

    // Post: returns current reset amount left
    int returnResetAmountLeft();

    // Pre: k >= 0 k < m, enableK != -1
    // Post: disables kth enabled index, if non exist throws exceptions
    void disableKthTerm(unsigned int k) override ;

    // Pre : resetAmountLeft != 0
    // Post: WildPattern object is reset and resetAmountLeft - 1
    void resetObject() override ;
};

//global functions to support mixe mode
NumPattern operator+(int inc, NumPattern& b);

#endif
