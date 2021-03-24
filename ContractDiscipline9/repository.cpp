#include "repository.h"
#include <assert.h>
#include <sstream>
using std::stringstream;
#include <random>
#include <string>
#include <vector>
#include <functional>
#include <vector>
#include <list>
#include <numeric>
#include <fstream>

void DisciplinaRepo::adauga(const Disciplina& d)
{
	if (exist(d)) {
		throw DisciplinaRepoException("Exista deja o Disciplina cu acest titlu !");
	}
	all.push_back(d);
}

bool DisciplinaRepo::exist(const Disciplina& d) const {
	try {
		find(d.getDenumire());
		return true;
	}
	catch (DisciplinaRepoException&) {
		return false;
	}
}

const Disciplina& DisciplinaRepo::find(string denumire) const {
	auto rez = std::find_if(all.begin(), all.end(), [denumire](const Disciplina& c) {
		if (c.getDenumire() == denumire) return true;
		else return false;
		});
	if (rez != all.end())
		return *rez;
	else
		//daca nu exista arunc o exceptie
		throw DisciplinaRepoException("Nu exista nicio disciplina cu acest titlu!");
}

vector<Disciplina> DisciplinaRepo::getAll() noexcept {
	return all;
}

ostream& operator<<(ostream& out, const DisciplinaRepoException& ex) {
	out << ex.msg;
	return out;
}

void DisciplinaRepo::sterge(const Disciplina& d)
{
	if (!exist(d))
		throw DisciplinaRepoException("Nu exista Disciplina cu acest titlu!");
	else
	{
		int i = 0;
		for (auto& car : all)
		{
			if (car.getDenumire() == d.getDenumire())
				all.erase(all.begin() + i);
			i++;
		}
	}
}

void DisciplinaRepo::modifica(const Disciplina& d)
{
	bool found = false;
	for (auto& of : all) {
		if (of.getDenumire() == d.getDenumire()) {
			of = d;
			found = true;
			return;
		}
	}
	if (found == false)
		throw DisciplinaRepoException("Nu exista nicio Disciplina cu acest titlu!");
}


void testAdauga() {
	DisciplinaRepo rep;
	rep.adauga(Disciplina{ "aa",8,"ss","cc" });
	assert(rep.getAll().size() == 1);
	assert(rep.find("aa").getTip() == "ss");

	rep.adauga(Disciplina{ "bb",6,"bb","bb" });
	assert(rep.getAll().size() == 2);


	try {
		rep.adauga(Disciplina{ "aa",6,"ss","cc" }); assert(false);
	}
	catch (const DisciplinaRepoException&) {
		assert(true);
	}
	//cauta ceva inexistent
	try {
		rep.find("abcd"); assert(false);
	}
	catch (const DisciplinaRepoException & e) {
		stringstream os;
		os << e;
		assert(os.str().find("exista") >= 0);
	}
}

void testCauta() {
	DisciplinaRepo rep;
	rep.adauga(Disciplina{ "aa",8,"ss","cc" });
	rep.adauga(Disciplina{ "bb",8,"bb","bb" });

	auto p = rep.find("aa");
	assert(p.getOre() == 8);

	//arunca exceptie daca nu gaseste
	try {
		rep.find("Sara");
		assert(false);
	}
	catch (DisciplinaRepoException&) { assert(true); }
}

void testModifica()
{
	DisciplinaRepo rep;
	rep.adauga(Disciplina{ "aa",8,"ss","cc" });
	rep.adauga(Disciplina{ "bb",8,"bb","bb" });
	rep.modifica(Disciplina{ "bb", 7, "qq", "bb" });
	auto c = rep.find("bb");
	assert(c.getOre() == 7);
	//incerc sa modific o disciplina cu denumire inexistent
	try
	{
		rep.modifica(Disciplina{ "cc",8,"ss","cc" }); assert(false);
	}
	catch (DisciplinaRepoException&) { assert(true); }
}

void testStergere()
{
	DisciplinaRepo rep;
	rep.adauga(Disciplina{ "aa",8,"ss","cc" });
	rep.adauga(Disciplina{ "bb",8,"ss","cc" });
	rep.adauga(Disciplina{ "cc",8,"ss","cc" });
	rep.adauga(Disciplina{ "dd",8,"ss","cc" });
	assert(rep.getAll().size() == 4);
	rep.sterge(Disciplina{ "aa",8,"ss","cc" });
	assert(rep.getAll().size() == 3);
	rep.sterge(Disciplina{ "bb",8,"ss","cc" });
	assert(rep.getAll().size() == 2);
	//incerc sa sterg o carte cu id inexistent
	try {
		rep.sterge(Disciplina{ "aa",8,"ss","cc" });
		assert(false);
	}
	catch (DisciplinaRepoException&) {
		assert(true);
	}
}

void testeRepo() {
	testAdauga();
	testCauta();
	testModifica();
	testStergere();

}