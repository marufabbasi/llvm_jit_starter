# Groot JIT Compiler Starter Project

This is an example of how to prepare a function JIT compile it and call it.
Here is the equavalent function we will be creating.

```
int add(int X, int Y)
{
    auto  val =  X + Y;
    return val;
}
```

## Steps to create a ```hello world``` JIT Compiler

1. Create the context and module
2. Create function header/prototype
3. Extract the function parameters to be used with instructions
4. Create function body block structure
5. Create instructions for the block
6. Create JIT compiler and add the module we prepared
7. Lookup the prepared  function
8. Call the function

## Add LLVM to CMake project

```
find_package(LLVM REQUIRED CONFIG)
llvm_map_components_to_libnames(LLVM_LIBS core native orcjit support)

target_link_libraries(${PROJECT_NAME} PRIVATE ${LLVM_LIBS})

```