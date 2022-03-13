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
  struct CallGraphPass : public FunctionPass {
    static char ID;
    std::unordered_map<Function*, std::set<Function*>> graph;
    CallGraphPass() : FunctionPass(ID) {}

    /**
     * Examine each function and look for method calls (@CallInst instances).
     * Append each call by invoking @CallInst->getCalledFunction() to the call graph.
     * @param F The input @Function
     * @return
     */
    virtual bool runOnFunction(Function &F) {
        for (auto& B : F) {
            for (auto& I : B) {
                if (auto* op = dyn_cast<CallInst>(&I)) {
                    Function* f = op->getCalledFunction();

                    // Add to the call graph
                    graph[&F].insert(op->getCalledFunction());
                }
            }
        }
      return false;
    }

    /**
     * Print the call graph.
     * @param M The @Module
     * @return
     */
    virtual bool doFinalization(Module &M) {
        errs() << "Call graph of: " << M.getName() << "\n";

        auto iter = graph.begin();
        auto end = graph.end();

        for (; iter != end; iter++) {
            errs() << "Function: " << iter->first->getName() << "\n";
            errs() << "-- Calls:\n";

            auto setIter = iter->second.begin();
            auto setEnd = iter->second.end();

            for (; setIter != setEnd; ++setIter) {
                errs() << "----> " << setIter.operator*()->getName() << "\n";
            }
            errs() << "\n";
        }

        return false;
    }

  };
}

char CallGraphPass::ID = 0;

// Automatically enable the pass.
// http://adriansampson.net/blog/clangpass.html
static void registerSkeletonPass(const PassManagerBuilder &,
                         legacy::PassManagerBase &PM) {
  PM.add(new CallGraphPass());
}
static RegisterStandardPasses
  RegisterMyPass(PassManagerBuilder::EP_EarlyAsPossible,
                 registerSkeletonPass);
