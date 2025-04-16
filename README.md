# Lox Interpreter in C++

This is a C++ implementation of the [Lox programming language](http://craftinginterpreters.com/contents.html) based on the book *Crafting Interpreters* by Bob Nystrom.

It supports a full-featured, dynamically-typed scripting language with:
- Classes, inheritance, `this`, and `super`
- First-class functions and closures
- Lexical scoping and block statements
- Variable resolution via static analysis
---

## Features Implemented (Chapters 1–13)

| Feature                         | Status     |
|--------------------------------|------------|
| Tokenizer (Scanner)            | ✅ Complete |
| Recursive descent Parser       | ✅ Complete |
| AST via Expressions & Stmts    | ✅ Complete |
| Visitor pattern (Expr/Stmt)    | ✅ Complete |
| Interpreter engine             | ✅ Complete |
| Environment (Scopes)           | ✅ Complete |
| Closures & Functions           | ✅ Complete |
| Classes & Instances            | ✅ Complete |
| `this` keyword                 | ✅ Complete |
| Inheritance (`super`)          | ✅ Complete |
| Static Resolver (variable depth) | ✅ Complete |
| Error reporting (runtime + parse) | ✅ Complete |

---

## Build Instructions

### Dependencies
- C++17 or later
- CMake (3.16+)
- A C++ compiler (GCC, Clang, MSVC)

## Example Lox Code
```
class Person {
  sayHi() {
    print "Hello from " + this;
  }
}

var p = Person();
p.sayHi();

class CoolPerson < Person {
  sayHi() {
    super.sayHi();
    print "And I'm cool.";
  }
}

CoolPerson().sayHi();
```

## Design Choices
- Uses std::shared_ptr and enable_shared_from_this for safe AST traversal

- Applies the Visitor Pattern to decouple data and behavior

- Tracks variable resolution statically to avoid runtime scope crawling

- Organized per chapter structure of the Crafting Interpreters book

## Credits
Based on Crafting Interpreters by Bob Nystrom
