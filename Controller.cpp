#include "Controller.h"
#include "NumPattern.h"

Controller::Controller(unsigned int size, std::unique_ptr<std::unique_ptr<NumPattern>[]> p)
{
    if(size <= 0) throw std::invalid_argument("size must be greater than zero");

    this->x = std::move(p);
    this->s = size;

    prevNum = 0;
    currentNum = 0;
    span = 0;
    spanLeftVal = 0;
    spanRightVal = 0;
}

Controller &Controller::operator=(Controller &&src)
{
    std::swap(s,src.s);
    std::swap(x,src.x);

    std::swap(prevNum,src.prevNum);
    std::swap(currentNum,src.currentNum);
    std::swap(spanLeftVal,src.spanLeftVal);
    std::swap(spanRightVal,src.spanRightVal);
    std::swap(span,src.span);

    return *this;
}

Controller::Controller(Controller &&src)
{
    s = src.s;
    x = std::move(src.x);

    prevNum = src.prevNum;
    currentNum = src.currentNum;
    span = src.span;
    spanLeftVal = src.spanLeftVal;
    spanRightVal = src.spanRightVal;

    //zero out caller
    src.s = 0;
    src.x = nullptr;

    src.prevNum = 0;
    src.currentNum = 0;
    src.span = 0;
    src.spanLeftVal = 0;
    src.spanRightVal = 0;

}

bool Controller::inject(unsigned int size, std::unique_ptr<std::unique_ptr<NumPattern>[]> p)
{
    if(size <= 0) return false;
    if(p == nullptr) return false;

    x = std::move(p);
    return true;
}

void Controller::setSpanValues(int currentVal) {
    span = currentVal/2;
    spanLeftVal = currentVal - span;
    spanRightVal = currentVal + span;
}

int Controller::queryUnrestrictedNumber(unsigned int kthObject) {
    if(kthObject >= s) throw std::invalid_argument("kthObject must be less than s");

    return queryValue(kthObject);
}

int Controller::queryValueAwayFromSpan(unsigned int kthObject)
{
    if(kthObject >= s) throw std::invalid_argument("kthObject must be less than s");
    if(span <= 0) throw std::invalid_argument("span must be greater zero");

    return valueAwayFromSpan(kthObject);
}

int Controller::queryValue(unsigned int kthObject)
{
    currentNum = x[kthObject]->generateRandomValue();
    setSpanValues(currentNum);
    return prevNum = currentNum;
}

int Controller::valueAwayFromSpan(unsigned int kthObject)
{
    currentNum = getValueWithSpan(kthObject);

    if (currentNum == -1) throw std::invalid_argument("No such value outside the span");

    setSpanValues(currentNum);
    return prevNum = currentNum;
}

int Controller::queryValueFromAtLeastM(int m)
{
    if(m <= 0) throw std::invalid_argument("m must be greater than zero");

    for (unsigned int i = 0; i < s; i++) {
        if (m <= kthObjectSize(i)) return queryValue(i);
    }

    throw std::invalid_argument("No NumPattern has object sized at least m");
}

int Controller::getValueWithSpan(unsigned int kthObject)
{
    int returnVal;
    int remainingGenerateAttempt = x[kthObject]->remainingGenerates();

    for (int i = 0; i < remainingGenerateAttempt; i++)
    {
        returnVal = x[kthObject]->generateRandomValue();
        if ((returnVal <= spanLeftVal || returnVal >= spanRightVal)) return returnVal;
    }

    return -1;
}

void Controller::disableKthTermOfObject(unsigned int objectNumber, unsigned int kthTerm) {
    x[objectNumber]->disableKthTerm(kthTerm);
}

void Controller::enableKthTermOfObject(unsigned int objectNumber, unsigned int kthTerm) {
    x[objectNumber]->enableKthTerm(kthTerm);
}

int Controller::statusKthTermOfObject(unsigned int objectNumber, unsigned int kthTerm) {
    return x[objectNumber]->kthTermStatus(kthTerm);
}

int Controller::numberOfDisable(unsigned int objectNumber) {
    return x[objectNumber]->returnDisabledAmount();
}

int Controller::getControllerSize() const {
    return s;
}

bool Controller::replaceNumPatternObject(unsigned int objectNumber, std::unique_ptr<NumPattern> object)
{
    int size = x[objectNumber]->returnObjectSize();
    int disabledAmount = x[objectNumber]->returnDisabledAmount();

    if (disabledAmount >= size/2) {
        x[objectNumber] = std::move(object);
        return true;
    }
    return false;
}

int Controller::kthObjectSize(unsigned int objectNumber) {
    return x[objectNumber]->returnObjectSize();
}

void Controller::resetKthObject(unsigned int objectNumber)
{
    x[objectNumber]->resetObject();
}

bool Controller::operator==(const Controller &objB) {

    if (s != objB.s) return false;

    for (int i= 0; i < s; i++) {
        if (*x[i] == *objB.x[i]) return true;
    }

    return false;
}

bool Controller::operator!=(const Controller &objB) {
    return !(*this == objB);
}

Controller& Controller::increment() {

    for (int i =0; i < s; i++) {
        ++(*x[i]);
    }
    return *this;
}

Controller& Controller::operator++() {
    return increment();
}

Controller& Controller::decrement() {
    for (int i =0; i < s; i++) {
        --(*x[i]);
    }
    return *this;
}

Controller& Controller::operator--() {
    return decrement();
}

std::ostream& operator<<(std::ostream& out, const Controller& obj) {
    std::cout << "Span range: " << obj.spanLeftVal << "," << obj.spanRightVal << std::endl;
    return out;
}


