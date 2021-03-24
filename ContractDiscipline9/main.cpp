#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h> 

#include "repofile.h"
#include "repocontract.h"
#include "domain.h"
#include "validator.h"
#include "DisciplinaDTO.h"
#include "repository.h"
#include "service.h"
#include "ui.h"
#include "undo.h"
#include "repolab.h"

void run_all_tests()
{
	testValidator();
	testeRepo();
	//testFile();
	testCtr();
}

void adaugacateva(DisciplinaStore& ctr)
{
	ctr.addDisciplina("a", 4, "a", "a");
	ctr.addDisciplina("b", 2, "b", "b");
	ctr.addDisciplina("c", 8, "c", "c");
	ctr.addDisciplina("d", 2, "d", "d");
	ctr.addDisciplina("e", 5, "e", "e");
}

void run()
{
	//DisciplinaRepo rep;
	FileRepository repF("discipline.txt");
	RepoLab repN(0.75);
	DisciplinaValidator val;
	RepoContract contract;
	DisciplinaStore ctr{ repF,val,contract };
	//adaugacateva(ctr);//adaug cateva discipline
	ConsolaUI ui{ ctr };
	ui.start();
}

int main()
{
	//run_all_tests();
	run();
	if (_CrtDumpMemoryLeaks())
	{
		cout << "Exista leakuri";
	}
	return 0;
}