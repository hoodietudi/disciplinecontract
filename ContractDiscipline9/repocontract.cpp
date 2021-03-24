#include "repocontract.h"
#include "domain.h"
#include "repository.h"
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

RepoContract::RepoContract()noexcept
{
	//cout << "REPO\n";
}

void RepoContract::Add(const Disciplina& item)
{
	list.push_back(item);
}

void RepoContract::Delete(string denumire)
{
	list.erase(remove_if(list.begin(), list.end(), [denumire](const Disciplina a) { return a.getDenumire() == denumire; }), list.end());
}

const vector<Disciplina>& RepoContract::getAll() const noexcept {
	return list;
}

Disciplina* RepoContract::GetByDenumire(std::string denumire) {
	//for (Activitate &var : list) if (var.Get_Titlu() == titlu) return &var;	
	auto x = find_if(list.begin(), list.end(), [denumire](const Disciplina& a) {return a.getDenumire() == denumire; });
	if (x != list.end())
		return &*x;
	throw DisciplinaRepoException{ "Disciplina inexistenta!\n" };
}

int RepoContract::Length()
{
	return list.size();
}

void RepoContract::DeleteUndo(std::string denumire)
{
	int i = 0;
	for (auto& c : list)
	{
		if (c.getDenumire() == denumire)
		{
			list.erase(list.begin() + i); return;
		}
		else i++;
	}
}