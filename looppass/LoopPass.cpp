#include<unordered_map>
#include<set>

#include "llvm/Pass.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Value.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

namespace {
  struct MyLoopPass : public LoopPass {
    static char ID;
      MyLoopPass() : LoopPass(ID) {}

      virtual bool runOnLoop(Loop *L, LPPassManager &LPM) {
          unsigned int op;

          bool changed;

          do {
              for (auto &block: L->getBlocks()) {
                  for (auto &inst: block->getInstList()) {
                      // Check if the instruction is invariant by checking all of its operands
                      bool invariant = true;
                      for (op = 0; op < inst.getNumOperands(); ++op) {
                          if (!L->isLoopInvariant(inst.getOperand(op))) {
                              invariant = false;
                          }
                      }

                      // If it's invariant, mark it as invariant
                      if (invariant) {
                          L->makeLoopInvariant(&inst, changed);
                      }
                  }
              }
          } while (changed);

          return false;
      }

  };
}

char MyLoopPass::ID = 0;

// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
static void registerSkeletonPass(const PassManagerBuilder &,
                         legacy::PassManagerBase &PM) {
  PM.add(new MyLoopPass());
}
static RegisterStandardPasses
  RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                 registerSkeletonPass);
