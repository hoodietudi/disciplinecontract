#pragma once
#include "repository.h"
#include "domain.h"
#include <string>
using namespace std;
class FileRepository :
	public Repo
{
private:
	std::vector<Disciplina> list;
	std::string fName;
	void loadFromFile();
	void writeToFile();
public:
	void modifica(const Disciplina& d)override {
		bool found = false;
		for (auto& of : list) {
			if (of.getDenumire() == d.getDenumire()) {
				of = d;
				found = true;
				writeToFile();
				return;
			}
		}
		if (found == false)
			throw DisciplinaRepoException("Nu exista nicio Disciplina cu acest titlu!");
	}
	FileRepository(std::string fName) :Repo(), fName{ fName } {
		loadFromFile();//incarcam datele din fisier
	}
	void adauga(const Disciplina& d) override {
		//Repository::Add(p);//apelam metoda din clasa de baza
		if (exist(d)) {
			throw DisciplinaRepoException("Exista deja o Disciplina cu acest titlu !");
		}
		list.push_back(d);
		writeToFile();
	}
	void sterge(const Disciplina& d) override {
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
		writeToFile();
	}
	vector<Disciplina> getAll() noexcept override {
		return list;
	}

	const Disciplina& find(string denumire) const override {
		auto rez = std::find_if(list.begin(), list.end(), [denumire](const Disciplina& d) {
			if (d.getDenumire() == denumire) return true;
			else return false;
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

	~FileRepository() = default;
};

//void testFile()