#pragma once
#include <vector>
#include <string>
#include "domain.h"

class RepoContract
{
public:
	RepoContract()noexcept;
	void Add(const Disciplina& item);
	void Delete(std::string denumire);
	Disciplina* GetByDenumire(std::string denumire);
	const std::vector<Disciplina>& getAll() const noexcept;
	int Length();
	void DeleteUndo(std::string denumire);
private:
	std::vector<Disciplina> list;
};