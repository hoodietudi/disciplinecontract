#pragma once
#include "DisciplinaDTO.h"
#include "domain.h"
#include "repository.h"
#include <map>
#include <string>
#include <vector>
#include <functional>
#include "validator.h"
#include "undo.h"
#include "repocontract.h"

using namespace std;


class DisciplinaStore {
	Repo& rep;
	DisciplinaValidator& val;
	RepoContract& contractRepository;
	std::vector<unique_ptr<ActiuneUndo>> undoActions;
	



public:
	DisciplinaStore(Repo& rep, DisciplinaValidator& val, RepoContract& contractRepository) noexcept :rep{ rep }, val{ val }, contractRepository{ contractRepository }{
	}
	//nu permitem copierea de obiecte CarteStore
	DisciplinaStore(const DisciplinaStore& ot) = delete;
	/*
	 returneaza toate cartile in ordinea in care au fost adaugate
	*/
	const vector<Disciplina> getAll() noexcept {
		return rep.getAll();
	}

	/*
	Adauga o noua carte
	arunca exceptie daca: nu se poate salva, nu este valid
	*/
	void addDisciplina(const string& denumire, int ore, const string& tip, const string& cadru);


	//vector<unique_ptr<ActiuneUndo>> undoActions;
	/*
	Sorteaza dupa titlu crescator
	*/
	vector<Disciplina> sortByDenumire(const bool reverse);

	/*
	Sorteaza dupa autor crescator
	*/
	vector<Disciplina> sortByOre(const bool reverse);

	/*
	Sorteaza dupa gen+an crescator
	*/
	vector<Disciplina>sortByCadruTip(const bool reverse);

	/*
	returneaza doar cartile cu titlul dat
	*/
	vector<Disciplina> filtrareDenumire(const string denumire);

	/*
	returneaza doar cartile aparute in anul dat
	*/
	vector<Disciplina> filtrareOre(int ore);

	/*
	Sterge o carte cu un titlu dat
	Exceptii: nu exista carte cu cu titlul dat
	*/
	void sterge(string denumire);

	/*
	Modifica datele despre cartea cu titlu si autor dat
	Exceptii: datele introduse sunt invalide, nu exista carte cu titlul introdus
	*/
	void modifica(const string denumire, int ore, const string tip, const string cadru);

	void raport(std::vector<DisciplinaDTO>& output);


	int totalore();

	void adaugaContract(const string& denumire);

	void emptyContractP();

	void populateContractP(const int& nrProduse);

	const vector<Disciplina>& getAllProductsContract();

	void saveToFile(const string& fileName);

	int sizeContract() const;

	void undo();


	vector<Disciplina> generalSort(bool (*maiMicF)(const Disciplina&, const Disciplina&));
	/*
	Functie generala de filtrare
	fct - poate fi o functie
	fct - poate fi lambda, am folosit function<> pentru a permite si functii lambda care au ceva in capture list
	returneaza doar animalele care trec de filtru (fct(c)==true)
	*/
	vector<Disciplina> filtreaza(function<bool(const Disciplina&)> fct);

};
void testCtr();