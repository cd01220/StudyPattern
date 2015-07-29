#include "SystemInclude.h"
#include "PersonMapper.h"
#include "PersonDomain.h"

using namespace std;
/* Example:
    Company company;
    cout << company.CalculateSalarySum() << endl;
 */
uint_t Person::GetId()
{
    return id;
}

void Person::SetId(uint_t theId)
{
    id = theId;
}

uint_t Person::GetAge()
{
    return age;
}

void Person::SetAge(uint_t theAge)
{
    age = theAge;
}

uint_t Company::CalculateSalarySum()
{
    uint_t sum = 0;
    PersonMapper<Person> mapper;
    list<Person> records;
    mapper.FindAll(records);

    list<Person>::iterator iter;
    for (iter = records.begin(); iter != records.end(); ++iter)
    {
        if (iter->GetAge() > 20)
        {
            sum = sum + 100;
        }
    }

    Person person;
    error_code errCode = mapper.Find(1, person);
    if (!errCode)
    {
        cout << "record of (id = 1) exist, age = " << person.GetAge() << endl;
    }

    return sum;
}