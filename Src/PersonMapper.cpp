#include "SystemInclude.h"
#if DependenceMode == IncludeHeader
#   include "PersonDomain.h"
#endif
#include "PersonMapper.h"

using namespace std;

#if DependenceMode == IncludeHeader
error_code PersonMapper::Find(uint_t id, Person& person)
{
    map<uint_t, Person>::iterator iter = hashMap.find(id);

    if (iter != hashMap.end())
    {
        person = iter->second;
        return error_code();
    }
    /* select * from table where id == ? */
    uint_t age = 0;
    person.SetId(id);
    person.SetAge(age);
    hashMap.insert(make_pair(id, person));

    return error_code();
}

error_code PersonMapper::FindAll(Records& list)
{
    list<Person> allPersons;
    /*  1 select * from PersonTable;
        2 add records in allPerson;
        We assume there are 2 recordes in database {id=1, age = 10}, {id=1, age = 30} 
    */
    allPersons.push_back(Person(1, 10));
    allPersons.push_back(Person(2, 30));
        
    list<Person>::iterator iter;
    for (iter = allPersons.begin(); iter != allPersons.end(); ++iter)
    {
        std::map<uint_t, Person>::iterator mapIter = hashMap.find(iter->GetId());

        if (mapIter == hashMap.end())
        {
            hashMap.insert(std::make_pair(iter->GetId(), *iter));
            records.push_back(*iter);
        }
        else
        {
            records.push_back(*iter);
        }
    }
        
    return error_code();
}
#endif