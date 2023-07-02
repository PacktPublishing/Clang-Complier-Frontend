#include "Visitor.hpp"
#include "clang/Frontend/ASTConsumers.h"

namespace clangbook {
namespace astdumper {
class Consumer : public clang::ASTConsumer {
public:
  Consumer() : V(std::make_unique<Visitor>()) {}

  virtual void HandleTranslationUnit(clang::ASTContext &Context) override {
    V->TraverseDecl(Context.getTranslationUnitDecl());
  }

private:
  std::unique_ptr<Visitor> V;
};
} // namespace astdumper
} // namespace clangbook
