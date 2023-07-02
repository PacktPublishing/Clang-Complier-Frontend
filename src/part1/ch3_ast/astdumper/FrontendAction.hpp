#include "Consumer.hpp"
#include "clang/Frontend/FrontendActions.h"

namespace clangbook {
namespace astdumper {
class FrontendAction : public clang::ASTFrontendAction {
public:
  virtual std::unique_ptr<clang::ASTConsumer>
  CreateASTConsumer(clang::CompilerInstance &CI,
                    clang::StringRef File) override {
    return std::make_unique<Consumer>();
  }
};
} // namespace astdumper
} // namespace clangbook
