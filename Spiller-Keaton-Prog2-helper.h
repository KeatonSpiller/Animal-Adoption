// CS 302 Winter 2024
// Keaton Spiller
// Prog 2 Header file

// Templates, Operator Overloading, Exception Handeling, DLL, std::Vector

// How Do People Interact With Animals?
// A generic Template for varieties of animals in a DLL
// A std::vector to generate random personalities
// Allow A random animal to be adopted from those inserted

/*                  Pet
        /            |           \
    Working     Competitive      Breeding
        \            |           /
            DLL Node Template
                     |
       Data Structure DLL Template        */

# pragma once

# include <iostream>
# include <vector>
# include <string>
# include <list>
# include <cstring>
# include <cstdlib>
# include <stdexcept>
# include <memory>


using std::string, std::cin, std::cout, std::endl, std::vector,
std::stoi, std::stof, std::ostream, std::istream, std::exception,
std::rand, std::srand;

// Types of Pets
enum PET {None=0, cat=1, dog=2, fish=3, bird=4};
// Types of Personalities
enum PERSONALITY{unknown=0, sweet=1, loving=2, smart=3, stubborn=4, adventurer=5, 
                 lazy=6, food_motivated=7, lap_animal=8, attention_seeker=9};


//Pet base case*********************************************************************
class Pet
{
	public:
		Pet();  // constructor
		~Pet(); // deconstructor
        Pet(const char * pet_name, PET pet_type, const int pet_age); // parametric
        Pet(const Pet & to_copy); // Copy Constructor
        // Overloaders
        // 1. Assignment 
        Pet & operator = (const Pet & src); // obj1 == obj2
        // 2. Relational (< <= > >=) 
        // Compare the age of Pets a and b
        friend bool operator >   (const Pet a, const Pet b); // a > b
        friend bool operator >=  (const Pet a, const Pet b); // a >= b
        friend bool operator <   (const Pet a, const Pet b); // a < b
        friend bool operator <=  (const Pet a, const Pet b); // a <= b
        // 3. Equality (== !=) 
        // Compare the names of the pets a and b
        friend bool operator ==  (const Pet a, const Pet b); // a == b
        friend bool operator !=  (const Pet a, const Pet b); // a != b
        // 4. I/O (<< >>)
        // cout << "Hello" << "World!"
        friend ostream & operator << (ostream & out, const Pet & op2);
        // cin >> str
        friend istream & operator >> (istream & in, Pet & op2);
        // 5. One Binary arithmetic (e.g., +) and compound assignment (e.g., +=)
        // a + b
        // concatenate the names and add the ages of a and b
        friend Pet operator + (const Pet & a, const Pet & b); 
        // a = a + b
        // concatenate the names and add the ages of a and b
        friend Pet operator += (Pet & a, const Pet & b); 
        // member functions
        int deep_copy_str(char * dest, const char * src);
        // return by reference length of name
        int name_length(int & length);
        int display(void);

	protected:
        // data members
        char * name;
        PET type;
        int age;
};


//Working***************************************************************************
class Working: public Pet
{
	public:
		Working();  // constructor
		~Working(); // deconstructor
        Working(const char * pet_name, // Parametric Constructor
                PET pet_type,
                const int pet_age,
                const char * working_type, 
                const int working_duration);
        Working(const Working & to_copy); // Copy Constructor
        Working & operator = (const Working & src); // obj1 == obj2
        //4. I/O (<< >>)
        // cout << "Hello" << "World!"
        friend ostream & operator << (ostream & out, const Working & op2);
        // cin >> str
        friend istream & operator >> (istream & in, Working & op2);
		int display(void); // instead of a getters, displaying the data
        // return by reference length of variety
        int variety_length(int & length);
        // 1. if duration < to_cmp return 1
        // 2. else return 0
        int compare_duration(const int to_cmp);
	protected:
        // data members
		char * variety;
        int duration;
};

//Competitive **********************************************************************
class Competitive: public Pet
{
	public:
		Competitive();  // constructor
		~Competitive(); // deconstructor
        Competitive(const char * pet_name, // Parametric Constructor
                    PET pet_type,
                    const int pet_age,
                    const string competitive_type, 
                    const int num_awards);
        Competitive(const Competitive & to_copy); // Copy Constructor
        Competitive & operator = (const Competitive & src); // obj1 == obj2
        //4. I/O (<< >>)
        // cout << "Hello" << "World!"
        friend ostream & operator << (ostream & out, const Competitive & op2);
        // cin >> str
        friend istream & operator >> (istream & in, Competitive & op2);
		int display(void); // instead of a getters, displaying the data
        // return by reference length of sport
        int sport_length(int & length);
        // 1. if awards < to_cmp return 1
        // 2. else return 0
        int compare_awards(const int to_cmp);
	protected:
        // data members
        string sport;
        int awards;
};

//Breeding ***********************************************************************
class Breeding: public Pet
{
	public:
		Breeding();  // constructor
		~Breeding(); // deconstructor
        Breeding(const char * pet_name, // Parametric Constructor
                 PET pet_type,
                 const int pet_age,
                 const string breed_type, 
                 const float num_percentage);
        Breeding(const Breeding & to_copy); // Copy Constructor
        Breeding & operator = (const Breeding & src); // obj1 == obj2
        //4. I/O (<< >>)
        // cout << "Hello" << "World!"
        friend ostream & operator << (ostream & out, const Breeding & op2);
        // cin >> str
        friend istream & operator >> (istream & in, Breeding & op2);
		int display(void); // instead of a getters, displaying the data
        // return by reference length of breed 
        int breed_length(int & length);
        // 1. if awards < to_cmp return 1
        // 2. else return 0
        int compare_percentage(const float to_cmp);
	protected:
        // data members
        string breed;
        float percentage;
};


//Node *****************************************************************************
template <typename TYPE> 
class Node
{
    public:
        // Simplify the retyping of Node<TYPE>*
        typedef Node<TYPE> node_type;
        typedef node_type * node_ptr;
        Node();
        ~Node();
        // Copy Constructor
        Node(const TYPE & to_add);
        // Node Functionality for the DLL
        node_type *& get_next();
        node_type *& get_prev();
        int set_next(node_type *& src);
        int set_prev(node_type *& src);
        bool has_next();
        bool has_prev();
        // Returning the Data because Node doesn't inherit
        TYPE & get_data();
        int display();

    protected:
        TYPE     data;
        node_ptr next;  
        node_ptr prev;
};

//DLL ******************************************************************************

template <typename TYPE>
class DLL
{
    typedef Node<TYPE> node_type;
    typedef node_type * node_ptr;
    public:
        DLL();
        ~DLL();
        // Inserting In Sorted Order by Pet age smallest to largest
        int insert(const TYPE & to_add);
        DLL<TYPE> & operator = (const DLL<TYPE> & src); // obj1 == obj2
        // Generating a random number from 0 to the from
        int random_number(int from);
        int display_all();
        int adopt_animal();
        int personality_num_conversion(int personality_num, string & personality);
        int find_ith_animal(int i);
        int remove_all();
    protected:
        // utilizing the one required std:: library container for personality
        vector<string> animal_personalities;
        node_ptr head; 
        node_ptr tail;

        int display_all(node_ptr src, int i);
        int insert(node_ptr src, const TYPE & to_add);
        int find_ith_animal(node_ptr src, int iteration, int i);
        int remove_all(node_ptr src);
};

class Menu
{
    public:
        Menu();
        ~Menu();
        // Simplifying the functionality of the main User system into multiple
        // menu options
        int greetings();
        int run_program();
        int competitive();
        int breeding();
        int working();
        int prompt_animal_type();
        int cin_animal_type(string & activity);
        int prompt_list_options();
        int cin_list_options(string & option);
        int prompt_insert_animal();
        int outro();
};

// Exception Handeling
class Exception_Handling
{
    public:
        Exception_Handling();
        ~Exception_Handling();
        // functions to try and catch any bugs that could be found in the
        // operator overloaders as we receive input and perform arithmetic
        // (overloaders don't always catch where there is a bug on their own)
        int validate_stoi(string src);
        int validate_stof(string src);
        int validate_negative(int a);
};

// tpp is required to run after .h file
# include "Spiller-Keaton-Prog2-template.tpp"
