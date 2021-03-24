#include "validator.h"
#include <assert.h>
#include <sstream>

//validarea datelor introduse
//exceptii daca titlul, autorul sau genul sunt vide, anul este mai mic decat 0
void DisciplinaValidator::validate(const Disciplina& d) {
	vector<string> msgs;
	if (d.getDenumire().size() == 0) msgs.push_back("Denumirea nu poate sa fie vida!");
	if (d.getOre() <= 0) msgs.push_back("Ore trebuie sa fie mai mare decat 0!");
	if (d.getTip().size() == 0) msgs.push_back("Tipul nu poate sa fie vid!");
	if (d.getCadru().size() <= 0) msgs.push_back("Cadrul nu poate sa fie vid!");
	if (msgs.size() > 0) {
		throw ValidateException(msgs);
	}
}

ostream& operator<<(ostream& out, const ValidateException& ex) {
	for (const auto& msg : ex.msgs) {
		out << msg << " ";
	}
	return out;
}

void testValidator() {
	DisciplinaValidator v;
	Disciplina p{ "",0,"","" };
	try {
		v.validate(p);
	}
	catch (const ValidateException & ex) {
		std::stringstream sout;
		sout << ex;
		const auto mesaj = sout.str();
		assert(mesaj.find("decat") >= 0);
		assert(mesaj.find("vid") >= 0);
	}

}