
/*************************************************************************
This is an example of how to prepare a function JIT compile it and call it.
Here is the equavalent function we willbe creating.

int add(int X, int Y)
{
    auto  val =  X + Y;
    return val;
}
**************************************************************************/

#include <iostream>
#include <memory>

#include "llvm/ExecutionEngine/Orc/LLJIT.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetSelect.h"

using namespace llvm;
using namespace llvm::orc;

ExitOnError check;

int main(int argc, char *argv[])
{
    InitializeNativeTarget();
    InitializeNativeTargetAsmPrinter();

    // 1. Create the context and module
    auto context = std::make_unique<LLVMContext>();
    auto module = std::make_unique<Module>("hg2galaxy", *context);

    // 2. Create function header/prototype
    auto intType = Type::getInt32Ty(*context);
    auto funPrototype = FunctionType::get(intType, {intType, intType}, false);
    auto addFunction = Function::Create(funPrototype, Function::ExternalLinkage, "add", module.get());

    // 3. Extract the function parameters to be used with instructions
    auto argX = &*addFunction->arg_begin();
    auto argY = argX++;

    // 4. Create function body block structure
    auto block = BasicBlock::Create(*context, "addFuncBlock", addFunction);

    // 5. Create instructions for the block
    IRBuilder<> builder(block);
    auto val = builder.CreateAdd(argX, argY);
    builder.CreateRet(val);

    auto tsmodule = ThreadSafeModule(std::move(module), std::move(context));

    // 6. Create JIT compiler and add the module we prepared
    auto jitc = check(LLJITBuilder().create());
    check(jitc->addIRModule(std::move(tsmodule)));

    // 7. Lookup the prepared  function
    auto addFunSym = check(jitc->lookup("add"));
    auto addFunc = (int (*)(int, int))addFunSym.getAddress();

    // 8. Call the function
    int meaning = addFunc(40, 2);

    std::cout << "Meaning of life = " << meaning << std::endl;
    return 0;
}
