// 由 benchmark/tools/import_exercism.py 从上游 Catch2 测试机械转换；隐藏材料，不提供给被评测的生成 Agent。
#define EXERCISM_RUN_ALL_TESTS 1
#include <gtest/gtest.h>
#include "catch_compat.h"



#include <peglib.h>
#include "grammar_scope.h"
#include <iostream>

namespace {

#if !defined(PEGLIB_NO_UNICODE_CHARS)
TEST(PegParser, T001_Simple_syntax_test_with_unicode)
{
    peg::parser parser(
        u8" ROOT ← _ "
        " _ <- ' ' "
    );

    bool ret = parser;
    REQUIRE(ret == true);
}
#endif

TEST(PegParser, T002_Simple_syntax_test)
{
    peg::parser parser(
        " ROOT <- _ "
        " _ <- ' ' "
    );

    bool ret = parser;
    REQUIRE(ret == true);
}

TEST(PegParser, T003_Empty_syntax_test)
{
    peg::parser parser("");
    bool ret = parser;
    REQUIRE(ret == false);
}

TEST(PegParser, T004_Action_taking_non_const_Semantic_Values_parameter)
{
    peg::parser parser(R"(
        ROOT <- TEXT
        TEXT <- [a-zA-Z]+
    )");

    parser["ROOT"] = [&](peg::SemanticValues& sv) {
        auto& s = sv[0].get<std::string>();
        s[0] = 'H'; // mutate
        return std::string(std::move(s)); // move
    };

    parser["TEXT"] = [&](peg::SemanticValues& sv) {
        return sv.token();
    };

    std::string val;
    auto ret = parser.parse("hello", val);
    REQUIRE(ret == true);
    REQUIRE(val == "Hello");
}

TEST(PegParser, T005_String_capture_test)
{
    peg::parser parser(
        "  ROOT      <-  _ ('[' TAG_NAME ']' _)*  "
        "  TAG_NAME  <-  (!']' .)+                "
        "  _         <-  [ \t]*                   "
    );

    std::vector<std::string> tags;

    parser["TAG_NAME"] = [&](const peg::SemanticValues& sv) {
        tags.push_back(sv.str());
    };

    auto ret = parser.parse(" [tag1] [tag:2] [tag-3] ");

    REQUIRE(ret == true);
    REQUIRE(tags.size() == 3);
    REQUIRE(tags[0] == "tag1");
    REQUIRE(tags[1] == "tag:2");
    REQUIRE(tags[2] == "tag-3");
}

using namespace peg;
using namespace std;

TEST(PegParser, T006_String_capture_test2)
{
    vector<string> tags;

    Definition ROOT, TAG, TAG_NAME, WS;
    ROOT     <= seq(WS, zom(TAG));
    TAG      <= seq(chr('['), TAG_NAME, chr(']'), WS);
    TAG_NAME <= oom(seq(npd(chr(']')), dot())), [&](const SemanticValues& sv) { tags.push_back(sv.str()); };
    WS       <= zom(cls(" \t"));

    auto r = ROOT.parse(" [tag1] [tag:2] [tag-3] ");

    REQUIRE(r.ret == true);
    REQUIRE(tags.size() == 3);
    REQUIRE(tags[0] == "tag1");
    REQUIRE(tags[1] == "tag:2");
    REQUIRE(tags[2] == "tag-3");
}

TEST(PegParser, T007_String_capture_test3)
{
    auto syntax =
        " ROOT  <- _ TOKEN*                "
        " TOKEN <- '[' < (!']' .)+ > ']' _ "
        " _     <- [ \t\r\n]*              "
        ;

    parser pg(syntax);

    std::vector<std::string> tags;

    pg["TOKEN"] = [&](const SemanticValues& sv) {
        tags.push_back(sv.token());
    };

    auto ret = pg.parse(" [tag1] [tag:2] [tag-3] ");

    REQUIRE(ret == true);
    REQUIRE(tags.size() == 3);
    REQUIRE(tags[0] == "tag1");
    REQUIRE(tags[1] == "tag:2");
    REQUIRE(tags[2] == "tag-3");
}

TEST(PegParser, T008_Cyclic_grammer_test)
{
    Definition PARENT;
    Definition CHILD;

    PARENT <= seq(CHILD);
    CHILD  <= seq(PARENT);
}

TEST(PegParser, T009_Visit_test)
{
    Definition ROOT, TAG, TAG_NAME, WS;

    ROOT     <= seq(WS, zom(TAG));
    TAG      <= seq(chr('['), TAG_NAME, chr(']'), WS);
    TAG_NAME <= oom(seq(npd(chr(']')), dot()));
    WS       <= zom(cls(" \t"));

    AssignIDToDefinition defIds;
    ROOT.accept(defIds);

    REQUIRE(defIds.ids.size() == 4);
}

TEST(PegParser, T010_Token_check_test)
{
    parser parser(
        "  EXPRESSION       <-  _ TERM (TERM_OPERATOR TERM)*      "
        "  TERM             <-  FACTOR (FACTOR_OPERATOR FACTOR)*  "
        "  FACTOR           <-  NUMBER / '(' _ EXPRESSION ')' _   "
        "  TERM_OPERATOR    <-  < [-+] > _                        "
        "  FACTOR_OPERATOR  <-  < [/*] > _                        "
        "  NUMBER           <-  < [0-9]+ > _                      "
        "  _               <-  [ \t\r\n]*                        "
        );

    REQUIRE(parser["EXPRESSION"].is_token() == false);
    REQUIRE(parser["FACTOR"].is_token() == false);
    REQUIRE(parser["FACTOR_OPERATOR"].is_token() == true);
    REQUIRE(parser["NUMBER"].is_token() == true);
    REQUIRE(parser["_"].is_token() == true);
}

TEST(PegParser, T011_Lambda_action_test)
{
    parser parser(
       "  START <- (CHAR)* "
       "  CHAR  <- .       ");

    string ss;
    parser["CHAR"] = [&](const SemanticValues& sv) {
        ss += *sv.c_str();
    };

    bool ret = parser.parse("hello");
    REQUIRE(ret == true);
    REQUIRE(ss == "hello");
}

TEST(PegParser, T012_enter_leave_handlers_test)
{
    parser parser(R"(
        START  <- LTOKEN '=' RTOKEN
        LTOKEN <- TOKEN
        RTOKEN <- TOKEN
        TOKEN  <- [A-Za-z]+
    )");

    parser["LTOKEN"].enter = [&](const char*, size_t, any& dt) {
        auto& require_upper_case = *dt.get<bool*>();
        require_upper_case = false;
    };
    parser["LTOKEN"].leave = [&](const char*, size_t, size_t, any&, any& dt) {
        auto& require_upper_case = *dt.get<bool*>();
        require_upper_case = true;
    };

    auto message = "should be upper case string...";

    parser["TOKEN"] = [&](const SemanticValues& sv, any& dt) {
        auto& require_upper_case = *dt.get<bool*>();
        if (require_upper_case) {
            const auto& s = sv.str();
            if (!std::all_of(s.begin(), s.end(), ::isupper)) {
                throw parse_error(message);
            }
        }
    };

    bool require_upper_case = false;
    any dt = &require_upper_case;
    REQUIRE(parser.parse("hello=world", dt) == false);
    REQUIRE(parser.parse("HELLO=world", dt) == false);
    REQUIRE(parser.parse("hello=WORLD", dt) == true);
    REQUIRE(parser.parse("HELLO=WORLD", dt) == true);

    parser.log = [&](size_t ln, size_t col, const string& msg) {
        REQUIRE(ln == 1);
        REQUIRE(col == 7);
        REQUIRE(msg == message);
    };
    parser.parse("hello=world", dt);
}

TEST(PegParser, T013_WHITESPACE_test)
{
    peg::parser parser(R"(
        # Rules
        ROOT         <-  ITEM (',' ITEM)*
        ITEM         <-  WORD / PHRASE

        # Tokens
        WORD         <-  < [a-zA-Z0-9_]+ >
        PHRASE       <-  < '"' (!'"' .)* '"' >

        %whitespace  <-  [ \t\r\n]*
    )");

    auto ret = parser.parse(R"(  one, 	 "two, three",   four  )");

    REQUIRE(ret == true);
}

TEST(PegParser, T014_WHITESPACE_test2)
{
    peg::parser parser(R"(
        # Rules
        ROOT         <-  ITEM (',' ITEM)*
        ITEM         <-  '[' < [a-zA-Z0-9_]+ > ']'

        %whitespace  <-  (SPACE / TAB)*
        SPACE        <-  ' '
        TAB          <-  '\t'
    )");

    vector<string> items;
    parser["ITEM"] = [&](const SemanticValues& sv) {
        items.push_back(sv.token());
    };

    auto ret = parser.parse(R"([one], 	[two] ,[three] )");

    REQUIRE(ret == true);
    REQUIRE(items.size() == 3);
    REQUIRE(items[0] == "one");
    REQUIRE(items[1] == "two");
    REQUIRE(items[2] == "three");
}

TEST(PegParser, T015_WHITESPACE_test3) {
    peg::parser parser(R"(
        StrQuot      <- < '"' < (StrEscape / StrChars)* > '"' >
        StrEscape    <- '\\' any
        StrChars     <- (!'"' !'\\' any)+
        any          <- .
        %whitespace  <- [ \t]*
    )");

    parser["StrQuot"] = [](const SemanticValues& sv) {
        REQUIRE(sv.token() == R"(  aaa \" bbb  )");
    };

    auto ret = parser.parse(R"( "  aaa \" bbb  " )");
    REQUIRE(ret == true);
}

TEST(PegParser, T016_Word_expression_test) {
    peg::parser parser(R"(
        ROOT         <-  'hello' ','? 'world'
        %whitespace  <-  [ \t\r\n]*
        %word        <-  [a-z]+
    )");

	REQUIRE(parser.parse("helloworld") == false);
	REQUIRE(parser.parse("hello world") == true);
	REQUIRE(parser.parse("hello,world") == true);
	REQUIRE(parser.parse("hello, world") == true);
	REQUIRE(parser.parse("hello , world") == true);
}

TEST(PegParser, T017_Skip_token_test)
{
    peg::parser parser(
        "  ROOT  <-  _ ITEM (',' _ ITEM _)* "
        "  ITEM  <-  ([a-z0-9])+  "
        "  ~_    <-  [ \t]*    "
    );

    parser["ROOT"] = [&](const SemanticValues& sv) {
        REQUIRE(sv.size() == 2);
    };

    auto ret = parser.parse(" item1, item2 ");

    REQUIRE(ret == true);
}

TEST(PegParser, T018_Skip_token_test2)
{
    peg::parser parser(R"(
        ROOT        <-  ITEM (',' ITEM)*
        ITEM        <-  < ([a-z0-9])+ >
        %whitespace <-  [ \t]*
    )");

    parser["ROOT"] = [&](const SemanticValues& sv) {
        REQUIRE(sv.size() == 2);
    };

    auto ret = parser.parse(" item1, item2 ");

    REQUIRE(ret == true);
}

TEST(PegParser, T019_Backtracking_test)
{
    parser parser(
       "  START <- PAT1 / PAT2  "
       "  PAT1  <- HELLO ' One' "
       "  PAT2  <- HELLO ' Two' "
       "  HELLO <- 'Hello'      "
    );

    size_t count = 0;
    parser["HELLO"] = [&](const SemanticValues& /*sv*/) {
        count++;
    };

    parser.enable_packrat_parsing();

    bool ret = parser.parse("Hello Two");
    REQUIRE(ret == true);
    REQUIRE(count == 1); // Skip second time
}

TEST(PegParser, T020_Backtracking_with_AST)
{
    parser parser(R"(
        S <- A? B (A B)* A
        A <- 'a'
        B <- 'b'
    )");

    parser.enable_ast();
    shared_ptr<Ast> ast;
    bool ret = parser.parse("ba", ast);
    REQUIRE(ret == true);
    REQUIRE(ast->nodes.size() == 2);
}

TEST(PegParser, T021_Octal_Hex_Unicode_value_test)
{
    peg::parser parser(
        R"( ROOT <- '\132\x7a\u30f3' )"
    );

    auto ret = parser.parse("Zzン");

    REQUIRE(ret == true);
}

TEST(PegParser, T022_mutable_lambda_test)
{
    vector<string> vec;

    parser pg("ROOT <- 'mutable lambda test'");

    // This test makes sure if the following code can be compiled.
    pg["TOKEN"] = [=](const SemanticValues& sv) mutable {
        vec.push_back(sv.str());
    };
}

TEST(PegParser, T023_Simple_calculator_test)
{
    auto syntax =
        " Additive  <- Multitive '+' Additive / Multitive "
        " Multitive <- Primary '*' Multitive / Primary "
        " Primary   <- '(' Additive ')' / Number "
        " Number    <- [0-9]+ ";

    parser parser(syntax);

    parser["Additive"] = [](const SemanticValues& sv) {
        switch (sv.choice()) {
        case 0:
            return sv[0].get<int>() + sv[1].get<int>();
        default:
            return sv[0].get<int>();
        }
    };

    parser["Multitive"] = [](const SemanticValues& sv) {
        switch (sv.choice()) {
        case 0:
            return sv[0].get<int>() * sv[1].get<int>();
        default:
            return sv[0].get<int>();
        }
    };

    parser["Number"] = [](const SemanticValues& sv) {
        return atoi(sv.c_str());
    };

    int val;
    parser.parse("(1+2)*3", val);

    REQUIRE(val == 9);
}

TEST(PegParser, T024_Calculator_test)
{
    // Construct grammer
    Definition EXPRESSION, TERM, FACTOR, TERM_OPERATOR, FACTOR_OPERATOR, NUMBER;

    EXPRESSION      <= seq(TERM, zom(seq(TERM_OPERATOR, TERM)));
    TERM            <= seq(FACTOR, zom(seq(FACTOR_OPERATOR, FACTOR)));
    FACTOR          <= cho(NUMBER, seq(chr('('), EXPRESSION, chr(')')));
    TERM_OPERATOR   <= cls("+-");
    FACTOR_OPERATOR <= cls("*/");
    NUMBER          <= oom(cls("0-9"));

    // Setup actions
    auto reduce = [](const SemanticValues& sv) -> long {
        long ret = sv[0].get<long>();
        for (auto i = 1u; i < sv.size(); i += 2) {
            auto num = sv[i + 1].get<long>();
            switch (sv[i].get<char>()) {
                case '+': ret += num; break;
                case '-': ret -= num; break;
                case '*': ret *= num; break;
                case '/': ret /= num; break;
            }
        }
        return ret;
    };

    EXPRESSION      = reduce;
    TERM            = reduce;
    TERM_OPERATOR   = [](const SemanticValues& sv) { return *sv.c_str(); };
    FACTOR_OPERATOR = [](const SemanticValues& sv) { return *sv.c_str(); };
    NUMBER          = [](const SemanticValues& sv) { return stol(sv.str(), nullptr, 10); };

    // Parse
    long val;
    auto r = EXPRESSION.parse_and_get_value("1+2*3*(4-5+6)/7-8", val);

    REQUIRE(r.ret == true);
    REQUIRE(val == -3);
}

TEST(PegParser, T025_Calculator_test2)
{
    // Parse syntax
    auto syntax =
        "  # Grammar for Calculator...\n                          "
        "  EXPRESSION       <-  TERM (TERM_OPERATOR TERM)*        "
        "  TERM             <-  FACTOR (FACTOR_OPERATOR FACTOR)*  "
        "  FACTOR           <-  NUMBER / '(' EXPRESSION ')'       "
        "  TERM_OPERATOR    <-  [-+]                              "
        "  FACTOR_OPERATOR  <-  [/*]                              "
        "  NUMBER           <-  [0-9]+                            "
        ;

    string start;
    auto grammar = ParserGenerator::parse(syntax, strlen(syntax), start, nullptr);
    auto& g = *grammar;

    // Setup actions
    auto reduce = [](const SemanticValues& sv) -> long {
        long ret = sv[0].get<long>();
        for (auto i = 1u; i < sv.size(); i += 2) {
            auto num = sv[i + 1].get<long>();
            switch (sv[i].get<char>()) {
                case '+': ret += num; break;
                case '-': ret -= num; break;
                case '*': ret *= num; break;
                case '/': ret /= num; break;
            }
        }
        return ret;
    };

    g["EXPRESSION"]      = reduce;
    g["TERM"]            = reduce;
    g["TERM_OPERATOR"]   = [](const SemanticValues& sv) { return *sv.c_str(); };
    g["FACTOR_OPERATOR"] = [](const SemanticValues& sv) { return *sv.c_str(); };
    g["NUMBER"]          = [](const SemanticValues& sv) { return stol(sv.str(), nullptr, 10); };

    // Parse
    long val;
    auto r = g[start].parse_and_get_value("1+2*3*(4-5+6)/7-8", val);

    REQUIRE(r.ret == true);
    REQUIRE(val == -3);
}

TEST(PegParser, T026_Calculator_test3)
{
    // Parse syntax
    parser parser(
        "  # Grammar for Calculator...\n                          "
        "  EXPRESSION       <-  TERM (TERM_OPERATOR TERM)*        "
        "  TERM             <-  FACTOR (FACTOR_OPERATOR FACTOR)*  "
        "  FACTOR           <-  NUMBER / '(' EXPRESSION ')'       "
        "  TERM_OPERATOR    <-  [-+]                              "
        "  FACTOR_OPERATOR  <-  [/*]                              "
        "  NUMBER           <-  [0-9]+                            "
        );

    auto reduce = [](const SemanticValues& sv) -> long {
        long ret = sv[0].get<long>();
        for (auto i = 1u; i < sv.size(); i += 2) {
            auto num = sv[i + 1].get<long>();
            switch (sv[i].get<char>()) {
                case '+': ret += num; break;
                case '-': ret -= num; break;
                case '*': ret *= num; break;
                case '/': ret /= num; break;
            }
        }
        return ret;
    };

    // Setup actions
    parser["EXPRESSION"]      = reduce;
    parser["TERM"]            = reduce;
    parser["TERM_OPERATOR"]   = [](const SemanticValues& sv) { return static_cast<char>(*sv.c_str()); };
    parser["FACTOR_OPERATOR"] = [](const SemanticValues& sv) { return static_cast<char>(*sv.c_str()); };
    parser["NUMBER"]          = [](const SemanticValues& sv) { return stol(sv.str(), nullptr, 10); };

    // Parse
    long val;
    auto ret = parser.parse("1+2*3*(4-5+6)/7-8", val);

    REQUIRE(ret == true);
    REQUIRE(val == -3);
}

TEST(PegParser, T027_Calculator_test_with_AST)
{
    parser parser(
        "  EXPRESSION       <-  _ TERM (TERM_OPERATOR TERM)*      "
        "  TERM             <-  FACTOR (FACTOR_OPERATOR FACTOR)*  "
        "  FACTOR           <-  NUMBER / '(' _ EXPRESSION ')' _   "
        "  TERM_OPERATOR    <-  < [-+] > _                        "
        "  FACTOR_OPERATOR  <-  < [/*] > _                        "
        "  NUMBER           <-  < [0-9]+ > _                      "
        "  ~_               <-  [ \t\r\n]*                        "
        );

    parser.enable_ast();

    function<long (const Ast&)> eval = [&](const Ast& ast) {
        if (ast.name == "NUMBER") {
            return stol(ast.token);
        } else {
            const auto& nodes = ast.nodes;
            auto result = eval(*nodes[0]);
            for (auto i = 1u; i < nodes.size(); i += 2) {
                auto num = eval(*nodes[i + 1]);
                auto ope = nodes[i]->token[0];
                switch (ope) {
                    case '+': result += num; break;
                    case '-': result -= num; break;
                    case '*': result *= num; break;
                    case '/': result /= num; break;
                }
            }
            return result;
        }
    };

    shared_ptr<Ast> ast;
    auto ret = parser.parse("1+2*3*(4-5+6)/7-8", ast);
    ast = peg::AstOptimizer(true).optimize(ast);
    auto val = eval(*ast);

    REQUIRE(ret == true);
    REQUIRE(val == -3);
}

TEST(PegParser, T028_Ignore_semantic_value_test)
{
    parser parser(
       " START <-  ~HELLO WORLD "
       " HELLO <- 'Hello' _     "
       " WORLD <- 'World' _     "
       " _     <- [ \t\r\n]*    "
    );

    parser.enable_ast();

    shared_ptr<Ast> ast;
    auto ret = parser.parse("Hello World", ast);

    REQUIRE(ret == true);
    REQUIRE(ast->nodes.size() == 1);
    REQUIRE(ast->nodes[0]->name == "WORLD");
}

TEST(PegParser, T029_Ignore_semantic_value_of_or_predicate_test)
{
    parser parser(
       " START       <- _ !DUMMY HELLO_WORLD '.' "
       " HELLO_WORLD <- HELLO 'World' _          "
       " HELLO       <- 'Hello' _                "
       " DUMMY       <- 'dummy' _                "
       " ~_          <- [ \t\r\n]*               "
    );

    parser.enable_ast();

    shared_ptr<Ast> ast;
    auto ret = parser.parse("Hello World.", ast);

    REQUIRE(ret == true);
    REQUIRE(ast->nodes.size() == 1);
    REQUIRE(ast->nodes[0]->name == "HELLO_WORLD");
}

TEST(PegParser, T030_Ignore_semantic_value_of_and_predicate_test)
{
    parser parser(
       " START       <- _ &HELLO HELLO_WORLD '.' "
       " HELLO_WORLD <- HELLO 'World' _          "
       " HELLO       <- 'Hello' _                "
       " ~_          <- [ \t\r\n]*               "
    );

    parser.enable_ast();

    shared_ptr<Ast> ast;
    auto ret = parser.parse("Hello World.", ast);

    REQUIRE(ret == true);
    REQUIRE(ast->nodes.size() == 1);
    REQUIRE(ast->nodes[0]->name == "HELLO_WORLD");
}

TEST(PegParser, T031_Literal_token_on_AST_test1)
{
    parser parser(R"(
        STRING_LITERAL  <- '"' (('\\"' / '\\t' / '\\n') / (!["] .))* '"'
    )");
    parser.enable_ast();

    shared_ptr<Ast> ast;
    auto ret = parser.parse(R"("a\tb")", ast);

    REQUIRE(ret == true);
    REQUIRE(ast->is_token == true);
    REQUIRE(ast->token == R"("a\tb")");
    REQUIRE(ast->nodes.empty());
}

TEST(PegParser, T032_Literal_token_on_AST_test2)
{
    parser parser(R"(
        STRING_LITERAL  <-  '"' (ESC / CHAR)* '"'
        ESC             <-  ('\\"' / '\\t' / '\\n')
        CHAR            <-  (!["] .)
    )");
    parser.enable_ast();

    shared_ptr<Ast> ast;
    auto ret = parser.parse(R"("a\tb")", ast);

    REQUIRE(ret == true);
    REQUIRE(ast->is_token == false);
    REQUIRE(ast->token.empty());
    REQUIRE(ast->nodes.size() == 3);
}

TEST(PegParser, T033_Literal_token_on_AST_test3)
{
    parser parser(R"(
        STRING_LITERAL  <-  < '"' (ESC / CHAR)* '"' >
        ESC             <-  ('\\"' / '\\t' / '\\n')
        CHAR            <-  (!["] .)
    )");
    parser.enable_ast();

    shared_ptr<Ast> ast;
    auto ret = parser.parse(R"("a\tb")", ast);

    REQUIRE(ret == true);
    REQUIRE(ast->is_token == true);
    REQUIRE(ast->token == R"("a\tb")");
    REQUIRE(ast->nodes.empty());
}

TEST(PegParser, T034_Missing_missing_definitions_test)
{
    parser parser(
        " A <- B C "
    );

    REQUIRE(!parser);
}

TEST(PegParser, T035_Definition_duplicates_test)
{
    parser parser(
        " A <- ''"
        " A <- ''"
    );

    REQUIRE(!parser);
}

TEST(PegParser, T036_Semantic_values_test)
{
    parser parser(R"(
        term <- ( a b c x )? a b c
        a <- 'a'
        b <- 'b'
        c <- 'c'
        x <- 'x'
    )");

	for (const auto& rule: parser.get_rule_names()){
		parser[rule.c_str()] = [rule](const SemanticValues& sv, any&) {
            if (rule == "term") {
                REQUIRE(sv[0].get<string>() == "a at 0");
                REQUIRE(sv[1].get<string>() == "b at 1");
                REQUIRE(sv[2].get<string>() == "c at 2");
                return string();
            } else {
                return rule + " at " + to_string(sv.c_str() - sv.ss);
            }
		};
	}

	REQUIRE(parser.parse("abc"));
}

TEST(PegParser, T037_Ordered_choice_count)
{
    auto syntax = R"(S <- 'a' / 'b')";

    parser parser(syntax);

    parser["S"] = [](const SemanticValues& sv) {
        REQUIRE(sv.choice() == 1);
        REQUIRE(sv.choice_count() == 2);
    };

    parser.parse("b");
}

TEST(PegParser, T038_Ordered_choice_count_2)
{
    auto syntax = R"(S <- ('a' / 'b')*)";

    parser parser(syntax);

    parser["S"] = [](const SemanticValues& sv) {
        REQUIRE(sv.choice() == 0);
        REQUIRE(sv.choice_count() == 0);
    };

    parser.parse("b");
}

TEST(PegParser, T039_Packrat_parser_test_with_whitespace)
{
    peg::parser parser(R"(
        ROOT         <-  'a'
        %whitespace  <-  SPACE*
        SPACE        <-  ' '
    )");

    parser.enable_packrat_parsing();

    auto ret = parser.parse("a");
    REQUIRE(ret == true);
}

TEST(PegParser, T040_Packrat_parser_test_with_macro)
{
    parser parser(R"(
        EXPRESSION       <-  _ LIST(TERM, TERM_OPERATOR)
        TERM             <-  LIST(FACTOR, FACTOR_OPERATOR)
        FACTOR           <-  NUMBER / T('(') EXPRESSION T(')')
        TERM_OPERATOR    <-  T([-+])
        FACTOR_OPERATOR  <-  T([/*])
        NUMBER           <-  T([0-9]+)
		~_               <-  [ \t]*
		LIST(I, D)       <-  I (D I)*
		T(S)             <-  < S > _
	)");

    parser.enable_packrat_parsing();

    auto ret = parser.parse(" 1 + 2 * 3 * (4 - 5 + 6) / 7 - 8 ");
    REQUIRE(ret == true);
}

TEST(PegParser, T041_Backreference_test)
{
    parser parser(R"(
        START  <- _ LQUOTE < (!RQUOTE .)* > RQUOTE _
        LQUOTE <- 'R"' $delm< [a-zA-Z]* > '('
        RQUOTE <- ')' $delm '"'
        ~_     <- [ \t\r\n]*
    )");

    std::string token;
    parser["START"] = [&](const SemanticValues& sv) {
        token = sv.token();
    };

    {
        token.clear();
        auto ret = parser.parse(R"delm(
            R"("hello world")"
        )delm");

        REQUIRE(ret == true);
        REQUIRE(token == "\"hello world\"");
    }

    {
        token.clear();
        auto ret = parser.parse(R"delm(
            R"foo("(hello world)")foo"
        )delm");

        REQUIRE(ret == true);
        REQUIRE(token == "\"(hello world)\"");
    }

    {
        token.clear();
        auto ret = parser.parse(R"delm(
            R"foo("(hello world)foo")foo"
        )delm");

        REQUIRE(ret == false);
        REQUIRE(token == "\"(hello world");
    }

    {
        token.clear();
        auto ret = parser.parse(R"delm(
            R"foo("(hello world)")bar"
        )delm");

        REQUIRE(ret == false);
        REQUIRE(token.empty());
    }
}

TEST(PegParser, T042_Invalid_backreference_test)
{
    parser parser(R"(
        START  <- _ LQUOTE (!RQUOTE .)* RQUOTE _
        LQUOTE <- 'R"' $delm< [a-zA-Z]* > '('
        RQUOTE <- ')' $delm2 '"'
        ~_     <- [ \t\r\n]*
    )");

    REQUIRE_THROWS_AS(
        parser.parse(R"delm(
            R"foo("(hello world)")foo"
        )delm"),
        std::runtime_error);
}


TEST(PegParser, T043_Nested_capture_test)
{
    parser parser(R"(
        ROOT      <- CONTENT
        CONTENT   <- (ELEMENT / TEXT)*
        ELEMENT   <- $(STAG CONTENT ETAG)
        STAG      <- '<' $tag< TAG_NAME > '>'
        ETAG      <- '</' $tag '>'
        TAG_NAME  <- 'b' / 'u'
        TEXT      <- TEXT_DATA
        TEXT_DATA <- ![<] .
    )");

    REQUIRE(parser.parse("This is <b>a <u>test</u> text</b>."));
    REQUIRE(!parser.parse("This is <b>a <u>test</b> text</u>."));
    REQUIRE(!parser.parse("This is <b>a <u>test text</b>."));
    REQUIRE(!parser.parse("This is a <u>test</u> text</b>."));
}

TEST(PegParser, T044_Backreference_with_Prioritized_Choice_test)
{
    parser parser(R"(
        TREE           <- WRONG_BRANCH / CORRECT_BRANCH
        WRONG_BRANCH   <- BRANCH THAT IS_capture WRONG
        CORRECT_BRANCH <- BRANCH THAT IS_backref CORRECT
        BRANCH         <- 'branch'
        THAT           <- 'that'
        IS_capture     <- $ref<..>
        IS_backref     <- $ref
        WRONG          <- 'wrong'
        CORRECT        <- 'correct'
    )");

    REQUIRE_THROWS_AS(parser.parse("branchthatiscorrect"), std::runtime_error);
}

TEST(PegParser, T045_Backreference_with_Zero_or_More_test)
{
    parser parser(R"(
        TREE           <- WRONG_BRANCH* CORRECT_BRANCH
        WRONG_BRANCH   <- BRANCH THAT IS_capture WRONG
        CORRECT_BRANCH <- BRANCH THAT IS_backref CORRECT
        BRANCH         <- 'branch'
        THAT           <- 'that'
        IS_capture     <- $ref<..>
        IS_backref     <- $ref
        WRONG          <- 'wrong'
        CORRECT        <- 'correct'
    )");

    REQUIRE(parser.parse("branchthatiswrongbranchthatiscorrect"));
    REQUIRE(!parser.parse("branchthatiswrongbranchthatIscorrect"));
    REQUIRE(!parser.parse("branchthatiswrongbranchthatIswrongbranchthatiscorrect"));
    REQUIRE(parser.parse("branchthatiswrongbranchthatIswrongbranchthatIscorrect"));
    REQUIRE_THROWS_AS(parser.parse("branchthatiscorrect"), std::runtime_error);
    REQUIRE_THROWS_AS(parser.parse("branchthatiswron_branchthatiscorrect"), std::runtime_error);
}

TEST(PegParser, T046_Backreference_with_One_or_More_test)
{
    parser parser(R"(
        TREE           <- WRONG_BRANCH+ CORRECT_BRANCH
        WRONG_BRANCH   <- BRANCH THAT IS_capture WRONG
        CORRECT_BRANCH <- BRANCH THAT IS_backref CORRECT
        BRANCH         <- 'branch'
        THAT           <- 'that'
        IS_capture     <- $ref<..>
        IS_backref     <- $ref
        WRONG          <- 'wrong'
        CORRECT        <- 'correct'
    )");

    REQUIRE(parser.parse("branchthatiswrongbranchthatiscorrect"));
    REQUIRE(!parser.parse("branchthatiswrongbranchthatIscorrect"));
    REQUIRE(!parser.parse("branchthatiswrongbranchthatIswrongbranchthatiscorrect"));
    REQUIRE(parser.parse("branchthatiswrongbranchthatIswrongbranchthatIscorrect"));
    REQUIRE(!parser.parse("branchthatiscorrect"));
    REQUIRE(!parser.parse("branchthatiswron_branchthatiscorrect"));
}

TEST(PegParser, T047_Backreference_with_Option_test)
{
    parser parser(R"(
        TREE           <- WRONG_BRANCH? CORRECT_BRANCH
        WRONG_BRANCH   <- BRANCH THAT IS_capture WRONG
        CORRECT_BRANCH <- BRANCH THAT IS_backref CORRECT
        BRANCH         <- 'branch'
        THAT           <- 'that'
        IS_capture     <- $ref<..>
        IS_backref     <- $ref
        WRONG          <- 'wrong'
        CORRECT        <- 'correct'
    )");

    REQUIRE(parser.parse("branchthatiswrongbranchthatiscorrect"));
    REQUIRE(!parser.parse("branchthatiswrongbranchthatIscorrect"));
    REQUIRE(!parser.parse("branchthatiswrongbranchthatIswrongbranchthatiscorrect"));
    REQUIRE(!parser.parse("branchthatiswrongbranchthatIswrongbranchthatIscorrect"));
    REQUIRE_THROWS_AS(parser.parse("branchthatiscorrect"), std::runtime_error);
    REQUIRE_THROWS_AS(parser.parse("branchthatiswron_branchthatiscorrect"), std::runtime_error);
}

TEST(PegParser, T048_Left_recursive_test)
{
    parser parser(
        " A <- A 'a'"
        " B <- A 'a'"
    );

    REQUIRE(!parser);
}

TEST(PegParser, T049_Left_recursive_with_option_test)
{
    parser parser(
        " A  <- 'a' / 'b'? B 'c' "
        " B  <- A                "
    );

    REQUIRE(!parser);
}

TEST(PegParser, T050_Left_recursive_with_zom_test)
{
    parser parser(
        " A <- 'a'* A* "
    );

    REQUIRE(!parser);
}

TEST(PegParser, T051_Left_recursive_with_a_ZOM_content_rule)
{
    parser parser(R"(
        A <- B
        B <- _ A
        _ <- ' '* # Zero or more
    )");

    REQUIRE(!parser);
}

TEST(PegParser, T052_Left_recursive_with_empty_string_test)
{
    parser parser(
        " A <- '' A"
    );

    REQUIRE(!parser);
}

TEST(PegParser, T053_User_defined_rule_test)
{
    auto g = parser(R"(
        ROOT <- _ 'Hello' _ NAME '!' _
    )",
    {
        {
            "NAME", usr([](const char* s, size_t n, SemanticValues& /*sv*/, any& /*dt*/) -> size_t {
                static vector<string> names = { "PEG", "BNF" };
                for (const auto& name: names) {
                    if (name.size() <= n && !name.compare(0, name.size(), s, name.size())) {
                        return name.size();
                    }
                }
                return static_cast<size_t>(-1);
            })
        },
        {
            "~_", zom(cls(" \t\r\n"))
        }
    });

    REQUIRE(g.parse(" Hello BNF! ") == true);
}

TEST(PegParser, T054_Semantic_predicate_test)
{
    parser parser("NUMBER  <-  [0-9]+");

    parser["NUMBER"] = [](const SemanticValues& sv) {
        auto val = stol(sv.token(), nullptr, 10);
        if (val != 100) {
            throw parse_error("value error!!");
        }
        return val;
    };

    long val;
    REQUIRE(parser.parse("100", val));
    REQUIRE(val == 100);

    REQUIRE(!parser.parse("200", val));
}

TEST(PegParser, T055_Japanese_character)
{
    peg::parser parser(u8R"(
        文 <- 修飾語? 主語 述語 '。'
        主語 <- 名詞 助詞
        述語 <- 動詞 助詞
        修飾語 <- 形容詞
        名詞 <- 'サーバー' / 'クライアント'
        形容詞 <- '古い' / '新しい'
        動詞 <- '落ち' / '復旧し'
        助詞 <- 'が' / 'を' / 'た' / 'ます' / 'に'
    )");

    bool ret = parser;
    REQUIRE(ret == true);

    REQUIRE(parser.parse(u8R"(サーバーを復旧します。)"));
}

TEST(PegParser, T056_dot_with_a_code)
{
    peg::parser parser(" S <- 'a' . 'b' ");
    REQUIRE(parser.parse(u8R"(aあb)"));
}

TEST(PegParser, T057_dot_with_a_char)
{
    peg::parser parser(" S <- 'a' . 'b' ");
    REQUIRE(parser.parse(u8R"(aåb)"));
}

TEST(PegParser, T058_character_class)
{
    peg::parser parser(R"(
        S <- 'a' [い-おAさC-Eた-とは] 'b'
    )");

    bool ret = parser;
    REQUIRE(ret == true);

    REQUIRE(!parser.parse(u8R"(aあb)"));
    REQUIRE(parser.parse(u8R"(aいb)"));
    REQUIRE(parser.parse(u8R"(aうb)"));
    REQUIRE(parser.parse(u8R"(aおb)"));
    REQUIRE(!parser.parse(u8R"(aかb)"));
    REQUIRE(parser.parse(u8R"(aAb)"));
    REQUIRE(!parser.parse(u8R"(aBb)"));
    REQUIRE(parser.parse(u8R"(aEb)"));
    REQUIRE(!parser.parse(u8R"(aFb)"));
    REQUIRE(!parser.parse(u8R"(aそb)"));
    REQUIRE(parser.parse(u8R"(aたb)"));
    REQUIRE(parser.parse(u8R"(aちb)"));
    REQUIRE(parser.parse(u8R"(aとb)"));
    REQUIRE(!parser.parse(u8R"(aなb)"));
    REQUIRE(parser.parse(u8R"(aはb)"));
    REQUIRE(!parser.parse(u8R"(a?b)"));
}

#if 0 // TODO: Unicode Grapheme support
TEST(PegParser, T059_dot_with_a_grapheme)
{
    peg::parser parser(" S <- 'a' . 'b' ");
    REQUIRE(parser.parse(u8R"(aसिb)"));
}
#endif

TEST(PegParser, T060_Macro_simple_test)
{
    parser parser(R"(
		S     <- HELLO WORLD
		HELLO <- T('hello')
		WORLD <- T('world')
		T(a)  <- a [ \t]*
	)");

    REQUIRE(parser.parse("hello \tworld "));
}

TEST(PegParser, T061_Macro_two_parameters)
{
    parser parser(R"(
		S           <- HELLO_WORLD
		HELLO_WORLD <- T('hello', 'world')
		T(a, b)     <- a [ \t]* b [ \t]*
	)");

    REQUIRE(parser.parse("hello \tworld "));
}

TEST(PegParser, T062_Macro_syntax_error)
{
    parser parser(R"(
		S     <- T('hello')
		T (a) <- a [ \t]*
	)");

    bool ret = parser;
    REQUIRE(ret == false);
}

TEST(PegParser, T063_Macro_missing_argument)
{
    parser parser(R"(
		S       <- T ('hello')
		T(a, b) <- a [ \t]* b
	)");

    bool ret = parser;
    REQUIRE(ret == false);
}

TEST(PegParser, T064_Macro_reference_syntax_error)
{
    parser parser(R"(
		S    <- T ('hello')
		T(a) <- a [ \t]*
	)");

    bool ret = parser;
    REQUIRE(ret == false);
}

TEST(PegParser, T065_Macro_invalid_macro_reference_error)
{
    parser parser(R"(
		S <- T('hello')
		T <- 'world'
	)");

    bool ret = parser;
    REQUIRE(ret == false);
}

TEST(PegParser, T066_Macro_calculator)
{
	// Create a PEG parser
    parser parser(R"(
        # Grammar for simple calculator...
        EXPRESSION       <-  _ LIST(TERM, TERM_OPERATOR)
        TERM             <-  LIST(FACTOR, FACTOR_OPERATOR)
        FACTOR           <-  NUMBER / T('(') EXPRESSION T(')')
        TERM_OPERATOR    <-  T([-+])
        FACTOR_OPERATOR  <-  T([/*])
        NUMBER           <-  T([0-9]+)
		~_               <-  [ \t]*
		LIST(I, D)       <-  I (D I)*
		T(S)             <-  < S > _
	)");

	// Setup actions
    auto reduce = [](const SemanticValues& sv) -> long {
        auto result = sv[0].get<long>();
        for (auto i = 1u; i < sv.size(); i += 2) {
            auto num = sv[i + 1].get<long>();
            auto ope = sv[i].get<char>();
            switch (ope) {
                case '+': result += num; break;
                case '-': result -= num; break;
                case '*': result *= num; break;
                case '/': result /= num; break;
            }
        }
        return result;
    };

    parser["EXPRESSION"]      = reduce;
    parser["TERM"]            = reduce;
    parser["TERM_OPERATOR"]   = [](const SemanticValues& sv) { return static_cast<char>(*sv.c_str()); };
    parser["FACTOR_OPERATOR"] = [](const SemanticValues& sv) { return static_cast<char>(*sv.c_str()); };
    parser["NUMBER"]          = [](const SemanticValues& sv) { return atol(sv.c_str()); };

    bool ret = parser;
    REQUIRE(ret == true);

	auto expr = " 1 + 2 * 3 * (4 - 5 + 6) / 7 - 8 ";
    long val = 0;
    ret = parser.parse(expr, val);

    REQUIRE(ret == true);
    REQUIRE(val == -3);
}

TEST(PegParser, T067_Macro_expression_arguments)
{
    parser parser(R"(
		S             <- M('hello' / 'Hello', 'world' / 'World')
		M(arg0, arg1) <- arg0 [ \t]+ arg1
	)");

    REQUIRE(parser.parse("Hello world"));
}

TEST(PegParser, T068_Macro_recursive)
{
    parser parser(R"(
		S    <- M('abc')
		M(s) <- !s / s ' ' M(s / '123') / s
	)");

    REQUIRE(parser.parse(""));
    REQUIRE(parser.parse("abc"));
    REQUIRE(parser.parse("abc abc"));
    REQUIRE(parser.parse("abc 123 abc"));
}

TEST(PegParser, T069_Macro_recursive2)
{
	auto syntaxes = std::vector<const char*>{
		"S <- M('abc') M(s) <- !s / s ' ' M(s* '-' '123') / s",
		"S <- M('abc') M(s) <- !s / s ' ' M(s+ '-' '123') / s",
		"S <- M('abc') M(s) <- !s / s ' ' M(s? '-' '123') / s",
		"S <- M('abc') M(s) <- !s / s ' ' M(&s s+ '-' '123') / s",
		"S <- M('abc') M(s) <- !s / s ' ' M(s '-' !s '123') / s",
		"S <- M('abc') M(s) <- !s / s ' ' M(< s > '-' '123') / s",
		"S <- M('abc') M(s) <- !s / s ' ' M(~s '-' '123') / s",
	};

	for (const auto& syntax: syntaxes) {
        parser parser(syntax);
        REQUIRE(parser.parse("abc abc-123"));
	}
}

TEST(PegParser, T070_Macro_exclusive_modifiers)
{
    parser parser(R"(
		S                   <- Modifiers(!"") _
		Modifiers(Appeared) <- (!Appeared) (
								   Token('public') Modifiers(Appeared / 'public') /
								   Token('static') Modifiers(Appeared / 'static') /
								   Token('final') Modifiers(Appeared / 'final') /
								   "")
		Token(t)            <- t _
		_                   <- [ \t\r\n]*
	)");

	REQUIRE(parser.parse("public"));
	REQUIRE(parser.parse("static"));
	REQUIRE(parser.parse("final"));
	REQUIRE(parser.parse("public static final"));
	REQUIRE(!parser.parse("public public"));
	REQUIRE(!parser.parse("public static public"));
}

TEST(PegParser, T071_Macro_token_check_test)
{
    parser parser(R"(
        # Grammar for simple calculator...
        EXPRESSION       <-  _ LIST(TERM, TERM_OPERATOR)
        TERM             <-  LIST(FACTOR, FACTOR_OPERATOR)
        FACTOR           <-  NUMBER / T('(') EXPRESSION T(')')
        TERM_OPERATOR    <-  T([-+])
        FACTOR_OPERATOR  <-  T([/*])
        NUMBER           <-  T([0-9]+)
		~_               <-  [ \t]*
		LIST(I, D)       <-  I (D I)*
		T(S)             <-  < S > _
	)");

    REQUIRE(parser["EXPRESSION"].is_token() == false);
    REQUIRE(parser["TERM"].is_token() == false);
    REQUIRE(parser["FACTOR"].is_token() == false);
    REQUIRE(parser["FACTOR_OPERATOR"].is_token() == true);
    REQUIRE(parser["NUMBER"].is_token() == true);
    REQUIRE(parser["_"].is_token() == true);
    REQUIRE(parser["LIST"].is_token() == false);
    REQUIRE(parser["T"].is_token() == true);
}

TEST(PegParser, T072_Line_information_test)
{
    parser parser(R"(
        S    <- _ (WORD _)+
        WORD <- [A-Za-z]+
        ~_   <- [ \t\r\n]+
    )");

    std::vector<std::pair<int, int>> locations;
    parser["WORD"] = [&](const peg::SemanticValues& sv) {
        locations.push_back(sv.line_info());
    };

    bool ret = parser;
    REQUIRE(ret == true);

    ret = parser.parse(" Mon Tue Wed \nThu  Fri  Sat\nSun\n");
    REQUIRE(ret == true);

    REQUIRE(locations[0] == std::make_pair(1, 2));
    REQUIRE(locations[1] == std::make_pair(1, 6));
    REQUIRE(locations[2] == std::make_pair(1, 10));
    REQUIRE(locations[3] == std::make_pair(2, 1));
    REQUIRE(locations[4] == std::make_pair(2, 6));
    REQUIRE(locations[5] == std::make_pair(2, 11));
    REQUIRE(locations[6] == std::make_pair(3, 1));
}

bool exact(Grammar& g, const char* d, const char* s) {
    auto n = strlen(s);
    auto r = g[d].parse(s, n);
    return r.ret && r.len == n;
}

Grammar& make_peg_grammar() {
    return ParserGenerator::grammar();
}

TEST(PegParser, T073_PEG_Grammar)
{
    GlobalGrammarScope restore;
    auto g = ParserGenerator::grammar();
    REQUIRE(exact(g, "Grammar", " Definition <- a / ( b c ) / d \n rule2 <- [a-zA-Z][a-z0-9-]+ ") == true);
}

TEST(PegParser, T074_PEG_Definition)
{
    GlobalGrammarScope restore;
    auto g = ParserGenerator::grammar();
    REQUIRE(exact(g, "Definition", "Definition <- a / (b c) / d ") == true);
    REQUIRE(exact(g, "Definition", "Definition <- a / b c / d ") == true);
    REQUIRE(exact(g, "Definition", u8"Definitiond ← a ") == true);
    REQUIRE(exact(g, "Definition", "Definition ") == false);
    REQUIRE(exact(g, "Definition", " ") == false);
    REQUIRE(exact(g, "Definition", "") == false);
    REQUIRE(exact(g, "Definition", "Definition = a / (b c) / d ") == false);
	REQUIRE(exact(g, "Definition", "Macro(param) <- a ") == true);
	REQUIRE(exact(g, "Definition", "Macro (param) <- a ") == false);
}

TEST(PegParser, T075_PEG_Expression)
{
    GlobalGrammarScope restore;
    auto g = ParserGenerator::grammar();
    REQUIRE(exact(g, "Expression", "a / (b c) / d ") == true);
    REQUIRE(exact(g, "Expression", "a / b c / d ") == true);
    REQUIRE(exact(g, "Expression", "a b ") == true);
    REQUIRE(exact(g, "Expression", "") == true);
    REQUIRE(exact(g, "Expression", " ") == false);
    REQUIRE(exact(g, "Expression", " a b ") == false);
}

TEST(PegParser, T076_PEG_Sequence)
{
    GlobalGrammarScope restore;
    auto g = ParserGenerator::grammar();
    REQUIRE(exact(g, "Sequence", "a b c d ") == true);
    REQUIRE(exact(g, "Sequence", "") == true);
    REQUIRE(exact(g, "Sequence", "!") == false);
    REQUIRE(exact(g, "Sequence", "<-") == false);
    REQUIRE(exact(g, "Sequence", " a") == false);
}

TEST(PegParser, T077_PEG_Prefix)
{
    GlobalGrammarScope restore;
    auto g = ParserGenerator::grammar();
    REQUIRE(exact(g, "Prefix", "&[a]") == true);
    REQUIRE(exact(g, "Prefix", "![']") == true);
    REQUIRE(exact(g, "Prefix", "-[']") == false);
    REQUIRE(exact(g, "Prefix", "") == false);
    REQUIRE(exact(g, "Prefix", " a") == false);
}

TEST(PegParser, T078_PEG_Suffix)
{
    GlobalGrammarScope restore;
    auto g = ParserGenerator::grammar();
    REQUIRE(exact(g, "Suffix", "aaa ") == true);
    REQUIRE(exact(g, "Suffix", "aaa? ") == true);
    REQUIRE(exact(g, "Suffix", "aaa* ") == true);
    REQUIRE(exact(g, "Suffix", "aaa+ ") == true);
    REQUIRE(exact(g, "Suffix", ". + ") == true);
    REQUIRE(exact(g, "Suffix", "?") == false);
    REQUIRE(exact(g, "Suffix", "") == false);
    REQUIRE(exact(g, "Suffix", " a") == false);
}

TEST(PegParser, T079_PEG_Primary)
{
    GlobalGrammarScope restore;
    auto g = ParserGenerator::grammar();
    REQUIRE(exact(g, "Primary", "_Identifier0_ ") == true);
    REQUIRE(exact(g, "Primary", "_Identifier0_<-") == false);
    REQUIRE(exact(g, "Primary", "( _Identifier0_ _Identifier1_ )") == true);
    REQUIRE(exact(g, "Primary", "'Literal String'") == true);
    REQUIRE(exact(g, "Primary", "\"Literal String\"") == true);
    REQUIRE(exact(g, "Primary", "[a-zA-Z]") == true);
    REQUIRE(exact(g, "Primary", ".") == true);
    REQUIRE(exact(g, "Primary", "") == false);
    REQUIRE(exact(g, "Primary", " ") == false);
    REQUIRE(exact(g, "Primary", " a") == false);
    REQUIRE(exact(g, "Primary", "") == false);
}

TEST(PegParser, T080_PEG_Identifier)
{
    GlobalGrammarScope restore;
    auto g = ParserGenerator::grammar();
    REQUIRE(exact(g, "Identifier", "_Identifier0_ ") == true);
    REQUIRE(exact(g, "Identifier", "0Identifier_ ") == false);
    REQUIRE(exact(g, "Identifier", "Iden|t ") == false);
    REQUIRE(exact(g, "Identifier", " ") == false);
    REQUIRE(exact(g, "Identifier", " a") == false);
    REQUIRE(exact(g, "Identifier", "") == false);
}

TEST(PegParser, T081_PEG_IdentStart)
{
    GlobalGrammarScope restore;
    auto g = ParserGenerator::grammar();
    REQUIRE(exact(g, "IdentStart", "_") == true);
    REQUIRE(exact(g, "IdentStart", "a") == true);
    REQUIRE(exact(g, "IdentStart", "Z") == true);
    REQUIRE(exact(g, "IdentStart", "") == false);
    REQUIRE(exact(g, "IdentStart", " ") == false);
    REQUIRE(exact(g, "IdentStart", "0") == false);
}

TEST(PegParser, T082_PEG_IdentRest)
{
    GlobalGrammarScope restore;
    auto g = ParserGenerator::grammar();
    REQUIRE(exact(g, "IdentRest", "_") == true);
    REQUIRE(exact(g, "IdentRest", "a") == true);
    REQUIRE(exact(g, "IdentRest", "Z") == true);
    REQUIRE(exact(g, "IdentRest", "") == false);
    REQUIRE(exact(g, "IdentRest", " ") == false);
    REQUIRE(exact(g, "IdentRest", "0") == true);
}

TEST(PegParser, T083_PEG_Literal)
{
    GlobalGrammarScope restore;
    auto g = ParserGenerator::grammar();
    REQUIRE(exact(g, "Literal", "'abc' ") == true);
    REQUIRE(exact(g, "Literal", "'a\\nb\\tc' ") == true);
    REQUIRE(exact(g, "Literal", "'a\\277\tc' ") == true);
    REQUIRE(exact(g, "Literal", "'a\\77\tc' ") == true);
    REQUIRE(exact(g, "Literal", "'a\\80\tc' ") == false);
    REQUIRE(exact(g, "Literal", "'\n' ") == true);
    REQUIRE(exact(g, "Literal", "'a\\'b' ") == true);
    REQUIRE(exact(g, "Literal", "'a'b' ") == false);
    REQUIRE(exact(g, "Literal", "'a\"'b' ") == false);
    REQUIRE(exact(g, "Literal", "\"'\\\"abc\\\"'\" ") == true);
    REQUIRE(exact(g, "Literal", "\"'\"abc\"'\" ") == false);
    REQUIRE(exact(g, "Literal", "abc") == false);
    REQUIRE(exact(g, "Literal", "") == false);
    REQUIRE(exact(g, "Literal", u8"'日本語'") == true);
    REQUIRE(exact(g, "Literal", u8"\"日本語\"") == true);
    REQUIRE(exact(g, "Literal", u8"日本語") == false);
}

TEST(PegParser, T084_PEG_Class)
{
    GlobalGrammarScope restore;
    auto g = ParserGenerator::grammar();
    REQUIRE(exact(g, "Class", "[]") == true);
    REQUIRE(exact(g, "Class", "[a]") == true);
    REQUIRE(exact(g, "Class", "[a-z]") == true);
    REQUIRE(exact(g, "Class", "[az]") == true);
    REQUIRE(exact(g, "Class", "[a-zA-Z-]") == true);
    REQUIRE(exact(g, "Class", "[a-zA-Z-0-9]") == true);
    REQUIRE(exact(g, "Class", "[a-]") == false);
    REQUIRE(exact(g, "Class", "[-a]") == true);
    REQUIRE(exact(g, "Class", "[") == false);
    REQUIRE(exact(g, "Class", "[a") == false);
    REQUIRE(exact(g, "Class", "]") == false);
    REQUIRE(exact(g, "Class", "a]") == false);
    REQUIRE(exact(g, "Class", u8"[あ-ん]") == true);
    REQUIRE(exact(g, "Class", u8"あ-ん") == false);
    REQUIRE(exact(g, "Class", "[-+]") == true);
    REQUIRE(exact(g, "Class", "[+-]") == false);
}

TEST(PegParser, T085_PEG_Range)
{
    GlobalGrammarScope restore;
    auto g = ParserGenerator::grammar();
    REQUIRE(exact(g, "Range", "a") == true);
    REQUIRE(exact(g, "Range", "a-z") == true);
    REQUIRE(exact(g, "Range", "az") == false);
    REQUIRE(exact(g, "Range", "") == false);
    REQUIRE(exact(g, "Range", "a-") == false);
    REQUIRE(exact(g, "Range", "-a") == false);
}

TEST(PegParser, T086_PEG_Char)
{
    GlobalGrammarScope restore;
    auto g = ParserGenerator::grammar();
    REQUIRE(exact(g, "Char", "\\n") == true);
    REQUIRE(exact(g, "Char", "\\r") == true);
    REQUIRE(exact(g, "Char", "\\t") == true);
    REQUIRE(exact(g, "Char", "\\'") == true);
    REQUIRE(exact(g, "Char", "\\\"") == true);
    REQUIRE(exact(g, "Char", "\\[") == true);
    REQUIRE(exact(g, "Char", "\\]") == true);
    REQUIRE(exact(g, "Char", "\\\\") == true);
    REQUIRE(exact(g, "Char", "\\000") == true);
    REQUIRE(exact(g, "Char", "\\377") == true);
    REQUIRE(exact(g, "Char", "\\477") == false);
    REQUIRE(exact(g, "Char", "\\087") == false);
    REQUIRE(exact(g, "Char", "\\079") == false);
    REQUIRE(exact(g, "Char", "\\00") == true);
    REQUIRE(exact(g, "Char", "\\77") == true);
    REQUIRE(exact(g, "Char", "\\80") == false);
    REQUIRE(exact(g, "Char", "\\08") == false);
    REQUIRE(exact(g, "Char", "\\0") == true);
    REQUIRE(exact(g, "Char", "\\7") == true);
    REQUIRE(exact(g, "Char", "\\8") == false);
    REQUIRE(exact(g, "Char", "a") == true);
    REQUIRE(exact(g, "Char", ".") == true);
    REQUIRE(exact(g, "Char", "0") == true);
    REQUIRE(exact(g, "Char", "\\") == false);
    REQUIRE(exact(g, "Char", " ") == true);
    REQUIRE(exact(g, "Char", "  ") == false);
    REQUIRE(exact(g, "Char", "") == false);
    REQUIRE(exact(g, "Char", u8"あ") == true);
}

TEST(PegParser, T087_PEG_Operators)
{
    GlobalGrammarScope restore;
    auto g = ParserGenerator::grammar();
    REQUIRE(exact(g, "LEFTARROW", "<-") == true);
    REQUIRE(exact(g, "SLASH", "/ ") == true);
    REQUIRE(exact(g, "AND", "& ") == true);
    REQUIRE(exact(g, "NOT", "! ") == true);
    REQUIRE(exact(g, "QUESTION", "? ") == true);
    REQUIRE(exact(g, "STAR", "* ") == true);
    REQUIRE(exact(g, "PLUS", "+ ") == true);
    REQUIRE(exact(g, "OPEN", "( ") == true);
    REQUIRE(exact(g, "CLOSE", ") ") == true);
    REQUIRE(exact(g, "DOT", ". ") == true);
}

TEST(PegParser, T088_PEG_Comment)
{
    GlobalGrammarScope restore;
    auto g = ParserGenerator::grammar();
    REQUIRE(exact(g, "Comment", "# Comment.\n") == true);
    REQUIRE(exact(g, "Comment", "# Comment.") == false);
    REQUIRE(exact(g, "Comment", " ") == false);
    REQUIRE(exact(g, "Comment", "a") == false);
}

TEST(PegParser, T089_PEG_Space)
{
    GlobalGrammarScope restore;
    auto g = ParserGenerator::grammar();
    REQUIRE(exact(g, "Space", " ") == true);
    REQUIRE(exact(g, "Space", "\t") == true);
    REQUIRE(exact(g, "Space", "\n") == true);
    REQUIRE(exact(g, "Space", "") == false);
    REQUIRE(exact(g, "Space", "a") == false);
}

TEST(PegParser, T090_PEG_EndOfLine)
{
    GlobalGrammarScope restore;
    auto g = ParserGenerator::grammar();
    REQUIRE(exact(g, "EndOfLine", "\r\n") == true);
    REQUIRE(exact(g, "EndOfLine", "\n") == true);
    REQUIRE(exact(g, "EndOfLine", "\r") == true);
    REQUIRE(exact(g, "EndOfLine", " ") == false);
    REQUIRE(exact(g, "EndOfLine", "") == false);
    REQUIRE(exact(g, "EndOfLine", "a") == false);
}

TEST(PegParser, T091_PEG_EndOfFile)
{
    GlobalGrammarScope restore;
    Grammar g = make_peg_grammar();
    REQUIRE(exact(g, "EndOfFile", "") == true);
    REQUIRE(exact(g, "EndOfFile", " ") == false);
}

// vim: et ts=4 sw=4 cin cino={1s ff=unix

}  // namespace
