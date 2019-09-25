#include "Z80.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

Target llvm::TheZ80Target;

extern "C" void LLVMInitializeZ80TargetInfo() {
  RegisterTarget<Triple::lc2200> X(TheZ80Target, "lc2200", "Z80", "Z80");
}
