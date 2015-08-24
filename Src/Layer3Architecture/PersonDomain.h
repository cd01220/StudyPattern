#ifndef _PersonDomain_h_
#define _PersonDomain_h_

class Person
{
private:
    uint_t id;
    uint_t age;

public:
    Person()
    {
        id = 0;
        age = 0;
    }

    Person(uint_t id, uint_t age)
    {
        Person::id = id;
        Person::age = age;
    }

    uint_t GetId();
    void SetId(uint_t);
    uint_t GetAge();
    void SetAge(uint_t);
};

class Company
{
public:
    uint_t CalculateSalarySum();
};

#endif