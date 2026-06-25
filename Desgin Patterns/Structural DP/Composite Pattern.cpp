#include <bits/stdc++.h>
using namespace std;

class OrganizationComponent
{
public:
    virtual int getEmpCount() = 0;
    virtual ~OrganizationComponent() = default;
};

class Employee : public OrganizationComponent
{
    string name;

public:
    Employee(string name)
    {
        this->name = name;
    }
    int getEmpCount()
    {
        return 1;
    }
};

class CompositeOrganization : public OrganizationComponent
{
    vector<shared_ptr<OrganizationComponent>> v;

public:
    void add(shared_ptr<OrganizationComponent> c)
    {
        v.push_back(c);
    }
    int getEmpCount()
    {
        int ans = 0;
        for (auto it : v)
        {
            ans += it->getEmpCount();
        }
        return ans;
    }
};

class Team : public CompositeOrganization
{
};
class Department : public CompositeOrganization
{
};

class Company : public CompositeOrganization
{
};

int main()
{
    auto emp1 = make_shared<Employee>("abhishek1");
    auto emp2 = make_shared<Employee>("abhishek2");
    auto emp3 = make_shared<Employee>("abhishek3");
    auto emp4 = make_shared<Employee>("abhishek4");

    auto t1 = make_shared<Team>();
    auto t2 = make_shared<Team>();

    auto d1 = make_shared<Department>();

    auto c = make_shared<Company>();

    t1->add(emp1);
    t1->add(emp2);
    t1->add(emp3);

    t2->add(emp4);

    d1->add(t1);
    d1->add(t2);

    c->add(d1);

    cout << t1->getEmpCount() << endl;
    cout << t2->getEmpCount() << endl;
    cout << d1->getEmpCount() << endl;

    return 0;
}

// The trick is :

//     Don't start with the classes. Start with the operation.

//     Ask :

//     "What should work on both a single item and a group of items?"

//     That becomes the interface.

//     Examples :

//     Employee +
//     Team + Department + Company

//                             Operation :

//     getEmployeeCount() displayHierarchy() calculateSalary()

//         So :

//     class OrganizationComponent
// {
//     virtual int getEmployeeCount() = 0;
// };

//-------------------------------------------------------------------------------------------------------------

// For Composite, the structure would look like:

//                     Company
//                        |
//         --------------------------------
//         |                              |
//    Department A                  Department B
//         |                              |
//    ------------                  ------------
//    |          |                  |          |
//  Team 1    Team 2            Team 3     Team 4
//    |          |                  |
//  -----      -----             --------
//  |   |      |   |             |   |  |
// E1  E2     E3  E4            E5 E6 E7

// Now map it to Composite:

// Component
//    ^
//    |
// -------------------------
// |                       |
// Employee             OrganizationUnit
// (Leaf)                (Composite)
//                            ^
//                            |
//                   -----------------
//                   |               |
//               Team          Department
//                                ^
//                                |
//                             Company

// Where:

// Employee      -> Leaf
// Team          -> Composite
// Department    -> Composite
// Company       -> Composite

// And every node supports the same operation, for example:

// getEmployeeCount()
// displayHierarchy()
// calculateSalary()

// So:

// Employee.getEmployeeCount()   -> 1

// Team.getEmployeeCount()
//     = sum of employees

// Department.getEmployeeCount()
//     = sum of teams

// Company.getEmployeeCount()
//     = sum of departments

// This is the hallmark of Composite:

// Leaf and Group are treated uniformly through the same interface.

// The moment you see:

// Company
//  └── Department
//       └── Team
//            └── Employee

// and want the same operation to work at every level, think Composite Pattern.

// --------------------------------------------------------------------------------------------------------------------------------------

/// Then Composite should not own it.

// In that case:

// vector<OrganizationComponent*>

// or

// vector<shared_ptr<OrganizationComponent>>

// may be the right design.

// Think of ownership separately from hierarchy.

// Case 1: Tree ownership (most Composite examples)
// Company owns Department
// Department owns Team
// Team owns Employee

// Use:

// unique_ptr

// because a Team belongs to exactly one Department.

// Case 2: Shared objects

// Suppose:

// Team Backend

// is referenced from multiple places.

// Then:

// Department A ----+
//                  |
//                  +----> Backend Team
//                  |
// Department B ----+

// Now unique ownership doesn't exist.

// Use:

// shared_ptr

// So your statement:

// "What if composite dies and I still want to use floor?"

// is actually saying:

// Composite does NOT own floor.

// If that's your business rule, then don't use unique_ptr there.

// The reason I suggested unique_ptr is because most Composite hierarchies imply:

// parent owns children

//-----------------------------------------------------------------------------------------------

// You don't need shared_ptr for that. we implemented above just for implemetation

// Production code would do:

// auto t1 = make_unique<Team>();

// Team* teamPtr = t1.get();   // observer only

// d1->add(move(t1));

// Later:

// cout << teamPtr->getEmpCount() << endl;

// works perfectly.

// Why?
// Department owns Team      (unique_ptr)
// teamPtr observes Team     (raw pointer)

// Ownership and access are different things.

// Think of it this way:

// shared_ptr
//     => I own it

// raw pointer/reference
//     => I can access it

// But one caveat — the raw observer teamPtr is only safe as long as the owner (d1) is alive. If d1 gets destroyed before you use teamPtr, it's a dangling pointer. With shared_ptr that can't happen.
// So:

// unique_ptr + raw observer → faster, more explicit, fine when lifetimes are clear (which in a tree structure they usually are — parent always outlives child)
// shared_ptr → safer, slight overhead, better when lifetimes are unclear

// production prefers raw ptr Because shared_ptr has overhead:

// Atomic reference counting — every copy/destroy does an atomic increment/decrement. In a large org tree with thousands of nodes this adds up.
