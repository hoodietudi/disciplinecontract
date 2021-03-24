#pragma once
#include "domain.h"
#include <vector>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <map>
using namespace std;
class Repo {
public:
	virtual bool exist(const Disciplina& d) const = 0;
	virtual void adauga(const Disciplina& d) = 0;
	virtual const Disciplina& find(string denumire) const = 0;
	virtual vector<Disciplina> getAll() noexcept = 0;
	virtual void sterge(const Disciplina& d) = 0;
	virtual void modifica(const Disciplina& d) = 0;
};

class DisciplinaRepo : public Repo {

	//map<string, Disciplina> repo;
	vector<Disciplina> all;
	//bool exist(const Disciplina& c) const;

public:
	bool exist(const Disciplina& c) const override;
	/*
	constructor
	*/
	DisciplinaRepo() = default;

	//nu permitem copierea de obiecte
	DisciplinaRepo(const DisciplinaRepo& ot) = delete;

	/*
	Salvare carte
	arunca exceptie daca mai exista o carte cu acelasi id
	*/
	void adauga(const Disciplina& c)override;

	/*
	Cauta
	arunca exceptie daca nu exista carte
	*/
	const Disciplina& find(string denumire) const override;

	/*
	returneaza toate cartile salvate
	*/
	vector<Disciplina> getAll() noexcept override;

	/*
	sterge o carte
	*/
	void sterge(const Disciplina& d) override;

	/*
	modifica o carte
	*/
	void modifica(const Disciplina& d) override;

};

/*
Folosit pentru a semnala situatii exceptionale care pot aparea in repo
*/
class DisciplinaRepoException {
	string msg;
public:
	DisciplinaRepoException(string m) :msg{ m } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const DisciplinaRepoException& ex);
};

ostream& operator<<(ostream& out, const DisciplinaRepoException& ex);


void testeRepo();