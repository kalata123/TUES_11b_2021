#ifndef CAR_HH
#define CAR_HH
#include <land.hh>
class Car : public Land{
    int sth;
    public:
        Car();
        Car(int sth);
}

#endif // !CAR_HH