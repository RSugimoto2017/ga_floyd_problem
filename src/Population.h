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
  void evaluate();           //個体を評価
  int select();              //親個体の選択
  void sort(int lb, int ub); //個体を良い順にソート
  //double trFit[POP_SIZE];     //適応度を変換した値(ルーレット選択用変数)
  //double denom;               //ルーレット選択の確率を求める時の分母(ルーレット選択用変数)

  Individual **nextInd; //次世代の個体群メンバ
};
