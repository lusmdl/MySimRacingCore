# Common Contributing Guidelines for C and C++ Projects

Welcome to the team! Please adhere to the following guidelines to contribute effectively to the project.

## Version Control

1. Use [Git](https://git-scm.com/) for version control.
2. Work on a separate branch and create pull requests for your changes.
3. Ensure your code is clean and well-documented before submitting a pull request.
4. Use meaningful commit messages to describe your changes.

## IDE Serrings

Configure your IDE to match the formatting conventions mentioned below.

```cpp
#include <iostream>

int main() {
  
    // This is example code demonstrating indentation and line length
  
    int number = 42;
    if(number > 0) {
  
        std::cout << "The number is positive." << std::endl;
    } 
    else {
  
        std::cout << "The number is negative." << std::endl;
    }
    return 0;
}
```

### Indentation

- Always use tabs for indentation.
- One tab equals 4 spaces.

### Line Length

- Limit line length to a maximum of 72 characters.
- Wrap lines exceeding this length.

### Font

- Use a monospaced font where each character has the same width.


## Limits of Functions, Methods and Files

If the file exceeds the limits, reconsider the architecture.

> **.cpp files** may exceed the limit of lines, but it is **not recommended** to split a `.cpp` file for a single class. Keep `.cpp` files as compact as possible while maintaining clarity and structure.


#### **File: `main.cpp`**
```cpp
/**
 * @file main.cpp
 * @brief implements the object
 */
 
#include "MyClass.hpp"

int main() {

    MyClass obj;

    obj.incrementElementCount();
    obj.incrementElementCount();
    obj.displayElementCount();

    obj.decrementElementCount();
    obj.displayElementCount();

    obj.resetElementCount();
    obj.displayElementCount();

    return 0;
}
```

#### **File: `MyClass.hpp`**

```cpp
/**
 * @file MyClass.hpp
 * @brief Contains the definition of the MyClass class.
 */

#pragma once

#include <iostream>

/**
 * @class MyClass
 * @brief A class for counting elements with increment, decrement, and reset functionality.
 */
class MyClass {

    public:

        MyClass();
        void incrementElementCount();
        void decrementElementCount();
        int getElementCount() const;
        void displayElementCount() const;
        void resetElementCount();

    private:

        int numberofelements_; // The count of elements in the class.
};
```

#### **File: `MyClass.cpp`**

```cpp
/**
 * @file MyClass.cpp
 * @brief Contains implementation of the MyClass class.
 */

#include "MyClass.hpp"

/**
 * @brief Constructor for MyClass.
 */
MyClass::MyClass() : number_of_elements(0) {}

/**
 * @brief Increments the count of elements.
 */
void MyClass::incrementElementCount() {

    // Increment the count of elements
    
    number_of_elements++;
}



[...] (many lines of code)



/**
 * @brief Resets the element count to zero.
 */
void MyClass::resetElementCount() {

    number_of_elements = 0;
}

```



### Function and Methods

- Funtions should not exceed..
	- 5 statements per function.
	- 10 lines of code.

### File

- Files should not exceed..
	- 100 lines per file. (.cpp files could exceed, it is not recommend to split a .cpp file for a class)

- Files are not allowed to exceed..
	- 500 lines per file.
	- One class per file.

## Braces and Spaces

```cpp
#include <iostream>

int main() { // Opening brace on the same line

    if(true) {

        // Insert a blank line after every opening curly brace
        // Source code or comments follow afterward

        // Blocks within curly braces are indented
        std::cout << "Braces and spaces example" << std::endl;
    } // Closing brace placed at the same indentation level as the keyword + newline
    else {
    
        int numbers[] = {1, 2, 3, 4, 5}; // Insert a space after commas in lists, but not before
    }

    // Wrap single statements with braces
    for(int i = 0; i < 5; ++i) {
    
        std::cout << i; // Statement wrapped in braces
    }
    std::cout << std::endl;

    return 0; // Add a blank line before every `return` statement
}
``` 

### Brace Placement

- Place the opening brace on the same line as the keyword.
- Code inside curly braces `{}` should be indented.
- Always wrap single statements in braces.
- The closing brace `}` should be aligned with the keyword and followed by a newline **(exceptions: ';')**.

### Spaces

- No space before opening parentheses.
- Space after closing parentheses is acceptable, but not before.
- Insert a space after commas in lists, but not before.

### Blank Line

- Insert a blank line after every opening curly brace `{`.
- Before each line with a comment `//`, a blank line should be added.
- Add a blank line before every `return` statement.

## Naming Conventions

```cpp
#include <iostream>

// Variable in camelCase
int btnNumberOfPushed;

// Constants, Enum elements, and Macros in SCREAMING_SNAKE_CASE
#define MAX_VALUE    100
const int NUMBER_OF_LINES = 50;
enum ColorEnum {

    RED,
    GREEN,
    BLUE
};

// Class name in PascalCase
class MyClass {

public:

    // Method name in camelCase
    void getStatus();

private:

    // Class attribute in snake_case
    int number_of_elements;
};

// User-defined data type in skewer-case
enum modesledcolor_enum {

    MODE_OFF,
    MODE_ON
};

// Method implementation
void MyClass::getStatus() {

    std::cout << "Getting status..." << std::endl;
}

// Main function
int main() {

    MyClass obj;
    obj.getStatus();
    return 0;
}
```
### General

#### Variables / Attributes

- The name should describe the object first, followed by adjectives for clarity
- Objects may be shortened, but not descriptions

### Function / Methods
- Start names with a verb like `set` or `get` (setter and getter)


### `PascalCase`

**Used for:**
- Classes
- Files

**Pros:**
- Seems neat

**Cons:**
- Barely used (why??)

```cpp
class MyClass { // Class definition

};
```

### `camelCase`

**Used for:**
- local variable
- global variable
- function
- method

**Pros:**
- Widely used in the programmer community

**Cons:**
- Looks ugly when a few methods are n-worded

```cpp

int varLocal = 42; // Local variable in camelCase

printMessage(); // Calling function

printer.getState(); // Calling method. 

std::cout << "Global variable value: " << varGlobal << std::endl; // Accessing global variable
```


### `snake_case`

**Used for:**
- function attributes

**Pros:**
- Concise when it consists of a few words

**Cons:**
- Rdundant as hell when it gets longer

```cpp

void process_user_input(int user_input_value, double user_input_factor);

```

### `SCREAMING_SNAKE_CASE`

**Used `SCREAMING_SNAKE_CASE` only for:**
- Macros
- Constants
- Enum elements

**Used `SCREAMING_SNAKE_CASE` then `_` for:**
- Constant class attributes

**Pros:**
- Can demonstrate your anger with text

**Cons:**
- Makes your eyes deaf

```cpp
#define MAX_VALUE    100

const int NUMBER_OF_LINES {50};

enum color_enum {

    RED,
    GREEN,
    BLUE
};
```

### `nocase`

**Used `nocase` then `_` and then `nocase` for:**
- enum 
- structures

**Used `nocase` then `_` for:** 
- class attributes

**Pros:**
- Looks professional
- help when useing Intellisense and autofill
- force the developer to use short names

**Cons:**
- Misleading af

```cpp
enum enum_modesledcolor {

    // elements here
};

int attribute_; // Description of attribute
```


### `fUcKtHeCaSe`

**Used for:**
- nothing (it takes decades to type this shit)

**Pros:**
- Can live outside of the law

**Cons:**
- Can be out of a job


### `skewer-case`

**Used for:**
- nothing (the most IDEs hate this shit)

**Pros:**
- Easy to type

**Cons:**
- Any sane language freaks out when you try it

## Header Files

Ensure headers are not included multiple times.

### Preprocessor Directive

- Use `#pragma once` to prevent multiple inclusions in a translation unit. This is generally preferred over traditional `#ifndef`, `#define`, and `#endif`.

```cpp
// Example.hpp

#pragma once

class Example {
public:
    Example(); // Constructor
    void output();
    
private:
    int number;
};
```

### Header Guard

- If not using `#pragma once`, use header guards to prevent multiple inclusions.

```cpp
// Example.hpp

#ifndef EXAMPLE_HPP
#define EXAMPLE_HPP

class Example {
public:
    Example(); // Constructor
    void output();
    
private:
    int number;
};

#endif // EXAMPLE_HPP
```

## Memory Optimization

Always aim for the least memory usage possible.

### Local Variables

- Avoid global variables
- prefer local variables or constants.

```cpp
void myFunctionExample() {

    int varLocal; // Local variable
    const int MY_CONSTANT = 5; // Local constant
}
```

## Comments

Comments play a crucial role in understanding and maintaining the code. 

```cpp
/** Calculates the Fibonacci number.
 * @param n -- Input number, must be greater than 0
 * @return the nth Fibonacci number */
unsigned fib(unsigned n) {

    // Mathematically: fib(n) = { 0: 0, 1: 1, else: fib(n–1) + fib(n–2) }
    // Recursive, and hence slow. Could optimize using a loop or table.
    // 'unsigned' may overflow for n >= 50.

    // Check for 0 since argument is unsigned.
    if (n == 0) {
    
        return 0;
    }
    
    if (n == 1) {
    
        return 1;
    }
    
    return fib(n - 1) + fib(n - 2);
}
```

### Commenting Principles

- Add comments to explain the purpose of the code without repeating it.
- Avoid over-commenting; comments should enhance clarity, not clutter the code.
- Comments should be like recipes—clear enough for beginners to understand.
- Use meaningful names for classes, functions, and variables to reduce the need for comments.

### Block Comments

- Block comments outside methods are for generating Doxygen documentation.
- Inside functions, block comments are used to hide code for testing purposes.

### Line Comments

- Explain the logic of a function directly after the function header.
- After function declarations, briefly explain the following code block or important details.
- The line comments are only for the programmer who reads the code, the Doxygen stuff are in a block comment

## Documentation

- Document all public interfaces, classes, and key functionalities.
- Use Doxygen to auto-generate documentation, and adhere to Doxygen syntax.
- Update documentation when changes are made to the code.
- Remember, comments in code count as documentation.

### Doxygen Syntax Overview

```cpp
/**
 * @file documentation.hpp
 * @brief Documentation for public interfaces, classes, and key functionalities.
 * @date 2024-03-05
 * @author Max Mustermann
 * 
 * This is an example header file for documentation.
 * All public interfaces, classes, and key functionalities are documented here.
 */

#pragma once

/**
 * @brief This class represents an example class.
 * 
 * It contains various functions and data members for demonstration.
 */
class ExampleClass {

    public:

        int operation(int input);
        int getValue() const;

    private:

        int data; // A private data member for internal use
};

/**
 * @brief This function performs a specific calculation.
 * 
 * @param x The first parameter.
 * @param y The second parameter.
 * @return The result of the calculation.
 */
int calculation(int x, int y);

/**
* @brief This function returns a specific value.
* 
* @return The returned value.
*/
bool ExampleClass::getValue();
```

## Pull Requests

1. Clearly describe what your pull request does and which issues it solves.
2. Include any necessary screenshots, code samples, or relevant information.
3. Request reviews from other team members before merging.

---

Thank you for your contributions!
