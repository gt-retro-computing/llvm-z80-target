//===-- Z80.td - Describe the Z80 Target Machine -------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//===----------------------------------------------------------------------===//
//
// This is the top level entry point for the Z80 target.
//
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

include "Z80RegisterInfo.td"
//include "Z80InstrInfo.td"
//include "Z80CallingConv.td"

def Z80InstrInfo : InstrInfo;

//===----------------------------------------------------------------------===//
// Z80 processors supported.
//===----------------------------------------------------------------------===//

class Proc<string Name, list<SubtargetFeature> Features>
    : Processor<Name, NoItineraries, Features>;

def : Proc<"generic", []>;

//===----------------------------------------------------------------------===//
// Declare the target which we are implementing
//===----------------------------------------------------------------------===//

def Z80 : Target {
  let InstructionSet = Z80InstrInfo;
}