#include "Z80MCTargetDesc.h"
#include "Z80MCAsmInfo.h"
#include "InstPrinter/Z80InstPrinter.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Support/TargetRegistry.h"

#define GET_INSTRINFO_MC_DESC
#include "Z80GenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "Z80GenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "Z80GenRegisterInfo.inc"

using namespace llvm;

static MCInstrInfo *createZ80MCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitZ80MCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createZ80MCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitZ80MCRegisterInfo(X, 0);
  return X;
}

//static MCSubtargetInfo *createZ80MCSubtargetInfo(const Triple &TT, StringRef CPU,
//                                                    StringRef FS) {
//  return createZ80MCSubtargetInfoImpl(TT, CPU, FS);
//}

static MCAsmInfo *createZ80MCAsmInfo(const MCRegisterInfo &MRI, const Triple &TT) {
  MCAsmInfo *MAI = new Z80MCAsmInfo(TT);
  return MAI;
}

//static MCCodeGenInfo *createZ80MCCodeGenInfo(const Triple &TT, Reloc::Model RM,
//	CodeModel::Model CM, CodeGenOpt::Level OL) {
//	MCCodeGenInfo *X = new MCCodeGenInfo();
//	if (RM == Reloc::Default) {
//		RM = Reloc::Static;
//	}
//	if (CM == CodeModel::Default) {
//		CM = CodeModel::Small;
//	}
//	if (CM != CodeModel::Small && CM != CodeModel::Large) {
//		report_fatal_error("Target only supports CodeModel Small or Large");
//	}
//	X->InitMCCodeGenInfo(RM, CM, OL);
//	return X;
//}

static MCInstPrinter *
createZ80MCInstPrinter(const Triple &T, unsigned SyntaxVariant,
                          const MCAsmInfo &MAI, const MCInstrInfo &MII,
                          const MCRegisterInfo &MRI) {
  return new Z80InstPrinter(MAI, MII, MRI);
}

static MCStreamer* createZ80ELFStreamer(const Triple &T, MCContext &Ctx,
                                           std::unique_ptr<MCAsmBackend> &&MAB,
                                           std::unique_ptr<MCObjectWriter> &&OW,
                                           std::unique_ptr<MCCodeEmitter> &&Emitter, bool RelaxAll) {
  return createELFStreamer(Ctx, std::move(MAB), std::move(OW), std::move(Emitter), RelaxAll);
}

//static MCStreamer *
//createMCAsmStreamer(MCContext &Ctx, formatted_raw_ostream &OS,
//	bool isVerboseAsm, bool useDwarfDirectory, MCInstPrinter *InstPrint,
//	MCCodeEmitter *CE,MCAsmBackend *TAB, bool ShowInst) {
//	return createAsmStreamer(Ctx, OS, isVerboseAsm,
//		useDwarfDirectory, InstPrint, CE, TAB, ShowInst);
//}
//
//static MCStreamer *createMCStreamer(const Target &T,
//	StringRef TT, MCContext &Ctx, MCAsmBackend &MAB,
//	raw_ostream &OS, MCCodeEmitter *Emitter, const MCSubtargetInfo &STI,
//	bool RelaxAll, bool NoExecStack) {
//	return createELFStreamer(Ctx, MAB, OS, Emitter, false, NoExecStack);
//}

// Force static initialization.
extern "C" void LLVMInitializeZ80TargetMC() {

// Register the MC asm info.
  RegisterMCAsmInfoFn X(TheZ80Target, createZ80MCAsmInfo);

// Register the MC codegen info.
//  TargetRegistry::RegisterMCCodeGenInfo(TheZ80Target,
//                                        createZ80MCCodeGenInfo);

// Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheZ80Target,
                                      createZ80MCInstrInfo);
// Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheZ80Target,
                                    createZ80MCRegisterInfo);
// Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheZ80Target,
                                          createZ80MCSubtargetInfoImpl);

// Register the MCInstPrinter
  TargetRegistry::RegisterMCInstPrinter(TheZ80Target,
                                        createZ80MCInstPrinter);
// Register the ASM Backend.
  TargetRegistry::RegisterMCAsmBackend(TheZ80Target,
                                       createZ80AsmBackend);

// Register the assembly streamer.
//TargetRegistry::RegisterAsmStreamer(TheZ80Target,
//createMCAsmStreamer);

 Register the object streamer.
  TargetRegistry::RegisterELFStreamer(TheZ80Target, createZ80ELFStreamer);
// Register the MCCodeEmitter
//  TargetRegistry::RegisterMCCodeEmitter(TheZ80Target, createZ80MCCodeEmitter);
}