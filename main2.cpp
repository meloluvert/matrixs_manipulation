#include <iostream>

using namespace std;

class Matriz
{

private:
    double **Mat;
    int l, c;
    double det, diagP, diagS;

public:
    /*Cria a Matriz em si*/

    Matriz(int l, int c)
    {
        this->setLines(l);
        this->setColumns(c);
    }

    /*Para que possa alocar sem passar parâmetro*/
    Matriz() {}

    void showMatriz(int n)
    { /*n é o nº da matriz*/
        cout << "Matriz " << n << "\n";
        for (int i = 0; i < l; i++)
        { // loop mostra as linhas
            /*std::cout << i + 1 << "   ";*/
            for (int j = 0; j < c; j++)
            {
                if (Mat[i][j] != '\0')
                {
                    std::cout << " " << Mat[i][j] << "|";
                }
                else
                {
                    std::cout << " " << Mat[i][j] << " |";
                }
            }
            if (i != this->getLines())
            {
                std::cout << std::endl
                          << "     __ __ __\n"
                          << std::endl;
            }
        }

        diagonais();
        getDet();
        cout << "Qtd de linhas:" << l << "\n";
        cout << "Qtd de colunas:" << c << "\n";
        cout << "Soma Diagonal principal:" << diagP << "\n";
        cout << "Soma Diagonal Secudária:" << diagS << "\n";
        cout << "Determinante:" << det << "\n";
    }
    /*Soma de Matrizes*/
    void soma(Matriz Mat2)
    { /*Vai ser a soma*/
        for (int i = 0; i < this->getLines(); i++)
        {
            for (int j = 0; j < this->getColumn(); j++)
            {

                this->setNumber(i, j, this->getNumber(i, j) + Mat2.getNumber(i, j));
            }
        }
    }

    /*Preenche com nº aleatórios*/
    void fillRandNumbers(int max)
    { /*Valor máximo dos aleatórios*/
        for (int i = 0; i < this->getLines(); i++)
        {
            for (int j = 0; j < this->getColumn(); j++)
            {
                Mat[i][j] = rand() % (max + 1); /*vai de 0 até max*/
            }
        }
        if (square())
        {
            diagonais();
            getDet();
        };
    }
    /*é quadrada?*/
    bool square()
    {
        return (c == l) ? true : false;
    }

    /*Gera o determinante*/
    void getDet()
    {
        if (diagP == 0 || diagS == 0)
        {
            return;
        }
        det = 1;
        Matriz M(l, c);
        for (int i = 0; i < l; i++)
        {
            for (int j = 0; j < c; j++)
            {
                M.Mat[i][j] = Mat[i][j];
            }
        }
        for (int i = 0; i < l - 1; i++)
        {
            for (int j = i + 1; j < l; j++)
            {
                double factor = M.Mat[j][i] / M.Mat[i][i];
                for (int k = i; k < c; k++)
                {
                    M.Mat[j][k] -= factor * M.Mat[i][k];
                }
            }
        }
        for (int i = 0; i < l; i++)
        {
            det *= M.Mat[i][i];
        }
    }

    void diagonais()
    {

        diagP = 0;
        diagS = 0;
        for (int i = 0; i < l; i++)
        {
            diagP += Mat[i][i];
            diagS += Mat[i][l - 1 - i];
        }
    }

    int getColumn()
    {
        return this->c;
    }
    int getLines()
    {
        return c;
    }
    double getNumber(int l, int c)
    {
        return Mat[l][c];
    }
    void setColumns(int c)
    {
        this->c = c;
        for (int i = 0; i < l; i++)
        {
            Mat[i] = new double[c];
        }
    }
    void setLines(int l)
    {
        this->l = l;
        Mat = new double *[l];
    }

    void setNumber(int l, int c, double n)
    {
        Mat[l][c] = n;
    }
    /*desaloca*/
    ~Matriz()
    {
        for (int i = 0; i < l; i++)
        {
            delete Mat[i];
        }
        delete[] Mat;
    }
};

int main()
{
    srand(time(NULL));
    int op, op2, op3, op4;
    double n;
    int numMatrizes;
    int l, c;
    std::cout << "Bem vindo ao Menu das Matrizes, quantas matrizesw você deseja alocar?" << std::endl;
    cin >> numMatrizes;
    /*Pede linha e colunas de cada matriz*/

    Matriz matrizes[numMatrizes];
    for (int i = 0; i < numMatrizes; i++)
    {
        cout << "Matriz" << i + 1 << "\n";
        cout << "Linhas:";
        cin >> l;
        cout << "\n";
        cout << "Colunas:";
        cin >> c;
        matrizes[i].setLines(l);
        matrizes[i].setColumns(c);
    }

    system("clear");
    do
    {
        system("clear");
        cout << "Escolha uma opção\n";
        cout << "1 - Mostrar matriz\n";
        cout << "Fazer a Matriz Transposta(falta implementar)\n";
        cout << "2 - Preecnher Matriz\n";
        cout << "3 - Alterar Matriz\n";
        cout << "4 - Somar Matrizes\n";
        cout << "5 - Multiplicar Matruizes\n";
        cin >> op;
        system("clear");
        switch (op)
        {

        case 1:
            cout << "Qual matriz?";
            cin >> op;
            matrizes[op - 1].showMatriz(op);
            cout << "Aperte Enter";
            cin.ignore().get();
            break;
        case 2:
            cout << "Qual matriz?";
            cin >> op;
            matrizes[op - 1].fillRandNumbers(9);
            cout << "Matriz preecnhida! (aperte enter)";
            cin.ignore().get();
            break;
        case 3:
            cout << "Qual matriz?";
            cin >> op;
            matrizes[op - 1].showMatriz(op);

            cout << "Qual linha e coluna?\n";
            cout << "Linha:";
            cin >> l;
            cout << "\n";
            cout << "Coluna:";
            cin >> c;
            cout << "\n";
            cout << "Número:";
            cin >> n;
            cout << "\n";
            matrizes[op - 1].setNumber(l - 1, c - 1, n);
            cout << "Alterada com sucesso(aperte enter)";
            cin.ignore().get();
        case 4:
            cout << "Quais matrizes deseja somar?";
            cout << "Matriz A:";
            cin >> op;
            cout << "Matriz B:";
            cin >> op2;

            if (matrizes[op - 1].getColumn() == matrizes[op2 - 1].getColumn() && matrizes[op - 1].getLines() == matrizes[op2 - 1].getLines())
            {
                cout << "Qual matriz você deseja desalocar para isso? " << op2 << " ou " << op;
                cin >> op3;
                if (op3 == op2)
                {
                    matrizes[op2 - 1].soma(matrizes[op - 1]);
                }
                else if (op3 == op)
                {
                    matrizes[op - 1].soma(matrizes[op2 - 1]);
                }
            }
        }

    } while (op != 4);

    return 0;
}
