#include "Population.h"

//コンストラクタ
Population::Population()
{
  int i;

  ind = new Individual *[POP_SIZE];
  nextInd = new Individual *[POP_SIZE];
  for (i = 0; i < POP_SIZE; i++)
  {
    ind[i] = new Individual();
    nextInd[i] = new Individual();
  }
  evaluate();
};

//デストラクタ
Population::~Population()
{
  int i;

  for (i = 0; i < POP_SIZE; i++)
  {
    delete ind[i];
    delete nextInd[i];
  }
  delete[] ind;
  delete[] ind;
};

//全ての個体を評価して、適応度順に並び替える
void Population::evaluate()
{
  int i;

  for (i = 0; i < POP_SIZE; i++)
  {
    ind[i]->evaluate();
  }
  sort(0, POP_SIZE - 1);
}
