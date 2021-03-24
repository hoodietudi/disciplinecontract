#pragma once
#include "service.h"
#include "domain.h"
#include "undo.h"

class ConsolaUI {
	DisciplinaStore& ctr;

	void adaugaContractUI();

	void golesteContractUI();

	void populeazaContractUI();

	void afiseazaContractUI();

	void saveContractUI();

	/*
	Citeste datele de la tastatura si adauga o disciplina
	arunca exceptie daca: nu se poate salva, nu e valid
	*/
	void adaugaUI();
	/*
	Tipareste o lista de carti la consola
	*/
	void tipareste(const vector<Disciplina>& discipline);

	/*
	Citeste datele de la tastatura si modifica o disciplina
	exceptii: date invalide
	*/
	void modificaUI();

	void stergeUI();

	void raportUI();

	void randomUI();

public:
	ConsolaUI(DisciplinaStore& ctr) noexcept :ctr{ ctr } {
	}
	//nu permitem copierea obiectelor
	ConsolaUI(const ConsolaUI& ot) = delete;

	void start();

};