#include "Individual.h"

//コンストラクタ
Individual ::Individual()
{
  int i;

  for (i = 0; i < N; i++)
  {
    chrom[i] = rand() % 2;
  }
  fitness = 0.0;
}

//デストラクタ
Individual::~Individual()
{
}

//適応度を算出
void Individual::evaluate()
{
  int i;

  fitness = 0.0;
  for (i = 0; i < N; i++)
  {
    fitness += (chrom[i] * 2 - 1) * sqrt((double)i + 1);
  }
  fitness = fabs(fitness);
}

//p1とp2から「二点交叉」で作った子にする
//p1:親個体1
//p2:親個体2
void Individual::crossover(Individual *p1, Individual *p2)
{
  int point1, point2, tmp, i;

  point1 = rand() % (N - 1);
  point2 = (point1 + (rand() % (N - 2) + 1)) % (N - 1);
  if (point1 > point2)
  {
    tmp = point1;
    point1 = point2;
    point2 = tmp;
  }
  for (i = 0; i <= point1; i++)
  {
    chrom[i] = p1->chrom[i];
  }
  for (; i <= point2; i++)
  {
    chrom[i] = p2->chrom[i];
  }
  for (; i < N; i++)
  {
    chrom[i] = p1->chrom[i];
  }
}

void Individual::mutate()
{
  int i;

  for (i = 0; i < N; i++)
  {
    if (RAND_01 < MUTATE_PROB)
    {
      chrom[i] = 1 - chrom[i];
    }
  }
}