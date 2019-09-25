#ifndef Z80TARGETASMINFO_H
#define Z80TARGETASMINFO_H

#include "llvm/ADT/Triple.h"
#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {
class StringRef;
class Target;
class Z80MCAsmInfo : public MCAsmInfoELF {
  virtual void anchor();
public:
  explicit Z80MCAsmInfo(const Triple &TT);

};
} // namespace llvm

#endif

