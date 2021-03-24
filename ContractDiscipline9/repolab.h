#pragma once
#include "repository.h"
#include <stdio.h>      /*  NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

class RepoLab :
	public Repo
{
private:
	double procent;
	std::vector<Disciplina> list;
public:

	RepoLab(double proc) :Repo(), procent{ proc } {
		procent = procent * 100;
		srand(static_cast<unsigned int>(time(nullptr)));
	}
	void modifica(const Disciplina& d)override {
		if (rand() % 100 >= procent) throw DisciplinaRepoException{ "Probabilitate!" };
		bool found = false;
		for (auto& of : list) {
			if (of.getDenumire() == d.getDenumire()) {
				of = d;
				found = true;
				return;
			}
		}
		if (found == false)
			throw DisciplinaRepoException("Nu exista nicio Disciplina cu acest titlu!");
	}
	void adauga(const Disciplina& d) override {
		if (rand() % 100 >= procent) throw DisciplinaRepoException{ "Probabilitate!" };
		if (exist(d)) {
			throw DisciplinaRepoException("Exista deja o Disciplina cu acest titlu !");
		}
		list.push_back(d);
	}
	void sterge(const Disciplina& d) override {
		if (rand() % 100 >= procent) throw DisciplinaRepoException{ "Probabilitate!" };
		if (!exist(d))
			throw DisciplinaRepoException("Nu exista Disciplina cu acest titlu!");
		else
		{
			int i = 0;
			for (auto& car : list)
			{
				if (car.getDenumire() == d.getDenumire())
					list.erase(list.begin() + i);
				i++;
			}
		}
	}
	vector<Disciplina> getAll() noexcept override {
		return list;
	}

	const Disciplina& find(string denumire) const override {
		auto rez = std::find_if(list.begin(), list.end(), [denumire](const Disciplina& d) {
			if (d.getDenumire() == denumire) return true; else return false;
			});
		if (rez != list.end())
			return *rez;
		else
			//daca nu exista arunc o exceptie
			throw DisciplinaRepoException("Nu exista nicio Disciplina cu acest titlu!");
	}

	bool exist(const Disciplina& d) const {
		try {
			find(d.getDenumire());
			return true;
		}
		catch (DisciplinaRepoException&) {
			return false;
		}
	}

	~RepoLab() = default;

};