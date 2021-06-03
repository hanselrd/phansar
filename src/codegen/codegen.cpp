#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/ASTMatchers/ASTMatchers.h>
#include <clang/Frontend/ASTUnit.h>
#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>
#include <fmt/format.h>
#include <llvm/Support/CommandLine.h>
#include <nlohmann/json.hpp>

#include <cctype>
#include <unordered_map>
#include <vector>

/* using namespace llvm; */
/* using namespace clang; */
using namespace clang::ast_matchers;
/* using namespace clang::tooling; */

auto g_decl_matcher = decl(anyOf(enumDecl(),
                                 cxxRecordDecl(/*unless(hasParent(classTemplateDecl())),
                                               unless(classTemplatePartialSpecializationDecl()),
                                               unless(classTemplateSpecializationDecl())*/)),
                           isExpansionInMainFile(),
                           unless(isImplicit()),
                           hasAttr(clang::attr::Kind::Annotate))
                          .bind("id");

static nlohmann::json parse_annotations(const clang::Decl * decl) {
    if (! decl->hasAttrs()) {
        return {};
    }

    auto json = nlohmann::json{};

    for (const auto & attr : decl->attrs()) {
        if (attr->getKind() != clang::attr::Kind::Annotate) {
            continue;
        }

        auto str       = std::string{};
        auto os        = llvm::raw_string_ostream{str};
        auto lang_opts = clang::LangOptions{};
        auto policy    = clang::PrintingPolicy{lang_opts};
        attr->printPretty(os, policy);
        str = str.substr(std::strlen("__attribute__((annotate(\"") + 1,
                         str.size() - std::strlen("__attribute__((annotate(\"") -
                             std::strlen("\")))") - 1);

        auto escape        = bool{false};
        auto token         = std::string{};
        auto history       = std::vector<std::string>{"__root__", std::to_string(0)};
        auto history_index = std::unordered_map<std::string, std::uint64_t>{{"/__root__", 0}};

        for (const auto & c : str) {
            if (std::exchange(escape, false)) {
                token.push_back(c);
                continue;
            }

            switch (c) {
            case '\\': {
                escape = true;
            } break;
            case '(': {
                history.push_back(token);
                auto path = fmt::format("/{}", fmt::join(history, "/"));
                if (! history_index.contains(path)) {
                    history_index.emplace(path, 0);
                } else {
                    ++history_index.at(path);
                }
                history.push_back(fmt::format("{}", history_index.at(path)));
                token.clear();
            } break;
            case ')': {
                if (! token.empty()) {
                    auto path = fmt::format("/{}", fmt::join(history, "/"));
                    json.emplace(path, token);
                    token.clear();
                }
                history.pop_back();
                history.pop_back();
            } break;
            case ',': {
                if (! token.empty()) {
                    auto path = fmt::format("/{}", fmt::join(history, "/"));
                    json.emplace(path, token);
                    token.clear();
                }
                history.pop_back();
                auto path = fmt::format("/{}", fmt::join(history, "/"));
                if (! history_index.contains(path)) {
                    history_index.emplace(path, 0);
                } else {
                    ++history_index.at(path);
                }
                history.push_back(fmt::format("{}", history_index.at(path)));
            } break;
            default: {
                if (std::isspace(static_cast<unsigned char>(c)) && token.empty()) {
                    continue;
                }

                token.push_back(c);
            } break;
            }
        }

        if (! token.empty()) {
            auto path = fmt::format("/{}", fmt::join(history, "/"));
            json.emplace(path, token);
            token.clear();
        }
    }

    return json.is_object() ? json.unflatten() : json;
}

class Printer : public MatchFinder::MatchCallback {
public:
    void onStartOfTranslationUnit() override {
        llvm::outs() << "#include <fmt/format.h>\n";
        llvm::outs() << "#include <pybind11/chrono.h>\n";
        llvm::outs() << "#include <pybind11/complex.h>\n";
        llvm::outs() << "#include <pybind11/embed.h>\n";
        llvm::outs() << "#include <pybind11/functional.h>\n";
        llvm::outs() << "#include <pybind11/stl.h>\n\n";

        llvm::outs() << "namespace py = pybind11;\n\n";

        llvm::outs() << "// NOLINTNEXTLINE(modernize-use-trailing-return-type)\n";
        llvm::outs() << "PYBIND11_EMBEDDED_MODULE(phansar, m) {\n";
    }

    void onEndOfTranslationUnit() override {
        llvm::outs() << "}\n";
    }

    void run(const MatchFinder::MatchResult & _result) override {
        if (const auto * decl = _result.Nodes.getNodeAs<clang::Decl>("id")) {
            if ((decl->getAccess() != clang::AccessSpecifier::AS_public &&
                 decl->getAccess() != clang::AccessSpecifier::AS_none) ||
                decl->isInAnonymousNamespace()) {
                return;
            }

            auto annotations = parse_annotations(decl);

            switch (decl->getKind()) {
            case clang::Decl::Kind::Enum: {
                auto enum_decl = llvm::cast<clang::EnumDecl>(decl);

                llvm::outs() << fmt::format("{:{}}py::enum_<{}>(m, \"{}\")",
                                            "",
                                            4,
                                            enum_decl->getQualifiedNameAsString(),
                                            enum_decl->getNameAsString());

                for (const auto & noload_decl : enum_decl->noload_decls()) {
                    switch (noload_decl->getKind()) {
                    case clang::Decl::Kind::EnumConstant: {
                        auto enum_constant_decl = llvm::cast<clang::EnumConstantDecl>(noload_decl);

                        llvm::outs() << fmt::format("\n{:{}}.value(\"{}\", {})",
                                                    "",
                                                    8,
                                                    enum_constant_decl->getNameAsString(),
                                                    enum_constant_decl->getQualifiedNameAsString());
                    } break;
                    default:
                        break;
                    }
                }

                llvm::outs() << ";\n";
            } break;
            case clang::Decl::Kind::CXXRecord: {
                auto cxx_record_decl = llvm::cast<clang::CXXRecordDecl>(decl);
                /* cxx_record_decl->dump(); */

                /* if (annotations.contains("__root__")) { */
                /*     for (const auto & level0 : annotations.at("__root__")) { */
                /*         if (level0.contains("template")) { */
                /*             llvm::outs() */
                /*                 << fmt::format("{}, {}", */
                /*                                level0.at("template").at(0).at("name").at(0), */
                /*                                "test"); */
                /*         } */
                /*         for (const auto & level1 : level0) { */
                /*             llvm::outs() << fmt::format("{}\n", level1.dump()); */
                /*         } */
                /*     } */
                /* } */

                llvm::outs() << fmt::format("{:{}}py::class_<{}>(m, \"{}\")",
                                            "",
                                            4,
                                            cxx_record_decl->getQualifiedNameAsString(),
                                            cxx_record_decl->getNameAsString());

                if (cxx_record_decl->ctors().empty()) {
                    llvm::outs() << fmt::format("\n{:{}}.def(py::init<>())", "", 8);
                }

                for (const auto & noload_decl : cxx_record_decl->noload_decls()) {
                    switch (noload_decl->getKind()) {
                    case clang::Decl::Kind::CXXConstructor: {
                        auto * ctor = llvm::cast<clang::CXXConstructorDecl>(noload_decl);

                        if (ctor->isCopyOrMoveConstructor() ||
                            ctor->getAccess() != clang::AccessSpecifier::AS_public) {
                            continue;
                        }

                        llvm::outs() << fmt::format("\n{:{}}.def(py::init<", "", 8);
                        for (const auto & param : ctor->parameters()) {
                            llvm::outs() << fmt::format(
                                "{}{}",
                                param->getType().getAsString(),
                                (param != *(ctor->parameters().rbegin())) ? ", " : "");
                        }
                        llvm::outs() << ">())";
                    } break;
                    case clang::Decl::Kind::CXXMethod: {
                        auto * method = llvm::cast<clang::CXXMethodDecl>(noload_decl);

                        if (method->isOverloadedOperator() ||
                            method->getAccess() != clang::AccessSpecifier::AS_public) {
                            continue;
                        }

                        llvm::outs() << fmt::format("\n{:{}}.{}(\"{}\", py::overload_cast<",
                                                    "",
                                                    8,
                                                    method->isStatic() ? "def_static" : "def",
                                                    method->getNameAsString());
                        for (const auto & param : method->parameters()) {
                            llvm::outs() << fmt::format(
                                "{}{}",
                                param->getType().getAsString(),
                                (param != *(method->parameters().rbegin())) ? ", " : "");
                        }
                        llvm::outs() << fmt::format(">(&{}{}))",
                                                    method->getQualifiedNameAsString(),
                                                    method->isConst() ? ", py::const_" : "");
                    } break;
                    case clang::Decl::Kind::Field: {
                        auto * field = llvm::cast<clang::FieldDecl>(noload_decl);

                        if (field->getAccess() != clang::AccessSpecifier::AS_public) {
                            continue;
                        }

                        llvm::outs() << fmt::format(
                            "\n{:{}}.{}(\"{}\", &{})",
                            "",
                            8,
                            field->getType().isConstQualified() ? "def_readonly" : "def_readwrite",
                            field->getNameAsString(),
                            field->getQualifiedNameAsString());
                    } break;
                    case clang::Decl::Kind::Var: {
                        auto * var = llvm::cast<clang::VarDecl>(noload_decl);

                        if (var->getAccess() != clang::AccessSpecifier::AS_public) {
                            continue;
                        }

                        llvm::outs() << fmt::format("\n{:{}}.{}(\"{}\", &{})",
                                                    "",
                                                    8,
                                                    var->getType().isConstQualified()
                                                        ? "def_readonly_static"
                                                        : "def_readwrite_static",
                                                    var->getNameAsString(),
                                                    var->getQualifiedNameAsString());
                    } break;
                    default:
                        break;
                    }
                }
                llvm::outs() << fmt::format("\n{:{}}.def(\"__repr__\", [](const {} &_o) {{",
                                            "",
                                            8,
                                            cxx_record_decl->getQualifiedNameAsString());
                llvm::outs() << fmt::format(
                    "\n{:{}}return fmt::format(\"<{} object at {{}} with {{}} "
                    "byte(s)>\", static_cast<const void *>(&_o), sizeof(_o));",
                    "",
                    12,
                    cxx_record_decl->getQualifiedNameAsString());
                llvm::outs() << fmt::format("\n{:{}}}})", "", 8);
                llvm::outs() << ";\n";
            } break;
            default:
                break;
            }
        }
    }
};

static llvm::cl::OptionCategory g_CodegenCategory("codegen options");
static llvm::cl::extrahelp      g_CommonHelp(clang::tooling::CommonOptionsParser::HelpMessage);

auto main(int _argc, const char * _argv[]) -> int {
    auto expected_parser =
        clang::tooling::CommonOptionsParser::create(_argc, _argv, g_CodegenCategory);
    if (! expected_parser) {
        llvm::errs() << expected_parser.takeError();
        return 1;
    }

    auto & options_parser = expected_parser.get();
    auto   tool           = clang::tooling::ClangTool{options_parser.getCompilations(),
                                          options_parser.getSourcePathList()};

    /* tool.appendArgumentsAdjuster(clang::tooling::getInsertArgumentAdjuster("-stdlib=libc++")); */
    tool.appendArgumentsAdjuster(clang::tooling::getInsertArgumentAdjuster("-nostdinc++"));
    tool.appendArgumentsAdjuster(clang::tooling::getInsertArgumentAdjuster("-I" STDINC0));
    tool.appendArgumentsAdjuster(clang::tooling::getInsertArgumentAdjuster("-I" STDINC1));
    /* tool.appendArgumentsAdjuster(clang::tooling::getInsertArgumentAdjuster("-L" STDLIB0)); */
    /* tool.appendArgumentsAdjuster(clang::tooling::getInsertArgumentAdjuster("-Wl,-rpath,"
     * STDLIB0)); */
    tool.appendArgumentsAdjuster(
        clang::tooling::getInsertArgumentAdjuster("-Wno-unknown-warning-option"));
    tool.appendArgumentsAdjuster(
        clang::tooling::getInsertArgumentAdjuster("-Wno-unused-command-line-argument"));

    auto printer = Printer{};
    auto finder  = MatchFinder{};
    finder.addMatcher(g_decl_matcher, &printer);

    return tool.run(clang::tooling::newFrontendActionFactory(&finder).get());
}
