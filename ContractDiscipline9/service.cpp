#include "service.h"
#include "repofile.h"
#include "repolab.h"
#include <functional>
#include <algorithm>
#include <assert.h>
#include <vector>
#include <list>
#include <numeric>
#include <fstream>
#include <random>
using namespace std;

/*
vector<Carte> CarteStore::generalSort(bool(*maiMicF)(const Carte&, const Carte&)) {
	vector<Carte> v{ rep.getAll() };//fac o copie
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = i + 1; j < v.size(); j++) {
			if (!maiMicF(v[i], v[j])) {
				//interschimbam
				Carte aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
		}
	}
	return v;
}
*/
void DisciplinaStore::addDisciplina(const string& denumire, int ore, const string& tip, const string& cadru) {
	Disciplina p{ denumire,ore,tip,cadru };
	val.validate(p);
	rep.adauga(p);
	undoActions.push_back(std::make_unique<UndoAdauga>(rep, p));
}


vector<Disciplina>DisciplinaStore::sortByOre(const bool reverse)

{
	vector<Disciplina> discipline = rep.getAll();
	std::sort(discipline.begin(), discipline.end(), [reverse](const Disciplina& d1, const Disciplina& d2)noexcept {
		if (reverse == false) {
			return d1.getOre() < d2.getOre();
		}
		else return d1.getOre() > d2.getOre();
		});
	return discipline;

}

vector<Disciplina>DisciplinaStore::sortByDenumire(const bool reverse)
{
	vector<Disciplina> discipline = rep.getAll();
	std::sort(discipline.begin(), discipline.end(), [reverse](const Disciplina& d1, const Disciplina& d2)noexcept {
		if (reverse == false) {
			return d1.getDenumire() < d2.getDenumire();
		}
		else return d1.getDenumire() > d2.getDenumire();
		});
	return discipline;
}

vector<Disciplina> DisciplinaStore::sortByCadruTip(const bool reverse) {
	vector<Disciplina> discipline = rep.getAll();
	std::sort(discipline.begin(), discipline.end(), [reverse](const Disciplina& d1, const Disciplina& d2)noexcept {
		if (reverse == true) {
			return cmpAn_Gen_DESC(d1, d2);
		}
		else {
			return cmpAn_Gen_ASC(d1, d2);
		}
		});
	return discipline;
}
/*
vector<Carte> CarteStore::filtreaza(function<bool(const Carte&)> fct) {
	vector<Carte> rez;
	for (const auto& c : rep.getAll()) {
		if (fct(c)) {
			rez.push_back(c);
		}
	}
	return rez;
}
*/
vector<Disciplina> DisciplinaStore::filtrareDenumire(const string denumire) {
	vector<Disciplina>filtrat;
	vector<Disciplina> repo = rep.getAll();
	std::copy_if(repo.begin(), repo.end(), back_inserter(filtrat), [denumire](const Disciplina d)noexcept {
		return d.getDenumire() == denumire; });
	return filtrat;
}

vector<Disciplina> DisciplinaStore::filtrareOre(int ore) {
	vector<Disciplina>filtrat;
	vector<Disciplina>repo = rep.getAll();
	std::copy_if(repo.begin(), repo.end(), back_inserter(filtrat), [ore](const Disciplina d)noexcept {
		return d.getOre() == ore; });
	return filtrat;
}

void DisciplinaStore::sterge(string denumire)
{
	vector<Disciplina> all = rep.getAll();
	auto rez = std::find_if(all.begin(), all.end(), [denumire](const Disciplina& d) {
		if (d.getDenumire() == denumire) return true;
		else return false;
		});
	Disciplina d{ denumire,0,"","" };
	rep.sterge(d);
	undoActions.push_back(std::make_unique<UndoSterge>(rep, *rez));
}

void DisciplinaStore::modifica(const string denumire, int ore, const string tip, const string cadru)
{
	vector<Disciplina> all = rep.getAll();
	auto rez = std::find_if(all.begin(), all.end(), [denumire](const Disciplina& d) {
		if (d.getDenumire() == denumire) return true;
		else return false;
		});
	Disciplina d{ denumire,ore,tip,cadru };
	val.validate(d);
	rep.modifica(d);
	undoActions.push_back(std::make_unique<UndoModifica>(rep, *rez));
}

void DisciplinaStore::raport(vector<DisciplinaDTO>& out)
{
	vector<Disciplina> lista = getAll();
	map<string, DisciplinaDTO> output;
	for (auto item : lista)
	{
		if (output.find(item.getTip()) == output.end())
		{
			DisciplinaDTO act{};
			act.tip = item.getTip();
			act.count = 0;
			output.insert(pair<string, DisciplinaDTO>(item.getTip(), act));
		}
		output[item.getTip()].count++;
	}
	for (auto item : lista) {
		DisciplinaDTO act{};
		act.count = output[item.getTip()].count;
		act.denumire = item.getDenumire();
		act.tip = item.getTip();
		out.push_back(act);
	}
}



int DisciplinaStore::totalore()
{
	vector<Disciplina>total = getAll();
	return std::accumulate(total.begin(), total.end(), 0, [](int sum, Disciplina d) {
		return d.getOre() + sum;
		});
}

void DisciplinaStore::adaugaContract(const string& denumire) {
	/*vector<Carte> all = rep.getAll();
	auto rez = std::find_if(all.begin(), all.end(), [titlu](const Carte& c) {
		if (c.getTitlu() == titlu) return true;
		else return false;
		});
	cosRepository.addCos(titlu);
	undoActions.push_back(std::make_unique<UndoAdaugaCos>(cosRepository, *rez));
	*/
	auto a = rep.find(denumire);
	contractRepository.Add(a);
	undoActions.push_back(make_unique<UndoAdaugaCos>(contractRepository, a));
}

void DisciplinaStore::emptyContractP() {
	//cosRepository.emptyCos();
	for (auto item : contractRepository.getAll()) contractRepository.Delete(item.getDenumire());
}

void DisciplinaStore::populateContractP(const int& nrProduse) {
	//cosRepository.populateCos(nrProduse);
	std::mt19937 mt{ std::random_device{}() };
	const std::uniform_int_distribution<> dist(0, rep.getAll().size() - 1);
	for (int i = 0; i < nrProduse; i++)
	{
		const int rndNr = dist(mt);// numar aleator intre [0,size-1]
		contractRepository.Add(rep.getAll()[rndNr]);
	}
}

const vector<Disciplina>& DisciplinaStore::getAllProductsContract() {
	return contractRepository.getAll();
}

void DisciplinaStore::saveToFile(const string& fileName) {
	//cosRepository.saveCos(fileName);
	ofstream fout(fileName);
	fout << "Titlu,Autor,Gen,An\n";
	for (auto item : contractRepository.getAll()) {

		fout << item.getDenumire() << "," << item.getOre() << "," << item.getTip() << "," << item.getCadru() << "\n";
	}
	fout.close();
}

int DisciplinaStore::sizeContract() const {
	return contractRepository.Length();
}

void DisciplinaStore::undo()
{
	if (undoActions.empty())
		throw DisciplinaRepoException("Nu mai exista operatii Undo!");
	undoActions.back()->doUndo();
	undoActions.pop_back();
}

//TESTE
void testAdaugaCtr() {
	DisciplinaRepo rep;
	DisciplinaValidator val;
	RepoContract contract;
	DisciplinaStore ctr{ rep,val ,contract };
	ctr.addDisciplina("a", 6, "a", "a");
	assert(ctr.getAll().size() == 1);

	//adaug ceva invalid
	try {
		ctr.addDisciplina("", -1, "", "");
		assert(false);
	}
	catch (ValidateException&) {
		assert(true);
	}
	//incerc sa adaug ceva ce existadeja
	try {
		ctr.addDisciplina("a", 6, "a", "a");
		assert(false);
	}
	catch (DisciplinaRepoException&) {
		assert(true);
	}
}



void testFiltrare() {
	DisciplinaRepo rep;
	DisciplinaValidator val;
	RepoContract contract;
	DisciplinaStore ctr{ rep,val ,contract };
	ctr.addDisciplina("a", 6, "a", "a");
	ctr.addDisciplina("bc", 60, "b", "b");
	ctr.addDisciplina("c", 600, "c", "c");
	assert(ctr.filtrareOre(6).size() == 1);
	assert(ctr.filtrareOre(100).size() == 0);
	assert(ctr.filtrareDenumire("c").size() == 1);

}

void testSortare() {
	DisciplinaRepo rep;
	DisciplinaValidator val;
	RepoContract contract;
	DisciplinaStore ctr{ rep,val ,contract };
	ctr.addDisciplina("a", 6, "a", "a");
	ctr.addDisciplina("b", 60, "b", "b");
	ctr.addDisciplina("c", 600, "c", "c");
	ctr.addDisciplina("x", 6, "x", "a");

	auto firstP = ctr.sortByDenumire(false)[0];
	assert(firstP.getDenumire() == "a");

	firstP = ctr.sortByOre(true)[1];
	assert(firstP.getOre() == 60);

	firstP = ctr.sortByCadruTip(true)[0];
	assert(firstP.getCadru() == "a");

	firstP = ctr.sortByCadruTip(false)[0];
	assert(firstP.getCadru() == "c");

}

void testRaport()
{
	//int suma=0;
	DisciplinaRepo rep;
	DisciplinaValidator val;
	RepoContract contract;
	DisciplinaStore ctr{ rep,val ,contract };
	vector<DisciplinaDTO>out;
	ctr.addDisciplina("a", 6, "a", "a");
	ctr.addDisciplina("b", 6, "a", "a");
	ctr.addDisciplina("c", 6, "a", "a");
	assert(ctr.totalore() == 18);
	ctr.raport(out);
	assert(out.size() == 3);
	assert(out[0].count == 3);
}


void testStergereCtr()
{
	DisciplinaRepo rep;
	DisciplinaValidator val;
	RepoContract contract;
	DisciplinaStore ctr{ rep,val ,contract };
	ctr.addDisciplina("a", 6, "a", "a");
	ctr.addDisciplina("b", 6, "a", "a");
	ctr.addDisciplina("c", 6, "a", "a");
	ctr.sterge("b");
	assert(ctr.getAll().size() == 2);
}

void testModificaCtr()
{
	DisciplinaRepo rep;
	DisciplinaValidator val;
	RepoContract contract;
	DisciplinaStore ctr{ rep,val ,contract };
	ctr.addDisciplina("a", 6, "a", "a");
	ctr.addDisciplina("b", 6, "a", "a");
	ctr.addDisciplina("c", 6, "a", "a");
	ctr.modifica("a", 8, "a", "a");
	auto p = rep.find("a");
	assert(p.getOre() == 8);

	try {
		ctr.modifica("d", 6, "a", "a"); assert(false);
	}
	catch (DisciplinaRepoException&) { assert(true); }
	try {
		ctr.modifica("d", 6, "a", "a"); assert(false);
	}
	catch (DisciplinaRepoException&) { assert(true); }
}



void testCos()
{
	DisciplinaRepo rep;
	DisciplinaValidator val;
	RepoContract contract;
	DisciplinaStore ctr{ rep,val ,contract };
	ctr.addDisciplina("a", 6, "a", "a");
	ctr.addDisciplina("b", 6, "a", "a");
	ctr.addDisciplina("c", 6, "a", "a");
	//Adaugare
	ctr.adaugaContract("b");
	assert(ctr.sizeContract() == 1);
	try {
		ctr.adaugaContract("d"); assert(false);
	}
	catch (const DisciplinaRepoException&) {
		assert(true);
	}
	//Adaugare random
	ctr.populateContractP(2);
	assert(contract.Length() == 3);
	contract.GetByDenumire("b");
	try {
		contract.GetByDenumire("e"); assert(false);
	}
	catch (DisciplinaRepoException&) { assert(true); }
	assert(ctr.getAllProductsContract().size() == 3);
	ctr.saveToFile("test.csv");
	//Golire cos
	ctr.emptyContractP();
}


void testUndo()
{
	DisciplinaRepo rep;
	DisciplinaValidator val;
	RepoContract contract;
	DisciplinaStore ctr{ rep,val ,contract };
	assert(ctr.getAll().size() == 0);
	try {
		ctr.undo(); assert(false);
	}
	catch (const DisciplinaRepoException&) {
		assert(true);
	}
	ctr.addDisciplina("a", 6, "a", "a");
	ctr.addDisciplina("b", 6, "a", "a");
	ctr.addDisciplina("c", 6, "a", "a");
	assert(rep.getAll().size() == 3);
	ctr.undo();
	assert(rep.getAll().size() == 2);
	ctr.modifica("a", 7, "ww", "a");
	auto p = rep.find("a");
	assert(p.getOre() == 7);
	ctr.undo();
	p = rep.find("a");
	assert(p.getOre() == 6);
	ctr.sterge("b");
	assert(rep.getAll().size() == 1);
	ctr.undo();
	assert(rep.getAll().size() == 2);
	ctr.adaugaContract("a");
	ctr.adaugaContract("b");
	//assert(contract.size() == 1);
	ctr.undo();
	assert(contract.Length() == 1);
}

void testFile()
{
	FileRepository rep("test.txt");
	DisciplinaValidator val;
	RepoContract contract;
	DisciplinaStore ctr{ rep,val ,contract };
	ctr.addDisciplina("yy", 6, "a", "a");
	assert(ctr.getAll().size() == 5);
	try {
		ctr.addDisciplina("a", 6, "a", "a"); assert(false);
	}
	catch (DisciplinaRepoException&) {
		assert(true);
	}
	ctr.modifica("yy", 8, "a", "a");
	auto p = rep.find("yy");
	assert(p.getOre() == 8);
	ctr.sterge("yy");
	try {
		ctr.sterge("banana"); assert(false);
	}
	catch (DisciplinaRepoException&) { assert(true); }
	try { ctr.modifica("uu", 6, "a", "a"); assert(false); }
	catch (DisciplinaRepoException&) { assert(true); }
}

void testRLab()
{
	RepoLab rep(1.1);
	DisciplinaValidator val;
	RepoContract contract;
	DisciplinaStore ctr{ rep,val,contract };
	ctr.addDisciplina("a", 6, "a", "a");
	assert(ctr.getAll().size() == 1);
	try {
		ctr.addDisciplina("a", 6, "a", "a"); assert(false);
	}
	catch (DisciplinaRepoException&) {
		assert(true);
	}
	ctr.modifica("a", 7, "a", "a");
	auto p = rep.find("a");
	assert(p.getOre() == 7);
	ctr.sterge("a");
	try {
		ctr.sterge("banana"); assert(false);
	}
	catch (DisciplinaRepoException&) { assert(true); }
	try { ctr.modifica("banana",6,"a","a"); assert(false); }
	catch (DisciplinaRepoException&) { assert(true); }
}

void testCtr() {
	testAdaugaCtr();
	testFiltrare();
	testSortare();
	testModificaCtr();
	testStergereCtr();
	testRaport();
	testCos();
	testUndo();
	testFile();
	testRLab();
}