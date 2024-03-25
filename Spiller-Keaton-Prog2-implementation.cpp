# include "Spiller-Keaton-Prog2-helper.h"
/**
Contains The Implementation for 
base:    Pet
derived: Working, Breeding, Competitive
Menu system
Exception Handling
*/

// Pet : Base *********************************************************************
// Protected Data Members 
// char* name, PET type

/**
Default Constructor
input: Pet obj();
output: empty obj
*/
Pet::Pet(): 
    name(nullptr), type(PET::None), age(0) {}


/**
Default Deconstructor
input: ~Pet to deconstruct upon exit
output: deletion of char *
*/
Pet::~Pet() 
{
    if(name)
    {
        delete [] name;
    }
} 


/**
Parametric Constructor
input:  input to be placed into new Pet object 
output: new pet object with variables
*/
Pet::Pet(const char * pet_name, PET pet_type, const int pet_age):
    name(nullptr), type(pet_type), age(pet_age)
{
    if(pet_name)
    {
        name = new char[ strlen(pet_name) + 1 ];
        strcpy(name, pet_name);
    }
}


/**
Copy Constructor
input:  Pet Object to Copy
output: new Pet Object with copied data
*/
Pet::Pet(const Pet & to_copy):
    name(nullptr), type(to_copy.type), age(to_copy.age)
{
    if(to_copy.name)
    {
        name = new char[ strlen(to_copy.name) + 1 ];
        strcpy(name, to_copy.name);
    }
}

//Pet : Operators******************************************************************

/**
    input: Pet Object
    output: cout
        Print(name
              type
              age)
*/
ostream & operator << (ostream & out, const Pet & op2)
{
    if(!op2.name)
    {
        out << "No Pet Name Given\n";
        return out;
    }
    out << "Pet Name: " << op2.name << endl;
    switch(op2.type)
    {
        case 0:
            out << "Pet Type: None"<< endl;
            break;

        case 1:
            out << "Pet Type: Cat"<< endl;
            break;

        case 2:
            out << "Pet Type: Dog"<< endl;
            break;

        case 3:
            out << "Pet Type: Fish"<< endl;
            break;

        case 4:
            out << "Pet Type: Bird"<< endl;
            break;
    }
    cout << "Pet Age: " << op2.age << endl;
    return out;
}


/**
    input: Pet Object
    output: cin Pet
            Obj.name  = name
            Obj.type  = type
            Obj.age   = age
*/
istream & operator >> (istream & in, // cin >> "Hello" >> "World!"
                       Pet & op2)
{
    string pet_name;
    string pet_age_input;
    int pet_age;
    string pet_int_input;
    int pet_int;
    int validate_int;
    int validate_age;
    int validate_non_negative;
    PET pet_type;
    Exception_Handling e;

    cout << "What Is Your Pet Name?\n";
    
    in >> pet_name;
    if(!in) return in;

    cout << "What Is Your Pet Type Number?\n";
    cout << "{None=0, cat=1, dog=2, fish=3, bird=4}\n";
    in >> pet_int_input;
    validate_int = e.validate_stoi(pet_int_input);
    while(!validate_int)
    {
        cout << "What Is Your Pet Type Number?\n";
        cout << "{None=0, cat=1, dog=2, fish=3, bird=4}\n";
        in >> pet_int_input;
        validate_int = e.validate_stoi(pet_int_input);
    }
    pet_int = stoi(pet_int_input);

    if(!in) return in;

    switch(pet_int)
    {

        //enum PET {None=0, cat=1, dog=2, fish=3, bird=4};
        case 0:
            pet_type = PET::None;
            break;

        case 1:
            pet_type = PET::cat;
            break;

        case 2:
            pet_type = PET::dog;
            break;

        case 3:
            pet_type = PET::fish;
            break;

        case 4:
            pet_type = PET::bird;
            break;
    }

    cout << "What Is Your Pet's Age?\n";
    in >> pet_age_input;
    // validate integar
    validate_age = e.validate_stoi(pet_age_input);
    // validate negative
    if(validate_age)
    {
        validate_non_negative = e.validate_negative(stoi(pet_age_input));
        if(!validate_non_negative) validate_age = 0;
    }
    while(!validate_age)
    {
        cout << "What Is Your Pet's Age?\n";
        in >> pet_age_input;
        validate_age = e.validate_stoi(pet_age_input);
        if(validate_age)
        {
            validate_non_negative = e.validate_negative(stoi(pet_age_input));
            if(!validate_non_negative) validate_age = 0;
        }
    }
    pet_age = stoi(pet_age_input);
    
    // Assign input values to object
    // deep copy string input to destination  char * name
    if(!pet_name.empty())
    {
        op2.name = new char[ pet_name.size() + 1 ];
        strcpy(op2.name, pet_name.c_str());
    }
    op2.type = pet_type;
    op2.age = pet_age;
    return in;
}


/**
    input: obj1 = obj2
    output: obj1
        1. return obj1 if the same
        2. delete obj1 if contains memory
        3. Fill obj1 with obj2 and return obj1
*/

Pet & Pet::operator=(const Pet & src)
{
    // If Equal
    if (this == &src) return *this;

    // If Already Has Memory
    if(name)
    {
        delete [] name;
        name = nullptr;
    }
    name = new char[strlen(src.name) + 1];
    strcpy(name, src.name);

    type = src.type;
    age = src.age;
    
    return *this;
}


/**
    input: a < b
    output: boolean true or false exclusive
       true if a is greater b
       false if a is <= b
        
*/
bool operator > (const Pet a, const Pet b) // a > b
{
    Exception_Handling e;
    int negative_a = e.validate_negative(a.age);
    int negative_b = e.validate_negative(b.age);
    if(negative_a || negative_b) return false;

    if(a.age > b.age) return true;
    return false;
}


/**
    input: a >= b 
    output: boolean true or false inclusive
       true if a is greater b or equal
       false if a is < b
        
*/
bool operator >= (const Pet a, const Pet b) // a >= b
{
    Exception_Handling e;
    int negative_a = e.validate_negative(a.age);
    int negative_b = e.validate_negative(b.age);
    if(negative_a || negative_b) return false;

    if(a.age >= b.age) return true;
    return false;
}


/**
    input: a < b
    output: boolean true or false exclusive
       true if a is less than b
       false if a is >= b
        
*/
bool operator < (const Pet a, const Pet b) // a < b
{
    Exception_Handling e;
    int negative_a = e.validate_negative(a.age);
    int negative_b = e.validate_negative(b.age);
    if(negative_a || negative_b) return false;

    if(a.age < b.age) return true;
    return false;
}


/**
    input: a <= b
    output: boolean true or false inclusive
       true if a is less than b or equal
       false if a is > b
        
*/
bool operator <= (const Pet a, const Pet b) // a <= b
{
    Exception_Handling e;
    int negative_a = e.validate_negative(a.age);
    int negative_b = e.validate_negative(b.age);
    if(negative_a || negative_b) return false;
    
    if(a.age <= b.age) return true;
    return false;
}


/**
    input: a == b
    output: boolean true or false
       true if equal
       false if not equal
        
*/
bool operator == (const Pet a, const Pet b) // a == b
{
    if(a.name == b.name) return true;
    return false;
}


/**
    input: a != b
    output: boolean true or false
       true if not equal
       false if equal
*/
bool operator != (const Pet a, const Pet b) // a != b
{
    if(a.name != b.name) return true;
    return false;
}


/**
    input: a + b
    output: temp
        new Pet
            if (a.type == b.type)
            a.name + b.name
            a.age + b.age
        
*/
Pet operator + (const Pet & a, const Pet & b)// a + b
{

    Exception_Handling e;

    Pet temp;
    if(!a.name || !b.name){
        cout << "Invalid a or b input\n";
        return temp;
    }
    
    if(a.type != b.type){
        cout << "Inalid Pet Types\n";
        return temp;
    }

    temp.name = new char[strlen(a.name) + strlen(b.name) + 1];

    strcpy(temp.name, a.name);
    strcat(temp.name, " ");
    strcat(temp.name, b.name);

    int negative_a = e.validate_negative(a.age);
    int negative_b = e.validate_negative(b.age);
    if(negative_a && !negative_b)
    {
        temp.age = negative_a;     
    }  

    if(!negative_a && negative_b)
    {
        temp.age = negative_b;     
    }  
    
    temp.type = a.type;
    if(!negative_a && !negative_b)
    {
        temp.age = a.age + b.age;
    }
    return temp;
}


/**
    input: a += b
    output: a
        modify a
            if (a.type == b.type)
            a.name + b.name
            a.age + b.age
        
*/
Pet operator+=(Pet & a, const Pet & b) 
{
    Pet temp;
    Exception_Handling e;
    if(!b.name){
        cout << "Invalid a or b input\n";
        return a;
    }
    
    if(a.type != b.type){
        cout << "Inalid Pet Types\n";
        return a;
    }

    temp.name = new char[strlen(a.name) + strlen(b.name) + 1];

    strcpy(temp.name, a.name);
    strcat(temp.name, " ");
    strcat(temp.name, b.name);
    
    temp.type = a.type;

    a.name = new char[strlen(temp.name) + 1];
    strcpy(a.name, temp.name);
    delete [] temp.name;
    temp.name = nullptr;

    int negative_a = e.validate_negative(a.age);
    int negative_b = e.validate_negative(b.age);
    if(!negative_a && negative_b)
    {
        temp.age = negative_b;     
    }  
    
    temp.type = a.type;
    if(!negative_a && !negative_b)
    {
        a.age = a.age + b.age;
    }

    return a;
}


// End of Pet Operators ***********************************************************
// Continue Pet Baseclass
// char * name, PET type, int age


/**
Deep Copy char * strings
input:  char * destination and char * source to copy from
output: deep copy of memory
*/
int Pet::deep_copy_str(char * dest, const char * src)
{
    if(! src) return 0;
    dest = new char[ strlen(src) + 1 ];
    strcpy(dest, src);
    return 1;
}


/**
cout  Data stored in the private data members in pet
input:   obj.display() null argument
output:  cout to screen 
*/
int Pet::display()
{
    if(!name)
    {
        cout << "No Pet Name Given\n";
        return 0;
    }
    cout << "Pet Name: " << name << endl;
    switch(type)
    {
        case 0:
            cout << "Pet Type: None"<< endl;
            break;

        case 1:
            cout << "Pet Type: Cat"<< endl;
            break;

        case 2:
            cout << "Pet Type: Dog"<< endl;
            break;

        case 3:
            cout << "Pet Type: Fish"<< endl;
            break;

        case 4:
            cout << "Pet Type: Bird"<< endl;
            break;
    }
    cout << "Pet Age: " << age << endl;

    return 1;
}


/**
    return length by reference
    input: int & length
    output: 1 success or 0 failure
*/
int Pet::name_length(int & length)
{
    if(!name) return 0;
    length = strlen(name);
    return 1;
}


// Working : public Pet************************************************************
// Protected Data Members
// char * type, int duration

/**
Default Constructor
input:  Object to construct Working obj();
output: Initialize empty working object
*/
Working::Working():  // constructor
    variety(nullptr), duration(0) {}


/**
Default Deconstructor
input:  End of object lifespan
output: deallocate variety char *
*/
Working::~Working() 
{
    if(variety)
    {
        delete [] variety;
    }
} 


/**
Parametric Constructor
input:  Variables to Insert into a new Working object
output: New Object Filled With Variables
*/
Working::Working(const char * pet_name, // Parametric Constructor
                 PET pet_type,
                 const int pet_age,
                 const char * working_type, 
                 const int working_duration):
    Pet(pet_name, pet_type, pet_age), variety(nullptr), duration(working_duration)
{
    variety = new char[strlen(working_type) + 1];
    strcpy(variety, working_type);
}


/**
Copy Constructor
input:  Working Object to copy
output: New Object Filled With object copy
*/
Working::Working(const Working & to_copy): // Copy Constructor
    Pet(to_copy), variety(nullptr), duration(to_copy.duration)
{
    variety = new char[strlen(to_copy.variety) + 1];
    strcpy(variety, to_copy.variety);
}


/**
    input: obj1 = obj2
    output: obj1
        1. return obj1 if the same
        2. delete obj1 if contains memory
        3. Fill obj1 with obj2 and return obj1
*/
Working & Working::operator=(const Working & src) // obj1 == obj2
{
    Pet::operator=(static_cast<Pet>(src));
    // If Equal
    if (this == &src) return *this;

    if(variety)
    {
        delete [] variety;
        variety = nullptr;
    }
        
    //deep_copy_str(variety, src.variety);
    variety = new char[strlen(src.variety)+1];
    strcpy(variety, src.variety);
    duration = src.duration;
    
    return *this;
}


/**
    input: object
    output: cout
        Print(name
              pet_type
              age
              working_type
              duration)
*/
ostream & operator << (ostream & out, const Working & op2)
{
    // Call upstream base class <<
    out << static_cast<const Pet &> (op2);
    
    if(!op2.variety) 
    {
        out << "No Working Type Given\n";
        return out;
    }
    out << "Working Pet Type: " << op2.variety << endl;
    out << "Pet Working Duration In Years: " << op2.duration << endl;
    return out;
}


/**
    input: object
    output: cin
        Print(name
              pet_type
              age
              working_type
              duration)
*/
istream & operator >> (istream & in, Working & op2)
{
    // Call upstream base class >>
    in >> static_cast<Pet &> (op2);
    
    string working_name;
    string working_duration_input;
    int working_duration;
    int valid_duration;
    Exception_Handling e;

    cout << "What Is Your Working Pet Type?" << endl;
    
    in >> working_name;
    if(!in) return in;

    cout << "How Long has your Pet been working in Years?\n";
    in >> working_duration_input;
    valid_duration = e.validate_stoi(working_duration_input);
    while(!valid_duration)
    {
        cout << "How Long has your Pet been working in Years?\n";
        in >> working_duration_input;
        valid_duration = e.validate_stoi(working_duration_input);
    }
    working_duration = stoi(working_duration_input);
    
    // Assign input values to object
    // deep copy string input to destination  char * name
    if(!working_name.empty())
    {
        op2.variety = new char[ working_name.size() + 1 ];
        strcpy(op2.variety, working_name.c_str());
    }
    op2.duration = working_duration;
    return in;
}


/**
cout all Data in Working and in Pet
input:  Working object to display arguments void
output: cout Working and Pet data to screen
*/
int Working::display(void) // instead of a getters, displaying the data
{
    Pet::display();
    
    if(!variety)
    {
        cout << "No Working Type Given\n";
        return 0;
    }
    cout << "Working Pet Type: " << variety << endl;
    cout << "Pet Working Duration In Years: " << duration << endl;
    return 1;
}


/**
    return length by reference
    input: char * src
    output: 1 success or 0 failure
*/
int Working::variety_length(int & length)
{
    if(!variety) return 0;
    length = strlen(variety);
    return 1;
}


/**
    return int
    input: integar to compare
    output: 
        1 success duration < to_cmp or 
        0 failure duration >= to_cmp
*/
int Working::compare_duration(const int to_cmp)
{
    if(duration < to_cmp) return 1;
    return 0;
}


// Competitive : Public Pet  **********************************************
// Protected Data Members 
// string sport, int awards


/**
Default Constructor
input:  new Competitive Object to initialize
output: empty Competitive object
*/
Competitive::Competitive():  // constructor
    awards(0) {}


/**
Default Constructor
input:  End of Competitive lifespan
output: Deallocation of any dynamic memory
*/
Competitive::~Competitive() {} // deconstructor


/**
Parametric Constructor
input:  Object with arugments to fill
output: filled object
*/
Competitive::Competitive(const char * pet_name, // Parametric Constructor
                         PET pet_type,
                         const int pet_age,
                         const string competitive_type, 
                         const int num_awards):
    Pet(pet_name, pet_type, pet_age), sport(competitive_type), awards(num_awards) {}


/**
Copy constructor
input:  Object with object to fill
output: filled object
*/
Competitive::Competitive(const Competitive & to_copy): // Copy Constructor
    Pet(to_copy), sport(to_copy.sport), awards(to_copy.awards) {}


/**
    input: obj1 = obj2
    output: obj1
        1. return obj1 if the same
        2. delete obj1 if contains memory
        3. Fill obj1 with obj2 and return obj1
*/
Competitive & Competitive::operator = (const Competitive & src) // obj1 == obj2
{
    Pet::operator=(static_cast<Pet>(src));
    // If Equal
    if (this == &src) return *this;

    sport.clear();

    sport = src.sport;
    awards = src.awards;
    
    return *this;
}


/**
    input: object
    output: cout
        Print(name
              pet_type
              age
              working_type
              duration)
*/
ostream & operator << (ostream & out, const Competitive & op2)
{
    // Call upstream base class <<
    out << static_cast<const Pet &> (op2);
    
    if(op2.sport.empty()) 
    {
        out << "No Competitive Sport Given\n";
        return out;
    }
    out << "Competitive Sport: " << op2.sport << endl;
    out << "Number of Competitive Sport Awards: " << op2.awards << endl;
    return out;
}


/**
    input: object
    output: cin
        Print(name
              pet_type
              age
              working_type
              duration)
*/
istream & operator >> (istream & in, Competitive & op2)
{
    // Call upstream base class >>
    in >> static_cast<Pet &> (op2);
    
    string competitive_name;
    string num_awards_input;
    int num_awards;
    int valid_awards;
    Exception_Handling e;

    cout << "What Is Your Competitive Sport?" << endl;
    
    in >> competitive_name;
    if(!in) return in;

    cout << "How Many Awards Had Your Pet Won?\n"; 
    in >> num_awards_input;
    valid_awards = e.validate_stoi(num_awards_input);
    while(!valid_awards)
    {
        cout << "How Many Awards Had Your Pet Won?\n"; 
        in >> num_awards_input;
        valid_awards = e.validate_stoi(num_awards_input);
    }
    num_awards = stoi(num_awards_input);
    
    // Assign input values to object
    // deep copy string input to destination  char * name
    if(!competitive_name.empty())
    {
        op2.sport = competitive_name;
    }
    op2.awards = num_awards;
    return in;
}


/**
cout all data in Competitive and Pet
input: object to cout
output: cout to screen
*/
int Competitive::display(void) // instead of a getters, displaying the data
{
    Pet::display();
    
    if(sport.empty())
    {
        cout << "No Competitive Sport Given\n";
        return 0;
    }
    cout << "Competitive Sport: " << sport << endl;
    cout << "Competitive Sport Awards: " << awards << endl;
    return 1;
}


/**
    return length by reference
    input: char * src
    output: 1 success or 0 failure
*/
int Competitive::sport_length(int & length)
{
    if(sport.empty()) return 0;
    length = sport.size();
    return 1;
}


/**
    return int
    input: integar to compare
    output: 
        1 success awards < to_cmp or 
        0 failure awards >= to_cmp
*/
int Competitive::compare_awards(const int to_cmp)
{
    if(awards < to_cmp) return 1;
    return 0;
}

// Breeding : Public Pet  **********************************************
// Protected Data Members 
// string breed, float percentage


/**
Default Constructor
input:  new Breeding object to initalize
output: Empty Breeding object
*/
Breeding::Breeding():  // constructor
    percentage(0.0) {}


/**
Default Deconstructor
input:  End of object lifespan
output: Deallocate any dynamic Memory
*/
Breeding::~Breeding() {} // deconstructor


/**
Parametric Constructor
input:  Arguments to copy into new object
output: New object filled with arguments
*/
Breeding::Breeding(const char * pet_name, // Parametric Constructor
                   PET pet_type,
                   const int pet_age,
                   const string breed_type, 
                   const float num_percentage):
    Pet(pet_name, pet_type, pet_age), breed(breed_type),
    percentage(num_percentage) {}


/**
Copy Constructor
input:  Breeding object to copy into new object
output: New object filled with objects data
*/
Breeding::Breeding(const Breeding & to_copy): // Copy Constructor
    Pet(to_copy), breed(to_copy.breed), percentage(to_copy.percentage) {}


/**
    input: obj1 = obj2
    output: obj1
        1. return obj1 if the same
        2. delete obj1 if contains memory
        3. Fill obj1 with obj2 and return obj1
*/
Breeding & Breeding::operator = (const Breeding & src) // obj1 == obj2
{
    Pet::operator=(static_cast<Pet>(src));
    // If Equal
    if (this == &src) return *this;

    breed = src.breed;
    percentage = src.percentage;
    
    return *this;
}


/**
    input: object
    output: cout
        Print(name
              pet_type
              age
              breed
              percentage)
*/
ostream & operator << (ostream & out, const Breeding & op2)
{
    // Call upstream base class <<
    out << static_cast<const Pet &> (op2);
    
    if(op2.breed.empty()) 
    {
        out << "No Breed Given\n";
        return out;
    }
    out << "Breeding Breed: " << op2.breed << endl;
    out << "Percentage of Breed: " << (op2.percentage * 10) << " %" << endl;
    return out;
}


/**
    input: object
    output: cin
        Print(name
              pet_type
              age
              breed
              percentage)
*/
istream & operator >> (istream & in, Breeding & op2)
{
    // Call upstream base class >>
    in >> static_cast<Pet &> (op2);
    
    string breed_name;
    string input_percentage;
    float num_percentage;
    int stof_validate;
    Exception_Handling e;

    cout << "What Is Your Animal Breed?" << endl;
    
    in >> breed_name;
    if(!in) return in;
    
    cout << "What Is Your Animal Breed Percentage?\n";
    in >> input_percentage;
    stof_validate = e.validate_stof(input_percentage);
    while(!stof_validate)
    {
        cout << "What Is Your Animal Breed Percentage?\n";
        in >> input_percentage;
        stof_validate = e.validate_stof(input_percentage);
    }
    num_percentage = stof(input_percentage);
    
    // Assign input values to object
    // deep copy string input to destination  char * name
    if(!breed_name.empty())
    {
        op2.breed = breed_name;
    }
    op2.percentage = num_percentage;
    return in;
}


/**
cout all Data in Breeding and Pet
input:  Breeding object to display
output: Breeding and Pet data displayed to screen
*/
int Breeding::display(void) // instead of a getters, displaying the data
{
    Pet::display();
    
    if(breed.empty())
    {
        cout << "No Animal Breed Given\n";
        return 0;
    }
    cout << "Animal Breed: " << breed << endl;
    cout << "Animal Breed Percentage: " << percentage << endl;
    return 1;
}


/**
    return length by reference
    input: char * src
    output: 1 success or 0 failure
*/
int Breeding::breed_length(int & length)
{
    if(breed.empty()) return 0;
    length = breed.size();
    return 1;
}


/**
    return int
    input: integar to compare
    output: 
        1 success percentage < to_cmp or 
        0 failure percentage >= to_cmp
*/
int Breeding::compare_percentage(const float to_cmp)
{

    if(percentage < to_cmp) return 1;
    return 0;
}


// Menu ***************************************************************************


/**
Default Constructor
input:  new Object to initialize
output: Object for use of calling functions
*/
Menu::Menu(){}


/**
Default Deconstructor
input:  End of Menu obj lifespan
output: Dealloction of any dynamic memory
*/
Menu::~Menu(){}


/**
Menu greeting
input:  Menu obj
output: greet the user
*/
int Menu::greetings()
{
    cout << "Welcome To the Animal Program!!!" << endl;
    return 1;
}


/**
Menu run program
input:  Menu obj
output: Run the Different Cases Prompted for the user
*/
int Menu::run_program()
{
    string activity = "1";
    string input;
    string list_options;
    srand(time(nullptr));

    while(activity != "0")
    {
        // Ask User Activity
        cin_animal_type(activity);
        switch(stoi(activity))
        {
            case 1: // Working
            {
                working();
                break;
            }//End Case 1 Working

            case 2: // Competitive
            {
                competitive();
                break;
            }//End Case 2 Competitive

            case 3: // Breeding
            {
                breeding();
                break;
            }//End Case 3 Breeding
        }//End Switch
    }//End While
    return 1;
}


/**
Menu breeding
input:  Menu obj
output: Run the options for the Breeding Case
*/
int Menu::breeding()
{
    string activity = "1";
    string input;
    string list_options;

    DLL<Breeding> list;

    list_options = "1";
    while(stoi(list_options) != 0)
    {
        // Ask User Options
        cin_list_options(list_options);
        switch(stoi(list_options))
        {
            case 1:// Insert
            {
                input = "y";
                while(input != "N" && input != "n")
                {
                    cin >> list;
                    prompt_insert_animal();
                    cin >> input;
                }
                break;
            }

            case 2: // Display All
            {
                int display_success = list.display_all();
                if(display_success) cout << "Display Success\n";
                if(!display_success) cout << "Display Failure\n";
                break;
            }

            case 3: // Adopt An Animal
            {
                int adopt_animal = list.adopt_animal();
                if(adopt_animal) cout << "Adoption Success\n";
                if(!adopt_animal) cout << "Adoption Failure\n";
                break;
            }
        }
    }//End Options

    return 1;
}


/**
Menu working
input:  Menu obj
output: Run the options for the Working case
*/
int Menu::working()
{
    string activity = "1";
    string input;
    string list_options;
    
    DLL<Working> list;
    list_options = "1";
    while(stoi(list_options) != 0)
    {
        // Ask User Options
        cin_list_options(list_options);
        switch(stoi(list_options))
        {
            case 1:// Insert
            {
                input = "y";
                while(input != "N" && input != "n")
                {
                    cin >> list;
                    prompt_insert_animal();
                    cin >> input;
                }
                break;
            }

            case 2: // Display All
            {
                int display_success = list.display_all();
                if(display_success) cout << "Display Success\n";
                if(!display_success) cout << "Display Failure\n";
                break;
            }

            case 3: // Adopt An Animal
            {
                int adopt_animal = list.adopt_animal();
                if(adopt_animal) cout << "Adoption Success\n";
                if(!adopt_animal) cout << "Adoption Failure\n";
                break;
            }
        }
    }//End Options

    return 1;
}


/**
Menu competitive
input:  Menu obj
output: Run the options for the Competitive case
*/
int Menu::competitive()
{
    string activity = "1";
    string input;
    string list_options;
    DLL<Competitive> list;

    list_options = "1";
    while(stoi(list_options) != 0)
    {
        // Ask User Options
        cin_list_options(list_options);
        switch(stoi(list_options))
        {
            case 1:// Insert
            {
                input = "y";
                while(input != "N" && input != "n")
                {
                    cin >> list;
                    prompt_insert_animal();
                    cin >> input;
                }
                break;
            }

            case 2: // Display All
            {
                int display_success = list.display_all();
                if(display_success) cout << "Display Success\n";
                if(!display_success) cout << "Display Failure\n";
                break;
            }

            case 3: // Adopt An Animal
            {
                int adopt_animal = list.adopt_animal();
                if(adopt_animal) cout << "Adoption Success\n";
                if(!adopt_animal) cout << "Adoption Failure\n";
                break;
            }
        }
    }//End Options
    return 1;
}


/**
Menu prompt type
input:  Menu obj
output: cout list of options for the user
*/
int Menu::prompt_animal_type()
{
    cout << "******************************************************" << endl;
    cout << "Would You Like To Build a list of Animals?" << endl;
    cout << "1 Working | 2 Competitive | 3 Breeding" << endl;
    cout << "0 to Quit Program" << endl;
    cout << "******************************************************" << endl;

    return 1;
}


/**
Menu prompt animal type
input:  Menu obj
output: integar 
        Repeating prompt until valid animal type entered
*/
int Menu::cin_animal_type(string & activity)
{
    Exception_Handling e;
    prompt_animal_type();
    cin >> activity; 
    int stoi_valid = e.validate_stoi(activity);
    while(!stoi_valid)
    {
        cout << "Please Enter a Valid Integer\n";
        prompt_animal_type();
        cin >> activity; 
        stoi_valid = e.validate_stoi(activity);
    }
    return 1;
}

/**
Menu input list options
input:  Menu obj
output: integar 
        Repeating prompt until valid prompt given
*/
int Menu::cin_list_options(string & list_options)
{
    Exception_Handling e;

    prompt_list_options();
    cin >> list_options;
    int stoi_valid = e.validate_stoi(list_options);
    while(!stoi_valid)
    {
        cout << "Please Enter a Valid Integer\n";
        cin >> list_options;
        stoi_valid = e.validate_stoi(list_options);
    }
    return 1;
}

/**
Menu prompt insert
input:  Menu obj
output: cout to screen asking to insert an animal
*/
int Menu::prompt_insert_animal()
{
    cout << "Add Another Animal?" << endl;
    cout << "'y' to Continue | 'n' to Quit" << endl;
    return 1;
}


/**
Menu prompt options
input:  Menu obj
output: cout to screen list of prompt options
*/
int Menu::prompt_list_options()
{
    cout << "******************************************************" << endl;
    cout << "What Would You Like To Do For The List?" << endl;
    cout << "1 Insert | 2 Display All | 3 Adopt An Animal" << endl;
    cout << "0 to Exit List" << endl;
    cout << "******************************************************" << endl;
    return 1;
}


/**
Menu prompt outro
input:  Menu obj
output: cout to screen outro sequence
*/
int Menu::outro()
{
    cout << "Thank You For Running The Program!\n";
    cout << "Have A Wondeful Day!!!\n";
    return 1;
}


// Exception Handling *************************************************************


/**
Default Constructor
input:  Exception_Handling object
output: Empty object to call exception functions
*/
Exception_Handling::Exception_Handling() {}


/**
Default Deconstructor
input:  End of Exception_Handling lifespan
output: Deallocate any dynamic Memory
*/
Exception_Handling::~Exception_Handling() {}


/**
Validate If the string is an integar
input:  string
output: 1 or 0 if string is an integar
*/
int Exception_Handling::validate_stoi(string src)
{
   try{
        stoi(src);
        return 1;
   }
   catch(const exception & stoi_Error)
   {
        cout << "Invalid Integar: " << stoi_Error.what() << endl;
        return 0;
   }
}


/**
Validate If the string is a float
input:  string
output: 1 or 0 if string is an float
*/
int Exception_Handling::validate_stof(string src)
{
   try{
       try{
            stof(src);
            return 1;
       }
       catch(const exception & stof_Error)
       {
            cout << "Invalid float: " << stof_Error.what() << endl;
            return 0;
       }
    }
    catch(const std::invalid_argument & invalid_arg_Error)
    {
        cout << "Invalid float: " << invalid_arg_Error.what() << endl;
        return 0;
    }
}


/**
Validate If the integar is negative
input:  integar
output: 1 if positive
        0 if negative
*/
int Exception_Handling::validate_negative(int a)
{
    if(a < 0){
        cout << "Negative Value Detected\n";
        return 0;
    }
    return 1;
}
