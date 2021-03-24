#pragma once
#include "domain.h"
#include "repository.h"
#include "repocontract.h"

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
	Disciplina dAdaugata;
	Repo& repo;
public:
	UndoAdauga(Repo& repo, const Disciplina& d) : repo{ repo }, dAdaugata{ d }{}
	void doUndo() override {
		repo.sterge(dAdaugata);
	}
};

class UndoSterge : public ActiuneUndo {
	Disciplina dStearsa;
	Repo& repo;
public:
	UndoSterge(Repo& repo, const Disciplina& d) : repo{ repo }, dStearsa{ d }{}
	void doUndo() override {
		repo.adauga(dStearsa);
	}
};

class UndoModifica : public ActiuneUndo {
	Disciplina dModificata;
	Repo& repo;
public:
	UndoModifica(Repo& repo, const Disciplina& d) :repo{ repo }, dModificata{ d }{}
	void doUndo() override {
		repo.modifica(dModificata);
	}
};

class UndoAdaugaCos : public ActiuneUndo {
	Disciplina d;
	RepoContract& contract;
public:
	UndoAdaugaCos(RepoContract& contract, const Disciplina& d) : contract{ contract }, d{ d }{}
	void doUndo() override {
		contract.DeleteUndo(d.getDenumire());
	}
};