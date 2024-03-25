// Node *************************************************************
// Protected Data Members
// Node * next, Node * prev
# pragma once


/**
Default Constructor
    input:  Node object
    output: Empty node Object
*/
template <typename TYPE>
Node<TYPE>::Node():
    next(nullptr), prev(nullptr) {}


/**
Default Deconstructor
    input:  End of Node Lifespan
    output: Deallocate Node Dynamic Memory
*/
template <typename TYPE>
Node<TYPE>::~Node() {}


/**
Copy Constructor
    input:  Node Object and TYPE to_add
    output: Fill Node With the TYPE to_add 
*/
template <typename TYPE>
Node<TYPE>::Node(const TYPE & to_add):
    next(nullptr), prev(nullptr)
{

    data = to_add;
}


/**
Pass Which Type to display up the tree
    input: Pet Object
    output: cout << The Data Up the tree
*/
template <typename TYPE>
int Node<TYPE>::display()
{
    cout << TYPE::data;
    return 1;
}


/**
Get Next Pointer in DLL
    input:  Current Node
    output: Output Node next in line
*/
template <typename TYPE>
Node<TYPE> *& Node<TYPE>::get_next()
{
    return next;
}


/**
Get Prev Pointer in DLL
    input:  Current Node
    output: Output Node prev Node
*/
template <typename TYPE>
Node<TYPE> *& Node<TYPE>::get_prev()
{
    return prev;
}


/**
Set The Next Node Current Node Points To
    input:  Current Node
    output: Current Node next to src
*/
template <typename TYPE>
int Node<TYPE>::set_next(Node<TYPE> *& src)
{
    if(!src) return 0;
    next = src;
    return 1;
}


/**
Set The Prev Node Current Node Points To
    input:  Current Node
    output: Current Node Prev to src
*/
template <typename TYPE>
int Node<TYPE>::set_prev(Node<TYPE> *& src)
{
    if(!prev) return 0;
    prev = src;
    return 1;
}


/**
Get the data of the current Node to modify
    input:  Current Node
    output: Current Nodes Data
*/
template <typename TYPE>
TYPE & Node<TYPE>::get_data()
{
    return data;    
}


// DLL *************************************************************
// Protected Data Members
// Node * head, Node * tail


/**
Default Constructor
    input:  new DLL object
    output: empty DLL object
*/
template<typename TYPE>
DLL<TYPE>::DLL():
    head(nullptr), tail(nullptr) {}


/**
Default Deconstructor
    input:  End of DLL lifespan
    output: Deallocate DLL dynamic memory
*/
template<typename TYPE>
DLL<TYPE>::~DLL() 
{
    if(head)
    {
        remove_all();
    }
}


/**
Remove Wrapper
    input: DLL
    output: Deallocated DLL
        0 if no node
        returns count of Nodes Deallocated in recursive call
*/
template<typename TYPE>
int DLL<TYPE>::remove_all()
{
    if(!head) return 0;
    return remove_all(head);
}


/**
Remove recursive Call Head Recursion
    input: DLL and head pointer
    output: Deallocated DLL
        Removed Nodes from Back To Front returning count of removed
*/
template<typename TYPE>
int DLL<TYPE>::remove_all(node_ptr src)
{
    if(!src) return 0;
    // Head Recursion
    int removed_count = 1 + remove_all(src->get_next());
    // delete Back to Front
    delete src;
    src = nullptr;
    return removed_count;
}


/**
Random Number generator
    input:  integar
    output: random integar in range from 0 - integar given exclusive
*/
template<typename TYPE>
int DLL<TYPE>::random_number(int from)
{
    try{
        unsigned int random_number = rand() % from;
        return random_number;
    }
    catch(const exception & random_Error)
    {
        cout << "Random Number Generation Error" << random_Error.what() << endl;
        return 0;
    }
}


/**
Enum Conversion
    input:  enum integar, string to return
    output: string associated with enum number passed by reference
*/
template<typename TYPE>
int DLL<TYPE>::personality_num_conversion(int personality_num, string & personality)
{
    // unknown=0, sweet=1, loving=2, smart=3, stubborn=4, adventurer=5, lazy=6,
    // food_motivated=7, lap_animal=8, attention_seeker=9
    switch(personality_num)    
    {
        case 0:
        {
            personality = "unknown";
            break;
        }
        case 1:
        {
            personality = "sweet";
            break;
        }
        case 2:
        {
            personality = "loving";
            break;
        }
        case 3:
        {
            personality = "smart";
            break;
        }
        case 4:
        {
            personality = "stubborn";
            break;
        }
        case 5:
        {
            personality = "adventurer";
            break;
        }
        case 6:
        {
            personality = "lazy";
            break;
        }
        case 7:
        {
            personality = "food motivated";
            break;
        }
        case 8:
        {
            personality = "lap animal";
            break;
        }
        case 9:
        {
            personality = "attention seeker";
            break;
        }
    }
    return 1;
}


/**
Insert Wrapper
    input: DLL and TYPE to_add
    output: Inserted Node into DLL
        1. Insert New Head
        2. Insert New Tail
        3. Insert After Tail At The End
        Pass to Recursive Wrapper
        insert in sorted order smallest age to largest age
*/
template<typename TYPE>
int DLL<TYPE>::insert(const TYPE & to_add)
{
    // Give The Animal A Personality
    srand(time(nullptr));
    int rnd_choice = random_number(sizeof(PERSONALITY));
    string personality = "undetermined";
    personality_num_conversion(rnd_choice, personality);
    animal_personalities.push_back(personality);

    //if(!to_add) return 0;
    if(!head)
    {
        head = new Node<TYPE>(to_add);
        return 1;
    }
    if(!tail)
    {   
        // input > head?
        bool is_larger = to_add >= head->get_data();
        // insert at End
        if(is_larger)
        {
            tail = new Node<TYPE>(to_add);
            head->set_next(tail);
            tail->set_prev(head);
            return 1;
        }
        // Insert At Front
        else
        {
            // hold
            node_ptr curr = new Node<TYPE>(to_add);
            // Set
            tail = head;
            head = curr;
            head->set_next(tail);
            tail->set_prev(head);
            return 1;
        }
    }
    else
    {
        // recursively loop and insert in order
        return insert(head, to_add);
    }
}


/**
Insert Wrapper
    input: DLL, head ptr,  TYPE to_add
    output: Inserted Node into DLL
        3. Insert After Tail At The End
        insert in sorted order smallest age to largest age
*/
template<typename TYPE>
int DLL<TYPE>::insert(node_ptr src, const TYPE & to_add)
{  
    if(!src) return 0;

    // We are the largest node
    if(!src->get_next())
    {
        // hold
        node_ptr curr = new Node<TYPE>(to_add);
        curr->set_prev(src);
        // Set
        src->set_next(curr);
        tail = curr;
        return 1;
    }

    bool is_smaller = to_add < src->get_next()->get_data();
    // e.g., to_add = 3
    // [1] [2] { } [5] 
    //     src     src->get_next()
    // [1] [2] [3] [5]
    if(is_smaller) // 3 < 5
    {
        // Create
        node_ptr curr = new Node<TYPE>(to_add);
        // connect new node
        curr->set_next(src->get_next());
        curr->set_prev(src);
        // connect old next to curr
        src->get_next()->set_prev(curr);
        // connect previous to curr
        src->set_next(curr);
        
        return 1;
    }
    return insert(src->get_next(), to_add);
}


/**
1. Handle The Creation of Node objects,
2. Overloaded insertion cin into the Nodes,
3. and call to insert nodes into DLL
    input: cin >> DLL<TYPE>
    output: istream
*/
template<typename TYPE>
istream & operator >> (istream & in, DLL<TYPE> & op2)
{
    TYPE node;
    in >> node;
    op2.insert(node);

    return in;
}


/**
find wrapper
    input: DLL<TYPE> and integar i to find animal
    output: returns 1 or 0 if successful
*/
template<typename TYPE>
int DLL<TYPE>::find_ith_animal(int i)
{
    if(!head) return 0;
    return find_ith_animal(head, 0, i);
}


/**
find Recursive Tail Recursion
    input: DLL<TYPE>, integar iteration, and integar i to find
    output: returns 1 or 0 if successful
        iterates incrementing iteration ++ until i == iteration
        cout the animal found at the ith position
*/
template<typename TYPE>
int DLL<TYPE>::find_ith_animal(node_ptr src, int iteration, int i)
{
    if(!src) return 0;
    if(iteration == i)
    {
        cout << "***************************************************************\n";
        cout << "Your Newly Adopted Animal Is!!!"<< endl;
        cout << src->get_data();
        cout << "Animal Personality: " << animal_personalities[i] << endl;
        cout << "***************************************************************\n";
        return 1;
    }
    ++iteration;
    return  find_ith_animal(src->get_next(), iteration, i);
}


/**
Randomly Select An Animal From the List of Animals
    input:  DLL<TYPE>
    output: returns 1 or 0 if successful
        cout random animal found
*/
template<typename TYPE>
int DLL<TYPE>::adopt_animal()
{
    srand(time(nullptr));
    int animal_count = animal_personalities.size();
    if(animal_count > 0)
    {
        int random_animal = random_number(animal_count);
        cout << random_animal << endl;
        int animal_found = find_ith_animal(random_animal);
        return animal_found;
    }
    return 0;
}


/**
Recursive Wrapper to display All Animals
    input:  DLL<TYPE>
    output: returns count of those displayed
        1. Return 0 if no node
        2. Call the Recursive Call To Cout display from Each Node
*/
template<typename TYPE>
int DLL<TYPE>::display_all()
{
    //if(!to_add) return 0;
    if(!head)
    {
        cout << "***************************************************************\n";
        cout << "No Nodes To Display\n";
        cout << "***************************************************************\n";
    }
    return display_all(head, 0);
}


/**
Recursive display with Tail Recursion
    input:  DLL<TYPE>, intergar i to print out personality at index of vector
    output: count of those displayed
        3. Recursively call each node, and cout overloaded Node operators
*/
template<typename TYPE>
int DLL<TYPE>::display_all(node_ptr src, int i)
{
    if(!src) return 0;
    
    cout << "***************************************************************\n";
    cout << src->get_data();
    cout << "Animal Personality: " << animal_personalities[i] << endl;
    cout << "***************************************************************\n";
    ++i;
    int display_success = 1 + display_all(src->get_next(), i);

    return display_success;
}

