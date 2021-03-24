#pragma once
#include <string>
#include "domain.h"
#include <vector>

using std::vector;
using std::string;
using std::ostream;

class ValidateException {
	vector<string> msgs;
public:
	//constructor
	ValidateException(const vector<string>& errors) :msgs{ errors } {}

	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const ValidateException& ex);
};

ostream& operator<<(ostream& out, const ValidateException& ex);

class DisciplinaValidator {
public:
	void validate(const Disciplina& d);
};

void testValidator();