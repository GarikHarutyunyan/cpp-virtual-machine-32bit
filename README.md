# Virtual machine for 32 bit CPU.

Virtual machine executes commands from Program.txt file.

This CPU has 15 Registers, Counter(which indicates the index of commands). 
First 2 registers are used as Input and Output for CPU.
The count of registers can be changed via REGISTERS_COUNT constant.

Each command must have 32 bit length.

Command is splited to 4 parts/bytes.

```
Firs Byte - OPCODE(Operation Code)
Second Byte - ARGUMENT_1
Third Byte - ARGUMENT_2
Fourth Byte - RESULT_ADDRESS
```

Cpu has 2 modes: Conditional and Arithmetic-Logical

We can switch the mode by changing the 3th(5th index) bit of OPCODE. 
  ```
  **1***** - Conditional
  **0***** - ALU
  ```
  
Conditional operations (=, !=, <, <=, >, >=), if the condition is true the value from RESULT_ADDRESS will be coppied in Counter as a next command index.
  The last 3 bits of OPCODE show the condition
  ```
  **1**000 - Value1 = Value2
  **1**001 - Value1 != Value2
  **1**010 - Value1 < Value2
  **1**011 - Value1 <= Value2
  **1**100 - Value1 > Value2
  **1**101 - Value1 >= Value2
  ```

01****** - Arithmetical and Logical operations(ADD, SUB, AND, OR, NOT(ignores second value), XOR)
  The last 3 bits of OPCODE show which insturction must be done between Value1 and Value2. 
  When we use ALU the RESULT_ADDRESS is used as calculation result's destination(register's index). 
  ```
  **0**000 - OR
  **0**001 - NAND
  **0**010 - NOR
  **0**011 - AND
  **0**100 - ADD
  **0**100 - SUB
  ```

First two bits of OPCODE(on index 6,7) show the type of Arguments
First bit of OPCODE show if ARGUMENT_1 is representing the immediate value or the address of register
  ```
  1******* - Immediate
  0******* - Register's address
  ```
Second bit of OPCODE show if ARGUMENT_2 is representing the immediate value or the address of register
  ```
  *1****** - Immediate
  *0****** - Register's address
  ```
