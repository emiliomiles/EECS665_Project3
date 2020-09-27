// A Bison parser, made by GNU Bison 3.7.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "grammar.hh"


// Unqualified %code blocks.
#line 35 "holeyc.yy"

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

#line 63 "parser.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 5 "holeyc.yy"
namespace holeyc {
#line 137 "parser.cc"

  /// Build a parser object.
  Parser::Parser (holeyc::Scanner &scanner_yyarg, holeyc::ProgramNode** root_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      root (root_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value (that.value)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t)
    : Base (t)
    , value ()
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (semantic_type) v)
    : Base (t)
    , value (YY_MOVE (v))
  {}

  template <typename Base>
  Parser::symbol_kind_type
  Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    value = YY_MOVE (s.value);
  }

  // by_kind.
  Parser::by_kind::by_kind ()
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  Parser::by_kind::by_kind (by_kind&& that)
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  Parser::by_kind::by_kind (const by_kind& that)
    : kind_ (that.kind_)
  {}

  Parser::by_kind::by_kind (token_kind_type t)
    : kind_ (yytranslate_ (t))
  {}

  void
  Parser::by_kind::clear ()
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  Parser::symbol_kind_type
  Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }

  Parser::symbol_kind_type
  Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.value))
  {
#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.value))
  {
    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    YYUSE (yysym.kind ());
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YYUSE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;


      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // program: globals
#line 186 "holeyc.yy"
                  {
		  (yylhs.value.transProgram) = new ProgramNode((yystack_[0].value.transDeclList));
		  *root = (yylhs.value.transProgram);
		  }
#line 592 "parser.cc"
    break;

  case 3: // globals: globals decl
#line 192 "holeyc.yy"
                  {
		  (yylhs.value.transDeclList) = (yystack_[1].value.transDeclList);
		  DeclNode * aGlobalDecl = (yystack_[0].value.transDecl);
		  (yystack_[1].value.transDeclList)->push_back(aGlobalDecl);
		  }
#line 602 "parser.cc"
    break;

  case 4: // globals: %empty
#line 198 "holeyc.yy"
                  {
		  std::list<DeclNode *> * startingGlobals;
		  startingGlobals = new std::list<DeclNode *>();
	 	  (yylhs.value.transDeclList) = startingGlobals;
		  }
#line 612 "parser.cc"
    break;

  case 5: // decl: varDecl SEMICOLON
#line 206 "holeyc.yy"
                  {
		  //TODO: Make sure to fill out this rule
		  // (as well as any other empty rule!)
				(yylhs.value.transDecl) = (yystack_[1].value.transVarDecl);
		  }
#line 622 "parser.cc"
    break;

  case 6: // decl: fnDecl
#line 212 "holeyc.yy"
                  {
				(yylhs.value.transDecl) = (yystack_[0].value.transFnDecl);
			}
#line 630 "parser.cc"
    break;

  case 7: // varDecl: type id
#line 217 "holeyc.yy"
                  {
		  size_t typeLine = (yystack_[1].value.transType)->line();
		  size_t typeCol = (yystack_[1].value.transType)->col();
		  (yylhs.value.transVarDecl) = new VarDeclNode(typeLine, typeCol, (yystack_[1].value.transType), (yystack_[0].value.transID));
		  }
#line 640 "parser.cc"
    break;

  case 8: // type: INT
#line 224 "holeyc.yy"
                  {
		  bool isPtr = false;
		  (yylhs.value.transType) = new IntTypeNode((yystack_[0].value.transToken)->line(), (yystack_[0].value.transToken)->col(), isPtr);
		  }
#line 649 "parser.cc"
    break;

  case 9: // type: INTPTR
#line 229 "holeyc.yy"
                  {
				bool isPtr = true;
				(yylhs.value.transType) = new IntPtrNode((yystack_[0].value.transToken)->line(), (yystack_[0].value.transToken)->col(), isPtr);
			}
#line 658 "parser.cc"
    break;

  case 10: // type: BOOL
#line 234 "holeyc.yy"
                  {
				bool isPtr = false;
				(yylhs.value.transType) = new BoolTypeNode((yystack_[0].value.transToken)->line(), (yystack_[0].value.transToken)->col(), isPtr);
			}
#line 667 "parser.cc"
    break;

  case 11: // type: BOOLPTR
#line 239 "holeyc.yy"
                  {
				bool isPtr = true;
				(yylhs.value.transType) = new BoolPtrNode((yystack_[0].value.transToken)->line(), (yystack_[0].value.transToken)->col(), isPtr);
			}
#line 676 "parser.cc"
    break;

  case 12: // type: CHAR
#line 244 "holeyc.yy"
                  {
				bool isPtr = false;
				(yylhs.value.transType) = new CharTypeNode((yystack_[0].value.transToken)->line(), (yystack_[0].value.transToken)->col(), isPtr);
			}
#line 685 "parser.cc"
    break;

  case 13: // type: CHARPTR
#line 249 "holeyc.yy"
                  {
				bool isPtr = true;
				(yylhs.value.transType) = new CharPtrNode((yystack_[0].value.transToken)->line(), (yystack_[0].value.transToken)->col(), isPtr);
			}
#line 694 "parser.cc"
    break;

  case 14: // type: VOID
#line 254 "holeyc.yy"
                  {
				bool isPtr = false;
				(yylhs.value.transType) = new VoidTypeNode((yystack_[0].value.transToken)->line(), (yystack_[0].value.transToken)->col(), isPtr);
			}
#line 703 "parser.cc"
    break;

  case 15: // fnDecl: type id formals fnBody
#line 260 "holeyc.yy"
                  {
				(yylhs.value.transFnDecl) = new FnDeclNode((yystack_[3].value.transType), (yystack_[2].value.transID), (yystack_[1].value.transFormals), (yystack_[0].value.transFnBody));
			}
#line 711 "parser.cc"
    break;

  case 16: // formals: LPAREN RPAREN
#line 265 "holeyc.yy"
                  {
				(yylhs.value.transFormals) = new std::list<FormalDeclNode*>;
			}
#line 719 "parser.cc"
    break;

  case 17: // formals: LPAREN formalsList RPAREN
#line 269 "holeyc.yy"
                  {
				(yylhs.value.transFormals) = (yystack_[1].value.transFormalsList);
			}
#line 727 "parser.cc"
    break;

  case 18: // formalsList: formalDecl
#line 275 "holeyc.yy"
                  {
				(yylhs.value.transFormalsList) = new std::list<FormalDeclNode*>;
				(yylhs.value.transFormalsList)->push_back((yystack_[0].value.transFormalDecl));
			}
#line 736 "parser.cc"
    break;

  case 19: // formalsList: formalDecl COMMA formalsList
#line 280 "holeyc.yy"
                  {
				(yylhs.value.transFormalsList) = (yystack_[0].value.transFormalsList);
				(yylhs.value.transFormalsList)->push_front((yystack_[2].value.transFormalDecl));
			}
#line 745 "parser.cc"
    break;

  case 20: // formalDecl: type id
#line 286 "holeyc.yy"
                  {
				(yylhs.value.transFormalDecl) = new FormalDeclNode((yystack_[1].value.transType), (yystack_[0].value.transID));
			}
#line 753 "parser.cc"
    break;

  case 21: // fnBody: LCURLY stmtList RCURLY
#line 291 "holeyc.yy"
                  {
				(yylhs.value.transFnBody) = (yystack_[1].value.transStmtList);
			}
#line 761 "parser.cc"
    break;

  case 22: // stmtList: %empty
#line 296 "holeyc.yy"
                  {
				std::list<StmtNode *> * startingStmt;
				startingStmt = new std::list<StmtNode *>;
				(yylhs.value.transStmtList) = startingStmt;
			}
#line 771 "parser.cc"
    break;

  case 23: // stmtList: stmtList stmt
#line 302 "holeyc.yy"
                  {
				(yylhs.value.transStmtList) = (yystack_[1].value.transStmtList);
				(yystack_[1].value.transStmtList)->push_back((yystack_[0].value.transStmt));
			}
#line 780 "parser.cc"
    break;

  case 24: // stmt: varDecl SEMICOLON
#line 308 "holeyc.yy"
                  {
				(yylhs.value.transStmt) = (yystack_[1].value.transVarDecl);
			}
#line 788 "parser.cc"
    break;

  case 25: // stmt: assignExp SEMICOLON
#line 312 "holeyc.yy"
                  {
				(yylhs.value.transStmt) = new AssignStmtNode((yystack_[1].value.transAssignExp));
			}
#line 796 "parser.cc"
    break;

  case 26: // stmt: lval DASHDASH SEMICOLON
#line 316 "holeyc.yy"
                  {
				(yylhs.value.transStmt) = new PostDecStmtNode((yystack_[2].value.transLVal));
			}
#line 804 "parser.cc"
    break;

  case 27: // stmt: lval CROSSCROSS SEMICOLON
#line 320 "holeyc.yy"
                  {
				(yylhs.value.transStmt) = new PostIncStmtNode((yystack_[2].value.transLVal));
			}
#line 812 "parser.cc"
    break;

  case 28: // stmt: FROMCONSOLE lval SEMICOLON
#line 324 "holeyc.yy"
                  {
				(yylhs.value.transStmt) = new FromConsoleStmtNode((yystack_[1].value.transLVal));
			}
#line 820 "parser.cc"
    break;

  case 29: // stmt: TOCONSOLE exp SEMICOLON
#line 328 "holeyc.yy"
                  {
				(yylhs.value.transStmt) = new ToConsoleStmtNode((yystack_[1].value.transExp));
			}
#line 828 "parser.cc"
    break;

  case 30: // stmt: IF LPAREN exp RPAREN LCURLY stmtList RCURLY
#line 332 "holeyc.yy"
                  {
				(yylhs.value.transStmt) = new IfStmtNode((yystack_[4].value.transExp), (yystack_[1].value.transStmtList));
			}
#line 836 "parser.cc"
    break;

  case 31: // stmt: IF LPAREN exp RPAREN LCURLY stmtList RCURLY ELSE LCURLY stmtList RCURLY
#line 336 "holeyc.yy"
                  {
				(yylhs.value.transStmt) = new IfElseStmtNode((yystack_[8].value.transExp), (yystack_[5].value.transStmtList), (yystack_[1].value.transStmtList));
			}
#line 844 "parser.cc"
    break;

  case 32: // stmt: WHILE LPAREN exp RPAREN LCURLY stmtList RCURLY
#line 340 "holeyc.yy"
                  {
				(yylhs.value.transStmt) = new WhileStmtNode((yystack_[4].value.transExp), (yystack_[1].value.transStmtList));
			}
#line 852 "parser.cc"
    break;

  case 33: // stmt: RETURN exp SEMICOLON
#line 344 "holeyc.yy"
                  {
				(yylhs.value.transStmt) = new ReturnStmtNode((yystack_[1].value.transExp), false);
			}
#line 860 "parser.cc"
    break;

  case 34: // stmt: RETURN SEMICOLON
#line 348 "holeyc.yy"
                  {
				(yylhs.value.transStmt) = new ReturnStmtNode((yystack_[0].value.transToken)->line(), (yystack_[0].value.transToken)->col(), true);
			}
#line 868 "parser.cc"
    break;

  case 35: // stmt: callExp SEMICOLON
#line 352 "holeyc.yy"
                  {
				(yylhs.value.transStmt) = new CallStmtNode((yystack_[1].value.transCallExp));
			}
#line 876 "parser.cc"
    break;

  case 36: // exp: assignExp
#line 357 "holeyc.yy"
                  {
				(yylhs.value.transExp) = (yystack_[0].value.transAssignExp);
			}
#line 884 "parser.cc"
    break;

  case 37: // exp: exp DASH exp
#line 361 "holeyc.yy"
                  {
				(yylhs.value.transExp) = new MinusNode((yystack_[1].value.transToken)->line(), (yystack_[1].value.transToken)->col(), (yystack_[2].value.transExp), (yystack_[0].value.transExp));
			}
#line 892 "parser.cc"
    break;

  case 38: // exp: exp CROSS exp
#line 365 "holeyc.yy"
                  {
				(yylhs.value.transExp) = new PlusNode((yystack_[1].value.transToken)->line(), (yystack_[1].value.transToken)->col(), (yystack_[2].value.transExp), (yystack_[0].value.transExp));
			}
#line 900 "parser.cc"
    break;

  case 39: // exp: exp STAR exp
#line 369 "holeyc.yy"
                  {
				(yylhs.value.transExp) = new TimesNode((yystack_[1].value.transToken)->line(), (yystack_[1].value.transToken)->col(), (yystack_[2].value.transExp), (yystack_[0].value.transExp));
			}
#line 908 "parser.cc"
    break;

  case 40: // exp: exp SLASH exp
#line 373 "holeyc.yy"
                  {
				(yylhs.value.transExp) = new DivideNode((yystack_[1].value.transToken)->line(), (yystack_[1].value.transToken)->col(), (yystack_[2].value.transExp), (yystack_[0].value.transExp));
			}
#line 916 "parser.cc"
    break;

  case 41: // exp: exp AND exp
#line 377 "holeyc.yy"
                  {
				(yylhs.value.transExp) = new AndNode((yystack_[2].value.transExp)->line(), (yystack_[2].value.transExp)->col(), (yystack_[2].value.transExp), (yystack_[0].value.transExp));
			}
#line 924 "parser.cc"
    break;

  case 42: // exp: exp OR exp
#line 381 "holeyc.yy"
                  {
				(yylhs.value.transExp) = new OrNode((yystack_[1].value.transToken)->line(), (yystack_[1].value.transToken)->col(), (yystack_[2].value.transExp), (yystack_[0].value.transExp));
			}
#line 932 "parser.cc"
    break;

  case 43: // exp: exp EQUALS exp
#line 385 "holeyc.yy"
                  {
				(yylhs.value.transExp) = new EqualsNode((yystack_[1].value.transToken)->line(), (yystack_[1].value.transToken)->col(), (yystack_[2].value.transExp), (yystack_[0].value.transExp));
			}
#line 940 "parser.cc"
    break;

  case 44: // exp: exp NOTEQUALS exp
#line 389 "holeyc.yy"
                  {
				(yylhs.value.transExp) = new NotEqualsNode((yystack_[1].value.transToken)->line(), (yystack_[1].value.transToken)->col(), (yystack_[2].value.transExp), (yystack_[0].value.transExp));
			}
#line 948 "parser.cc"
    break;

  case 45: // exp: exp GREATER exp
#line 393 "holeyc.yy"
                  {
				(yylhs.value.transExp) = new GreaterNode((yystack_[1].value.transToken)->line(), (yystack_[1].value.transToken)->col(), (yystack_[2].value.transExp), (yystack_[0].value.transExp));
			}
#line 956 "parser.cc"
    break;

  case 46: // exp: exp GREATEREQ exp
#line 397 "holeyc.yy"
                  {
				(yylhs.value.transExp) = new GreaterEqNode((yystack_[1].value.transToken)->line(), (yystack_[1].value.transToken)->col(), (yystack_[2].value.transExp), (yystack_[0].value.transExp));
			}
#line 964 "parser.cc"
    break;

  case 47: // exp: exp LESS exp
#line 401 "holeyc.yy"
                  {
				(yylhs.value.transExp) = new LessNode((yystack_[1].value.transToken)->line(), (yystack_[1].value.transToken)->col(), (yystack_[2].value.transExp), (yystack_[0].value.transExp));
			}
#line 972 "parser.cc"
    break;

  case 48: // exp: exp LESSEQ exp
#line 405 "holeyc.yy"
                  {
				(yylhs.value.transExp) = new LessEqNode((yystack_[1].value.transToken)->line(), (yystack_[1].value.transToken)->col(), (yystack_[2].value.transExp), (yystack_[0].value.transExp));
			}
#line 980 "parser.cc"
    break;

  case 49: // exp: NOT exp
#line 409 "holeyc.yy"
                  {
				(yylhs.value.transExp) = new NotNode((yystack_[0].value.transExp));
			}
#line 988 "parser.cc"
    break;

  case 50: // exp: DASH term
#line 413 "holeyc.yy"
                  {
				(yylhs.value.transExp) = new NegNode((yystack_[0].value.transTerm));
			}
#line 996 "parser.cc"
    break;

  case 51: // exp: term
#line 417 "holeyc.yy"
                  {
				(yylhs.value.transExp) = (yystack_[0].value.transTerm);
			}
#line 1004 "parser.cc"
    break;

  case 52: // assignExp: lval ASSIGN exp
#line 422 "holeyc.yy"
                  {
				(yylhs.value.transAssignExp) = new AssignExpNode((yystack_[1].value.transToken)->line(), (yystack_[1].value.transToken)->col(), (yystack_[2].value.transLVal), (yystack_[0].value.transExp));
			}
#line 1012 "parser.cc"
    break;

  case 53: // callExp: id LPAREN RPAREN
#line 427 "holeyc.yy"
                  {
				(yylhs.value.transCallExp) = new CallExpNode((yystack_[2].value.transID), new std::list<ExpNode*>);
			}
#line 1020 "parser.cc"
    break;

  case 54: // callExp: id LPAREN actualsList RPAREN
#line 431 "holeyc.yy"
                  {
				(yylhs.value.transCallExp) = new CallExpNode((yystack_[3].value.transID), (yystack_[1].value.transExpList));
			}
#line 1028 "parser.cc"
    break;

  case 55: // actualsList: exp
#line 436 "holeyc.yy"
                  {
				(yylhs.value.transExpList) = new std::list<ExpNode*>;
				(yylhs.value.transExpList)->push_back((yystack_[0].value.transExp));
			}
#line 1037 "parser.cc"
    break;

  case 56: // actualsList: actualsList COMMA exp
#line 441 "holeyc.yy"
                  {
				(yylhs.value.transExpList) = (yystack_[2].value.transExpList);
				(yylhs.value.transExpList)->push_back((yystack_[0].value.transExp));
			}
#line 1046 "parser.cc"
    break;

  case 57: // term: lval
#line 447 "holeyc.yy"
                  {
				(yylhs.value.transTerm) = (yystack_[0].value.transLVal);
			}
#line 1054 "parser.cc"
    break;

  case 58: // term: callExp
#line 451 "holeyc.yy"
                  {
				(yylhs.value.transTerm) = (yystack_[0].value.transCallExp);
			}
#line 1062 "parser.cc"
    break;

  case 59: // term: NULLPTR
#line 455 "holeyc.yy"
                        {
				(yylhs.value.transTerm) = new NullPtrNode((yystack_[0].value.transToken)->line(), (yystack_[0].value.transToken)->col());
			}
#line 1070 "parser.cc"
    break;

  case 60: // term: INTLITERAL
#line 459 "holeyc.yy"
                        {
				(yylhs.value.transTerm) = new IntLitNode((yystack_[0].value.transIntToken));
			}
#line 1078 "parser.cc"
    break;

  case 61: // term: STRLITERAL
#line 463 "holeyc.yy"
                        {
				(yylhs.value.transTerm) = new StrLitNode((yystack_[0].value.transStrToken)->line(), (yystack_[0].value.transStrToken)->col(), (yystack_[0].value.transStrToken));
			}
#line 1086 "parser.cc"
    break;

  case 62: // term: CHARLIT
#line 467 "holeyc.yy"
                        {
				(yylhs.value.transTerm) = new CharLitNode((yystack_[0].value.transCharToken));
			}
#line 1094 "parser.cc"
    break;

  case 63: // term: TRUE
#line 471 "holeyc.yy"
                        {
				(yylhs.value.transTerm) = new TrueNode((yystack_[0].value.transToken)->line(), (yystack_[0].value.transToken)->col());
			}
#line 1102 "parser.cc"
    break;

  case 64: // term: FALSE
#line 475 "holeyc.yy"
                        {
				(yylhs.value.transTerm) = new FalseNode((yystack_[0].value.transToken)->line(), (yystack_[0].value.transToken)->col());
			}
#line 1110 "parser.cc"
    break;

  case 65: // term: LPAREN exp RPAREN
#line 479 "holeyc.yy"
                        {
				(yylhs.value.transTerm) = (yystack_[1].value.transExp);
			}
#line 1118 "parser.cc"
    break;

  case 66: // lval: id
#line 484 "holeyc.yy"
                  {
				(yylhs.value.transLVal) = new LValNode((yystack_[0].value.transID));
		  }
#line 1126 "parser.cc"
    break;

  case 67: // lval: id LBRACE exp RBRACE
#line 488 "holeyc.yy"
                  {
				(yylhs.value.transLVal) = new IndexNode((yystack_[3].value.transID), (yystack_[1].value.transExp));
		  }
#line 1134 "parser.cc"
    break;

  case 68: // lval: AT id
#line 492 "holeyc.yy"
                  {
				(yylhs.value.transLVal) = new DerefNode((yystack_[0].value.transID));
		  }
#line 1142 "parser.cc"
    break;

  case 69: // lval: CARAT id
#line 496 "holeyc.yy"
                  {
				(yylhs.value.transLVal) = new RefNode((yystack_[0].value.transID));
		  }
#line 1150 "parser.cc"
    break;

  case 70: // id: ID
#line 501 "holeyc.yy"
                  {
		  	(yylhs.value.transID) = new IDNode((yystack_[0].value.transIDToken));
		  }
#line 1158 "parser.cc"
    break;


#line 1162 "parser.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // Parser::context.
  Parser::context::context (const Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        int yychecklim = yylast_ - yyn + 1;
        int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }



  int
  Parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -90;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
     -90,    18,    64,   -90,   -90,   -90,   -90,   -90,   -90,   -90,
     -90,   -90,   -38,    22,   -90,   -90,   -90,    13,    21,    31,
     -90,    22,    24,    53,   -90,   -90,   -90,   -90,    64,    70,
     -90,    22,    22,     3,    34,   -90,   214,   263,    37,    41,
      22,   -90,    42,    43,     1,   -16,   -90,   -90,    45,    44,
     263,   -90,   296,   -90,   -90,   263,   263,   -90,   -90,   -90,
     -90,   319,   -90,   -90,   -90,    75,   341,   263,   -90,   -90,
     -90,   -90,   263,    47,    55,   263,   253,   -90,   361,   -90,
     -90,   387,   -90,   263,   263,   263,   263,   263,   263,   263,
     263,   263,   263,   -90,   263,   263,   -90,   407,   453,   -90,
     -90,   433,   -90,   453,    -7,    65,   -90,    -5,    20,    20,
     116,   116,   116,   116,   116,   116,   475,   -90,   -90,    72,
     -90,   263,   -90,   -90,   -90,   453,   115,   160,    85,   -90,
      81,   -90,   205,   -90
  };

  const signed char
  Parser::yydefact_[] =
  {
       4,     0,     2,     1,    10,    11,    12,    13,     8,     9,
      14,     3,     0,     0,     6,     5,    70,     7,     0,     0,
      16,     0,     0,    18,    22,    15,    20,    17,     0,     0,
      19,     0,     0,     0,     0,    21,     0,     0,     0,     0,
       0,    23,     0,     0,     0,    66,    68,    69,     0,    66,
       0,    62,     0,    64,    60,     0,     0,    59,    34,    61,
      63,     0,    36,    58,    51,    57,     0,     0,    24,     7,
      25,    35,     0,     0,     0,     0,     0,    28,     0,    50,
      57,     0,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    33,     0,     0,    29,     0,    52,    27,
      26,     0,    53,    55,     0,     0,    65,    41,    38,    37,
      43,    45,    46,    47,    48,    44,    42,    40,    39,     0,
      67,     0,    54,    22,    22,    56,     0,     0,    30,    32,
       0,    22,     0,    31
  };

  const short
  Parser::yypgoto_[] =
  {
     -90,   -90,   -90,   -90,   102,    39,   -90,   -90,    86,   -90,
     -90,   -89,   -90,   -36,   -27,   -20,   -90,    61,   -29,   144
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,     1,     2,    11,    39,    40,    14,    19,    22,    23,
      25,    29,    41,    61,    62,    63,   104,    64,    65,    45
  };

  const short
  Parser::yytable_[] =
  {
      44,    66,    42,    15,    48,   121,    72,    31,    84,    43,
      85,    32,    75,    86,    78,    73,    76,    74,     3,    81,
      82,    87,    88,    80,    16,    89,    90,     4,     5,    91,
       6,    97,     7,   122,   126,   127,    98,    94,    95,   101,
     103,    13,   132,    16,     8,    18,     9,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,    21,   117,   118,
      24,    20,    94,    95,    27,    28,    50,    21,    10,    67,
       4,     5,    75,     6,    31,     7,     4,     5,    32,     6,
      72,     7,    68,    70,    71,   125,    77,     8,    99,     9,
      33,    16,    34,     8,   123,     9,   100,    44,    44,    42,
      42,   124,   130,    44,    12,    42,    43,    43,    35,    36,
     131,    10,    43,    79,    30,    37,     0,    10,    38,    31,
       0,     4,     5,    32,     6,     0,     7,     0,     0,    84,
       0,    85,     0,     0,    -1,    33,    16,    34,     8,     0,
       9,     0,    -1,    -1,     0,     0,    -1,    -1,     0,     0,
      -1,     0,     0,   128,    36,     0,     0,    17,    94,    95,
      37,     0,    10,    38,    31,    26,     4,     5,    32,     6,
       0,     7,     0,     0,     0,    46,    47,    49,     0,     0,
      33,    16,    34,     8,    69,     9,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   129,    36,
       0,     0,     0,     0,     0,    37,     0,    10,    38,    31,
       0,     4,     5,    32,     6,     0,     7,     0,    31,     0,
       0,     0,    32,     0,    51,    33,    16,    34,     8,    52,
       9,     0,     0,    53,     0,    16,     0,     0,    54,     0,
       0,     0,     0,   133,    36,     0,    55,    56,     0,    57,
      37,     0,    10,    38,     0,    58,     0,    31,    59,     0,
      60,    32,     0,    51,     0,     0,     0,    31,    52,     0,
       0,    32,    53,    51,    16,     0,     0,    54,    52,     0,
       0,     0,    53,     0,    16,    55,    56,    54,    57,     0,
       0,     0,     0,   102,     0,    55,    56,    59,    57,    60,
      31,     0,     0,     0,    32,     0,    51,    59,     0,    60,
       0,     0,     0,     0,     0,    53,     0,    16,     0,     0,
      54,     0,    83,     0,     0,     0,     0,     0,    55,     0,
       0,    57,    84,     0,    85,     0,     0,    86,     0,     0,
      59,     0,    60,     0,    83,    87,    88,     0,     0,    89,
      90,     0,     0,    91,    84,    92,    85,     0,     0,    86,
      93,    94,    95,     0,    83,     0,     0,    87,    88,     0,
       0,    89,    90,     0,    84,    91,    85,    92,     0,    86,
       0,     0,    96,    94,    95,     0,     0,    87,    88,     0,
      83,    89,    90,     0,     0,    91,     0,    92,     0,     0,
      84,   105,    85,    94,    95,    86,     0,     0,     0,     0,
      83,     0,     0,    87,    88,     0,     0,    89,    90,     0,
      84,    91,    85,    92,     0,    86,     0,   106,     0,    94,
      95,     0,     0,    87,    88,     0,    83,    89,    90,     0,
       0,    91,     0,    92,     0,     0,    84,   119,    85,    94,
      95,    86,     0,     0,     0,     0,    83,     0,     0,    87,
      88,     0,     0,    89,    90,     0,    84,    91,    85,    92,
     120,    86,     0,     0,     0,    94,    95,     0,    83,    87,
      88,     0,     0,    89,    90,     0,     0,    91,    84,    92,
      85,     0,     0,    86,     0,    94,    95,     0,     0,     0,
       0,    87,    88,     0,     0,    89,    90,     0,     0,    91,
       0,     0,     0,     0,     0,     0,     0,    94,    95
  };

  const short
  Parser::yycheck_[] =
  {
      29,    37,    29,    41,    33,    12,     5,     4,    13,    29,
      15,     8,    28,    18,    50,    14,    32,    16,     0,    55,
      56,    26,    27,    52,    21,    30,    31,     6,     7,    34,
       9,    67,    11,    40,   123,   124,    72,    42,    43,    75,
      76,     2,   131,    21,    23,    32,    25,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    18,    94,    95,
      29,    40,    42,    43,    40,    12,    32,    28,    47,    32,
       6,     7,    28,     9,     4,    11,     6,     7,     8,     9,
       5,    11,    41,    41,    41,   121,    41,    23,    41,    25,
      20,    21,    22,    23,    29,    25,    41,   126,   127,   126,
     127,    29,    17,   132,     2,   132,   126,   127,    38,    39,
      29,    47,   132,    52,    28,    45,    -1,    47,    48,     4,
      -1,     6,     7,     8,     9,    -1,    11,    -1,    -1,    13,
      -1,    15,    -1,    -1,    18,    20,    21,    22,    23,    -1,
      25,    -1,    26,    27,    -1,    -1,    30,    31,    -1,    -1,
      34,    -1,    -1,    38,    39,    -1,    -1,    13,    42,    43,
      45,    -1,    47,    48,     4,    21,     6,     7,     8,     9,
      -1,    11,    -1,    -1,    -1,    31,    32,    33,    -1,    -1,
      20,    21,    22,    23,    40,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    39,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    47,    48,     4,
      -1,     6,     7,     8,     9,    -1,    11,    -1,     4,    -1,
      -1,    -1,     8,    -1,    10,    20,    21,    22,    23,    15,
      25,    -1,    -1,    19,    -1,    21,    -1,    -1,    24,    -1,
      -1,    -1,    -1,    38,    39,    -1,    32,    33,    -1,    35,
      45,    -1,    47,    48,    -1,    41,    -1,     4,    44,    -1,
      46,     8,    -1,    10,    -1,    -1,    -1,     4,    15,    -1,
      -1,     8,    19,    10,    21,    -1,    -1,    24,    15,    -1,
      -1,    -1,    19,    -1,    21,    32,    33,    24,    35,    -1,
      -1,    -1,    -1,    40,    -1,    32,    33,    44,    35,    46,
       4,    -1,    -1,    -1,     8,    -1,    10,    44,    -1,    46,
      -1,    -1,    -1,    -1,    -1,    19,    -1,    21,    -1,    -1,
      24,    -1,     3,    -1,    -1,    -1,    -1,    -1,    32,    -1,
      -1,    35,    13,    -1,    15,    -1,    -1,    18,    -1,    -1,
      44,    -1,    46,    -1,     3,    26,    27,    -1,    -1,    30,
      31,    -1,    -1,    34,    13,    36,    15,    -1,    -1,    18,
      41,    42,    43,    -1,     3,    -1,    -1,    26,    27,    -1,
      -1,    30,    31,    -1,    13,    34,    15,    36,    -1,    18,
      -1,    -1,    41,    42,    43,    -1,    -1,    26,    27,    -1,
       3,    30,    31,    -1,    -1,    34,    -1,    36,    -1,    -1,
      13,    40,    15,    42,    43,    18,    -1,    -1,    -1,    -1,
       3,    -1,    -1,    26,    27,    -1,    -1,    30,    31,    -1,
      13,    34,    15,    36,    -1,    18,    -1,    40,    -1,    42,
      43,    -1,    -1,    26,    27,    -1,     3,    30,    31,    -1,
      -1,    34,    -1,    36,    -1,    -1,    13,    40,    15,    42,
      43,    18,    -1,    -1,    -1,    -1,     3,    -1,    -1,    26,
      27,    -1,    -1,    30,    31,    -1,    13,    34,    15,    36,
      37,    18,    -1,    -1,    -1,    42,    43,    -1,     3,    26,
      27,    -1,    -1,    30,    31,    -1,    -1,    34,    13,    36,
      15,    -1,    -1,    18,    -1,    42,    43,    -1,    -1,    -1,
      -1,    26,    27,    -1,    -1,    30,    31,    -1,    -1,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    42,    43
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    50,    51,     0,     6,     7,     9,    11,    23,    25,
      47,    52,    53,    54,    55,    41,    21,    68,    32,    56,
      40,    54,    57,    58,    29,    59,    68,    40,    12,    60,
      57,     4,     8,    20,    22,    38,    39,    45,    48,    53,
      54,    61,    63,    64,    67,    68,    68,    68,    67,    68,
      32,    10,    15,    19,    24,    32,    33,    35,    41,    44,
      46,    62,    63,    64,    66,    67,    62,    32,    41,    68,
      41,    41,     5,    14,    16,    28,    32,    41,    62,    66,
      67,    62,    62,     3,    13,    15,    18,    26,    27,    30,
      31,    34,    36,    41,    42,    43,    41,    62,    62,    41,
      41,    62,    40,    62,    65,    40,    40,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    40,
      37,    12,    40,    29,    29,    62,    60,    60,    38,    38,
      17,    29,    60,    38
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    49,    50,    51,    51,    52,    52,    53,    54,    54,
      54,    54,    54,    54,    54,    55,    56,    56,    57,    57,
      58,    59,    60,    60,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    63,    64,    64,    65,    65,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    67,    67,    67,    67,
      68
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     2,     0,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     4,     2,     3,     1,     3,
       2,     3,     0,     2,     2,     2,     3,     3,     3,     3,
       7,    11,     7,     3,     2,     2,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     1,     3,     3,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     4,     2,     2,
       1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end file\"", "error", "\"invalid token\"", "AND", "AT", "ASSIGN",
  "BOOL", "BOOLPTR", "CARAT", "CHAR", "CHARLIT", "CHARPTR", "COMMA",
  "CROSS", "CROSSCROSS", "DASH", "DASHDASH", "ELSE", "EQUALS", "FALSE",
  "FROMCONSOLE", "ID", "IF", "INT", "INTLITERAL", "INTPTR", "GREATER",
  "GREATEREQ", "LBRACE", "LCURLY", "LESS", "LESSEQ", "LPAREN", "NOT",
  "NOTEQUALS", "NULLPTR", "OR", "RBRACE", "RCURLY", "RETURN", "RPAREN",
  "SEMICOLON", "SLASH", "STAR", "STRLITERAL", "TOCONSOLE", "TRUE", "VOID",
  "WHILE", "$accept", "program", "globals", "decl", "varDecl", "type",
  "fnDecl", "formals", "formalsList", "formalDecl", "fnBody", "stmtList",
  "stmt", "exp", "assignExp", "callExp", "actualsList", "term", "lval",
  "id", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   185,   185,   191,   198,   205,   211,   216,   223,   228,
     233,   238,   243,   248,   253,   259,   264,   268,   274,   279,
     285,   290,   296,   301,   307,   311,   315,   319,   323,   327,
     331,   335,   339,   343,   347,   351,   356,   360,   364,   368,
     372,   376,   380,   384,   388,   392,   396,   400,   404,   408,
     412,   416,   421,   426,   430,   435,   440,   446,   450,   454,
     458,   462,   466,   470,   474,   478,   483,   487,   491,   495,
     500
  };

  void
  Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  Parser::symbol_kind_type
  Parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48
    };
    // Last valid token kind.
    const int code_max = 303;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 5 "holeyc.yy"
} // holeyc
#line 1839 "parser.cc"

#line 505 "holeyc.yy"


void holeyc::Parser::error(const std::string& msg){
	std::cout << msg << std::endl;
	std::cerr << "syntax error" << std::endl;
}
