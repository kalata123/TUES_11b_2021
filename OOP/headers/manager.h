#ifndef Manager_H
#define Manager_H
#include "employee.h"

class Manager : public Employee{
    int level;
    public:
        Manager();
        Manager(std::string name, int id, int level);
        void setLevel(int level);
        int getLevel() const;
}
#endif // !Manager_H