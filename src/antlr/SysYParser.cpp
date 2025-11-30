
// Generated from SysYParser.g4 by ANTLR 4.13.1


#include "SysYParserVisitor.h"

#include "SysYParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct SysYParserStaticData final {
  SysYParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  SysYParserStaticData(const SysYParserStaticData&) = delete;
  SysYParserStaticData(SysYParserStaticData&&) = delete;
  SysYParserStaticData& operator=(const SysYParserStaticData&) = delete;
  SysYParserStaticData& operator=(SysYParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag sysyparserParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
SysYParserStaticData *sysyparserParserStaticData = nullptr;

void sysyparserParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (sysyparserParserStaticData != nullptr) {
    return;
  }
#else
  assert(sysyparserParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<SysYParserStaticData>(
    std::vector<std::string>{
      "compUnit", "decl", "constDecl", "bType", "constDef", "constInitVal", 
      "varDecl", "varDef", "initVal", "funcDef", "funcType", "funcFParams", 
      "funcFParam", "arrayDim", "block", "blockItem", "stmt", "exp", "lVal", 
      "cond", "primaryExp", "number", "unaryExp", "unaryOp", "funcRParams", 
      "mulExp", "addExp", "relExp", "eqExp", "lAndExp", "lOrExp", "constExp"
    },
    std::vector<std::string>{
      "", "'const'", "'int'", "'void'", "'if'", "'else'", "'while'", "'break'", 
      "'continue'", "'return'", "'+'", "'-'", "'*'", "'/'", "'%'", "'='", 
      "'=='", "'!='", "'<'", "'>'", "'<='", "'>='", "'!'", "'&&'", "'||'", 
      "'('", "')'", "'{'", "'}'", "'['", "']'", "','", "';'"
    },
    std::vector<std::string>{
      "", "CONST", "INT", "VOID", "IF", "ELSE", "WHILE", "BREAK", "CONTINUE", 
      "RETURN", "PLUS", "MINUS", "MUL", "DIV", "MOD", "ASSIGN", "EQ", "NEQ", 
      "LT", "GT", "LE", "GE", "NOT", "AND", "OR", "L_PAREN", "R_PAREN", 
      "L_BRACE", "R_BRACE", "L_BRACKT", "R_BRACKT", "COMMA", "SEMICOLON", 
      "IDENT", "INTEGER_CONST", "WS", "LINE_COMMENT", "MULTILINE_COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,37,371,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,1,0,1,0,4,0,67,8,0,11,0,12,0,68,1,1,
  	1,1,3,1,73,8,1,1,2,1,2,1,2,1,2,1,2,5,2,80,8,2,10,2,12,2,83,9,2,1,2,1,
  	2,1,3,1,3,1,4,1,4,1,4,1,4,1,4,5,4,94,8,4,10,4,12,4,97,9,4,1,4,1,4,1,4,
  	1,5,1,5,1,5,1,5,1,5,5,5,107,8,5,10,5,12,5,110,9,5,3,5,112,8,5,1,5,3,5,
  	115,8,5,1,6,1,6,1,6,1,6,5,6,121,8,6,10,6,12,6,124,9,6,1,6,1,6,1,7,1,7,
  	1,7,1,7,1,7,5,7,133,8,7,10,7,12,7,136,9,7,1,7,1,7,1,7,1,7,1,7,5,7,143,
  	8,7,10,7,12,7,146,9,7,1,7,1,7,3,7,150,8,7,1,8,1,8,1,8,1,8,1,8,5,8,157,
  	8,8,10,8,12,8,160,9,8,3,8,162,8,8,1,8,3,8,165,8,8,1,9,1,9,1,9,1,9,3,9,
  	171,8,9,1,9,1,9,1,9,1,10,1,10,3,10,178,8,10,1,11,1,11,1,11,5,11,183,8,
  	11,10,11,12,11,186,9,11,1,12,1,12,1,12,3,12,191,8,12,1,13,1,13,1,13,1,
  	13,1,13,1,13,1,13,5,13,200,8,13,10,13,12,13,203,9,13,1,14,1,14,5,14,207,
  	8,14,10,14,12,14,210,9,14,1,14,1,14,1,15,1,15,3,15,216,8,15,1,16,1,16,
  	1,16,1,16,1,16,1,16,3,16,224,8,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,
  	1,16,1,16,3,16,235,8,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,
  	1,16,1,16,1,16,3,16,249,8,16,1,16,3,16,252,8,16,1,17,1,17,1,18,1,18,1,
  	18,1,18,1,18,5,18,261,8,18,10,18,12,18,264,9,18,1,19,1,19,1,20,1,20,1,
  	20,1,20,1,20,1,20,3,20,274,8,20,1,21,1,21,1,22,1,22,1,22,1,22,3,22,282,
  	8,22,1,22,1,22,1,22,1,22,3,22,288,8,22,1,23,1,23,1,23,3,23,293,8,23,1,
  	24,1,24,1,24,5,24,298,8,24,10,24,12,24,301,9,24,1,25,1,25,1,25,1,25,1,
  	25,1,25,5,25,309,8,25,10,25,12,25,312,9,25,1,26,1,26,1,26,1,26,1,26,1,
  	26,5,26,320,8,26,10,26,12,26,323,9,26,1,27,1,27,1,27,1,27,1,27,1,27,5,
  	27,331,8,27,10,27,12,27,334,9,27,1,28,1,28,1,28,1,28,1,28,1,28,5,28,342,
  	8,28,10,28,12,28,345,9,28,1,29,1,29,1,29,1,29,1,29,1,29,5,29,353,8,29,
  	10,29,12,29,356,9,29,1,30,1,30,1,30,1,30,1,30,1,30,5,30,364,8,30,10,30,
  	12,30,367,9,30,1,31,1,31,1,31,0,6,50,52,54,56,58,60,32,0,2,4,6,8,10,12,
  	14,16,18,20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,
  	60,62,0,4,1,0,12,14,1,0,10,11,1,0,18,21,1,0,16,17,385,0,66,1,0,0,0,2,
  	72,1,0,0,0,4,74,1,0,0,0,6,86,1,0,0,0,8,88,1,0,0,0,10,114,1,0,0,0,12,116,
  	1,0,0,0,14,149,1,0,0,0,16,164,1,0,0,0,18,166,1,0,0,0,20,177,1,0,0,0,22,
  	179,1,0,0,0,24,187,1,0,0,0,26,192,1,0,0,0,28,204,1,0,0,0,30,215,1,0,0,
  	0,32,251,1,0,0,0,34,253,1,0,0,0,36,255,1,0,0,0,38,265,1,0,0,0,40,273,
  	1,0,0,0,42,275,1,0,0,0,44,287,1,0,0,0,46,292,1,0,0,0,48,294,1,0,0,0,50,
  	302,1,0,0,0,52,313,1,0,0,0,54,324,1,0,0,0,56,335,1,0,0,0,58,346,1,0,0,
  	0,60,357,1,0,0,0,62,368,1,0,0,0,64,67,3,2,1,0,65,67,3,18,9,0,66,64,1,
  	0,0,0,66,65,1,0,0,0,67,68,1,0,0,0,68,66,1,0,0,0,68,69,1,0,0,0,69,1,1,
  	0,0,0,70,73,3,4,2,0,71,73,3,12,6,0,72,70,1,0,0,0,72,71,1,0,0,0,73,3,1,
  	0,0,0,74,75,5,1,0,0,75,76,3,6,3,0,76,81,3,8,4,0,77,78,5,31,0,0,78,80,
  	3,8,4,0,79,77,1,0,0,0,80,83,1,0,0,0,81,79,1,0,0,0,81,82,1,0,0,0,82,84,
  	1,0,0,0,83,81,1,0,0,0,84,85,5,32,0,0,85,5,1,0,0,0,86,87,5,2,0,0,87,7,
  	1,0,0,0,88,95,5,33,0,0,89,90,5,29,0,0,90,91,3,62,31,0,91,92,5,30,0,0,
  	92,94,1,0,0,0,93,89,1,0,0,0,94,97,1,0,0,0,95,93,1,0,0,0,95,96,1,0,0,0,
  	96,98,1,0,0,0,97,95,1,0,0,0,98,99,5,15,0,0,99,100,3,10,5,0,100,9,1,0,
  	0,0,101,115,3,62,31,0,102,111,5,27,0,0,103,108,3,10,5,0,104,105,5,31,
  	0,0,105,107,3,10,5,0,106,104,1,0,0,0,107,110,1,0,0,0,108,106,1,0,0,0,
  	108,109,1,0,0,0,109,112,1,0,0,0,110,108,1,0,0,0,111,103,1,0,0,0,111,112,
  	1,0,0,0,112,113,1,0,0,0,113,115,5,28,0,0,114,101,1,0,0,0,114,102,1,0,
  	0,0,115,11,1,0,0,0,116,117,3,6,3,0,117,122,3,14,7,0,118,119,5,31,0,0,
  	119,121,3,14,7,0,120,118,1,0,0,0,121,124,1,0,0,0,122,120,1,0,0,0,122,
  	123,1,0,0,0,123,125,1,0,0,0,124,122,1,0,0,0,125,126,5,32,0,0,126,13,1,
  	0,0,0,127,134,5,33,0,0,128,129,5,29,0,0,129,130,3,62,31,0,130,131,5,30,
  	0,0,131,133,1,0,0,0,132,128,1,0,0,0,133,136,1,0,0,0,134,132,1,0,0,0,134,
  	135,1,0,0,0,135,150,1,0,0,0,136,134,1,0,0,0,137,144,5,33,0,0,138,139,
  	5,29,0,0,139,140,3,62,31,0,140,141,5,30,0,0,141,143,1,0,0,0,142,138,1,
  	0,0,0,143,146,1,0,0,0,144,142,1,0,0,0,144,145,1,0,0,0,145,147,1,0,0,0,
  	146,144,1,0,0,0,147,148,5,15,0,0,148,150,3,16,8,0,149,127,1,0,0,0,149,
  	137,1,0,0,0,150,15,1,0,0,0,151,165,3,34,17,0,152,161,5,27,0,0,153,158,
  	3,16,8,0,154,155,5,31,0,0,155,157,3,16,8,0,156,154,1,0,0,0,157,160,1,
  	0,0,0,158,156,1,0,0,0,158,159,1,0,0,0,159,162,1,0,0,0,160,158,1,0,0,0,
  	161,153,1,0,0,0,161,162,1,0,0,0,162,163,1,0,0,0,163,165,5,28,0,0,164,
  	151,1,0,0,0,164,152,1,0,0,0,165,17,1,0,0,0,166,167,3,20,10,0,167,168,
  	5,33,0,0,168,170,5,25,0,0,169,171,3,22,11,0,170,169,1,0,0,0,170,171,1,
  	0,0,0,171,172,1,0,0,0,172,173,5,26,0,0,173,174,3,28,14,0,174,19,1,0,0,
  	0,175,178,5,3,0,0,176,178,5,2,0,0,177,175,1,0,0,0,177,176,1,0,0,0,178,
  	21,1,0,0,0,179,184,3,24,12,0,180,181,5,31,0,0,181,183,3,24,12,0,182,180,
  	1,0,0,0,183,186,1,0,0,0,184,182,1,0,0,0,184,185,1,0,0,0,185,23,1,0,0,
  	0,186,184,1,0,0,0,187,188,3,6,3,0,188,190,5,33,0,0,189,191,3,26,13,0,
  	190,189,1,0,0,0,190,191,1,0,0,0,191,25,1,0,0,0,192,193,5,29,0,0,193,194,
  	5,30,0,0,194,201,1,0,0,0,195,196,5,29,0,0,196,197,3,34,17,0,197,198,5,
  	30,0,0,198,200,1,0,0,0,199,195,1,0,0,0,200,203,1,0,0,0,201,199,1,0,0,
  	0,201,202,1,0,0,0,202,27,1,0,0,0,203,201,1,0,0,0,204,208,5,27,0,0,205,
  	207,3,30,15,0,206,205,1,0,0,0,207,210,1,0,0,0,208,206,1,0,0,0,208,209,
  	1,0,0,0,209,211,1,0,0,0,210,208,1,0,0,0,211,212,5,28,0,0,212,29,1,0,0,
  	0,213,216,3,2,1,0,214,216,3,32,16,0,215,213,1,0,0,0,215,214,1,0,0,0,216,
  	31,1,0,0,0,217,218,3,36,18,0,218,219,5,15,0,0,219,220,3,34,17,0,220,221,
  	5,32,0,0,221,252,1,0,0,0,222,224,3,34,17,0,223,222,1,0,0,0,223,224,1,
  	0,0,0,224,225,1,0,0,0,225,252,5,32,0,0,226,252,3,28,14,0,227,228,5,4,
  	0,0,228,229,5,25,0,0,229,230,3,38,19,0,230,231,5,26,0,0,231,234,3,32,
  	16,0,232,233,5,5,0,0,233,235,3,32,16,0,234,232,1,0,0,0,234,235,1,0,0,
  	0,235,252,1,0,0,0,236,237,5,6,0,0,237,238,5,25,0,0,238,239,3,38,19,0,
  	239,240,5,26,0,0,240,241,3,32,16,0,241,252,1,0,0,0,242,243,5,7,0,0,243,
  	252,5,32,0,0,244,245,5,8,0,0,245,252,5,32,0,0,246,248,5,9,0,0,247,249,
  	3,34,17,0,248,247,1,0,0,0,248,249,1,0,0,0,249,250,1,0,0,0,250,252,5,32,
  	0,0,251,217,1,0,0,0,251,223,1,0,0,0,251,226,1,0,0,0,251,227,1,0,0,0,251,
  	236,1,0,0,0,251,242,1,0,0,0,251,244,1,0,0,0,251,246,1,0,0,0,252,33,1,
  	0,0,0,253,254,3,52,26,0,254,35,1,0,0,0,255,262,5,33,0,0,256,257,5,29,
  	0,0,257,258,3,34,17,0,258,259,5,30,0,0,259,261,1,0,0,0,260,256,1,0,0,
  	0,261,264,1,0,0,0,262,260,1,0,0,0,262,263,1,0,0,0,263,37,1,0,0,0,264,
  	262,1,0,0,0,265,266,3,60,30,0,266,39,1,0,0,0,267,268,5,25,0,0,268,269,
  	3,34,17,0,269,270,5,26,0,0,270,274,1,0,0,0,271,274,3,36,18,0,272,274,
  	3,42,21,0,273,267,1,0,0,0,273,271,1,0,0,0,273,272,1,0,0,0,274,41,1,0,
  	0,0,275,276,5,34,0,0,276,43,1,0,0,0,277,288,3,40,20,0,278,279,5,33,0,
  	0,279,281,5,25,0,0,280,282,3,48,24,0,281,280,1,0,0,0,281,282,1,0,0,0,
  	282,283,1,0,0,0,283,288,5,26,0,0,284,285,3,46,23,0,285,286,3,44,22,0,
  	286,288,1,0,0,0,287,277,1,0,0,0,287,278,1,0,0,0,287,284,1,0,0,0,288,45,
  	1,0,0,0,289,293,5,10,0,0,290,293,5,11,0,0,291,293,5,22,0,0,292,289,1,
  	0,0,0,292,290,1,0,0,0,292,291,1,0,0,0,293,47,1,0,0,0,294,299,3,34,17,
  	0,295,296,5,31,0,0,296,298,3,34,17,0,297,295,1,0,0,0,298,301,1,0,0,0,
  	299,297,1,0,0,0,299,300,1,0,0,0,300,49,1,0,0,0,301,299,1,0,0,0,302,303,
  	6,25,-1,0,303,304,3,44,22,0,304,310,1,0,0,0,305,306,10,1,0,0,306,307,
  	7,0,0,0,307,309,3,44,22,0,308,305,1,0,0,0,309,312,1,0,0,0,310,308,1,0,
  	0,0,310,311,1,0,0,0,311,51,1,0,0,0,312,310,1,0,0,0,313,314,6,26,-1,0,
  	314,315,3,50,25,0,315,321,1,0,0,0,316,317,10,1,0,0,317,318,7,1,0,0,318,
  	320,3,50,25,0,319,316,1,0,0,0,320,323,1,0,0,0,321,319,1,0,0,0,321,322,
  	1,0,0,0,322,53,1,0,0,0,323,321,1,0,0,0,324,325,6,27,-1,0,325,326,3,52,
  	26,0,326,332,1,0,0,0,327,328,10,1,0,0,328,329,7,2,0,0,329,331,3,52,26,
  	0,330,327,1,0,0,0,331,334,1,0,0,0,332,330,1,0,0,0,332,333,1,0,0,0,333,
  	55,1,0,0,0,334,332,1,0,0,0,335,336,6,28,-1,0,336,337,3,54,27,0,337,343,
  	1,0,0,0,338,339,10,1,0,0,339,340,7,3,0,0,340,342,3,54,27,0,341,338,1,
  	0,0,0,342,345,1,0,0,0,343,341,1,0,0,0,343,344,1,0,0,0,344,57,1,0,0,0,
  	345,343,1,0,0,0,346,347,6,29,-1,0,347,348,3,56,28,0,348,354,1,0,0,0,349,
  	350,10,1,0,0,350,351,5,23,0,0,351,353,3,56,28,0,352,349,1,0,0,0,353,356,
  	1,0,0,0,354,352,1,0,0,0,354,355,1,0,0,0,355,59,1,0,0,0,356,354,1,0,0,
  	0,357,358,6,30,-1,0,358,359,3,58,29,0,359,365,1,0,0,0,360,361,10,1,0,
  	0,361,362,5,24,0,0,362,364,3,58,29,0,363,360,1,0,0,0,364,367,1,0,0,0,
  	365,363,1,0,0,0,365,366,1,0,0,0,366,61,1,0,0,0,367,365,1,0,0,0,368,369,
  	3,52,26,0,369,63,1,0,0,0,38,66,68,72,81,95,108,111,114,122,134,144,149,
  	158,161,164,170,177,184,190,201,208,215,223,234,248,251,262,273,281,287,
  	292,299,310,321,332,343,354,365
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  sysyparserParserStaticData = staticData.release();
}

}

SysYParser::SysYParser(TokenStream *input) : SysYParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

SysYParser::SysYParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  SysYParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *sysyparserParserStaticData->atn, sysyparserParserStaticData->decisionToDFA, sysyparserParserStaticData->sharedContextCache, options);
}

SysYParser::~SysYParser() {
  delete _interpreter;
}

const atn::ATN& SysYParser::getATN() const {
  return *sysyparserParserStaticData->atn;
}

std::string SysYParser::getGrammarFileName() const {
  return "SysYParser.g4";
}

const std::vector<std::string>& SysYParser::getRuleNames() const {
  return sysyparserParserStaticData->ruleNames;
}

const dfa::Vocabulary& SysYParser::getVocabulary() const {
  return sysyparserParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView SysYParser::getSerializedATN() const {
  return sysyparserParserStaticData->serializedATN;
}


//----------------- CompUnitContext ------------------------------------------------------------------

SysYParser::CompUnitContext::CompUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SysYParser::DeclContext *> SysYParser::CompUnitContext::decl() {
  return getRuleContexts<SysYParser::DeclContext>();
}

SysYParser::DeclContext* SysYParser::CompUnitContext::decl(size_t i) {
  return getRuleContext<SysYParser::DeclContext>(i);
}

std::vector<SysYParser::FuncDefContext *> SysYParser::CompUnitContext::funcDef() {
  return getRuleContexts<SysYParser::FuncDefContext>();
}

SysYParser::FuncDefContext* SysYParser::CompUnitContext::funcDef(size_t i) {
  return getRuleContext<SysYParser::FuncDefContext>(i);
}


size_t SysYParser::CompUnitContext::getRuleIndex() const {
  return SysYParser::RuleCompUnit;
}


std::any SysYParser::CompUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitCompUnit(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::CompUnitContext* SysYParser::compUnit() {
  CompUnitContext *_localctx = _tracker.createInstance<CompUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, SysYParser::RuleCompUnit);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(66); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(66);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(64);
        decl();
        break;
      }

      case 2: {
        setState(65);
        funcDef();
        break;
      }

      default:
        break;
      }
      setState(68); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 14) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclContext ------------------------------------------------------------------

SysYParser::DeclContext::DeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::ConstDeclContext* SysYParser::DeclContext::constDecl() {
  return getRuleContext<SysYParser::ConstDeclContext>(0);
}

SysYParser::VarDeclContext* SysYParser::DeclContext::varDecl() {
  return getRuleContext<SysYParser::VarDeclContext>(0);
}


size_t SysYParser::DeclContext::getRuleIndex() const {
  return SysYParser::RuleDecl;
}


std::any SysYParser::DeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitDecl(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::DeclContext* SysYParser::decl() {
  DeclContext *_localctx = _tracker.createInstance<DeclContext>(_ctx, getState());
  enterRule(_localctx, 2, SysYParser::RuleDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(72);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SysYParser::CONST: {
        enterOuterAlt(_localctx, 1);
        setState(70);
        constDecl();
        break;
      }

      case SysYParser::INT: {
        enterOuterAlt(_localctx, 2);
        setState(71);
        varDecl();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstDeclContext ------------------------------------------------------------------

SysYParser::ConstDeclContext::ConstDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::ConstDeclContext::getRuleIndex() const {
  return SysYParser::RuleConstDecl;
}

void SysYParser::ConstDeclContext::copyFrom(ConstDeclContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ConstDeclDefContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::ConstDeclDefContext::CONST() {
  return getToken(SysYParser::CONST, 0);
}

SysYParser::BTypeContext* SysYParser::ConstDeclDefContext::bType() {
  return getRuleContext<SysYParser::BTypeContext>(0);
}

std::vector<SysYParser::ConstDefContext *> SysYParser::ConstDeclDefContext::constDef() {
  return getRuleContexts<SysYParser::ConstDefContext>();
}

SysYParser::ConstDefContext* SysYParser::ConstDeclDefContext::constDef(size_t i) {
  return getRuleContext<SysYParser::ConstDefContext>(i);
}

tree::TerminalNode* SysYParser::ConstDeclDefContext::SEMICOLON() {
  return getToken(SysYParser::SEMICOLON, 0);
}

std::vector<tree::TerminalNode *> SysYParser::ConstDeclDefContext::COMMA() {
  return getTokens(SysYParser::COMMA);
}

tree::TerminalNode* SysYParser::ConstDeclDefContext::COMMA(size_t i) {
  return getToken(SysYParser::COMMA, i);
}

SysYParser::ConstDeclDefContext::ConstDeclDefContext(ConstDeclContext *ctx) { copyFrom(ctx); }


std::any SysYParser::ConstDeclDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitConstDeclDef(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::ConstDeclContext* SysYParser::constDecl() {
  ConstDeclContext *_localctx = _tracker.createInstance<ConstDeclContext>(_ctx, getState());
  enterRule(_localctx, 4, SysYParser::RuleConstDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    _localctx = _tracker.createInstance<SysYParser::ConstDeclDefContext>(_localctx);
    enterOuterAlt(_localctx, 1);
    setState(74);
    match(SysYParser::CONST);
    setState(75);
    bType();
    setState(76);
    constDef();
    setState(81);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::COMMA) {
      setState(77);
      match(SysYParser::COMMA);
      setState(78);
      constDef();
      setState(83);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(84);
    match(SysYParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BTypeContext ------------------------------------------------------------------

SysYParser::BTypeContext::BTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::BTypeContext::getRuleIndex() const {
  return SysYParser::RuleBType;
}

void SysYParser::BTypeContext::copyFrom(BTypeContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- IntTypeContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::IntTypeContext::INT() {
  return getToken(SysYParser::INT, 0);
}

SysYParser::IntTypeContext::IntTypeContext(BTypeContext *ctx) { copyFrom(ctx); }


std::any SysYParser::IntTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitIntType(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::BTypeContext* SysYParser::bType() {
  BTypeContext *_localctx = _tracker.createInstance<BTypeContext>(_ctx, getState());
  enterRule(_localctx, 6, SysYParser::RuleBType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    _localctx = _tracker.createInstance<SysYParser::IntTypeContext>(_localctx);
    enterOuterAlt(_localctx, 1);
    setState(86);
    match(SysYParser::INT);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstDefContext ------------------------------------------------------------------

SysYParser::ConstDefContext::ConstDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SysYParser::ConstDefContext::IDENT() {
  return getToken(SysYParser::IDENT, 0);
}

tree::TerminalNode* SysYParser::ConstDefContext::ASSIGN() {
  return getToken(SysYParser::ASSIGN, 0);
}

SysYParser::ConstInitValContext* SysYParser::ConstDefContext::constInitVal() {
  return getRuleContext<SysYParser::ConstInitValContext>(0);
}

std::vector<tree::TerminalNode *> SysYParser::ConstDefContext::L_BRACKT() {
  return getTokens(SysYParser::L_BRACKT);
}

tree::TerminalNode* SysYParser::ConstDefContext::L_BRACKT(size_t i) {
  return getToken(SysYParser::L_BRACKT, i);
}

std::vector<SysYParser::ConstExpContext *> SysYParser::ConstDefContext::constExp() {
  return getRuleContexts<SysYParser::ConstExpContext>();
}

SysYParser::ConstExpContext* SysYParser::ConstDefContext::constExp(size_t i) {
  return getRuleContext<SysYParser::ConstExpContext>(i);
}

std::vector<tree::TerminalNode *> SysYParser::ConstDefContext::R_BRACKT() {
  return getTokens(SysYParser::R_BRACKT);
}

tree::TerminalNode* SysYParser::ConstDefContext::R_BRACKT(size_t i) {
  return getToken(SysYParser::R_BRACKT, i);
}


size_t SysYParser::ConstDefContext::getRuleIndex() const {
  return SysYParser::RuleConstDef;
}


std::any SysYParser::ConstDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitConstDef(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::ConstDefContext* SysYParser::constDef() {
  ConstDefContext *_localctx = _tracker.createInstance<ConstDefContext>(_ctx, getState());
  enterRule(_localctx, 8, SysYParser::RuleConstDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(88);
    match(SysYParser::IDENT);
    setState(95);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::L_BRACKT) {
      setState(89);
      match(SysYParser::L_BRACKT);
      setState(90);
      constExp();
      setState(91);
      match(SysYParser::R_BRACKT);
      setState(97);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(98);
    match(SysYParser::ASSIGN);
    setState(99);
    constInitVal();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstInitValContext ------------------------------------------------------------------

SysYParser::ConstInitValContext::ConstInitValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::ConstInitValContext::getRuleIndex() const {
  return SysYParser::RuleConstInitVal;
}

void SysYParser::ConstInitValContext::copyFrom(ConstInitValContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ConstArrayInitValContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::ConstArrayInitValContext::L_BRACE() {
  return getToken(SysYParser::L_BRACE, 0);
}

tree::TerminalNode* SysYParser::ConstArrayInitValContext::R_BRACE() {
  return getToken(SysYParser::R_BRACE, 0);
}

std::vector<SysYParser::ConstInitValContext *> SysYParser::ConstArrayInitValContext::constInitVal() {
  return getRuleContexts<SysYParser::ConstInitValContext>();
}

SysYParser::ConstInitValContext* SysYParser::ConstArrayInitValContext::constInitVal(size_t i) {
  return getRuleContext<SysYParser::ConstInitValContext>(i);
}

std::vector<tree::TerminalNode *> SysYParser::ConstArrayInitValContext::COMMA() {
  return getTokens(SysYParser::COMMA);
}

tree::TerminalNode* SysYParser::ConstArrayInitValContext::COMMA(size_t i) {
  return getToken(SysYParser::COMMA, i);
}

SysYParser::ConstArrayInitValContext::ConstArrayInitValContext(ConstInitValContext *ctx) { copyFrom(ctx); }


std::any SysYParser::ConstArrayInitValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitConstArrayInitVal(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ConstExpInitValContext ------------------------------------------------------------------

SysYParser::ConstExpContext* SysYParser::ConstExpInitValContext::constExp() {
  return getRuleContext<SysYParser::ConstExpContext>(0);
}

SysYParser::ConstExpInitValContext::ConstExpInitValContext(ConstInitValContext *ctx) { copyFrom(ctx); }


std::any SysYParser::ConstExpInitValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitConstExpInitVal(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::ConstInitValContext* SysYParser::constInitVal() {
  ConstInitValContext *_localctx = _tracker.createInstance<ConstInitValContext>(_ctx, getState());
  enterRule(_localctx, 10, SysYParser::RuleConstInitVal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(114);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SysYParser::PLUS:
      case SysYParser::MINUS:
      case SysYParser::NOT:
      case SysYParser::L_PAREN:
      case SysYParser::IDENT:
      case SysYParser::INTEGER_CONST: {
        _localctx = _tracker.createInstance<SysYParser::ConstExpInitValContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(101);
        constExp();
        break;
      }

      case SysYParser::L_BRACE: {
        _localctx = _tracker.createInstance<SysYParser::ConstArrayInitValContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(102);
        match(SysYParser::L_BRACE);
        setState(111);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 25941773312) != 0)) {
          setState(103);
          constInitVal();
          setState(108);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == SysYParser::COMMA) {
            setState(104);
            match(SysYParser::COMMA);
            setState(105);
            constInitVal();
            setState(110);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(113);
        match(SysYParser::R_BRACE);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDeclContext ------------------------------------------------------------------

SysYParser::VarDeclContext::VarDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::VarDeclContext::getRuleIndex() const {
  return SysYParser::RuleVarDecl;
}

void SysYParser::VarDeclContext::copyFrom(VarDeclContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- VarDeclDefContext ------------------------------------------------------------------

SysYParser::BTypeContext* SysYParser::VarDeclDefContext::bType() {
  return getRuleContext<SysYParser::BTypeContext>(0);
}

std::vector<SysYParser::VarDefContext *> SysYParser::VarDeclDefContext::varDef() {
  return getRuleContexts<SysYParser::VarDefContext>();
}

SysYParser::VarDefContext* SysYParser::VarDeclDefContext::varDef(size_t i) {
  return getRuleContext<SysYParser::VarDefContext>(i);
}

tree::TerminalNode* SysYParser::VarDeclDefContext::SEMICOLON() {
  return getToken(SysYParser::SEMICOLON, 0);
}

std::vector<tree::TerminalNode *> SysYParser::VarDeclDefContext::COMMA() {
  return getTokens(SysYParser::COMMA);
}

tree::TerminalNode* SysYParser::VarDeclDefContext::COMMA(size_t i) {
  return getToken(SysYParser::COMMA, i);
}

SysYParser::VarDeclDefContext::VarDeclDefContext(VarDeclContext *ctx) { copyFrom(ctx); }


std::any SysYParser::VarDeclDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitVarDeclDef(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::VarDeclContext* SysYParser::varDecl() {
  VarDeclContext *_localctx = _tracker.createInstance<VarDeclContext>(_ctx, getState());
  enterRule(_localctx, 12, SysYParser::RuleVarDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    _localctx = _tracker.createInstance<SysYParser::VarDeclDefContext>(_localctx);
    enterOuterAlt(_localctx, 1);
    setState(116);
    bType();
    setState(117);
    varDef();
    setState(122);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::COMMA) {
      setState(118);
      match(SysYParser::COMMA);
      setState(119);
      varDef();
      setState(124);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(125);
    match(SysYParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDefContext ------------------------------------------------------------------

SysYParser::VarDefContext::VarDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::VarDefContext::getRuleIndex() const {
  return SysYParser::RuleVarDef;
}

void SysYParser::VarDefContext::copyFrom(VarDefContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- VarDefWithInitContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::VarDefWithInitContext::IDENT() {
  return getToken(SysYParser::IDENT, 0);
}

tree::TerminalNode* SysYParser::VarDefWithInitContext::ASSIGN() {
  return getToken(SysYParser::ASSIGN, 0);
}

SysYParser::InitValContext* SysYParser::VarDefWithInitContext::initVal() {
  return getRuleContext<SysYParser::InitValContext>(0);
}

std::vector<tree::TerminalNode *> SysYParser::VarDefWithInitContext::L_BRACKT() {
  return getTokens(SysYParser::L_BRACKT);
}

tree::TerminalNode* SysYParser::VarDefWithInitContext::L_BRACKT(size_t i) {
  return getToken(SysYParser::L_BRACKT, i);
}

std::vector<SysYParser::ConstExpContext *> SysYParser::VarDefWithInitContext::constExp() {
  return getRuleContexts<SysYParser::ConstExpContext>();
}

SysYParser::ConstExpContext* SysYParser::VarDefWithInitContext::constExp(size_t i) {
  return getRuleContext<SysYParser::ConstExpContext>(i);
}

std::vector<tree::TerminalNode *> SysYParser::VarDefWithInitContext::R_BRACKT() {
  return getTokens(SysYParser::R_BRACKT);
}

tree::TerminalNode* SysYParser::VarDefWithInitContext::R_BRACKT(size_t i) {
  return getToken(SysYParser::R_BRACKT, i);
}

SysYParser::VarDefWithInitContext::VarDefWithInitContext(VarDefContext *ctx) { copyFrom(ctx); }


std::any SysYParser::VarDefWithInitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitVarDefWithInit(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VarDefNoInitContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::VarDefNoInitContext::IDENT() {
  return getToken(SysYParser::IDENT, 0);
}

std::vector<tree::TerminalNode *> SysYParser::VarDefNoInitContext::L_BRACKT() {
  return getTokens(SysYParser::L_BRACKT);
}

tree::TerminalNode* SysYParser::VarDefNoInitContext::L_BRACKT(size_t i) {
  return getToken(SysYParser::L_BRACKT, i);
}

std::vector<SysYParser::ConstExpContext *> SysYParser::VarDefNoInitContext::constExp() {
  return getRuleContexts<SysYParser::ConstExpContext>();
}

SysYParser::ConstExpContext* SysYParser::VarDefNoInitContext::constExp(size_t i) {
  return getRuleContext<SysYParser::ConstExpContext>(i);
}

std::vector<tree::TerminalNode *> SysYParser::VarDefNoInitContext::R_BRACKT() {
  return getTokens(SysYParser::R_BRACKT);
}

tree::TerminalNode* SysYParser::VarDefNoInitContext::R_BRACKT(size_t i) {
  return getToken(SysYParser::R_BRACKT, i);
}

SysYParser::VarDefNoInitContext::VarDefNoInitContext(VarDefContext *ctx) { copyFrom(ctx); }


std::any SysYParser::VarDefNoInitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitVarDefNoInit(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::VarDefContext* SysYParser::varDef() {
  VarDefContext *_localctx = _tracker.createInstance<VarDefContext>(_ctx, getState());
  enterRule(_localctx, 14, SysYParser::RuleVarDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(149);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<SysYParser::VarDefNoInitContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(127);
      match(SysYParser::IDENT);
      setState(134);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == SysYParser::L_BRACKT) {
        setState(128);
        match(SysYParser::L_BRACKT);
        setState(129);
        constExp();
        setState(130);
        match(SysYParser::R_BRACKT);
        setState(136);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<SysYParser::VarDefWithInitContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(137);
      match(SysYParser::IDENT);
      setState(144);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == SysYParser::L_BRACKT) {
        setState(138);
        match(SysYParser::L_BRACKT);
        setState(139);
        constExp();
        setState(140);
        match(SysYParser::R_BRACKT);
        setState(146);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(147);
      match(SysYParser::ASSIGN);
      setState(148);
      initVal();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InitValContext ------------------------------------------------------------------

SysYParser::InitValContext::InitValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::InitValContext::getRuleIndex() const {
  return SysYParser::RuleInitVal;
}

void SysYParser::InitValContext::copyFrom(InitValContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ArrayInitValContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::ArrayInitValContext::L_BRACE() {
  return getToken(SysYParser::L_BRACE, 0);
}

tree::TerminalNode* SysYParser::ArrayInitValContext::R_BRACE() {
  return getToken(SysYParser::R_BRACE, 0);
}

std::vector<SysYParser::InitValContext *> SysYParser::ArrayInitValContext::initVal() {
  return getRuleContexts<SysYParser::InitValContext>();
}

SysYParser::InitValContext* SysYParser::ArrayInitValContext::initVal(size_t i) {
  return getRuleContext<SysYParser::InitValContext>(i);
}

std::vector<tree::TerminalNode *> SysYParser::ArrayInitValContext::COMMA() {
  return getTokens(SysYParser::COMMA);
}

tree::TerminalNode* SysYParser::ArrayInitValContext::COMMA(size_t i) {
  return getToken(SysYParser::COMMA, i);
}

SysYParser::ArrayInitValContext::ArrayInitValContext(InitValContext *ctx) { copyFrom(ctx); }


std::any SysYParser::ArrayInitValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitArrayInitVal(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExpInitValContext ------------------------------------------------------------------

SysYParser::ExpContext* SysYParser::ExpInitValContext::exp() {
  return getRuleContext<SysYParser::ExpContext>(0);
}

SysYParser::ExpInitValContext::ExpInitValContext(InitValContext *ctx) { copyFrom(ctx); }


std::any SysYParser::ExpInitValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitExpInitVal(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::InitValContext* SysYParser::initVal() {
  InitValContext *_localctx = _tracker.createInstance<InitValContext>(_ctx, getState());
  enterRule(_localctx, 16, SysYParser::RuleInitVal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(164);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SysYParser::PLUS:
      case SysYParser::MINUS:
      case SysYParser::NOT:
      case SysYParser::L_PAREN:
      case SysYParser::IDENT:
      case SysYParser::INTEGER_CONST: {
        _localctx = _tracker.createInstance<SysYParser::ExpInitValContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(151);
        exp();
        break;
      }

      case SysYParser::L_BRACE: {
        _localctx = _tracker.createInstance<SysYParser::ArrayInitValContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(152);
        match(SysYParser::L_BRACE);
        setState(161);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 25941773312) != 0)) {
          setState(153);
          initVal();
          setState(158);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == SysYParser::COMMA) {
            setState(154);
            match(SysYParser::COMMA);
            setState(155);
            initVal();
            setState(160);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(163);
        match(SysYParser::R_BRACE);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncDefContext ------------------------------------------------------------------

SysYParser::FuncDefContext::FuncDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::FuncTypeContext* SysYParser::FuncDefContext::funcType() {
  return getRuleContext<SysYParser::FuncTypeContext>(0);
}

tree::TerminalNode* SysYParser::FuncDefContext::IDENT() {
  return getToken(SysYParser::IDENT, 0);
}

tree::TerminalNode* SysYParser::FuncDefContext::L_PAREN() {
  return getToken(SysYParser::L_PAREN, 0);
}

tree::TerminalNode* SysYParser::FuncDefContext::R_PAREN() {
  return getToken(SysYParser::R_PAREN, 0);
}

SysYParser::BlockContext* SysYParser::FuncDefContext::block() {
  return getRuleContext<SysYParser::BlockContext>(0);
}

SysYParser::FuncFParamsContext* SysYParser::FuncDefContext::funcFParams() {
  return getRuleContext<SysYParser::FuncFParamsContext>(0);
}


size_t SysYParser::FuncDefContext::getRuleIndex() const {
  return SysYParser::RuleFuncDef;
}


std::any SysYParser::FuncDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitFuncDef(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::FuncDefContext* SysYParser::funcDef() {
  FuncDefContext *_localctx = _tracker.createInstance<FuncDefContext>(_ctx, getState());
  enterRule(_localctx, 18, SysYParser::RuleFuncDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(166);
    funcType();
    setState(167);
    match(SysYParser::IDENT);
    setState(168);
    match(SysYParser::L_PAREN);
    setState(170);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SysYParser::INT) {
      setState(169);
      funcFParams();
    }
    setState(172);
    match(SysYParser::R_PAREN);
    setState(173);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncTypeContext ------------------------------------------------------------------

SysYParser::FuncTypeContext::FuncTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::FuncTypeContext::getRuleIndex() const {
  return SysYParser::RuleFuncType;
}

void SysYParser::FuncTypeContext::copyFrom(FuncTypeContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- IntFuncTypeContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::IntFuncTypeContext::INT() {
  return getToken(SysYParser::INT, 0);
}

SysYParser::IntFuncTypeContext::IntFuncTypeContext(FuncTypeContext *ctx) { copyFrom(ctx); }


std::any SysYParser::IntFuncTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitIntFuncType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VoidFuncTypeContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::VoidFuncTypeContext::VOID() {
  return getToken(SysYParser::VOID, 0);
}

SysYParser::VoidFuncTypeContext::VoidFuncTypeContext(FuncTypeContext *ctx) { copyFrom(ctx); }


std::any SysYParser::VoidFuncTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitVoidFuncType(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::FuncTypeContext* SysYParser::funcType() {
  FuncTypeContext *_localctx = _tracker.createInstance<FuncTypeContext>(_ctx, getState());
  enterRule(_localctx, 20, SysYParser::RuleFuncType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(177);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SysYParser::VOID: {
        _localctx = _tracker.createInstance<SysYParser::VoidFuncTypeContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(175);
        match(SysYParser::VOID);
        break;
      }

      case SysYParser::INT: {
        _localctx = _tracker.createInstance<SysYParser::IntFuncTypeContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(176);
        match(SysYParser::INT);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncFParamsContext ------------------------------------------------------------------

SysYParser::FuncFParamsContext::FuncFParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SysYParser::FuncFParamContext *> SysYParser::FuncFParamsContext::funcFParam() {
  return getRuleContexts<SysYParser::FuncFParamContext>();
}

SysYParser::FuncFParamContext* SysYParser::FuncFParamsContext::funcFParam(size_t i) {
  return getRuleContext<SysYParser::FuncFParamContext>(i);
}

std::vector<tree::TerminalNode *> SysYParser::FuncFParamsContext::COMMA() {
  return getTokens(SysYParser::COMMA);
}

tree::TerminalNode* SysYParser::FuncFParamsContext::COMMA(size_t i) {
  return getToken(SysYParser::COMMA, i);
}


size_t SysYParser::FuncFParamsContext::getRuleIndex() const {
  return SysYParser::RuleFuncFParams;
}


std::any SysYParser::FuncFParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitFuncFParams(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::FuncFParamsContext* SysYParser::funcFParams() {
  FuncFParamsContext *_localctx = _tracker.createInstance<FuncFParamsContext>(_ctx, getState());
  enterRule(_localctx, 22, SysYParser::RuleFuncFParams);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(179);
    funcFParam();
    setState(184);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::COMMA) {
      setState(180);
      match(SysYParser::COMMA);
      setState(181);
      funcFParam();
      setState(186);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncFParamContext ------------------------------------------------------------------

SysYParser::FuncFParamContext::FuncFParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::BTypeContext* SysYParser::FuncFParamContext::bType() {
  return getRuleContext<SysYParser::BTypeContext>(0);
}

tree::TerminalNode* SysYParser::FuncFParamContext::IDENT() {
  return getToken(SysYParser::IDENT, 0);
}

SysYParser::ArrayDimContext* SysYParser::FuncFParamContext::arrayDim() {
  return getRuleContext<SysYParser::ArrayDimContext>(0);
}


size_t SysYParser::FuncFParamContext::getRuleIndex() const {
  return SysYParser::RuleFuncFParam;
}


std::any SysYParser::FuncFParamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitFuncFParam(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::FuncFParamContext* SysYParser::funcFParam() {
  FuncFParamContext *_localctx = _tracker.createInstance<FuncFParamContext>(_ctx, getState());
  enterRule(_localctx, 24, SysYParser::RuleFuncFParam);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(187);
    bType();
    setState(188);
    match(SysYParser::IDENT);
    setState(190);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == SysYParser::L_BRACKT) {
      setState(189);
      arrayDim();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayDimContext ------------------------------------------------------------------

SysYParser::ArrayDimContext::ArrayDimContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> SysYParser::ArrayDimContext::L_BRACKT() {
  return getTokens(SysYParser::L_BRACKT);
}

tree::TerminalNode* SysYParser::ArrayDimContext::L_BRACKT(size_t i) {
  return getToken(SysYParser::L_BRACKT, i);
}

std::vector<tree::TerminalNode *> SysYParser::ArrayDimContext::R_BRACKT() {
  return getTokens(SysYParser::R_BRACKT);
}

tree::TerminalNode* SysYParser::ArrayDimContext::R_BRACKT(size_t i) {
  return getToken(SysYParser::R_BRACKT, i);
}

std::vector<SysYParser::ExpContext *> SysYParser::ArrayDimContext::exp() {
  return getRuleContexts<SysYParser::ExpContext>();
}

SysYParser::ExpContext* SysYParser::ArrayDimContext::exp(size_t i) {
  return getRuleContext<SysYParser::ExpContext>(i);
}


size_t SysYParser::ArrayDimContext::getRuleIndex() const {
  return SysYParser::RuleArrayDim;
}


std::any SysYParser::ArrayDimContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitArrayDim(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::ArrayDimContext* SysYParser::arrayDim() {
  ArrayDimContext *_localctx = _tracker.createInstance<ArrayDimContext>(_ctx, getState());
  enterRule(_localctx, 26, SysYParser::RuleArrayDim);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(192);
    match(SysYParser::L_BRACKT);
    setState(193);
    match(SysYParser::R_BRACKT);
    setState(201);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::L_BRACKT) {
      setState(195);
      match(SysYParser::L_BRACKT);
      setState(196);
      exp();
      setState(197);
      match(SysYParser::R_BRACKT);
      setState(203);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

SysYParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SysYParser::BlockContext::L_BRACE() {
  return getToken(SysYParser::L_BRACE, 0);
}

tree::TerminalNode* SysYParser::BlockContext::R_BRACE() {
  return getToken(SysYParser::R_BRACE, 0);
}

std::vector<SysYParser::BlockItemContext *> SysYParser::BlockContext::blockItem() {
  return getRuleContexts<SysYParser::BlockItemContext>();
}

SysYParser::BlockItemContext* SysYParser::BlockContext::blockItem(size_t i) {
  return getRuleContext<SysYParser::BlockItemContext>(i);
}


size_t SysYParser::BlockContext::getRuleIndex() const {
  return SysYParser::RuleBlock;
}


std::any SysYParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::BlockContext* SysYParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 28, SysYParser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(204);
    match(SysYParser::L_BRACE);
    setState(208);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 30236741590) != 0)) {
      setState(205);
      blockItem();
      setState(210);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(211);
    match(SysYParser::R_BRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockItemContext ------------------------------------------------------------------

SysYParser::BlockItemContext::BlockItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::BlockItemContext::getRuleIndex() const {
  return SysYParser::RuleBlockItem;
}

void SysYParser::BlockItemContext::copyFrom(BlockItemContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- BlockItemStmtContext ------------------------------------------------------------------

SysYParser::StmtContext* SysYParser::BlockItemStmtContext::stmt() {
  return getRuleContext<SysYParser::StmtContext>(0);
}

SysYParser::BlockItemStmtContext::BlockItemStmtContext(BlockItemContext *ctx) { copyFrom(ctx); }


std::any SysYParser::BlockItemStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitBlockItemStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BlockItemDeclContext ------------------------------------------------------------------

SysYParser::DeclContext* SysYParser::BlockItemDeclContext::decl() {
  return getRuleContext<SysYParser::DeclContext>(0);
}

SysYParser::BlockItemDeclContext::BlockItemDeclContext(BlockItemContext *ctx) { copyFrom(ctx); }


std::any SysYParser::BlockItemDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitBlockItemDecl(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::BlockItemContext* SysYParser::blockItem() {
  BlockItemContext *_localctx = _tracker.createInstance<BlockItemContext>(_ctx, getState());
  enterRule(_localctx, 30, SysYParser::RuleBlockItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(215);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SysYParser::CONST:
      case SysYParser::INT: {
        _localctx = _tracker.createInstance<SysYParser::BlockItemDeclContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(213);
        decl();
        break;
      }

      case SysYParser::IF:
      case SysYParser::WHILE:
      case SysYParser::BREAK:
      case SysYParser::CONTINUE:
      case SysYParser::RETURN:
      case SysYParser::PLUS:
      case SysYParser::MINUS:
      case SysYParser::NOT:
      case SysYParser::L_PAREN:
      case SysYParser::L_BRACE:
      case SysYParser::SEMICOLON:
      case SysYParser::IDENT:
      case SysYParser::INTEGER_CONST: {
        _localctx = _tracker.createInstance<SysYParser::BlockItemStmtContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(214);
        stmt();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StmtContext ------------------------------------------------------------------

SysYParser::StmtContext::StmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::StmtContext::getRuleIndex() const {
  return SysYParser::RuleStmt;
}

void SysYParser::StmtContext::copyFrom(StmtContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ContinueStmtContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::ContinueStmtContext::CONTINUE() {
  return getToken(SysYParser::CONTINUE, 0);
}

tree::TerminalNode* SysYParser::ContinueStmtContext::SEMICOLON() {
  return getToken(SysYParser::SEMICOLON, 0);
}

SysYParser::ContinueStmtContext::ContinueStmtContext(StmtContext *ctx) { copyFrom(ctx); }


std::any SysYParser::ContinueStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitContinueStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IfStmtContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::IfStmtContext::IF() {
  return getToken(SysYParser::IF, 0);
}

tree::TerminalNode* SysYParser::IfStmtContext::L_PAREN() {
  return getToken(SysYParser::L_PAREN, 0);
}

SysYParser::CondContext* SysYParser::IfStmtContext::cond() {
  return getRuleContext<SysYParser::CondContext>(0);
}

tree::TerminalNode* SysYParser::IfStmtContext::R_PAREN() {
  return getToken(SysYParser::R_PAREN, 0);
}

std::vector<SysYParser::StmtContext *> SysYParser::IfStmtContext::stmt() {
  return getRuleContexts<SysYParser::StmtContext>();
}

SysYParser::StmtContext* SysYParser::IfStmtContext::stmt(size_t i) {
  return getRuleContext<SysYParser::StmtContext>(i);
}

tree::TerminalNode* SysYParser::IfStmtContext::ELSE() {
  return getToken(SysYParser::ELSE, 0);
}

SysYParser::IfStmtContext::IfStmtContext(StmtContext *ctx) { copyFrom(ctx); }


std::any SysYParser::IfStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitIfStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprStmtContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::ExprStmtContext::SEMICOLON() {
  return getToken(SysYParser::SEMICOLON, 0);
}

SysYParser::ExpContext* SysYParser::ExprStmtContext::exp() {
  return getRuleContext<SysYParser::ExpContext>(0);
}

SysYParser::ExprStmtContext::ExprStmtContext(StmtContext *ctx) { copyFrom(ctx); }


std::any SysYParser::ExprStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitExprStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- WhileStmtContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::WhileStmtContext::WHILE() {
  return getToken(SysYParser::WHILE, 0);
}

tree::TerminalNode* SysYParser::WhileStmtContext::L_PAREN() {
  return getToken(SysYParser::L_PAREN, 0);
}

SysYParser::CondContext* SysYParser::WhileStmtContext::cond() {
  return getRuleContext<SysYParser::CondContext>(0);
}

tree::TerminalNode* SysYParser::WhileStmtContext::R_PAREN() {
  return getToken(SysYParser::R_PAREN, 0);
}

SysYParser::StmtContext* SysYParser::WhileStmtContext::stmt() {
  return getRuleContext<SysYParser::StmtContext>(0);
}

SysYParser::WhileStmtContext::WhileStmtContext(StmtContext *ctx) { copyFrom(ctx); }


std::any SysYParser::WhileStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitWhileStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignStmtContext ------------------------------------------------------------------

SysYParser::LValContext* SysYParser::AssignStmtContext::lVal() {
  return getRuleContext<SysYParser::LValContext>(0);
}

tree::TerminalNode* SysYParser::AssignStmtContext::ASSIGN() {
  return getToken(SysYParser::ASSIGN, 0);
}

SysYParser::ExpContext* SysYParser::AssignStmtContext::exp() {
  return getRuleContext<SysYParser::ExpContext>(0);
}

tree::TerminalNode* SysYParser::AssignStmtContext::SEMICOLON() {
  return getToken(SysYParser::SEMICOLON, 0);
}

SysYParser::AssignStmtContext::AssignStmtContext(StmtContext *ctx) { copyFrom(ctx); }


std::any SysYParser::AssignStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitAssignStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BreakStmtContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::BreakStmtContext::BREAK() {
  return getToken(SysYParser::BREAK, 0);
}

tree::TerminalNode* SysYParser::BreakStmtContext::SEMICOLON() {
  return getToken(SysYParser::SEMICOLON, 0);
}

SysYParser::BreakStmtContext::BreakStmtContext(StmtContext *ctx) { copyFrom(ctx); }


std::any SysYParser::BreakStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitBreakStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BlockStmtContext ------------------------------------------------------------------

SysYParser::BlockContext* SysYParser::BlockStmtContext::block() {
  return getRuleContext<SysYParser::BlockContext>(0);
}

SysYParser::BlockStmtContext::BlockStmtContext(StmtContext *ctx) { copyFrom(ctx); }


std::any SysYParser::BlockStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitBlockStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ReturnStmtContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::ReturnStmtContext::RETURN() {
  return getToken(SysYParser::RETURN, 0);
}

tree::TerminalNode* SysYParser::ReturnStmtContext::SEMICOLON() {
  return getToken(SysYParser::SEMICOLON, 0);
}

SysYParser::ExpContext* SysYParser::ReturnStmtContext::exp() {
  return getRuleContext<SysYParser::ExpContext>(0);
}

SysYParser::ReturnStmtContext::ReturnStmtContext(StmtContext *ctx) { copyFrom(ctx); }


std::any SysYParser::ReturnStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitReturnStmt(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::StmtContext* SysYParser::stmt() {
  StmtContext *_localctx = _tracker.createInstance<StmtContext>(_ctx, getState());
  enterRule(_localctx, 32, SysYParser::RuleStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(251);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<SysYParser::AssignStmtContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(217);
      lVal();
      setState(218);
      match(SysYParser::ASSIGN);
      setState(219);
      exp();
      setState(220);
      match(SysYParser::SEMICOLON);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<SysYParser::ExprStmtContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(223);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 25807555584) != 0)) {
        setState(222);
        exp();
      }
      setState(225);
      match(SysYParser::SEMICOLON);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<SysYParser::BlockStmtContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(226);
      block();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<SysYParser::IfStmtContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(227);
      match(SysYParser::IF);
      setState(228);
      match(SysYParser::L_PAREN);
      setState(229);
      cond();
      setState(230);
      match(SysYParser::R_PAREN);
      setState(231);
      stmt();
      setState(234);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 23, _ctx)) {
      case 1: {
        setState(232);
        match(SysYParser::ELSE);
        setState(233);
        stmt();
        break;
      }

      default:
        break;
      }
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<SysYParser::WhileStmtContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(236);
      match(SysYParser::WHILE);
      setState(237);
      match(SysYParser::L_PAREN);
      setState(238);
      cond();
      setState(239);
      match(SysYParser::R_PAREN);
      setState(240);
      stmt();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<SysYParser::BreakStmtContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(242);
      match(SysYParser::BREAK);
      setState(243);
      match(SysYParser::SEMICOLON);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<SysYParser::ContinueStmtContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(244);
      match(SysYParser::CONTINUE);
      setState(245);
      match(SysYParser::SEMICOLON);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<SysYParser::ReturnStmtContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(246);
      match(SysYParser::RETURN);
      setState(248);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 25807555584) != 0)) {
        setState(247);
        exp();
      }
      setState(250);
      match(SysYParser::SEMICOLON);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpContext ------------------------------------------------------------------

SysYParser::ExpContext::ExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::ExpContext::getRuleIndex() const {
  return SysYParser::RuleExp;
}

void SysYParser::ExpContext::copyFrom(ExpContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ExpAddExpContext ------------------------------------------------------------------

SysYParser::AddExpContext* SysYParser::ExpAddExpContext::addExp() {
  return getRuleContext<SysYParser::AddExpContext>(0);
}

SysYParser::ExpAddExpContext::ExpAddExpContext(ExpContext *ctx) { copyFrom(ctx); }


std::any SysYParser::ExpAddExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitExpAddExp(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::ExpContext* SysYParser::exp() {
  ExpContext *_localctx = _tracker.createInstance<ExpContext>(_ctx, getState());
  enterRule(_localctx, 34, SysYParser::RuleExp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    _localctx = _tracker.createInstance<SysYParser::ExpAddExpContext>(_localctx);
    enterOuterAlt(_localctx, 1);
    setState(253);
    addExp(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LValContext ------------------------------------------------------------------

SysYParser::LValContext::LValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* SysYParser::LValContext::IDENT() {
  return getToken(SysYParser::IDENT, 0);
}

std::vector<tree::TerminalNode *> SysYParser::LValContext::L_BRACKT() {
  return getTokens(SysYParser::L_BRACKT);
}

tree::TerminalNode* SysYParser::LValContext::L_BRACKT(size_t i) {
  return getToken(SysYParser::L_BRACKT, i);
}

std::vector<SysYParser::ExpContext *> SysYParser::LValContext::exp() {
  return getRuleContexts<SysYParser::ExpContext>();
}

SysYParser::ExpContext* SysYParser::LValContext::exp(size_t i) {
  return getRuleContext<SysYParser::ExpContext>(i);
}

std::vector<tree::TerminalNode *> SysYParser::LValContext::R_BRACKT() {
  return getTokens(SysYParser::R_BRACKT);
}

tree::TerminalNode* SysYParser::LValContext::R_BRACKT(size_t i) {
  return getToken(SysYParser::R_BRACKT, i);
}


size_t SysYParser::LValContext::getRuleIndex() const {
  return SysYParser::RuleLVal;
}


std::any SysYParser::LValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitLVal(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::LValContext* SysYParser::lVal() {
  LValContext *_localctx = _tracker.createInstance<LValContext>(_ctx, getState());
  enterRule(_localctx, 36, SysYParser::RuleLVal);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(255);
    match(SysYParser::IDENT);
    setState(262);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(256);
        match(SysYParser::L_BRACKT);
        setState(257);
        exp();
        setState(258);
        match(SysYParser::R_BRACKT); 
      }
      setState(264);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CondContext ------------------------------------------------------------------

SysYParser::CondContext::CondContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::CondContext::getRuleIndex() const {
  return SysYParser::RuleCond;
}

void SysYParser::CondContext::copyFrom(CondContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- CondLOrExpContext ------------------------------------------------------------------

SysYParser::LOrExpContext* SysYParser::CondLOrExpContext::lOrExp() {
  return getRuleContext<SysYParser::LOrExpContext>(0);
}

SysYParser::CondLOrExpContext::CondLOrExpContext(CondContext *ctx) { copyFrom(ctx); }


std::any SysYParser::CondLOrExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitCondLOrExp(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::CondContext* SysYParser::cond() {
  CondContext *_localctx = _tracker.createInstance<CondContext>(_ctx, getState());
  enterRule(_localctx, 38, SysYParser::RuleCond);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    _localctx = _tracker.createInstance<SysYParser::CondLOrExpContext>(_localctx);
    enterOuterAlt(_localctx, 1);
    setState(265);
    lOrExp(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryExpContext ------------------------------------------------------------------

SysYParser::PrimaryExpContext::PrimaryExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::PrimaryExpContext::getRuleIndex() const {
  return SysYParser::RulePrimaryExp;
}

void SysYParser::PrimaryExpContext::copyFrom(PrimaryExpContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ParenExpContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::ParenExpContext::L_PAREN() {
  return getToken(SysYParser::L_PAREN, 0);
}

SysYParser::ExpContext* SysYParser::ParenExpContext::exp() {
  return getRuleContext<SysYParser::ExpContext>(0);
}

tree::TerminalNode* SysYParser::ParenExpContext::R_PAREN() {
  return getToken(SysYParser::R_PAREN, 0);
}

SysYParser::ParenExpContext::ParenExpContext(PrimaryExpContext *ctx) { copyFrom(ctx); }


std::any SysYParser::ParenExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitParenExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NumberPrimaryExpContext ------------------------------------------------------------------

SysYParser::NumberContext* SysYParser::NumberPrimaryExpContext::number() {
  return getRuleContext<SysYParser::NumberContext>(0);
}

SysYParser::NumberPrimaryExpContext::NumberPrimaryExpContext(PrimaryExpContext *ctx) { copyFrom(ctx); }


std::any SysYParser::NumberPrimaryExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitNumberPrimaryExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LValPrimaryExpContext ------------------------------------------------------------------

SysYParser::LValContext* SysYParser::LValPrimaryExpContext::lVal() {
  return getRuleContext<SysYParser::LValContext>(0);
}

SysYParser::LValPrimaryExpContext::LValPrimaryExpContext(PrimaryExpContext *ctx) { copyFrom(ctx); }


std::any SysYParser::LValPrimaryExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitLValPrimaryExp(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::PrimaryExpContext* SysYParser::primaryExp() {
  PrimaryExpContext *_localctx = _tracker.createInstance<PrimaryExpContext>(_ctx, getState());
  enterRule(_localctx, 40, SysYParser::RulePrimaryExp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(273);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SysYParser::L_PAREN: {
        _localctx = _tracker.createInstance<SysYParser::ParenExpContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(267);
        match(SysYParser::L_PAREN);
        setState(268);
        exp();
        setState(269);
        match(SysYParser::R_PAREN);
        break;
      }

      case SysYParser::IDENT: {
        _localctx = _tracker.createInstance<SysYParser::LValPrimaryExpContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(271);
        lVal();
        break;
      }

      case SysYParser::INTEGER_CONST: {
        _localctx = _tracker.createInstance<SysYParser::NumberPrimaryExpContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(272);
        number();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumberContext ------------------------------------------------------------------

SysYParser::NumberContext::NumberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::NumberContext::getRuleIndex() const {
  return SysYParser::RuleNumber;
}

void SysYParser::NumberContext::copyFrom(NumberContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- IntegerNumberContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::IntegerNumberContext::INTEGER_CONST() {
  return getToken(SysYParser::INTEGER_CONST, 0);
}

SysYParser::IntegerNumberContext::IntegerNumberContext(NumberContext *ctx) { copyFrom(ctx); }


std::any SysYParser::IntegerNumberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitIntegerNumber(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::NumberContext* SysYParser::number() {
  NumberContext *_localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 42, SysYParser::RuleNumber);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    _localctx = _tracker.createInstance<SysYParser::IntegerNumberContext>(_localctx);
    enterOuterAlt(_localctx, 1);
    setState(275);
    match(SysYParser::INTEGER_CONST);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryExpContext ------------------------------------------------------------------

SysYParser::UnaryExpContext::UnaryExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::UnaryExpContext::getRuleIndex() const {
  return SysYParser::RuleUnaryExp;
}

void SysYParser::UnaryExpContext::copyFrom(UnaryExpContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- PrimaryUnaryExpContext ------------------------------------------------------------------

SysYParser::PrimaryExpContext* SysYParser::PrimaryUnaryExpContext::primaryExp() {
  return getRuleContext<SysYParser::PrimaryExpContext>(0);
}

SysYParser::PrimaryUnaryExpContext::PrimaryUnaryExpContext(UnaryExpContext *ctx) { copyFrom(ctx); }


std::any SysYParser::PrimaryUnaryExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitPrimaryUnaryExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnaryOpExpContext ------------------------------------------------------------------

SysYParser::UnaryOpContext* SysYParser::UnaryOpExpContext::unaryOp() {
  return getRuleContext<SysYParser::UnaryOpContext>(0);
}

SysYParser::UnaryExpContext* SysYParser::UnaryOpExpContext::unaryExp() {
  return getRuleContext<SysYParser::UnaryExpContext>(0);
}

SysYParser::UnaryOpExpContext::UnaryOpExpContext(UnaryExpContext *ctx) { copyFrom(ctx); }


std::any SysYParser::UnaryOpExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitUnaryOpExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FuncCallUnaryExpContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::FuncCallUnaryExpContext::IDENT() {
  return getToken(SysYParser::IDENT, 0);
}

tree::TerminalNode* SysYParser::FuncCallUnaryExpContext::L_PAREN() {
  return getToken(SysYParser::L_PAREN, 0);
}

tree::TerminalNode* SysYParser::FuncCallUnaryExpContext::R_PAREN() {
  return getToken(SysYParser::R_PAREN, 0);
}

SysYParser::FuncRParamsContext* SysYParser::FuncCallUnaryExpContext::funcRParams() {
  return getRuleContext<SysYParser::FuncRParamsContext>(0);
}

SysYParser::FuncCallUnaryExpContext::FuncCallUnaryExpContext(UnaryExpContext *ctx) { copyFrom(ctx); }


std::any SysYParser::FuncCallUnaryExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitFuncCallUnaryExp(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::UnaryExpContext* SysYParser::unaryExp() {
  UnaryExpContext *_localctx = _tracker.createInstance<UnaryExpContext>(_ctx, getState());
  enterRule(_localctx, 44, SysYParser::RuleUnaryExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(287);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<SysYParser::PrimaryUnaryExpContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(277);
      primaryExp();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<SysYParser::FuncCallUnaryExpContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(278);
      match(SysYParser::IDENT);
      setState(279);
      match(SysYParser::L_PAREN);
      setState(281);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 25807555584) != 0)) {
        setState(280);
        funcRParams();
      }
      setState(283);
      match(SysYParser::R_PAREN);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<SysYParser::UnaryOpExpContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(284);
      unaryOp();
      setState(285);
      unaryExp();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryOpContext ------------------------------------------------------------------

SysYParser::UnaryOpContext::UnaryOpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::UnaryOpContext::getRuleIndex() const {
  return SysYParser::RuleUnaryOp;
}

void SysYParser::UnaryOpContext::copyFrom(UnaryOpContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- PlusUnaryOpContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::PlusUnaryOpContext::PLUS() {
  return getToken(SysYParser::PLUS, 0);
}

SysYParser::PlusUnaryOpContext::PlusUnaryOpContext(UnaryOpContext *ctx) { copyFrom(ctx); }


std::any SysYParser::PlusUnaryOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitPlusUnaryOp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NotUnaryOpContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::NotUnaryOpContext::NOT() {
  return getToken(SysYParser::NOT, 0);
}

SysYParser::NotUnaryOpContext::NotUnaryOpContext(UnaryOpContext *ctx) { copyFrom(ctx); }


std::any SysYParser::NotUnaryOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitNotUnaryOp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MinusUnaryOpContext ------------------------------------------------------------------

tree::TerminalNode* SysYParser::MinusUnaryOpContext::MINUS() {
  return getToken(SysYParser::MINUS, 0);
}

SysYParser::MinusUnaryOpContext::MinusUnaryOpContext(UnaryOpContext *ctx) { copyFrom(ctx); }


std::any SysYParser::MinusUnaryOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitMinusUnaryOp(this);
  else
    return visitor->visitChildren(this);
}
SysYParser::UnaryOpContext* SysYParser::unaryOp() {
  UnaryOpContext *_localctx = _tracker.createInstance<UnaryOpContext>(_ctx, getState());
  enterRule(_localctx, 46, SysYParser::RuleUnaryOp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(292);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case SysYParser::PLUS: {
        _localctx = _tracker.createInstance<SysYParser::PlusUnaryOpContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(289);
        match(SysYParser::PLUS);
        break;
      }

      case SysYParser::MINUS: {
        _localctx = _tracker.createInstance<SysYParser::MinusUnaryOpContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(290);
        match(SysYParser::MINUS);
        break;
      }

      case SysYParser::NOT: {
        _localctx = _tracker.createInstance<SysYParser::NotUnaryOpContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(291);
        match(SysYParser::NOT);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncRParamsContext ------------------------------------------------------------------

SysYParser::FuncRParamsContext::FuncRParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<SysYParser::ExpContext *> SysYParser::FuncRParamsContext::exp() {
  return getRuleContexts<SysYParser::ExpContext>();
}

SysYParser::ExpContext* SysYParser::FuncRParamsContext::exp(size_t i) {
  return getRuleContext<SysYParser::ExpContext>(i);
}

std::vector<tree::TerminalNode *> SysYParser::FuncRParamsContext::COMMA() {
  return getTokens(SysYParser::COMMA);
}

tree::TerminalNode* SysYParser::FuncRParamsContext::COMMA(size_t i) {
  return getToken(SysYParser::COMMA, i);
}


size_t SysYParser::FuncRParamsContext::getRuleIndex() const {
  return SysYParser::RuleFuncRParams;
}


std::any SysYParser::FuncRParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitFuncRParams(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::FuncRParamsContext* SysYParser::funcRParams() {
  FuncRParamsContext *_localctx = _tracker.createInstance<FuncRParamsContext>(_ctx, getState());
  enterRule(_localctx, 48, SysYParser::RuleFuncRParams);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(294);
    exp();
    setState(299);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == SysYParser::COMMA) {
      setState(295);
      match(SysYParser::COMMA);
      setState(296);
      exp();
      setState(301);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MulExpContext ------------------------------------------------------------------

SysYParser::MulExpContext::MulExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::MulExpContext::getRuleIndex() const {
  return SysYParser::RuleMulExp;
}

void SysYParser::MulExpContext::copyFrom(MulExpContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- UnaryMulExpContext ------------------------------------------------------------------

SysYParser::UnaryExpContext* SysYParser::UnaryMulExpContext::unaryExp() {
  return getRuleContext<SysYParser::UnaryExpContext>(0);
}

SysYParser::UnaryMulExpContext::UnaryMulExpContext(MulExpContext *ctx) { copyFrom(ctx); }


std::any SysYParser::UnaryMulExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitUnaryMulExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BinaryMulExpContext ------------------------------------------------------------------

SysYParser::MulExpContext* SysYParser::BinaryMulExpContext::mulExp() {
  return getRuleContext<SysYParser::MulExpContext>(0);
}

SysYParser::UnaryExpContext* SysYParser::BinaryMulExpContext::unaryExp() {
  return getRuleContext<SysYParser::UnaryExpContext>(0);
}

tree::TerminalNode* SysYParser::BinaryMulExpContext::MUL() {
  return getToken(SysYParser::MUL, 0);
}

tree::TerminalNode* SysYParser::BinaryMulExpContext::DIV() {
  return getToken(SysYParser::DIV, 0);
}

tree::TerminalNode* SysYParser::BinaryMulExpContext::MOD() {
  return getToken(SysYParser::MOD, 0);
}

SysYParser::BinaryMulExpContext::BinaryMulExpContext(MulExpContext *ctx) { copyFrom(ctx); }


std::any SysYParser::BinaryMulExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitBinaryMulExp(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::MulExpContext* SysYParser::mulExp() {
   return mulExp(0);
}

SysYParser::MulExpContext* SysYParser::mulExp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  SysYParser::MulExpContext *_localctx = _tracker.createInstance<MulExpContext>(_ctx, parentState);
  SysYParser::MulExpContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 50;
  enterRecursionRule(_localctx, 50, SysYParser::RuleMulExp, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<UnaryMulExpContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(303);
    unaryExp();
    _ctx->stop = _input->LT(-1);
    setState(310);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<BinaryMulExpContext>(_tracker.createInstance<MulExpContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleMulExp);
        setState(305);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(306);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 28672) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(307);
        unaryExp(); 
      }
      setState(312);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- AddExpContext ------------------------------------------------------------------

SysYParser::AddExpContext::AddExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::AddExpContext::getRuleIndex() const {
  return SysYParser::RuleAddExp;
}

void SysYParser::AddExpContext::copyFrom(AddExpContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- BinaryAddExpContext ------------------------------------------------------------------

SysYParser::AddExpContext* SysYParser::BinaryAddExpContext::addExp() {
  return getRuleContext<SysYParser::AddExpContext>(0);
}

SysYParser::MulExpContext* SysYParser::BinaryAddExpContext::mulExp() {
  return getRuleContext<SysYParser::MulExpContext>(0);
}

tree::TerminalNode* SysYParser::BinaryAddExpContext::PLUS() {
  return getToken(SysYParser::PLUS, 0);
}

tree::TerminalNode* SysYParser::BinaryAddExpContext::MINUS() {
  return getToken(SysYParser::MINUS, 0);
}

SysYParser::BinaryAddExpContext::BinaryAddExpContext(AddExpContext *ctx) { copyFrom(ctx); }


std::any SysYParser::BinaryAddExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitBinaryAddExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MulAddExpContext ------------------------------------------------------------------

SysYParser::MulExpContext* SysYParser::MulAddExpContext::mulExp() {
  return getRuleContext<SysYParser::MulExpContext>(0);
}

SysYParser::MulAddExpContext::MulAddExpContext(AddExpContext *ctx) { copyFrom(ctx); }


std::any SysYParser::MulAddExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitMulAddExp(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::AddExpContext* SysYParser::addExp() {
   return addExp(0);
}

SysYParser::AddExpContext* SysYParser::addExp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  SysYParser::AddExpContext *_localctx = _tracker.createInstance<AddExpContext>(_ctx, parentState);
  SysYParser::AddExpContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 52;
  enterRecursionRule(_localctx, 52, SysYParser::RuleAddExp, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<MulAddExpContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(314);
    mulExp(0);
    _ctx->stop = _input->LT(-1);
    setState(321);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<BinaryAddExpContext>(_tracker.createInstance<AddExpContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleAddExp);
        setState(316);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(317);
        _la = _input->LA(1);
        if (!(_la == SysYParser::PLUS

        || _la == SysYParser::MINUS)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(318);
        mulExp(0); 
      }
      setState(323);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- RelExpContext ------------------------------------------------------------------

SysYParser::RelExpContext::RelExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::RelExpContext::getRuleIndex() const {
  return SysYParser::RuleRelExp;
}

void SysYParser::RelExpContext::copyFrom(RelExpContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- AddRelExpContext ------------------------------------------------------------------

SysYParser::AddExpContext* SysYParser::AddRelExpContext::addExp() {
  return getRuleContext<SysYParser::AddExpContext>(0);
}

SysYParser::AddRelExpContext::AddRelExpContext(RelExpContext *ctx) { copyFrom(ctx); }


std::any SysYParser::AddRelExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitAddRelExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BinaryRelExpContext ------------------------------------------------------------------

SysYParser::RelExpContext* SysYParser::BinaryRelExpContext::relExp() {
  return getRuleContext<SysYParser::RelExpContext>(0);
}

SysYParser::AddExpContext* SysYParser::BinaryRelExpContext::addExp() {
  return getRuleContext<SysYParser::AddExpContext>(0);
}

tree::TerminalNode* SysYParser::BinaryRelExpContext::LT() {
  return getToken(SysYParser::LT, 0);
}

tree::TerminalNode* SysYParser::BinaryRelExpContext::GT() {
  return getToken(SysYParser::GT, 0);
}

tree::TerminalNode* SysYParser::BinaryRelExpContext::LE() {
  return getToken(SysYParser::LE, 0);
}

tree::TerminalNode* SysYParser::BinaryRelExpContext::GE() {
  return getToken(SysYParser::GE, 0);
}

SysYParser::BinaryRelExpContext::BinaryRelExpContext(RelExpContext *ctx) { copyFrom(ctx); }


std::any SysYParser::BinaryRelExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitBinaryRelExp(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::RelExpContext* SysYParser::relExp() {
   return relExp(0);
}

SysYParser::RelExpContext* SysYParser::relExp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  SysYParser::RelExpContext *_localctx = _tracker.createInstance<RelExpContext>(_ctx, parentState);
  SysYParser::RelExpContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 54;
  enterRecursionRule(_localctx, 54, SysYParser::RuleRelExp, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<AddRelExpContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(325);
    addExp(0);
    _ctx->stop = _input->LT(-1);
    setState(332);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<BinaryRelExpContext>(_tracker.createInstance<RelExpContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleRelExp);
        setState(327);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(328);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 3932160) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(329);
        addExp(0); 
      }
      setState(334);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- EqExpContext ------------------------------------------------------------------

SysYParser::EqExpContext::EqExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::EqExpContext::getRuleIndex() const {
  return SysYParser::RuleEqExp;
}

void SysYParser::EqExpContext::copyFrom(EqExpContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- BinaryEqExpContext ------------------------------------------------------------------

SysYParser::EqExpContext* SysYParser::BinaryEqExpContext::eqExp() {
  return getRuleContext<SysYParser::EqExpContext>(0);
}

SysYParser::RelExpContext* SysYParser::BinaryEqExpContext::relExp() {
  return getRuleContext<SysYParser::RelExpContext>(0);
}

tree::TerminalNode* SysYParser::BinaryEqExpContext::EQ() {
  return getToken(SysYParser::EQ, 0);
}

tree::TerminalNode* SysYParser::BinaryEqExpContext::NEQ() {
  return getToken(SysYParser::NEQ, 0);
}

SysYParser::BinaryEqExpContext::BinaryEqExpContext(EqExpContext *ctx) { copyFrom(ctx); }


std::any SysYParser::BinaryEqExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitBinaryEqExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RelEqExpContext ------------------------------------------------------------------

SysYParser::RelExpContext* SysYParser::RelEqExpContext::relExp() {
  return getRuleContext<SysYParser::RelExpContext>(0);
}

SysYParser::RelEqExpContext::RelEqExpContext(EqExpContext *ctx) { copyFrom(ctx); }


std::any SysYParser::RelEqExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitRelEqExp(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::EqExpContext* SysYParser::eqExp() {
   return eqExp(0);
}

SysYParser::EqExpContext* SysYParser::eqExp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  SysYParser::EqExpContext *_localctx = _tracker.createInstance<EqExpContext>(_ctx, parentState);
  SysYParser::EqExpContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 56;
  enterRecursionRule(_localctx, 56, SysYParser::RuleEqExp, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<RelEqExpContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(336);
    relExp(0);
    _ctx->stop = _input->LT(-1);
    setState(343);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<BinaryEqExpContext>(_tracker.createInstance<EqExpContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleEqExp);
        setState(338);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(339);
        _la = _input->LA(1);
        if (!(_la == SysYParser::EQ

        || _la == SysYParser::NEQ)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(340);
        relExp(0); 
      }
      setState(345);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- LAndExpContext ------------------------------------------------------------------

SysYParser::LAndExpContext::LAndExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::LAndExpContext::getRuleIndex() const {
  return SysYParser::RuleLAndExp;
}

void SysYParser::LAndExpContext::copyFrom(LAndExpContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- EqLAndExpContext ------------------------------------------------------------------

SysYParser::EqExpContext* SysYParser::EqLAndExpContext::eqExp() {
  return getRuleContext<SysYParser::EqExpContext>(0);
}

SysYParser::EqLAndExpContext::EqLAndExpContext(LAndExpContext *ctx) { copyFrom(ctx); }


std::any SysYParser::EqLAndExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitEqLAndExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BinaryLAndExpContext ------------------------------------------------------------------

SysYParser::LAndExpContext* SysYParser::BinaryLAndExpContext::lAndExp() {
  return getRuleContext<SysYParser::LAndExpContext>(0);
}

tree::TerminalNode* SysYParser::BinaryLAndExpContext::AND() {
  return getToken(SysYParser::AND, 0);
}

SysYParser::EqExpContext* SysYParser::BinaryLAndExpContext::eqExp() {
  return getRuleContext<SysYParser::EqExpContext>(0);
}

SysYParser::BinaryLAndExpContext::BinaryLAndExpContext(LAndExpContext *ctx) { copyFrom(ctx); }


std::any SysYParser::BinaryLAndExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitBinaryLAndExp(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::LAndExpContext* SysYParser::lAndExp() {
   return lAndExp(0);
}

SysYParser::LAndExpContext* SysYParser::lAndExp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  SysYParser::LAndExpContext *_localctx = _tracker.createInstance<LAndExpContext>(_ctx, parentState);
  SysYParser::LAndExpContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 58;
  enterRecursionRule(_localctx, 58, SysYParser::RuleLAndExp, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<EqLAndExpContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(347);
    eqExp(0);
    _ctx->stop = _input->LT(-1);
    setState(354);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<BinaryLAndExpContext>(_tracker.createInstance<LAndExpContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleLAndExp);
        setState(349);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(350);
        match(SysYParser::AND);
        setState(351);
        eqExp(0); 
      }
      setState(356);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 36, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- LOrExpContext ------------------------------------------------------------------

SysYParser::LOrExpContext::LOrExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t SysYParser::LOrExpContext::getRuleIndex() const {
  return SysYParser::RuleLOrExp;
}

void SysYParser::LOrExpContext::copyFrom(LOrExpContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- BinaryLOrExpContext ------------------------------------------------------------------

SysYParser::LOrExpContext* SysYParser::BinaryLOrExpContext::lOrExp() {
  return getRuleContext<SysYParser::LOrExpContext>(0);
}

tree::TerminalNode* SysYParser::BinaryLOrExpContext::OR() {
  return getToken(SysYParser::OR, 0);
}

SysYParser::LAndExpContext* SysYParser::BinaryLOrExpContext::lAndExp() {
  return getRuleContext<SysYParser::LAndExpContext>(0);
}

SysYParser::BinaryLOrExpContext::BinaryLOrExpContext(LOrExpContext *ctx) { copyFrom(ctx); }


std::any SysYParser::BinaryLOrExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitBinaryLOrExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LAndLOrExpContext ------------------------------------------------------------------

SysYParser::LAndExpContext* SysYParser::LAndLOrExpContext::lAndExp() {
  return getRuleContext<SysYParser::LAndExpContext>(0);
}

SysYParser::LAndLOrExpContext::LAndLOrExpContext(LOrExpContext *ctx) { copyFrom(ctx); }


std::any SysYParser::LAndLOrExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitLAndLOrExp(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::LOrExpContext* SysYParser::lOrExp() {
   return lOrExp(0);
}

SysYParser::LOrExpContext* SysYParser::lOrExp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  SysYParser::LOrExpContext *_localctx = _tracker.createInstance<LOrExpContext>(_ctx, parentState);
  SysYParser::LOrExpContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 60;
  enterRecursionRule(_localctx, 60, SysYParser::RuleLOrExp, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<LAndLOrExpContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(358);
    lAndExp(0);
    _ctx->stop = _input->LT(-1);
    setState(365);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<BinaryLOrExpContext>(_tracker.createInstance<LOrExpContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleLOrExp);
        setState(360);

        if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
        setState(361);
        match(SysYParser::OR);
        setState(362);
        lAndExp(0); 
      }
      setState(367);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 37, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ConstExpContext ------------------------------------------------------------------

SysYParser::ConstExpContext::ConstExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

SysYParser::AddExpContext* SysYParser::ConstExpContext::addExp() {
  return getRuleContext<SysYParser::AddExpContext>(0);
}


size_t SysYParser::ConstExpContext::getRuleIndex() const {
  return SysYParser::RuleConstExp;
}


std::any SysYParser::ConstExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<SysYParserVisitor*>(visitor))
    return parserVisitor->visitConstExp(this);
  else
    return visitor->visitChildren(this);
}

SysYParser::ConstExpContext* SysYParser::constExp() {
  ConstExpContext *_localctx = _tracker.createInstance<ConstExpContext>(_ctx, getState());
  enterRule(_localctx, 62, SysYParser::RuleConstExp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(368);
    addExp(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool SysYParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 25: return mulExpSempred(antlrcpp::downCast<MulExpContext *>(context), predicateIndex);
    case 26: return addExpSempred(antlrcpp::downCast<AddExpContext *>(context), predicateIndex);
    case 27: return relExpSempred(antlrcpp::downCast<RelExpContext *>(context), predicateIndex);
    case 28: return eqExpSempred(antlrcpp::downCast<EqExpContext *>(context), predicateIndex);
    case 29: return lAndExpSempred(antlrcpp::downCast<LAndExpContext *>(context), predicateIndex);
    case 30: return lOrExpSempred(antlrcpp::downCast<LOrExpContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool SysYParser::mulExpSempred(MulExpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool SysYParser::addExpSempred(AddExpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool SysYParser::relExpSempred(RelExpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool SysYParser::eqExpSempred(EqExpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 3: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool SysYParser::lAndExpSempred(LAndExpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 4: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool SysYParser::lOrExpSempred(LOrExpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 5: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

void SysYParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  sysyparserParserInitialize();
#else
  ::antlr4::internal::call_once(sysyparserParserOnceFlag, sysyparserParserInitialize);
#endif
}
