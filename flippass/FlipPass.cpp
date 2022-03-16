#include<unordered_map>
#include<set>

#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Value.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"

using namespace llvm;

namespace {
  struct FlipPass : public FunctionPass {
    static char ID;
    std::unordered_map<Function*, std::set<Function*>> graph;
      FlipPass() : FunctionPass(ID) {}

    /**
     * Examine each function and look for method calls (@CallInst instances).
     * Append each call by invoking @CallInst->getCalledFunction() to the call graph.
     * @param F The input @Function
     * @return
     */
    virtual bool runOnFunction(Function &F) {
        for (auto& B : F) {
            for (auto& I : B) {
                if (auto* op = dyn_cast<CmpInst>(&I)) {
                    op->setPredicate(op->getInversePredicate());
                }
            }
        }
      return false;
    }
  };
}

char FlipPass::ID = 0;

// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
static void registerSkeletonPass(const PassManagerBuilder &,
                         legacy::PassManagerBase &PM) {
  PM.add(new FlipPass());
}
static RegisterStandardPasses
  RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                 registerSkeletonPass);
