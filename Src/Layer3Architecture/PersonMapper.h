#ifndef _PersonMapper_h_
#define _PersonMapper_h_

/*   
IncludeHeaderMode:  bouth PersonMapper.cpp and PersonDomain.cpp should include each other's .h file.
TemplateMode     :  PersonMapper is desinged as a template class.  Person play as uppler layer of PersonMapper.
                    So PersonMapper do not need include "Person.h"
*/
#define IncludeHeaderMode 1
#define TemplateMode      2

#define DependenceMode TemplateMode

#if DependenceMode == IncludeHeaderMode
class Person;
class PersonMapper
{
public:
    typedef std::list<Person> Records;
    std::error_code Update();
    std::error_code Find(uint_t id, Person& person);
    std::error_code FindAll(Records&);

private:
     std::map<uint_t, Person> hashMap;
};

#else

template<typename Person>
class PersonMapper
{
public:
    typedef std::list<Person> Records;

    std::error_code Update();
    std::error_code Find(uint_t id, Person& person)
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

    std::error_code FindAll(Records& records)
    {
        std::list<Person> allPersons;
        /*  1 select * from PersonTable;
            2 add records in allPerson;
            We assume there are 2 recordes in database {id=1, age = 10}, {id=1, age = 30} 
         */
        allPersons.push_back(Person(1, 10));
        allPersons.push_back(Person(2, 30));
        
        std::list<Person>::iterator iter;
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
    
        return std::error_code();
    }

private:
     std::map<uint_t, Person> hashMap;
};

#endif

#endif