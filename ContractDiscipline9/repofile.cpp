#include "repofile.h"
#include <fstream>
#include "repository.h"
#include <assert.h>
void FileRepository::loadFromFile() {
	std::ifstream in(fName);
	if (!in.is_open()) { throw DisciplinaRepoException("Nu s-a putut deschide fisierul:" + fName); }
	while (!in.eof()) {
		std::string denumire;
		in >> denumire;
		//poate am linii goale
		if (in.eof()) break;
		int ore;
		in >> ore;
		std::string tip;
		in >> tip;
		std::string cadru;
		in >> cadru;
		Disciplina d{ denumire.c_str(),ore,tip.c_str(),cadru.c_str()};
		//Carte p{ type.c_str(),species.c_str(), price };
		FileRepository::adauga(d);
	}
	in.close();
}

void FileRepository::writeToFile() {
	std::ofstream out(fName);
	if (!out.is_open()) { std::string msg("Error open file"); throw DisciplinaRepoException(msg); }
	for (auto& p : getAll()) {
		out << p.getDenumire() << " " << p.getOre() << " " << p.getTip() << " " << p.getCadru() << std::endl;
	}
	out.close();
}