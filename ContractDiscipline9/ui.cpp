#include "ui.h"
#include "domain.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void ConsolaUI::adaugaContractUI() {
	string denumire;
	cout << "Denumire disciplina: ";
	cin >> denumire;

	try {
		ctr.adaugaContract(denumire);
		cout << "Disciplina " << denumire << " a fost adaugata cu succes in contract!\n";
	}
	catch (const DisciplinaRepoException & msg) {
		cout << msg << endl;
	}
}

void ConsolaUI::golesteContractUI() {
	ctr.emptyContractP();
	cout << "S-au sters cu succes toate disciplinele din contract!\n";
}

void ConsolaUI::populeazaContractUI() {
	int nrDiscipline = 0;
	cout << "Introduceti numarul de discipline: ";
	cin >> nrDiscipline;
	if (nrDiscipline > 0)
	{
		ctr.populateContractP(nrDiscipline);
		if (nrDiscipline > 1) cout << "S-au adaugat cu succes " << nrDiscipline << " discipline!\n";
		else cout << "S-a adaugat cu succes o disciplina!\n";
	}
	else cout << "Numarul introdus trebuie sa fie mai mare decat 0!\n";
}

void ConsolaUI::saveContractUI() {
	string fileName;
	cout << "Introduceti numele fisierului: ";
	cin >> fileName;
	ctr.saveToFile(fileName);
	cout << "S-a salvat cu succes!\n";
}

void ConsolaUI::afiseazaContractUI() {
	if (ctr.sizeContract() == 0)
		cout << "Contractul dvs. este gol!\n";
	else for (const auto& p : ctr.getAllProductsContract()) {
		cout << "   Denumire: " << p.getDenumire() << "   Ore: " << p.getOre();
		cout << "   Tip: " << p.getTip() << "   Cadru: " << p.getCadru() << endl;
	}
}

void ConsolaUI::tipareste(const vector<Disciplina>& discipline) {
	if (discipline.size() == 0) cout << "Nu exista discipline in lista!\n";
	else {
		cout << "Discipline:\n";
		for (const auto& d : discipline) {
			cout << ' ' << d.getDenumire() << ' ' << d.getOre() << ' ' << d.getTip() << ' ' << d.getCadru() << '\n';
		}
		cout << "Sfarsit lista discipline\n";
	}
}

void ConsolaUI::adaugaUI() {
	string denumire, tip, cadru;
	int ore;
	cout << "Dati denumire: ";
	cin >> denumire;
	cout << "Dati ore: ";
	cin >> ore;
	cout << "Dati tip: ";
	cin >> tip;
	cout << "Dati cadru: ";
	cin >> cadru;
	ctr.addDisciplina(denumire, ore, tip, cadru);
	cout << "Disciplina  " << denumire << " a fost adaugata cu succes!" << endl;
}

void ConsolaUI::modificaUI()
{
	string denumire, tip, cadru;
	int ore;
	cout << "Dati denumire: ";
	cin >> denumire;
	cout << "Dati ore: ";
	cin >> ore;
	cout << "Dati tip: ";
	cin >> tip;
	cout << "Dati cadru: ";
	cin >> cadru;
	ctr.modifica(denumire, ore, tip, cadru);
	cout << "Disciplina " << denumire << " a fost modificata cu succes!" << endl;
}

void ConsolaUI::raportUI()
{
	vector<DisciplinaDTO> lista;
	ctr.raport(lista);
	for (auto item : lista) {
		cout << item.denumire << " - Tip: " << item.tip << " (count=" << item.count << ")\n";
	}
}

void ConsolaUI::stergeUI()
{
	string denumire;

	cout << "Dati denumire: ";
	cin >> denumire;

	ctr.sterge(denumire);
	cout << "Disciplina " << denumire << " a fost stearsa cu succes!" << endl;
}

void ConsolaUI::start() {
	while (true) {
		cout << "Numarul curent de discipline in contract este: " << ctr.getAllProductsContract().size() << endl;
		cout << "Meniul este:\n";
		cout << "1. Adauga\n2. Sterge\n3. Modifica\n4. Sortare dupa denumire crescator\n5. Sortare dupa denumire descrescator\n";
		cout << "6. Sortare dupa ore crescator\n7. Sortare dupa ore descrescator\n8. Sortare dupa tip+cadru crescator\n";
		cout << "9. Sortare dupa tip+cadru descrescator\n10. Filtrare dupa denumire\n11. Filtrare dupa ore\n12. Tipareste\n";
		cout << "13. Raport\n14. Print contract\n15. Adauga contract\n16. Goleste contract\n17. Export contract\n18. Adaugare random\n";
		cout << "19. Total ore\n20. Undo\n0. Exit\nDati comanda: ";
		int cmd;
		cin >> cmd;
		try {
			if (cmd == 1)
				adaugaUI();
			else if (cmd == 2)
				stergeUI();

			else if (cmd == 3)
				modificaUI();
			else if (cmd == 4)
				tipareste(ctr.sortByDenumire(false));
			else if (cmd == 5)
				tipareste(ctr.sortByDenumire(true));
			else if (cmd == 6)
				tipareste(ctr.sortByOre(false));
			else if (cmd == 7)
				tipareste(ctr.sortByOre(true));
			else if (cmd == 8)
				tipareste(ctr.sortByCadruTip(true));
			else if (cmd == 9)
				tipareste(ctr.sortByCadruTip(false));
			else if (cmd == 10) {
				cout << "Dati denumirea: ";
				string denumire1;
				cin >> denumire1;
				tipareste(ctr.filtrareDenumire(denumire1));
			}
			else if (cmd == 11)
			{
				cout << "Dati nr ore: ";
				int ore1;
				cin >> ore1;
				tipareste(ctr.filtrareOre(ore1));
			}
			else if (cmd == 12)
				tipareste(ctr.getAll());
			else if (cmd == 13)
				raportUI();
			else if (cmd == 14)
				afiseazaContractUI();
			else if (cmd == 15)
				adaugaContractUI();
			else if (cmd == 16)
				golesteContractUI();
			else if (cmd == 17)
				saveContractUI();
			else if (cmd == 18)
				populeazaContractUI();
			else if (cmd == 19)
				cout << "Suma orelor este: " << ctr.totalore() << endl;
			else if (cmd == 20)
				ctr.undo();
			else if (cmd == 0)
			{
				return;
			}
			else
				cout << "Comanda invalida\n";
		}
		catch (const DisciplinaRepoException & ex) {
			cout << ex << '\n';
		}
		catch (const ValidateException & ex) {
			cout << ex << '\n';
		}
	}
}