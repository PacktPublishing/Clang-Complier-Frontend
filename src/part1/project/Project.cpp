#include <string>

#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/ASTConsumers.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

int numFunctions = 0;
int numVars = 0;

class ExampleVisitor : public clang::RecursiveASTVisitor<ExampleVisitor> {
public:
  explicit ExampleVisitor(const clang::SourceManager &SM) : SourceManager(SM) {}

  bool VisitFunctionDecl(const clang::FunctionDecl *FD) {
    numFunctions++;
    std::string funcName = FD->getNameInfo().getName().getAsString();
    llvm::errs() << "Found function: " << funcName << "\n";
    return true;
  }

  bool VisitVarDecl(const clang::VarDecl *VD) {
    numVars++;

    llvm::StringRef varName = VD->getName();
    llvm::errs() << "Found variable: " << varName << "; "
                 << "First declaration: " << VD->isFirstDecl() << "\n";

    // Info about type
    clang::QualType Type = VD->getType();

    llvm::errs() << "Type: " << Type.getAsString()
                 << "; IsCanonical: " << Type.isCanonical()
                 << "; CanonicalType: " << Type.getCanonicalType().getAsString()
                 << "\n";

    return true;
  }

  bool VisitDeclStmt(const clang::DeclStmt *DS) {
    llvm::errs() << "Found DeclStmt: at "
                 << SourceManager.getSpellingLineNumber(DS->getBeginLoc())
                 << ":" << SourceManager.getSpellingLineNumber(DS->getEndLoc())
                 << "\n";

    return true;
  }

private:
  const clang::SourceManager &SourceManager;
};

class ExampleASTConsumer : public clang::ASTConsumer {
public:
  ExampleASTConsumer(const clang::SourceManager &SM)
      : visitor(std::make_unique<ExampleVisitor>(SM)) {}

  virtual void HandleTranslationUnit(clang::ASTContext &Context) override {
    visitor->TraverseDecl(Context.getTranslationUnitDecl());
  }

private:
  std::unique_ptr<ExampleVisitor> visitor;
};

class ExampleFrontendAction : public clang::ASTFrontendAction {
public:
  virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
      clang::CompilerInstance &CI, clang::StringRef file) override {
    return std::make_unique<ExampleASTConsumer>(CI.getSourceManager());
  }
};

namespace {
llvm::cl::OptionCategory ProjectCategory("Example project");
}  // namespace

int main(int argc, const char **argv) {
  auto OptionsParser =
      clang::tooling::CommonOptionsParser::create(argc, argv, ProjectCategory);
  if (!OptionsParser) {
    llvm::errs() << OptionsParser.takeError();
    return 1;
  }
  auto Files = OptionsParser->getSourcePathList();
  clang::tooling::ClangTool Tool(OptionsParser->getCompilations(), Files);

  int result = Tool.run(
      clang::tooling::newFrontendActionFactory<ExampleFrontendAction>().get());

  llvm::errs() << "\nFound: " << numFunctions << " functions.\n\n";
  llvm::errs() << "\nFound: " << numVars << " variables.\n\n";
  return result;
}
