#pragma once
#include <string>
#include <iostream>
#include <vector>
using std::vector;
using std::string;
using std::cout;

class Disciplina
{
private:
	string denumire;
	int ore;
	string tip;
	string cadru;

public:

	Disciplina() = default;
	/*
	Constructor
	*/
	Disciplina(const string denumire, const int ore, const string tip, const string cadru) :denumire{ denumire }, ore{ ore }, tip{ tip }, cadru{ cadru }{}

	/*
	Copy constructor
	*/
	Disciplina(const Disciplina& ot) : denumire{ ot.denumire }, ore{ ot.ore }, tip{ ot.tip }, cadru{ ot.cadru }{ }

	/*
	returns carte's name
	*/
	string getDenumire() const;

	/*
	returns titlu
	*/
	int getOre() const noexcept;

	/*
	returneaza genul cartii
	*/
	string getTip() const;

	/*
	returns anul cartii
	*/
	string getCadru() const;

	/*
	define =
	*/
	Disciplina& operator=(const Disciplina& ot);

};

bool cmpAn_Gen_DESC(const Disciplina& o1, const Disciplina& o2);
bool cmpAn_Gen_ASC(const Disciplina& o1, const Disciplina& o2);

void testCreateDisciplina();