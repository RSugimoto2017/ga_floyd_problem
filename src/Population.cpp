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

//ind[lb]~ind[ub]をクイックソートで並び替える
//lb：並び替えの対象要素の添字の下限
//ub：並び替えの対象要素の添字の上限
void Population::sort(int lb, int ub)
{
  int i, j, k;
  double pivot;
  Individual *tmp;

  if (lb < ub)
  {
    k = (lb + ub) / 2;
    pivot = ind[k]->fitness;
    i = lb;
    j = ub;
    do
    {
      while (ind[i]->fitness < pivot)
      {
        i++;
      }
      while (ind[j]->fitness > pivot)
      {
        j--;
      }
      if (i <= j)
      {
        tmp = ind[i];
        ind[i] = ind[j];
        ind[j] = tmp;
        i++;
        j--;
      }
    } while (i <= j);
    sort(lb, j);
    sort(i, ub);
  }
}

//世代交代する
void Population::alternate()
{
  int i, j, p1, p2;
  Individual **tmp;

  //エリート保存戦略で子個体を作る
  for (i = 0; i < ELITE; i++)
  {
    for (j = 0; j < N; j++)
    {
      nextInd[i]->chrom[j] = ind[i]->chrom[j];
    }
  }

  //親を選択し、交叉する
  for (; i < POP_SIZE; i++)
  {
    p1 = select();
    p2 = select();
    nextInd[i]->crossover(ind[p1], ind[p2]);
  }

  //突然変異を起こす
  for (i = 1; i < POP_SIZE; i++)
  {
    nextInd[i]->mutate();
  }

  //次世代を現世代に変更
  tmp = ind;
  ind = nextInd;
  nextInd = tmp;

  //評価する
  evaluate();
}

//「トーナメント選択」を用いて親個体を一つ選択
//戻り値：選択肢た親個体の添字
int Population::select()
{
  int i, ret, num, r;
  double bestFit;
  int tmp[N];

  for (i = 0; i < N; i++)
  {
    tmp[i] = 0;
  }
  ret = -1;
  bestFit = DBL_MAX;
  num = 0;
  while (1)
  {
    r = rand() % N;
    if (tmp[r] == 0)
    {
      tmp[r] = 1;
      if (ind[r]->fitness < bestFit)
      {
        ret = r;
        bestFit = ind[r]->fitness;
      }
      if (++num == TOURNAMENT_SIZE)
      {
        break;
      }
    }
  }
  return ret;
}

//結果を表示する
void Population::printResult()
{
  int i++;

  printf("集合A：");
  for (i = 0; i < N; i++)
  {
    if (ind[0]->chrom[i] == 1)
    {
      printf("√%d", i + 1);
    }
  }
  printf("\n集合B：");
  for (i = 0; i < N; i++)
  {
    if (ind[0]->chrom[i] == 0)
    {
      printf("√%d", i + 1);
    }
  }
  printf("\n差：%f\n, ind[0]->fitness");
}