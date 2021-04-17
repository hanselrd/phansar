#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/ASTMatchers/ASTMatchers.h>
#include <clang/Frontend/ASTUnit.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <fmt/format.h>
#include <llvm/Support/CommandLine.h>

using namespace llvm;
using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::tooling;

auto EnumMatcher   = enumDecl(isExpansionInMainFile()).bind("enum");
auto RecordMatcher = recordDecl(isExpansionInMainFile(), unless(isImplicit())).bind("record");

class Printer : public MatchFinder::MatchCallback {
public:
    virtual void onStartOfTranslationUnit() {
        outs() << "PYBIND11_EMBEDDED_MODULE(phansar, m) {\n";
    }

    virtual void onEndOfTranslationUnit() {
        outs() << "}\n";
    }

    virtual void run(const MatchFinder::MatchResult & Result) {
        if (const auto * Enum = Result.Nodes.getNodeAs<EnumDecl>("enum")) {
            /* Enum->dump(); */
            /* outs() << "std::ostream & operator<<(std::ostream &os, " << Enum->getName() << " " */
            /*        << Enum->getName() << ") {\n" */
            /*        << "  switch (" << Enum->getName() << ") {\n"; */
            /* for (const EnumConstantDecl * EnumConstant : Enum->enumerators()) { */
            /*     outs() << "  case " << EnumConstant->getQualifiedNameAsString() << ": os << \""
             */
            /*            << EnumConstant->getName() << "\";\n"; */
            /* } */
            /* outs() << "  }\n  return os;\n}\n"; */
            outs() << fmt::format("{:{}}py::enum_<{}>(m, \"{}\")",
                                  "",
                                  4,
                                  Enum->getQualifiedNameAsString(),
                                  Enum->getName().str());
            for (const EnumConstantDecl * EnumConstant : Enum->enumerators()) {
                outs() << fmt::format("\n{:{}}.value(\"{}\", {})",
                                      "",
                                      8,
                                      EnumConstant->getName().str(),
                                      EnumConstant->getQualifiedNameAsString());
            }
            outs() << ";\n";
        }
        if (const auto * Record = Result.Nodes.getNodeAs<RecordDecl>("record")) {
            /* Record->dump(); */
            /* outs() << "std::ostream & operator<<(std::ostream &os, const " << Record->getName()
             */
            /*        << " &v) {\n" */
            /*        << "  os << \"" << Record->getName() << "(\";\n"; */
            /* for (const FieldDecl * Field : Record->fields()) { */
            /*     bool IsFirst = Field == *Record->field_begin(); */
            /*     outs() << "  os << \"" << (IsFirst ? "" : ", ") << Field->getName() << "=\" <<
             * v." */
            /*            << Field->getName() << ";\n"; */
            /* } */
            /* outs() << "  os << \")\"\n  return os;\n}\n"; */
            outs() << fmt::format("{:{}}py::class_<{}>(m, \"{}\")",
                                  "",
                                  4,
                                  Record->getQualifiedNameAsString(),
                                  Record->getName().str());
            outs() << fmt::format("\n{:{}}.def(py::init<>())", "", 8);
            for (const FieldDecl * Field : Record->fields()) {
                if (Field->getAccess() != clang::AS_public) {
                    continue;
                }

                if (Field->hasAttrs()) {
                    for (const Attr * Attr : Field->attrs()) {
                        if (Attr->getKind() == attr::Kind::Annotate) {
                            auto               str = std::string{};
                            raw_string_ostream os{str};
                            LangOptions        langOpts;
                            PrintingPolicy     policy{langOpts};
                            Attr->printPretty(os, policy);
                            if (str.find("readonly") != std::string::npos) {
                                outs() << fmt::format("\n{:{}}.def_readonly(\"{}\", &{})",
                                                      "",
                                                      8,
                                                      Field->getName().str(),
                                                      Field->getQualifiedNameAsString());
                            } else {
                                outs() << fmt::format("\n{:{}}.def_readwrite(\"{}\", &{})",
                                                      "",
                                                      8,
                                                      Field->getName().str(),
                                                      Field->getQualifiedNameAsString());
                            }
                        }
                    }
                } else {
                    outs() << fmt::format("\n{:{}}.def_readwrite(\"{}\", &{})",
                                          "",
                                          8,
                                          Field->getName().str(),
                                          Field->getQualifiedNameAsString());
                }
            }
            outs() << fmt::format("\n{:{}}.def(\"__str__\", [](const {} &o) {{",
                                  "",
                                  8,
                                  Record->getQualifiedNameAsString());
            outs() << fmt::format(
                "\n{:{}}return fmt::format(\"{{}}\", typeid(decltype(o).name()));",
                "",
                12);
            outs() << fmt::format("\n{:{}}}})", "", 8);
            outs() << fmt::format("\n{:{}}.def(\"__repr__\", [](const {} &o) {{",
                                  "",
                                  8,
                                  Record->getQualifiedNameAsString());
            outs() << fmt::format(
                "\n{:{}}return fmt::format(\"{{}}\", typeid(decltype(o).name()));",
                "",
                12);
            outs() << fmt::format("\n{:{}}}})", "", 8);
            outs() << ";\n";
        }
    }
};

static cl::OptionCategory CodegenCategory("codegen options");
static cl::extrahelp      CommonHelp(CommonOptionsParser::HelpMessage);

int main(int argc, const char * argv[]) {
    auto ExpectedParser = CommonOptionsParser::create(argc, argv, CodegenCategory);
    if (! ExpectedParser) {
        errs() << ExpectedParser.takeError();
        return 1;
    }
    auto &    OptionsParser = ExpectedParser.get();
    ClangTool Tool(OptionsParser.getCompilations(), OptionsParser.getSourcePathList());

    Printer     Printer;
    MatchFinder Finder;
    Finder.addMatcher(EnumMatcher, &Printer);
    Finder.addMatcher(RecordMatcher, &Printer);

    return Tool.run(newFrontendActionFactory(&Finder).get());
    /* return Tool.run(newFrontendActionFactory<clang::SyntaxOnlyAction>().get()); */
}
