# Reverse Polish (Postfix) Calculator

An implementation of a command-line Reverse Polish Notation (RPN) calculator written in C using a static stack data structure. This project evaluates postfix mathematical expressions efficiently in a single pass.

Developed as part of the **IC 2306 - Programming II | Final Group Project**.

## Version
0.0.1

## Features
- **Stack-Based Evaluation**: Utilizes a Last-In, First-Out (LIFO) stack mechanism to process operands and operators.
- **Robust Error Handling**: Includes defensive checks against stack overflow, stack underflow (insufficient operands), and division by zero.
- **Interactive CLI**: Prompts users sequentially for tokens and inputs, maintaining the stack state dynamically in real time.

## Supported Instructions

| Command | Action | Description |
| :---: | :--- | :--- |
| `?` | Push Operand | Prompts the user to enter a number and pushes it onto the stack. |
| `+` | Addition | Pops two numbers, computes their sum, and pushes the result back. |
| `-` | Subtraction | Pops two numbers, computes their difference (first_operand - second_operand), and pushes the result. |
| `*` | Multiplication | Pops two numbers, computes their product, and pushes the result. |
| `/` | Division | Pops two numbers, computes their quotient (first_operand / second_operand). Safeguarded against division by zero. |
| `=` | Peek | Prints the value at the top of the stack **without** removing it. |
| `q` | Quit | Gracefully exits the program. |

## How it Works (The Stack Mechanism)
1. **Operands (`?`)**: When an operand is parsed, it is pushed directly onto the global stack.
2. **Operators (`+`, `-`, `*`, `/`)**: When an operator token is passed, the top two elements are popped sequentially:
   - The *first* popped element corresponds to the right-hand side (`second_operand`).
   - The *second* popped element corresponds to the left-hand side (`first_operand`).
   - The arithmetic operation is executed, and the resolved value is pushed back onto the stack.
3. **Display (`=`)**: Inspects the current head element of the stack without altering the pointer or stack structure.

## Getting Started

### Prerequisites
To compile and run this program, you will need a standard C compiler (such as `gcc` or `clang`) installed on your system.

### Compilation
Compile the source code using the following terminal command:
```bash
gcc main.c -o rpn_calculator
