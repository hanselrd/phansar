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

auto g_EnumMatcher   = enumDecl(isExpansionInMainFile()).bind("enum");
auto g_RecordMatcher = cxxRecordDecl(isExpansionInMainFile(), unless(isImplicit())).bind("record");

class Printer : public MatchFinder::MatchCallback {
public:
    void onStartOfTranslationUnit() override {
        outs() << "#include <fmt/format.h>\n";
        outs() << "#include <pybind11/embed.h>\n\n";

        outs() << "PYBIND11_EMBEDDED_MODULE(phansar, m) {\n";
    }

    void onEndOfTranslationUnit() override {
        outs() << "}\n";
    }

    void run(const MatchFinder::MatchResult & _result) override {
        if (const auto * Enum = _result.Nodes.getNodeAs<EnumDecl>("enum")) {
            /* Enum->dump(); */
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
        if (const auto * Record = _result.Nodes.getNodeAs<CXXRecordDecl>("record")) {
            /* Record->dump(); */
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
                "\n{:{}}return fmt::format(\"{{}}\", typeid(decltype(o)).name());",
                "",
                12);
            outs() << fmt::format("\n{:{}}}})", "", 8);
            outs() << ";\n";
        }
    }
};

static cl::OptionCategory g_CodegenCategory("codegen options");
static cl::extrahelp      g_CommonHelp(CommonOptionsParser::HelpMessage);

auto main(int _argc, const char * _argv[]) -> int {
    auto expected_parser = CommonOptionsParser::create(_argc, _argv, g_CodegenCategory);
    if (! expected_parser) {
        errs() << expected_parser.takeError();
        return 1;
    }

    auto & options_parser = expected_parser.get();
    auto   tool = ClangTool{options_parser.getCompilations(), options_parser.getSourcePathList()};

    /* tool.appendArgumentsAdjuster(getInsertArgumentAdjuster("-stdlib=libc++")); */
    tool.appendArgumentsAdjuster(getInsertArgumentAdjuster("-nostdinc++"));
    tool.appendArgumentsAdjuster(getInsertArgumentAdjuster("-I" STDINC0));
    tool.appendArgumentsAdjuster(getInsertArgumentAdjuster("-I" STDINC1));
    /* tool.appendArgumentsAdjuster(getInsertArgumentAdjuster("-L" STDLIB0)); */
    /* tool.appendArgumentsAdjuster(getInsertArgumentAdjuster("-Wl,-rpath," STDLIB0)); */
    tool.appendArgumentsAdjuster(getInsertArgumentAdjuster("-Wno-unknown-warning-option"));
    tool.appendArgumentsAdjuster(getInsertArgumentAdjuster("-Wno-unused-command-line-argument"));

    auto printer = Printer{};
    auto finder  = MatchFinder{};
    finder.addMatcher(g_EnumMatcher, &printer);
    finder.addMatcher(g_RecordMatcher, &printer);

    return tool.run(newFrontendActionFactory(&finder).get());
}
