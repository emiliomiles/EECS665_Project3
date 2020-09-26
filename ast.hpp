#ifndef HOLEYC_AST_HPP
#define HOLEYC_AST_HPP

#include <ostream>
#include <list>
#include "tokens.hpp"

using namespace std;

// **********************************************************************
// ASTnode class (base class for all other kinds of nodes)
// **********************************************************************

namespace holeyc{

/* You may find it useful to forward declare AST subclasses
   here so that you can use a class before it's full definition
*/

//class DeclListNode;   We Probably don't need this one
class ExpNode;
class ProgramNode;
class StmtNode;
class TypeNode;

class AssignExpNode;
class BinaryExpNode;
class CallExpNode;
class CharLitNode;
class FalseNode;
class IntLitNode;
class LValNode;
class NullPtrNode;
class StrLitNode;
class TrueNode;
class UnaryExpNode;

class AssignStmtNode;
class CallStmtNode;
class DeclNode;
class FromConsoleStmtNode;
class IfElseStmtNode;
class PostDecStmtNode;
class PostIncStmtNode;
class ReturnStmtNode;
class ToConsoleStmtNode;
class WhileStmtNode;

class BoolTypeNode;
class CharTypeNode;
class IntTypeNode;
class VoidTypeNode;
class BoolPtrNode;
class CharPtrNode;
class IntPtrNode;

class AndNode;
class DivideNode;
class EqualsNode;
class GreaterEqNode;
class GreaterNode;
class LessEqNode;
class LessNode;
class MinusNode;
class NotEqualsNode;
class OrNode;
class PlusNode;
class TimesNode;


class DerefNode;
class IDNode;
class IndexNode;
class RefNode;

class NegNode;
class NotNode;


class ASTNode{
public:
	ASTNode(size_t lineIn, size_t colIn)
	: l(lineIn), c(colIn){
	}
	virtual void unparse(std::ostream& out, int indent) = 0;
	size_t line(){ return l; }
	size_t col() { return c; }

	/**
	* Return a string specifying the position this node begins.
	* For some node a position doesn't really make sense (i.e.
	* ProgramNode) but for the rest it's the position in the
	* input file that represents that node
	**/
	std::string pos(){
		return "[" + std::to_string(line()) + ","
		+ std::to_string(col()) + "]";
	}

private:
	size_t l; /// The line at which the node starts in the input file
	size_t c; /// The column at which the node starts in the input file
};


/******************************************************************************/
/*												4 sub class of ASTNode                              */
/******************************************************************************/


/**  \class ExpNode
* Superclass for expression nodes (i.e. nodes that can be used as
* part of an expression).  Nodes that are part of an expression
* should inherit from this abstract superclass.
**/
class ExpNode : public ASTNode{
protected:
	ExpNode(size_t line, size_t col)
	: ASTNode(line, col){
	}
};


/**
* \class ProgramNode
* Class that contains the entire abstract syntax tree for a program.
* Note the list of declarations encompasses all global declarations
* which includes (obviously) all global variables and struct declarations`
* and (perhaps less obviously), all function declarations
**/
class ProgramNode : public ASTNode{
public:
	ProgramNode(std::list<DeclNode *> * globalsIn)
	: ASTNode(1, 1), myGlobals(globalsIn){
	}
	void unparse(std::ostream& out, int indent) override;
private:
	std::list<DeclNode * > * myGlobals;
};


/* class StmtNode */
class StmtNode : public ASTNode{
public:
	StmtNode(size_t l, size_t c) : ASTNode(l ,c) {}
	virtual void unparse(std::ostream& out, int indent) override = 0;
};


/**  \class TypeNode
* Superclass of nodes that indicate a data type. For example, in
* the declaration "int a", the int part is the type node (a is an IDNode
* and the whole thing is a DeclNode).
**/
class TypeNode : public ASTNode{
protected:
	TypeNode(size_t lineIn, size_t colIn, bool refIn)
	: ASTNode(lineIn, colIn), myIsReference(refIn){
	}
public:
	virtual void unparse(std::ostream& out, int indent) = 0;
	//TODO: consider adding an isRef to use in unparse to
	// indicate if this is a reference type
	virtual string GetType() = 0;
private:
	bool myIsReference;
};


/******************************************************************************/
/*											12	sub class of ExpNode                              */
/******************************************************************************/
class AssignExpNode : public ExpNode
{
public:
	AssignExpNode(size_t l, size_t c, ExpNode* LVal, ExpNode* src) : ExpNode(l, c)
	{
		myLVal = LVal;
		mySrc = src;
	}
	void unparse(std::ostream& out, int indent) override;
private:
	ExpNode* myLVal;
	ExpNode* mySrc;
};


class BinaryExpNode : public ExpNode
{
public:
	BinaryExpNode(size_t l, size_t c, ExpNode* lhs, ExpNode* rhs) : ExpNode(l, c)
	{
		this->myLhs = lhs;
		this->myRhs = rhs;
	}
	virtual void unparse(std::ostream& out, int indent) override = 0;
	virtual string myOp() = 0;

private:
	ExpNode* myLhs;
	ExpNode* myRhs;
};


/** An identifier. Note that IDNodes subclass
 * ExpNode because they can be used as part of an expression.
**/
class IDNode : public ExpNode{
public:
	IDNode(IDToken * token)
	: ExpNode(token->line(), token->col()), myStrVal(token->value()){
		myStrVal = token->value();
	}
	void unparse(std::ostream& out, int indent);
private:
	/** The name of the identifier **/
	std::string myStrVal;
};


class CallExpNode : public ExpNode
{
public:
	CallExpNode(IDNode* id, std::list<ExpNode>* ExpList) : ExpNode(id->line(), id->col())
	{
		myID = id;
		myExpList = ExpList;
	}
	void unparse(std::ostream& out, int indent) override;

private:
	IDNode* myID;
	std::list<ExpNode>* myExpList;
};


class FalseNode : public ExpNode
{
public:
	FalseNode(size_t l, size_t c) : ExpNode(l,c){}
	void unparse(std::ostream& out, int indent) override;
};


class IntLitNode : public ExpNode
{
public:
	IntLitNode(IntLitToken* token) : ExpNode(token->line(), token->col() )
	{
		myInt = token->num();
	}
	void unparse(std::ostream& out, int indent) override;

private:
	int myInt;
};


class LValNode : public ExpNode
{
public:
	LValNode(IDNode* id) : ExpNode(id->line(), id->col()), myID(id){}
	virtual void unparse(std::ostream& out, int indent) override = 0;

private:
	IDNode* myID;
};


class NullPtrNode : public ExpNode
{
public:
	NullPtrNode(size_t l, size_t c) : ExpNode(l, c){}
	void unparse(std::ostream& out, int indent) override;
};


class StrLitNode : public ExpNode
{
public:
	StrLitNode(size_t l, size_t c, StrToken* strIn) : ExpNode(l, c)
	{
		myStr = strIn->str();
	}
	void unparse(std::ostream& out, int indent) override;
private:
	string myStr;
};


class TrueNode : public ExpNode
{
public:
	TrueNode(size_t l, size_t c) : ExpNode(l,c){}
	void unparse(std::ostream& out, int indent) override;
};


class UnaryExpNode : public ExpNode
{
public:
	UnaryExpNode(ExpNode* exp) : ExpNode(exp->line(), exp->col()){}
	virtual void unparse(std::ostream& out, int indent) override = 0;
};



/******************************************************************************/
/*												sub class of StmtNode                               */
/******************************************************************************/
class AssignStmtNode : public StmtNode
{
public:
	AssignStmtNode(AssignExpNode* assignment) : StmtNode(assignment->line(), assignment->col()), myAssign(assignment){}
	void unparse(std::ostream& out, int indent) override;
private:
	AssignExpNode* myAssign;
};


class CallStmtNode : public StmtNode{
public:
	CallStmtNode(CallExpNode* call) : StmtNode(call->line(), call->col()), myCall(call){}
	void unparse(std::ostream& out, int indent) override;

private:
	CallExpNode* myCall;
};


/** \class DeclNode
* Superclass for declarations (i.e. nodes that can be used to
* declare a struct, function, variable, etc).  This base class will
**/
class DeclNode : public StmtNode{
public:
	DeclNode(size_t l, size_t c) : StmtNode(l, c) {}
	virtual void unparse(std::ostream& out, int indent) = 0;
};


class FromConsoleStmtNode : public StmtNode
{
public:
	FromConsoleStmtNode(LValNode* lVal) : StmtNode(lVal->line(), lVal->col()), myLVal(lVal){}
	void unparse(std::ostream& out, int indent) override;

private:
	LValNode* myLVal;
};


class IfElseStmtNode : public StmtNode
{
public:
	IfElseStmtNode(ExpNode* exp, std::list<StmtNode*>* trueList, std::list<StmtNode*>* falseList) : StmtNode(exp->line(), exp->col()),
		myExp(exp), myTList(trueList), myFList(falseList){}
	void unparse(std::ostream& out, int indent) override;
private:
	ExpNode* myExp;
	std::list<StmtNode*>* myTList;
	std::list<StmtNode*>* myFList;
};


class PostDecStmtNode : public StmtNode
{
public:
	PostDecStmtNode(ExpNode* decID) : StmtNode(decID->line(), decID->col()), myExp(decID){}
	void unparse(std::ostream& out, int indent) override;

private:
	ExpNode* myExp;
};


class PostIncStmtNode : public StmtNode
{
public:
	PostIncStmtNode(ExpNode* incID) : StmtNode(incID->line(), incID->col()), myExp(incID){}
	void unparse(std::ostream& out, int indent) override;
private:
	ExpNode* myExp;
};


class ReturnStmtNode : public StmtNode
{
public:
	// The issue is right here.  When no values are passed, returnId = nullptr, then we try to call nullptr->line() which seg faults
	ReturnStmtNode(ExpNode* returnID, bool emptyIn) : StmtNode(returnID->line(), returnID->col()), myExp(returnID), empty(emptyIn){}
	ReturnStmtNode(size_t l, size_t c, bool emptyIn) : StmtNode(l, c), empty(emptyIn){}
	void unparse(std::ostream& out, int indent) override;

private:
	ExpNode* myExp;
	bool empty;
};


class ToConsoleStmtNode : public StmtNode
{
public:
	ToConsoleStmtNode(ExpNode* exp) : StmtNode(exp->line(), exp->col()), myExp(exp){}
	void unparse(std::ostream& out, int indent) override;

private:
	ExpNode* myExp;
};


class WhileStmtNode : public StmtNode
{
public:
	WhileStmtNode(ExpNode* condition, std::list<StmtNode*>* body) : StmtNode(condition->line(), condition->col()),
		myExp(condition), myStmtList(body){}
	void unparse(std::ostream& out, int indent) override;
private:
	ExpNode* myExp;
	std::list<StmtNode*>* myStmtList;
};



/******************************************************************************/
/*												sub class of TypeNode                               */
/******************************************************************************/
class BoolTypeNode : public TypeNode
{
public:
	BoolTypeNode(size_t lineIn, size_t colIn, bool isRefIn): TypeNode(lineIn, colIn, isRefIn){}
	void unparse(std::ostream& out, int indent) override;
};


class BoolPtrNode : public TypeNode{
public:
	BoolPtrNode(size_t lineIn, size_t colIn, bool isRefIn): TypeNode(lineIn, colIn, isRefIn){}
	void unparse(std::ostream& out, int indent) override;
};


class CharTypeNode : public TypeNode
{
public:
	CharTypeNode(size_t lineIn, size_t colIn, bool isRefIn): TypeNode(lineIn, colIn, isRefIn){}
	void unparse(std::ostream& out, int indent) override;
};


class CharPtrNode : public TypeNode{
public:
	CharPtrNode(size_t lineIn, size_t colIn, bool isRefIn): TypeNode(lineIn, colIn, isRefIn){}
	void unparse(std::ostream& out, int indent)override;
};


class IntTypeNode : public TypeNode
{
public:
	IntTypeNode(size_t lineIn, size_t colIn, bool isRefIn): TypeNode(lineIn, colIn, isRefIn){}
	void unparse(std::ostream& out, int indent) override;
};


class IntPtrNode : public TypeNode
{
public:
	IntPtrNode(size_t lineIn, size_t colIn, bool isRefIn): TypeNode(lineIn, colIn, isRefIn){}
	void unparse(std::ostream& out, int indent) override;
};


class VoidTypeNode : public TypeNode
{
public:
	VoidTypeNode(size_t lineIn, size_t colIn, bool isRefIn): TypeNode(lineIn, colIn, isRefIn){}
	void unparse(std::ostream& out, int indent) override;
};


/******************************************************************************/
/*												sub class of BinaryExpNode                          */
/******************************************************************************/
class AndNode : public BinaryExpNode
{
public:
	AndNode(size_t l, size_t c, ExpNode * exp1, ExpNode * exp2): BinaryExpNode(l, c, exp1, exp2){ }
	string myOp() override { return " and "; }
	void unparse(std::ostream& out, int indent) override;
};


class DivideNode : public BinaryExpNode
{
public:
	DivideNode(size_t l, size_t c, ExpNode * exp1, ExpNode * exp2): BinaryExpNode(l, c, exp1, exp2){ }
	string myOp() override { return "/"; }
	void unparse(std::ostream& out, int indent) override;
};


class EqualsNode : public BinaryExpNode
{
public:
	EqualsNode(size_t l, size_t c, ExpNode * exp1, ExpNode * exp2): BinaryExpNode(l, c, exp1, exp2){ }
	string myOp() override { return "=="; }
	void unparse(std::ostream& out, int indent) override;
};


class GreaterEqNode : public BinaryExpNode
{
public:
	GreaterEqNode(size_t l, size_t c, ExpNode * exp1, ExpNode * exp2): BinaryExpNode(l, c, exp1, exp2){ }
	string myOp() override { return ">="; }
	void unparse(std::ostream& out, int indent) override;
};


class GreaterNode : public BinaryExpNode
{
public:
	GreaterNode(size_t l, size_t c, ExpNode * exp1, ExpNode * exp2): BinaryExpNode(l, c, exp1, exp2){ }
	string myOp() override { return ">"; }
	void unparse(std::ostream& out, int indent) override;
};


class LessEqNode : public BinaryExpNode
{
public:
	LessEqNode(size_t l, size_t c, ExpNode * exp1, ExpNode * exp2): BinaryExpNode(l, c, exp1, exp2){ }
	string myOp() override { return "<="; }
	void unparse(std::ostream& out, int indent) override;
};


class MinusNode : public BinaryExpNode
{
public:
	MinusNode(size_t l, size_t c, ExpNode * exp1, ExpNode * exp2): BinaryExpNode(l, c, exp1, exp2){ }
	string myOp() override { return "-"; }
	void unparse(std::ostream& out, int indent) override;
};


class NotEqualsNode : public BinaryExpNode
{
public:
	NotEqualsNode(size_t l, size_t c, ExpNode * exp1, ExpNode * exp2): BinaryExpNode(l, c, exp1, exp2){ }
	string myOp() override { return "!="; }
	void unparse(std::ostream& out, int indent) override;
};


class OrNode : public BinaryExpNode
{
public:
	OrNode(size_t l, size_t c, ExpNode * exp1, ExpNode * exp2): BinaryExpNode(l, c, exp1, exp2){ }
	string myOp() override { return "or"; }
	void unparse(std::ostream& out, int indent) override;
};


class PlusNode : public BinaryExpNode
{
public:
	PlusNode(size_t l, size_t c, ExpNode * exp1, ExpNode * exp2): BinaryExpNode(l, c, exp1, exp2){ }
	string myOp() override { return "+"; }
	void unparse(std::ostream& out, int indent) override;
};


class TimesNode : public BinaryExpNode
{
public:
	TimesNode(size_t l, size_t c, ExpNode * exp1, ExpNode * exp2): BinaryExpNode(l, c, exp1, exp2){ }
	string myOp() override { return "*"; }
	void unparse(std::ostream& out, int indent) override;
};


/******************************************************************************/
/*												sub class of LValNode                               */
/******************************************************************************/
class DerefNode : public LValNode
{
public:
	DerefNode(IDNode* accessID) : LValNode(accessID), myID(accessID){} //not sure on this one
	void unparse(std::ostream& out, int indent) override;
private:
	IDNode * myID;
};


class IndexNode : public LValNode
{
public:
	IndexNode(IDNode* accessId, ExpNode* offset) : LValNode(accessId), myID(accessId), myExp(offset){}
	void unparse(std::ostream& out, int indent) override;

private:
	IDNode* myID;
	ExpNode* myExp;
};


class RefNode : public LValNode
{
public:
	RefNode(IDNode* accessId) : LValNode(accessId), myID(accessId) {}
	void unparse(std::ostream& out, int indent) override;
private:
	IDNode * myID;
};


/******************************************************************************/
/*												sub class of UnaryExpNode                           */
/******************************************************************************/
class NegNode : public UnaryExpNode
{
public:
	NegNode(ExpNode* exp) : UnaryExpNode(exp), myExp(exp){}
	void unparse(std::ostream& out, int indent) override;

private:
	ExpNode* myExp;
};


class NotNode : public UnaryExpNode
{
public:
	NotNode(ExpNode* exp) : UnaryExpNode(exp), myExp(exp){}
	void unparse(std::ostream& out, int indent) override;

private:
	ExpNode* myExp;
};


/******************************************************************************/
/*												sub class of DeclNode                               */
/******************************************************************************/
class FormalDeclNode : public DeclNode
{
public:
	FormalDeclNode(TypeNode* type, IDNode* id) : DeclNode(type->line(), type->col()), myType(type), myId(id){}
	void unparse(std::ostream& out, int indent) override;

private:
	TypeNode * myType;
	IDNode * myId;
};


/******************************************************************************/
/*												sub class of UnaryExpNode                           */
/******************************************************************************/
class FnDeclNode : public DeclNode
{
public:
	FnDeclNode(TypeNode* type, IDNode* id, std::list<FormalDeclNode*>* params, std::list<StmtNode*>* body):
	DeclNode(type->line(), type->col()), myType(type), myId(id), myParams(params), myBody(body){}
	void unparse(std::ostream& out, int indent) override;
	string GetType(){ return(myType->GetType()); }

private:
	TypeNode* myType;
	IDNode* myId;
	std::list<FormalDeclNode*>* myParams;
	std::list<StmtNode*>* myBody;
};


/** A variable declaration. Note that this class is intended to
 * represent a global or local variable of any type (including a struct
 * type. Note that this is not intended to represent a declaration of
 * a struct. In other words:
 * struct MyStruct {
 *   int fieldA;
 * };
 * is NOT a VarDeclNode because it introduces a new datatype, not a new
 * variable (in this case, the example is a StructDeclNode).  * However,
 * struct MyStruct instance; *is* a VarDeclNode, since it introduces a
 * new variable to the program.
**/
class VarDeclNode : public DeclNode
{
public:
	VarDeclNode(size_t l, size_t c, TypeNode * type, IDNode * id)
	: DeclNode(type->line(), type->col()), myType(type), myId(id){
	}
	virtual void unparse(std::ostream& out, int indent) override = 0;
private:
	TypeNode * myType;
	IDNode * myId;
};


} //End namespace holeyc

#endif
