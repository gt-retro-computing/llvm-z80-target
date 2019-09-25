//
// Created by codetector on 8/29/19.
//

#ifndef TARGET_Z80_H
#define TARGET_Z80_H
#include "MCTargetDesc/Z80MCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
class TargetMachine;
class Z80TargetMachine;
class MCInst;

namespace Z80ABI {

enum ABI {
  ABI_Unknown
};

}

FunctionPass *createZ80ISelDag(Z80TargetMachine &TM, CodeGenOpt::Level OptLevel);
} // end namespace llvm;

#endif