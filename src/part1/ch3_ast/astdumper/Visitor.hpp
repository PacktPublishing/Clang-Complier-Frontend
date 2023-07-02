#include "clang/AST/RecursiveASTVisitor.h"

namespace clangbook {
namespace astdumper {
class Visitor : public clang::RecursiveASTVisitor<Visitor> {
public:
  bool VisitDeclRefExpr(const clang::DeclRefExpr *DRE) {
    llvm::errs() << "Found reference to a declaration: '"
                 << DRE->getFoundDecl()->getName() << "'\n";
    return true;
  }
};
} // namespace astdumper
} // namespace clangbook
