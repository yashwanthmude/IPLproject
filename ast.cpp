#include "ast.hh"
#include <cstdarg>
//////////////////////////////

// statement_astnode::statement_astnode()
// {
// }

/////////////////////////////

empty_astnode::empty_astnode() : statement_astnode()
{
	astnode_type = EmptyNode;
}

void empty_astnode::print(int ntabs)
{
	cout << "\"empty\"" << endl;
}

//////////////////////////

seq_astnode::seq_astnode() : statement_astnode()
{

	astnode_type = SeqNode;
}

void seq_astnode::pushback(statement_astnode *child)
{
	children_nodes.push_back(child);
}

void seq_astnode::print(int ntabs)
{
	printblanks(ntabs);
	printAst("", "l", "seq", &children_nodes);
}

///////////////////////////////////

assignS_astnode::assignS_astnode(exp_astnode *l, exp_astnode *r, string tc) : statement_astnode()
{
	typecast = tc;
	left = l;
	right = r;
	id = "Ass";
	astnode_type = AssNode;
}

void assignS_astnode::print(int ntabs)
{
	printAst("assignS", "aa", "left", left, "right", right);
}

///////////////////////////////////

return_astnode::return_astnode(exp_astnode *c) : statement_astnode()
{
	child = c;
	id = "Return";
	astnode_type = ReturnNode;
}
void return_astnode::print(int ntabs)
{
	printAst("", "a", "return", child);
}

////////////////////////////////////

if_astnode::if_astnode(exp_astnode *l, statement_astnode *m, statement_astnode *r) : statement_astnode()
{
	left = l;
	middle = m;
	right = r;
	id = "If";
	astnode_type = IfNode;
}

void if_astnode::print(int ntabs)
{
	printAst("if", "aaa",
			 "cond", left,
			 "then", middle,
			 "else", right);
}
////////////////////////////////////

while_astnode::while_astnode(exp_astnode *l, statement_astnode *r) : statement_astnode()
{
	left = l;
	right = r;
	id = "While";
	astnode_type = WhileNode;
}

void while_astnode::print(int ntabs)
{
	printAst("while", "aa",
			 "cond", left,
			 "stmt", right);
}
/////////////////////////////////

for_astnode::for_astnode(exp_astnode *l, exp_astnode *m1, exp_astnode *m2, statement_astnode *r) : statement_astnode()
{
	left = l;
	middle1 = m1;
	middle2 = m2;
	right = r;
	id = "For";
	astnode_type = ForNode;
}

void for_astnode::print(int ntabs)
{
	printAst("for", "aaaa",
			 "init", left,
			 "guard", middle1,
			 "step", middle2,
			 "body", right);
}

//////////////////////////////////

// exp_astnode::exp_astnode() : abstract_astnode()
// {
// }

//////////////////////////////////
string exp_astnode::idname()
{
	return id;
};
op_binary_astnode::op_binary_astnode(string val, exp_astnode *l, exp_astnode *r) : exp_astnode()
{
	id = val;
	left = l;
	right = r;
	astnode_type = OpBinaryNode;
}

void op_binary_astnode::print(int ntabs)
{
	string str = "\"" + id + "\"";
	char *str1 = const_cast<char *>(str.c_str());
	printAst("op_binary", "saa", "op", str1, "left", left, "right", right);
}

///////////////////////////////////

op_unary_astnode::op_unary_astnode(string val) : exp_astnode()
{
	id = val;
	astnode_type = OpUnaryNode;
}

void op_unary_astnode::print(int ntabs)

{
	string str = "\"" + id + "\"";
	char *str1 = const_cast<char *>(str.c_str());
	printAst("op_unary", "sa", "op", str1, "child", child);
}

op_unary_astnode::op_unary_astnode(string val, exp_astnode *l) : exp_astnode()
{
	id = val;
	child = l;
	astnode_type = OpUnaryNode;
}

string op_unary_astnode::getoperator()
{
	return id;
}
///////////////////////////////////

assignE_astnode::assignE_astnode(exp_astnode *l, exp_astnode *r) : exp_astnode()
{
	left = l;
	right = r;
	astnode_type = AssignNode;
}

void assignE_astnode::print(int ntabs)
{
	printAst("assignE", "aa", "left", left, "right", right);
}

///////////////////////////////////

funcall_astnode::funcall_astnode() : exp_astnode()
{
	astnode_type = FunCallNode;
}

funcall_astnode::funcall_astnode(identifier_astnode *child)
{
	funcname = child;
	astnode_type = FunCallNode;
}

void funcall_astnode::setname(string name)
{
	funcname = new identifier_astnode(name);
}

void funcall_astnode::pushback(exp_astnode *subtree)
{
	children.push_back(subtree);
}

void funcall_astnode::print(int ntabs)
{
	printAst("funcall", "al", "fname", funcname, "params", &children);
}


proccall_astnode::proccall_astnode (funcall_astnode *fc)
{
	procname = fc->funcname;
	children = fc->children;
}
void proccall_astnode::print(int ntabs)
{
    printAst("proccall", "al", "fname", procname, "params", &children);
}
/////////////////////////////////////

intconst_astnode::intconst_astnode(int val) : exp_astnode()
{
	value = val;
	astnode_type = IntConstNode;
}

void intconst_astnode::print(int ntabs)
{

	printAst("", "i", "intconst", value);
}
/////////////////////////////////////
floatconst_astnode::floatconst_astnode(float val) : exp_astnode()
{
	value = val;
	astnode_type = FloatConstNode;
}

void floatconst_astnode::print(int ntabs)
{
	printAst("", "f", "floatconst", value);
}
///////////////////////////////////
stringconst_astnode::stringconst_astnode(string val) : exp_astnode()
{
	value = val;
	astnode_type = StringConstNode;
}

void stringconst_astnode::print(int ntabs)
{
	printAst("", "s", "stringconst", stringTocharstar(value));
}

// ref_astnode::ref_astnode() : exp_astnode()
// {
// 	lvalue = true;
// }

/////////////////////////////////

identifier_astnode::identifier_astnode(string val) : ref_astnode()
{
	id = val;
	astnode_type = IdentifierNode;
}

void identifier_astnode::print(int ntabs)
{
	string str = "\"" + id + "\"";
	char *str1 = const_cast<char *>(str.c_str());
	printAst("", "s", "identifier", str1);
}

////////////////////////////////

arrayref_astnode::arrayref_astnode(exp_astnode *l, exp_astnode *r) : ref_astnode() // again, changed from ref to exp
{
	left = l;
	right = r;
	id = "ArrayRef";
	astnode_type = ArrayRefNode;
}

void arrayref_astnode::print(int ntabs)
{
	printAst("arrayref", "aa", "array", left, "index", right);
}

///////////////////////////////

// pointer_astnode::pointer_astnode(ref_astnode *c) : ref_astnode()
// {
// 	child = c;
// 	id = "Pointer";
// 	astnode_type = PointerNode;
// }

// void pointer_astnode::print(int ntabs)
// {
// 	printAst("", "a", "pointer", child);
// }

////////////////////////////////

deref_astnode::deref_astnode(ref_astnode *c) : ref_astnode()
{
	child = c;
	id = "Deref";
	astnode_type = DerefNode;
}

void deref_astnode::print(int ntabs)
{
	printAst("", "a", "deref", child);
}

/////////////////////////////////

member_astnode::member_astnode(exp_astnode *l, identifier_astnode *r) // change from ref to exp(1st arg)
{
	left = l;
	right = r;
	astnode_type = MemberNode;
}

void member_astnode::print(int ntabs)
{

	printAst("member", "aa", "struct", left, "field", right);
}

/////////////////////////////////

arrow_astnode::arrow_astnode(exp_astnode *l, identifier_astnode *r)
{
	left = l;
	right = r;
	astnode_type = ArrowNode;
}

void arrow_astnode::print(int ntabs)
{

	printAst("arrow", "aa", "pointer", left, "field", right);
}
void printblanks(int blanks)
{
	for (int i = 0; i < blanks; i++)
		cout << " ";
}

/////////////////////////////////

void printAst(const char *astname, const char *fmt...) // fmt is a format string that tells about the type of the arguments.
{
	typedef vector<abstract_astnode *> *pv;
	va_list args;
	va_start(args, fmt);
	if ((astname != NULL) && (astname[0] != '\0'))
	{
		cout << "{ ";
		cout << "\"" << astname << "\""
			 << ": ";
	}
	cout << "{" << endl;
	while (*fmt != '\0')
	{
		if (*fmt == 'a')
		{
			char *field = va_arg(args, char *);
			abstract_astnode *a = va_arg(args, abstract_astnode *);
			cout << "\"" << field << "\": " << endl;

			a->print(0);
		}
		else if (*fmt == 's')
		{
			char *field = va_arg(args, char *);
			char *str = va_arg(args, char *);
			cout << "\"" << field << "\": ";

			cout << str << endl;
		}
		else if (*fmt == 'i')
		{
			char *field = va_arg(args, char *);
			int i = va_arg(args, int);
			cout << "\"" << field << "\": ";

			cout << i;
		}
		else if (*fmt == 'f')
		{
			char *field = va_arg(args, char *);
			double f = va_arg(args, double);
			cout << "\"" << field << "\": ";
			cout << f;
		}
		else if (*fmt == 'l')
		{
			char *field = va_arg(args, char *);
			pv f = va_arg(args, pv);
			cout << "\"" << field << "\": ";
			cout << "[" << endl;
			for (int i = 0; i < (int)f->size(); ++i)
			{
				(*f)[i]->print(0);
				if (i < (int)f->size() - 1)
					cout << "," << endl;
				else
					cout << endl;
			}
			cout << endl;
			cout << "]" << endl;
		}
		++fmt;
		if (*fmt != '\0')
			cout << "," << endl;
	}
	cout << "}" << endl;
	if ((astname != NULL) && (astname[0] != '\0'))
		cout << "}" << endl;
	va_end(args);
}

char *stringTocharstar(string str)
{
	char *charstar = const_cast<char *>(str.c_str());
	return charstar;
}
