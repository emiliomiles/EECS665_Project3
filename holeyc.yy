%skeleton "lalr1.cc"
%require "3.0"
%debug
%defines
%define api.namespace{holeyc}
%define api.parser.class {Parser}
%define parse.error verbose
%output "parser.cc"
%token-table

%code requires{
	#include <list>
	#include "tokens.hpp"
	#include "ast.hpp"
	namespace holeyc {
		class Scanner;
	}

//The following definition is required when
// we don't have the %locations directive
# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

//End "requires" code
}

%parse-param { holeyc::Scanner &scanner }
%parse-param { holeyc::ProgramNode** root }

%code{
   // C std code for utility functions
   #include <iostream>
   #include <cstdlib>
   #include <fstream>

   // Our code for interoperation between scanner/parser
   #include "scanner.hpp"
   #include "ast.hpp"
   #include "tokens.hpp"

  //Request tokens from our scanner member, not
  // from a global function
  #undef yylex
  #define yylex scanner.yylex
}


/*
The %union directive is a way to specify the
set of possible types that might be used as
translation attributes in the syntax-directed
translations.

TODO: You will have to add to this list to
create new translation value types
*/
%union {
   holeyc::Token *                     	  transToken;
   holeyc::IDToken *                   	  transIDToken;
   holeyc::ProgramNode *               	  transProgram;
   std::list<holeyc::DeclNode *> *     	  transDeclList;
   holeyc::DeclNode *                  	  transDecl;
   holeyc::VarDeclNode *               	  transVarDecl;
   holeyc::TypeNode *                  	  transType;
   holeyc::IDNode *                    	  transID;
	 holeyc::FnDeclNode *                   transFnDecl;
	 std::list<holeyc::FormalDeclNode *> * 	transFormalsList;
	 std::list<holeyc::FormalDeclNode *> * 	transFormals;
	 holeyc::FormalDeclNode *               transFormalDecl;
	 std::list<holeyc::StmtNode *> *        transFnBody;
	 std::list<holeyc::StmtNode *> *        transStmtList;
	 holeyc::StmtNode * 			          		transStmt;
	 holeyc::ExpNode * 						          transExp;
	 holeyc::AssignExpNode * 								transAssignExp;
	 holeyc::CallExpNode * 									transCallExp;
	 holeyc::ExpNode *                      transTerm;
	 holeyc::LValNode * 										transLVal;
	 holeyc::IntLitToken *									transIntToken;
	 holeyc::CharLitToken *									transCharToken;
	 holeyc::StrToken *											transStrToken;
	 std::list<holeyc::ExpNode*> *					transExpList;
}

%define parse.assert

%token                   END	   0 "end file"
%token	<transToken>     AND
%token	<transToken>     AT
%token	<transToken>     ASSIGN
%token	<transToken>     BOOL
%token	<transToken>     BOOLPTR
%token	<transToken>     CARAT
%token	<transToken>     CHAR
%token	<transCharToken> CHARLIT
%token	<transToken>     CHARPTR
%token	<transToken>     COMMA
%token	<transToken>     CROSS
%token	<transToken>     CROSSCROSS
%token	<transToken>     DASH
%token	<transToken>     DASHDASH
%token	<transToken>     ELSE
%token	<transToken>     EQUALS
%token	<transToken>     FALSE
%token	<transToken>     FROMCONSOLE
%token	<transIDToken>   ID
%token	<transToken>     IF
%token	<transToken>     INT
%token	<transIntToken>  INTLITERAL
%token	<transToken>     INTPTR
%token	<transToken>     GREATER
%token	<transToken>     GREATEREQ
%token	<transToken>     LBRACE
%token	<transToken>     LCURLY
%token	<transToken>     LESS
%token	<transToken>     LESSEQ
%token	<transToken>     LPAREN
%token	<transToken>     NOT
%token	<transToken>     NOTEQUALS
%token	<transToken>     NULLPTR
%token	<transToken>     OR
%token	<transToken>     RBRACE
%token	<transToken>     RCURLY
%token	<transToken>     RETURN
%token	<transToken>     RPAREN
%token	<transToken>     SEMICOLON
%token	<transToken>     SLASH
%token	<transToken>     STAR
%token	<transStrToken>  STRLITERAL
%token	<transToken>     TOCONSOLE
%token	<transToken>     TRUE
%token	<transToken>     VOID
%token	<transToken>     WHILE


/* Nonterminals
*  TODO: You will need to add more nonterminals
*  to this list as you add productions to the grammar
*  below (along with indicating the appropriate translation
*  attribute type). Note that the specifier in brackets
*  indicates the type of the translation attribute using
*  the names defined in the %union directive above
*/
/*    (attribute type)    (nonterminal)    */

//all these must match a rule down below

%type <transProgram>      program
%type <transDeclList>     globals
%type <transDecl>         decl
%type <transVarDecl>      varDecl
%type <transType>         type
%type <transID>           id

%type <transFnDecl>       fnDecl
%type <transFormalsList>  formalsList
%type <transFormals>      formals
%type <transFormalDecl>   formalDecl
%type <transFnBody>       fnBody
%type <transStmtList>     stmtList
%type <transStmt>         stmt
%type <transExp>          exp
%type <transAssignExp>    assignExp
%type <transCallExp>      callExp
%type <transTerm>         term
%type <transLVal>         lval
%type <transExpList>      actualsList


%right ASSIGN
%left OR
%left AND
%nonassoc LESS GREATER LESSEQ GREATEREQ EQUALS NOTEQUALS
%left DASH CROSS
%left STAR SLASH
%left NOT
%left AT CARAT

%%

program 	: globals                //done
		  {
		  $$ = new ProgramNode($1);
		  *root = $$;
		  }

globals 	: globals decl            //done
		  {
		  $$ = $1;
		  DeclNode * aGlobalDecl = $2;
		  $1->push_back(aGlobalDecl);
		  }
		| /* epsilon */
		  {
		  std::list<DeclNode *> * startingGlobals;
		  startingGlobals = new std::list<DeclNode *>();
	 	  $$ = startingGlobals;
		  }
		;

decl 		: varDecl SEMICOLON        //done
		  {
		  //TODO: Make sure to fill out this rule
		  // (as well as any other empty rule!)
				$$ = $1;
		  }
		| fnDecl
		  {
				$$ = $1;
			}

varDecl 	: type id          //done
		  {
		  size_t typeLine = $1->line();
		  size_t typeCol = $1->col();
		  $$ = new VarDeclNode(typeLine, typeCol, $1, $2);
		  }

type 		: INT               //done
		  {
		  bool isPtr = false;
		  $$ = new IntTypeNode($1->line(), $1->col(), isPtr);
		  }
		| INTPTR
		  {
				bool isPtr = true;
				$$ = new IntPtrNode($1->line(), $1->col(), isPtr);
			}
		| BOOL
		  {
				bool isPtr = false;
				$$ = new BoolTypeNode($1->line(), $1->col(), isPtr);
			}
		| BOOLPTR
		  {
				bool isPtr = true;
				$$ = new BoolPtrNode($1->line(), $1->col(), isPtr);
			}
		| CHAR
		  {
				bool isPtr = false;
				$$ = new CharTypeNode($1->line(), $1->col(), isPtr);
			}
		| CHARPTR
		  {
				bool isPtr = true;
				$$ = new CharPtrNode($1->line(), $1->col(), isPtr);
			}
		| VOID
		  {
				bool isPtr = false;
				$$ = new VoidTypeNode($1->line(), $1->col(), isPtr);
			}

fnDecl 		: type id formals fnBody           //done
		  {
				$$ = new FnDeclNode($1, $2, $3, $4);
			}

formals 	: LPAREN RPAREN             //done
		  {
				$$ = new std::list<FormalDeclNode*>;
			}
		| LPAREN formalsList RPAREN
		  {
				$$ = $2;
			}


formalsList	: formalDecl              //done
		  {
				$$ = new std::list<FormalDeclNode*>;
				$$->push_back($1);
			}
		| formalDecl COMMA formalsList
		  {
				$$ = $3;
				$$->push_front($1);
			}

formalDecl 	: type id                //done
		  {
				$$ = new FormalDeclNode($1, $2);
			}

fnBody		: LCURLY stmtList RCURLY         //done
		  {
				$$ = $2;
			}

stmtList 	: /* epsilon */             //done
		  {
				std::list<StmtNode *> * startingStmt;
				startingStmt = new std::list<StmtNode *>;
				$$ = startingStmt;
			}
		| stmtList stmt
		  {
				$$ = $1;
				$1->push_back($2);
			}

stmt		: varDecl SEMICOLON         //done
		  {
				$$ = $1;
			}
		| assignExp SEMICOLON
		  {
				$$ = new AssignStmtNode($1);
			}
		| lval DASHDASH SEMICOLON
		  {
				$$ = new PostDecStmtNode($1);
			}
		| lval CROSSCROSS SEMICOLON
		  {
				$$ = new PostIncStmtNode($1);
			}
		| FROMCONSOLE lval SEMICOLON
		  {
				$$ = new FromConsoleStmtNode($2);
			}
		| TOCONSOLE exp SEMICOLON
		  {
				$$ = new ToConsoleStmtNode($2);
			}
		| IF LPAREN exp RPAREN LCURLY stmtList RCURLY
		  {
				$$ = new IfStmtNode($3, $6);
			}
		| IF LPAREN exp RPAREN LCURLY stmtList RCURLY ELSE LCURLY stmtList RCURLY
		  {
				$$ = new IfElseStmtNode($3, $6, $10);
			}
		| WHILE LPAREN exp RPAREN LCURLY stmtList RCURLY
		  {
				$$ = new WhileStmtNode($3, $6);
			}
		| RETURN exp SEMICOLON
		  {
				$$ = new ReturnStmtNode($2, false);
			}
		| RETURN SEMICOLON
		  {
				$$ = new ReturnStmtNode($2->line(), $2->col(), true);
			}
		| callExp SEMICOLON
		  {
				$$ = new CallStmtNode($1);
			}

exp		: assignExp             //done
		  {
				$$ = $1;
			}
		| exp DASH exp
		  {
				$$ = new MinusNode($2->line(), $2->col(), $1, $3);
			}
		| exp CROSS exp
		  {
				$$ = new PlusNode($2->line(), $2->col(), $1, $3);
			}
		| exp STAR exp
		  {
				$$ = new TimesNode($2->line(), $2->col(), $1, $3);
			}
		| exp SLASH exp
		  {
				$$ = new DivideNode($2->line(), $2->col(), $1, $3);
			}
		| exp AND exp
		  {
				$$ = new AndNode($1->line(), $1->col(), $1, $3);
			}
		| exp OR exp
		  {
				$$ = new OrNode($2->line(), $2->col(), $1, $3);
			}
		| exp EQUALS exp
		  {
				$$ = new EqualsNode($2->line(), $2->col(), $1, $3);
			}
		| exp NOTEQUALS exp
		  {
				$$ = new NotEqualsNode($2->line(), $2->col(), $1, $3);
			}
		| exp GREATER exp
		  {
				$$ = new GreaterNode($2->line(), $2->col(), $1, $3);
			}
		| exp GREATEREQ exp
		  {
				$$ = new GreaterEqNode($2->line(), $2->col(), $1, $3);
			}
		| exp LESS exp
		  {
				$$ = new LessNode($2->line(), $2->col(), $1, $3);
			}
		| exp LESSEQ exp
		  {
				$$ = new LessEqNode($2->line(), $2->col(), $1, $3);
			}
		| NOT exp
		  {
				$$ = new NotNode($2);
			}
		| DASH term
		  {
				$$ = new NegNode($2);
			}
		| term
		  {
				$$ = $1;
			}

assignExp	: lval ASSIGN exp          //done
		  {
				$$ = new AssignExpNode($2->line(), $2->col(), $1, $3);
			}

callExp		: id LPAREN RPAREN            //done
		  {
				$$ = new CallExpNode($1, new std::list<ExpNode*>);
			}
		| id LPAREN actualsList RPAREN
		  {
				$$ = new CallExpNode($1, $3);
			}

actualsList	: exp             //done
		  {
				$$ = new std::list<ExpNode*>;
				$$->push_back($1);
			}
		| actualsList COMMA exp
		  {
				$$ = $1;
				$$->push_back($3);
			}

term 		: lval            //done
		  {
				$$ = $1;
			}
		| callExp
		  {
				$$ = $1;
			}
		| NULLPTR
			{
				$$ = new NullPtrNode($1->line(), $1->col());
			}
		| INTLITERAL
			{
				$$ = new IntLitNode($1);
			}
		| STRLITERAL
			{
				$$ = new StrLitNode($1->line(), $1->col(), $1);
			}
		| CHARLIT
			{
				$$ = new CharLitNode($1);
			}
		| TRUE
			{
				$$ = new TrueNode($1->line(), $1->col());
			}
		| FALSE
			{
				$$ = new FalseNode($1->line(), $1->col());
			}
		| LPAREN exp RPAREN
			{
				$$ = $2;
			}

lval		: id         //done
		  {
				$$ = new LValNode($1);
		  }
		| id LBRACE exp RBRACE
		  {
				$$ = new IndexNode($1, $3);
		  }
		| AT id
		  {
				$$ = new DerefNode($2);
		  }
		| CARAT id
		  {
				$$ = new RefNode($2);
		  }

id		: ID                  //done
		  {
		  	$$ = new IDNode($1);
		  }

%%

void holeyc::Parser::error(const std::string& msg){
	std::cout << msg << std::endl;
	std::cerr << "syntax error" << std::endl;
}
