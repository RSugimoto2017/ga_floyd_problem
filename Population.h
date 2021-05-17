#include "Individual.h"

class Population
{
public:
  Population();
  ~Population();
  void alternate();   //世代交代
  void printResult(); //結果表示

  Individual **ind; //現世代の個体群メンバ

private:
  void evaluate();            //個体を評価
  int select();               //親個体の選択
  void sort(int lbm, int ub); //個体を良い順にソート

  Individual **nextInd; //次世代の個体群メンバ
};
