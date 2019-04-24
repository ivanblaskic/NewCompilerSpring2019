#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

class TypeR2 {
public:
	virtual string toString() = 0;
	virtual bool isInt() = 0;
	virtual bool isBool() = 0;
};

class IntR2 : public TypeR2 {
public:
	IntR2(int _value) {
		this->value = _value;
	}
	bool isInt() {
		return true;
	}
	bool isBool() {
		return false;
	}
	string toString() {
		return to_string(this->value);
	}
	int getVal() {
		return this->value;
	}
private:
	int value;
};

class BoolR2 : public TypeR2 {
public:
	BoolR2(bool _value) {
		this->value = _value;
	}
	bool isBool() {
		return true;
	}
	bool isInt() {
		return false;
	}
	string toString() {
		if (this->value)
			return "true";
		else
			return "false";
	}
	bool getVal() {
		return this->value;
	}
private:
	bool value;
};

class ExpR2 {
public:
	virtual TypeR2* eval() = 0;
	virtual string toString() = 0;
};

class ExpR0 : public ExpR2{
public:
	virtual TypeR2* eval() = 0;
	virtual string toString() = 0;
	virtual string ExpR0Fun() = 0;
};

class DoubleR0 : public ExpR0{
public:
	DoubleR0(ExpR0* _arg) {
		this->arg = _arg;
	}
	TypeR2* eval() {
		this->value = this->arg->eval();
		IntR2 *temp = dynamic_cast<IntR2*>(this->value);
		return new IntR2(temp->getVal() + temp->getVal());
	}
	string toString() {
		string output = "DBL(" + this->arg->toString() + ")";
		return output;
	}
	string ExpR0Fun() {
		return "R0";
	}
private:
	TypeR2* value;
	ExpR0* arg;
};

class NumR0 : public ExpR0 {
public:
	NumR0(IntR2* _value) {
		this->value = _value;
	}
	TypeR2* eval() {
		return this->value;
	}
	string toString() {
		return this->value->toString();
	}
	string ExpR0Fun() {
		return "R0";
	}
private: 
	IntR2* value;
};

class IfR2 : public ExpR2 {
public:
	IfR2(ExpR2* _cond, ExpR2* _tr, ExpR2* _fl) {
		cond = _cond;
		tr = _tr;
		fl = _fl;
	}
	TypeR2* eval() {
		BoolR2 *temp = dynamic_cast<BoolR2*>(this->cond->eval());
		if (temp->getVal()) {
			return this->tr->eval();
		}
		else {
			return this->fl->eval();
		}
	}
	string toString() {
		string temp = "if(" + this->cond->toString() + ") {" + this->tr->toString() + "} else {" + this->fl->toString() + "}";
		return temp;
	}
private:
	ExpR2* cond;
	ExpR2* tr;
	ExpR2* fl;
};

class AndR2 : public ExpR2 {
public:
	AndR2(ExpR2* _l, ExpR2* _r) {
		this->l = _l;
		this->r = _r;
	}
	TypeR2* eval() {
		BoolR2 *temp_1 = dynamic_cast<BoolR2*>(this->l->eval());
		if (temp_1->getVal()) {
			BoolR2* temp_2 = dynamic_cast<BoolR2*>(this->r->eval());
			if (temp_2->getVal()) {
				return new BoolR2(true);
			}
			else {
				return new BoolR2(false);
			}
		}
		else {
			return new BoolR2(false);
		}
	}
	string toString() {
		string temp = "(" + this->l->toString() + " && " + this->r->toString() + ")";
		return temp;
	}
private:
	ExpR2* l;
	ExpR2* r;
};

class OrR2 : public ExpR2 {
public:
	OrR2(ExpR2* _l, ExpR2* _r) {
		this->l = _l;
		this->r = _r;
	}
	TypeR2* eval() {
		BoolR2 *temp_1 = dynamic_cast<BoolR2*>(this->l->eval());
		if (temp_1->getVal()) {
			return new BoolR2(true);
		}
		else {
			BoolR2* temp_2 = dynamic_cast<BoolR2*>(this->r->eval());
			if (temp_2->getVal()) {
				return new BoolR2(true);
			}
			else {
				return new BoolR2(false);
			}
		}
	}
	string toString() {
		string temp = "(" + this->l->toString() + " || " + this->r->toString() + ")";
		return temp;
	}
private:
	ExpR2* l;
	ExpR2* r;
};


class NotR2 : public ExpR2 {
public:
	NotR2(ExpR2* _arg) {
		this->arg = _arg;
	}
	TypeR2* eval() {
		BoolR2* temp = dynamic_cast<BoolR2*>(this->arg->eval());
		if (temp->getVal()) {
			return new BoolR2(false);
		}
		else {
			return new BoolR2(true);
		}
	}
	string toString() {
		string temp = "!(" + arg->toString() + ")";
		return temp;
	}
private:
	ExpR2* arg;
};

class FalseR2 : public ExpR2 {
public:
	FalseR2() {
		this->value = false;
	}
	TypeR2* eval() {
		return new BoolR2(false);
	}
	string toString() {
		return "false";
	}
private:
	bool value;
};

class TrueR2 : public ExpR2 {
public:
	TrueR2() {
		this->value = true;
	}
	TypeR2* eval() {
		return new BoolR2(true);
	}
	string toString() {
		return "true";
	}
private:
	bool value;
};

class CmpR2 : public ExpR2 {
	virtual TypeR2* eval() = 0;
	virtual string toString() = 0;
};

class LessR2 : public CmpR2 {
public: 
	LessR2(ExpR0* _l, ExpR0* _r) {
		this->l = _l;
		this->r = _r;
	}
	TypeR2* eval() {
		IntR2 *temp_l = dynamic_cast<IntR2*>(this->l->eval());
		IntR2 *temp_r = dynamic_cast<IntR2*>(this->r->eval());
		if (temp_l->getVal() < temp_r->getVal()) {
			return new BoolR2(true);
		}
		else {
			return new BoolR2(false);
		}
	}
	string toString() {
		string temp = "(" + this->l->toString() + " < " + this->r->toString() + ")";
		return temp;
	}
private:
	ExpR0* l;
	ExpR0* r;
};

class LseqR2 : public CmpR2 {
public:
	LseqR2(ExpR0* _l, ExpR0* _r) {
		this->l = _l;
		this->r = _r;
	}
	TypeR2* eval() {
		IntR2 *temp_l = dynamic_cast<IntR2*>(this->l->eval());
		IntR2 *temp_r = dynamic_cast<IntR2*>(this->r->eval());
		if (temp_l->getVal() <= temp_r->getVal()) {
			return new BoolR2(true);
		}
		else {
			return new BoolR2(false);
		}
	}
	string toString() {
		string temp = "(" + this->l->toString() + " <= " + this->r->toString() + ")";
		return temp;
	}
private:
	ExpR0* l;
	ExpR0* r;
};

class GrtrR2 : public CmpR2 {
public:
	GrtrR2(ExpR0* _l, ExpR0* _r) {
		this->l = _l;
		this->r = _r;
	}
	TypeR2* eval() {
		IntR2 *temp_l = dynamic_cast<IntR2*>(this->l->eval());
		IntR2 *temp_r = dynamic_cast<IntR2*>(this->r->eval());
		if (temp_l->getVal() > temp_r->getVal()) {
			return new BoolR2(true);
		}
		else {
			return new BoolR2(false);
		}
	}
	string toString() {
		string temp = "(" + this->l->toString() + " > " + this->r->toString() + ")";
		return temp;
	}
private:
	ExpR0* l;
	ExpR0* r;
};

class GreqR2 : public CmpR2 {
public:
	GreqR2(ExpR0* _l, ExpR0* _r) {
		this->l = _l;
		this->r = _r;
	}
	TypeR2* eval() {
		IntR2 *temp_l = dynamic_cast<IntR2*>(this->l->eval());
		IntR2 *temp_r = dynamic_cast<IntR2*>(this->r->eval());
		if (temp_l->getVal() >= temp_r->getVal()) {
			return new BoolR2(true);
		}
		else {
			return new BoolR2(false);
		}
	}
	string toString() {
		string temp = "(" + this->l->toString() + " >= " + this->r->toString() + ")";
		return temp;
	}
private:
	ExpR0* l;
	ExpR0* r;
};

class EqlR2 : public CmpR2 {
public:
	EqlR2(ExpR0* _l, ExpR0* _r) {
		this->l = _l;
		this->r = _r;
	}
	TypeR2* eval() {
		IntR2 *temp_l = dynamic_cast<IntR2*>(this->l->eval());
		IntR2 *temp_r = dynamic_cast<IntR2*>(this->r->eval());
		if (temp_l->getVal() == temp_r->getVal()) {
			return new BoolR2(true);
		}
		else {
			return new BoolR2(false);
		}
	}
	string toString() {
		string temp = "(" + this->l->toString() + " == " + this->r->toString() + ")";
		return temp;
	}
private:
	ExpR0* l;
	ExpR0* r;
};


int main() {
	// ExpR2* program = new NotR2(	new OrR2(	new EqlR2(	new DoubleR0(	new NumR0(	new IntR2(1)	)	), 
	//														new DoubleR0(	new NumR0(	new IntR2(2)	)	)	), 
	//											new EqlR2(	new DoubleR0(	new NumR0(	new IntR2(1)	)	), 
	//														new DoubleR0(	new NumR0(	new IntR2(2)	)	)	)	)	);
	ExpR2* program = new NotR2(new OrR2(new IfR2(new TrueR2(), new FalseR2(), new TrueR2()), new TrueR2()));
	TypeR2* result = program->eval();
	cout << "\n\t" << program->toString() << " = " << result->toString() << "\n\n";
	system("Pause");
}