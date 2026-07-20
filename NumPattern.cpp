#include "NumPattern.h"

NumPattern::NumPattern(int xIn, int aIn, int cIn)
{
    if(xIn < 1)  throw std::invalid_argument("xIn must be greater than or equal to 1");
    if(aIn < 1)  throw std::invalid_argument("aIn must be greater than or equal to 1");
    if(cIn < 1)  throw std::invalid_argument("cIn must be greater than or equal to 1");

    x = xIn;
    a = aIn;
    c = cIn;
    kIndex = 1;
    disabledAmount = 0;

    x0 = xIn;

    m = a + c;
    trackUtility = std::make_unique<int[]>(m);

    for (int i = 0; i < m; i++)
    {
        trackUtility[i] = 1;
    }
}

void NumPattern::copy(const NumPattern &src)
{
    m = src.m;
    trackUtility = std::make_unique<int[]>(m);

    for (int i = 0; i < m; i++) {
        trackUtility[i] = src.trackUtility[i];
    }

    x = src.x;
    a = src.a;
    c = src.c;
    kIndex = src.kIndex;
    x0 = src.x0;
    disabledAmount = src.disabledAmount;
}

NumPattern::NumPattern(const NumPattern &src)
{
    copy(src);
}

NumPattern& NumPattern::operator=(const NumPattern &src)
{
    if (this == &src) return *this;
    copy(src);
    return *this;
}

NumPattern::NumPattern(NumPattern &&src) {
    m = src.m;
    trackUtility = std::move(src.trackUtility);

    x = src.x;
    a = src.a;
    c = src.c;
    kIndex = src.kIndex;
    x0 = src.x0;
    disabledAmount = src.disabledAmount;

    //zero out caller
    src.m = 0;
    src.trackUtility = nullptr;

    src.x = 0;
    src.a = 0;
    src.c = 0;
    src.kIndex = 0;
    src.x0 = 0;
    src.disabledAmount = 0;
}

NumPattern &NumPattern::operator=(NumPattern &&src) {
    std::swap(m, src.m);
    std::swap(trackUtility, src.trackUtility);

    std::swap(a, src.a);
    std::swap(c, src.c);
    std::swap(kIndex, src.kIndex);
    std::swap(x0, src.x0);
    std::swap(x, src.x);
    std::swap(disabledAmount, src.disabledAmount);

    return *this;
}

bool NumPattern::operator==(const NumPattern &objB) {
    if (m == objB.m && a == objB.a && x == objB.x && c == objB.c) return true;

    return false;
}

bool NumPattern::operator!=(const NumPattern &objB) {
    return !(*this == objB);
}

NumPattern NumPattern::IncNumPattern() {
    ++a;
    ++x;
    ++c;

    m = a + c;

    x0 = x;

    trackUtility = std::make_unique<int[]>(m);

    for (int i = 0; i < m; i++) {
        trackUtility[i] = 1;
    }

    return *this;
}

NumPattern NumPattern::DecNumPattern() {
    --a;
    --x;
    --c;

    m = a + c;

    x0 = x;

    trackUtility = std::make_unique<int[]>(m);

    for (int i = 0; i < m; i++) {
        trackUtility[i] = 1;
    }

    return *this;
}

NumPattern NumPattern::operator++() {
    return IncNumPattern();
}

NumPattern NumPattern::operator++(int) {
    NumPattern oldState = *this;
    IncNumPattern();
    return oldState;
}

NumPattern NumPattern::operator--() {
    return DecNumPattern();
}

NumPattern NumPattern::operator--(int) {
    NumPattern oldState = *this;
    DecNumPattern();
    return oldState;
}

int &NumPattern::operator[](int index) {
    if (index < 0 || index >= m) throw std::range_error("Index out of range");
    return trackUtility[index];
}

NumPattern NumPattern::operator+(const NumPattern &objB) {
    NumPattern newObject = *this;

    newObject.x = x + objB.x;
    newObject.a = a + objB.a;
    newObject.c = c + objB.c;

    newObject.m = newObject.a + newObject.c;

    newObject.x0 = newObject.x;

    newObject.kIndex = 0;
    newObject.disabledAmount = 0;

    newObject.trackUtility = std::make_unique<int[]>(newObject.m);

    for (int i = 0; i < newObject.m; i++) {
        newObject.trackUtility[i] = 1;
    }

    return newObject;
}

NumPattern& NumPattern::operator+=(const NumPattern &objB) {
    x += objB.x;
    a += objB.a;
    c += objB.c;

    m = a + c;

    x0 = x;

    kIndex = 0;
    disabledAmount = 0;
    trackUtility = std::make_unique<int[]>(m);
    for (int i = 0; i < m; i++) {
        trackUtility[i] = 1;
    }
    return *this;
}

NumPattern &NumPattern::operator+=(int increment) {
    x += increment;
    a += increment;
    c += increment;

    m = a + c;

    x0 = x;
    kIndex = 0;
    disabledAmount = 0;
    trackUtility = std::make_unique<int[]>(m);
    for (int i = 0; i < m; i++) {
        trackUtility[i] = 1;
    }
    return *this;
}

NumPattern NumPattern::operator+(int increment) {
    NumPattern newObject = *this;

    newObject.x += increment;
    newObject.a += increment;
    newObject.c += increment;

    newObject.m = newObject.a + newObject.c;

    newObject.x0 = newObject.x;

    newObject.kIndex = 0;
    newObject.disabledAmount = 0;
    newObject.trackUtility = std::make_unique<int[]>(newObject.m);

    for (int i = 0; i < newObject.m; i++) {
        newObject.trackUtility[i] = 1;
    }

    return newObject;
}


int NumPattern::computeRandomValue(int x, int a, int c, int m) {return (a * x + c) % m;}

int NumPattern::generateRandomValue()
{
    if (kIndex >= m || trackUtility[kIndex] == 0) throw std::invalid_argument("index >= m or index disabled");

    x = computeRandomValue(x, a, c, m);

    kIndex++;

    return x;
}

void NumPattern::disableKthTerm(unsigned int k)
{
    if (trackUtility[k] == 1){
        trackUtility[k] = 0;
        disabledAmount++;
        if (disabledAmount >= m) resetObject();
    }
}

void NumPattern::enableKthTerm(unsigned int k)
{
    if (trackUtility[k] == 0){
        trackUtility[k] = 1;
        disabledAmount--;
    }
}

int NumPattern::kthTermStatus(unsigned int k)
{
    return trackUtility[k];
}

void NumPattern::resetObject()
{
    x = x0;

    kIndex = 1;

    disabledAmount = 0;

    for (int i = 0; i < m; i++){
        trackUtility[i] = 1;
    }
}

int NumPattern::returnDisabledAmount() const {return disabledAmount;}

//Post: size of object is returned
int NumPattern::returnObjectSize() const {return m;}

int NumPattern::remainingGenerates() const {return m - kIndex;}

//DubPattern methods
DubPattern::DubPattern(int xIn, int aIn, int cIn):NumPattern(xIn, aIn, cIn) {
    isActive = true;
    maxDisableAmount = (aIn + cIn) / 2;
}

int DubPattern::generateRandomValue() {
    if (!isActive) throw std::invalid_argument("Object is not active");

    return NumPattern::generateRandomValue();
}

void DubPattern::disableKthTerm(unsigned int k) {
    if (!isActive) throw std::invalid_argument("Object is not active");
    if(maxDisableAmount == 0) {
        isActive = false;
        throw std::invalid_argument("No more disables left");
    }

    NumPattern::disableKthTerm(k);
    maxDisableAmount--;
}

void DubPattern::enableKthTerm(unsigned int k) {
    if (!isActive) throw std::invalid_argument("Object is not active");
    NumPattern::enableKthTerm(k);
}

// WildPattern
WildPattern::WildPattern(int xIn, int aIn, int cIn):NumPattern(xIn, aIn, cIn) {
    resetAmountLeft = (aIn + cIn) / 2;
}

int WildPattern::mapKtoEnabledIndex(unsigned int k) {
    int enabledIndex = 0;

    for (unsigned int i = 0; i < returnObjectSize(); i++)
    {
        if (kthTermStatus(i) == 1)
        {
            if (enabledIndex == k) return (int)i ;
            enabledIndex++;
        }
    }
    return -1;
}

int WildPattern::returnResetAmountLeft() {return resetAmountLeft;}

void WildPattern::disableKthTerm(unsigned int k) {
    int enabledK = mapKtoEnabledIndex(k);
    if (enabledK == -1) throw std::invalid_argument("No enabled kth index found");
    NumPattern::disableKthTerm((unsigned int)enabledK);
}

void WildPattern::resetObject() {
    if (resetAmountLeft == 0) throw std::invalid_argument("No more Resets left");
    NumPattern::resetObject();
    resetAmountLeft--;
}

//global functions
NumPattern operator+(int inc, NumPattern& b)
{
    return b + inc;
}

std::ostream& operator<<(std::ostream& out, const NumPattern& src) {
    for (unsigned int i = 0; i < src.returnObjectSize(); i++) {
        out << src.trackUtility[i] << " ";
    }
    out << std::endl;

    return out;
}
