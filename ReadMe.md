# Brainfuck Interpreter

I got bored so i decided to write this

## Usage:
```cmd
brainfuck_interpreter file.bf
```

There is an optional `--debug` flag to log info on each instruction

## Additional features

### Memory logging

Use the `!` character to log the surrounding 10 memory addresses and their values.
Example:
```cmd
++++[>++>++>++>+++<<<<-]>>>!
```
Output:
```cmd
Logging surrounding memory
MemAddr -2:0
MemAddr -1:0
MemAddr 0:0
MemAddr 1:8 
MemAddr 2:8
MemAddr 3:8 (Current position)
MemAddr 4:12
MemAddr 5:0
MemAddr 6:0
MemAddr 7:0
```