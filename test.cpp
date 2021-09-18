#include <iostream>
#include <conio.h>
#include <cmath>
using namespace std;

class xyz {
public:
  double x, y, z;
};

bool NotIntersectPlaneLine;

xyz CreateVector(xyz A, xyz B) {
  xyz m;
  m.x = B.x - A.x;
  m.y = B.y - A.y;
  m.z = B.z - A.z;
  return m;
}

xyz VectorProduct(xyz A, xyz B) {
  xyz VP;
  VP.x = A.y * B.z - A.z * B.y;
  VP.y = A.z * B.x - A.x * B.z;
  VP.z = A.x * B.y - A.y * B.z;
  return VP;
}

double DotProduct(xyz A, xyz B) {
  //Skalyarnoe proizvedenie
  double vsp;
  vsp = A.x * B.x + A.y * B.y + A.z * B.z;
  return vsp;
}

void Normalize(xyz &A) {
  double R, mlr;

  mlr = sqrt(pow(A.x, 2) + pow(A.y, 2) + pow(A.z, 2));
  A.x = A.x / mlr;
  A.y = A.y / mlr;
  A.z = A.z / mlr;
}

xyz PlaneIntersectLine(xyz A, xyz B, xyz C, xyz X, xyz Y) {
  xyz rv, N, V, W;
  double e, d;

  NotIntersectPlaneLine = true;
  N = VectorProduct(CreateVector(A, B), CreateVector(A, C));
  Normalize(N);
  V = CreateVector(X, A);

  d = DotProduct(N, V);
  W = CreateVector(X, Y);

  e = DotProduct(N, W);

  if(e != 0) {
    rv.x = X.x + W.x * d / e;
    rv.y = X.y + W.y * d / e;
    rv.z = X.z + W.z * d / e;
    NotIntersectPlaneLine = false;
  }
  return rv;
}

int main(int argc, char *argv[]) {
  double spm;
  xyz D, E, F, G, H, I;

  D.x = 0;//A
  D.y = 0;
  D.z = 0;
  E.x = 1;//B
  E.y = 0;
  E.z = 0;
  F.x = 1;//C
  F.y = 0;
  F.z = 1;

  G.x = 1;//X(1)
  G.y = 1;
  G.z = 1;
  H.x = 5;//Y(2)
  H.y = 0;
  H.z = 0;
  /*G.x = 1;//X(1)
  G.y = 1;
  G.z = 1;
  H.x = 1;//Y(2)
  H.y = 1;
  H.z = 0;*/
  /*G.x = 0;//X(1)
  G.y = 1;
  G.z = 1;
  H.x = -1;//Y(2)
  H.y = 2;
  H.z = 1;*/
  I = PlaneIntersectLine(D, E, F, G, H);//O
  if(NotIntersectPlaneLine) {//Ne peresekaet
    cout << "Pryamaya parallelna ploskosti.";
    getch();
    return 0;
  }
  //I=O
  spm = DotProduct(CreateVector(I, G), CreateVector(I, H));
  cout << "spm = " << spm << '\n';
  if(spm <= 0) {
    //Ploskost peresekaet otrezok
    cout << "PLOSKOST PERESEKAET OTREZOK.\n";
  }
  cout << "Tochka peresecheniya:\n";
  cout << "X = " << H.x << '\n';
  cout << "Y = " << H.y << '\n';
  cout << "Z = " << H.z;

  getch();
  return 0;
}
//---------------------------------------------------------------------------
