#pragma once
#include <string>
using namespace std;
class DisciplinaDTO
{
public:
	string tip;
	string denumire;
	DisciplinaDTO(string _tip) :tip{ _tip } {

	}
	DisciplinaDTO() = default;
	DisciplinaDTO(const DisciplinaDTO& ot) = default;

	//RULE OF 3
	// 2.Operator assignment
	//void operator=(const ListaDinamica& ot);
	// 3.Dtor
	~DisciplinaDTO() = default;
	DisciplinaDTO(DisciplinaDTO&&) = default;
	DisciplinaDTO& operator=(DisciplinaDTO&&) = default;


	bool operator==(const DisciplinaDTO& ot) noexcept;
	int count = 0;
};
