#include "domain.h"

string Disciplina::getDenumire() const
{
	return denumire;
}

int Disciplina::getOre() const noexcept
{
	return ore;
}

string Disciplina::getTip() const
{
	return tip;
}

string Disciplina::getCadru() const
{
	return cadru;
}

Disciplina& Disciplina::operator=(const Disciplina& ot) {
	denumire = ot.denumire;
	ore = ot.ore;
	tip = ot.tip;
	cadru = ot.cadru;
	return *this;
}

bool cmpAn_Gen_DESC(const Disciplina& o1, const Disciplina& o2) {
	if (o1.getCadru() == o2.getCadru())
		return o1.getTip() < o2.getTip();
	return o1.getCadru() < o2.getCadru();
}

bool cmpAn_Gen_ASC(const Disciplina& o1, const Disciplina& o2) {
	if (o1.getCadru() == o2.getCadru())
		return o1.getTip() > o2.getTip();
	return o1.getCadru() > o2.getCadru();
}