//
// Created by codetector on 9/3/19.
//

#include "MCTargetDesc/Z80MCTargetDesc.h"
#include "MCTargetDesc/Z80FixupKinds.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCDirectives.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCFixupKindInfo.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
class Z80AsmBackend : public MCAsmBackend {
  Triple::OSType OSType;
public:
  Z80AsmBackend(const Target &T, Triple::OSType _OSType) : MCAsmBackend(support::endianness::little),
                                                              OSType(_OSType) {
  }

  void applyFixup(const MCAssembler &Asm, const MCFixup &Fixup, const MCValue &Target, MutableArrayRef<char> Data,
                  uint64_t Value, bool IsResolved, const MCSubtargetInfo *STI) const override;

  std::unique_ptr<MCObjectTargetWriter> createObjectTargetWriter() const override;

  unsigned int getNumFixupKinds() const override;

  bool mayNeedRelaxation(const MCInst &Inst, const MCSubtargetInfo &STI) const override;

  bool fixupNeedsRelaxation(const MCFixup &Fixup, uint64_t Value, const MCRelaxableFragment *DF,
                            const MCAsmLayout &Layout) const override;

  void relaxInstruction(const MCInst &Inst, const MCSubtargetInfo &STI, MCInst &Res) const override;

  bool writeNopData(raw_ostream &OS, uint64_t Count) const override;
};
}

void Z80AsmBackend::applyFixup(const MCAssembler &Asm, const MCFixup &Fixup, const MCValue &Target,
                                  MutableArrayRef<char> Data, uint64_t Value, bool IsResolved,
                                  const MCSubtargetInfo *STI) const {
  exit(-1);
}

std::unique_ptr<MCObjectTargetWriter> Z80AsmBackend::createObjectTargetWriter() const {
  if (OSType == Triple::OSType::UnknownOS) {
    return createZ80ELFObjectWriter(0);
  }
  llvm_unreachable("Can not process the specified OS");
}

unsigned int Z80AsmBackend::getNumFixupKinds() const {
  return Z80::Fixups::NumTargetFixupKinds;
}

bool Z80AsmBackend::mayNeedRelaxation(const MCInst &Inst, const MCSubtargetInfo &STI) const {
  return false;
}

bool Z80AsmBackend::fixupNeedsRelaxation(const MCFixup &Fixup, uint64_t Value, const MCRelaxableFragment *DF,
                                            const MCAsmLayout &Layout) const {
  return false;
}

void Z80AsmBackend::relaxInstruction(const MCInst &Inst, const MCSubtargetInfo &STI, MCInst &Res) const {
}

bool Z80AsmBackend::writeNopData(raw_ostream &OS, uint64_t Count) const {
  if (Count == 0) {
    return true;
  }
  return false;
}

MCAsmBackend *llvm::createZ80AsmBackend(const llvm::Target &T, const llvm::MCSubtargetInfo &STI,
                                           const llvm::MCRegisterInfo &MRI, const llvm::MCTargetOptions &Options) {
  return new Z80AsmBackend(T, STI.getTargetTriple().getOS());
}
