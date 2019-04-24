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
	IfR2() {

	}
	TypeR2* eval() {

	}
	string toString() {

	}
private:
};

class AndR2 : public ExpR2 {
public:
	AndR2() {

	}
	TypeR2* eval() {

	}
	string toString() {

	}
private:
};

class OrR2 : public ExpR2 {
public:
	OrR2() {

	}
	TypeR2* eval() {

	}
	string toString() {

	}
private:
};

class NotR2 : public ExpR2 {
public:
	NotR2() {

	}
	TypeR2* eval() {

	}
	string toString() {

	}
private:
};

class FalseR2 : public ExpR2 {
public:
	FalseR2() {

	}
	TypeR2* eval() {

	}
	string toString() {

	}
private:
};

class TrueR2 : public ExpR2 {
public:
	TrueR2() {

	}
	TypeR2* eval() {

	}
	string toString() {

	}
private:
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
		string temp = "(< " + this->l->toString() + " " + this->r->toString() + ")";
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
		string temp = "(<= " + this->l->toString() + " " + this->r->toString() + ")";
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
		string temp = "(> " + this->l->toString() + " " + this->r->toString() + ")";
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
		string temp = "(>= " + this->l->toString() + " " + this->r->toString() + ")";
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
		string temp = "(== " + this->l->toString() + " " + this->r->toString() + ")";
		return temp;
	}
private:
	ExpR0* l;
	ExpR0* r;
};


int main() {
	ExpR2* program = new GrtrR2(new DoubleR0(new DoubleR0(new NumR0(new IntR2(2)))), new DoubleR0(new NumR0(new IntR2(2))));
	TypeR2* result = program->eval();
	cout << "\n\t" << program->toString() << " = " << result->toString() << "\n\n";
	system("Pause");
}