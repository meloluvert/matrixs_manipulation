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
                std::cout << Mat[i][j] << "|"
                          << "\t";
            }
            if (i != this->getLines())
            {
                std::cout << std::endl;
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
    void soma(Matriz A, Matriz B)
    {
        int soma;
        for (int i = 0; i < this->getLines(); i++)
        {
            for (int j = 0; j < this->getColumn(); j++)
            {
                soma = A.getNumber(i, j) + B.getNumber(i, j);
                this->setNumber(i, j, soma);
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
    void userFill()
    {
        double n;
        for (int i2 = 0; i2 < getLines(); i2++)
        {

            for (int j2 = 0; j2 < getColumn(); j2++)
            {
                cout << "Matriz " << n << "\n";
                for (int i = 0; i < l; i++)
                { // loop mostra as linhas
                    /*std::cout << i + 1 << "   ";*/
                    for (int j = 0; j < c; j++)
                    {
                        if (i == i2 && j2 == j)
                        {
                            std::cout << "x";
                        }
                        else
                        {
                            std::cout << Mat[i][j];
                        }
                        cout << "|"
                             << "\t";
                    }
                    if (i != this->getLines())
                    {
                        std::cout << std::endl;
                    }
                }
                std::cout << "Linha:" << i2 + 1 << std::endl;
                std::cout << "Coluna:" << j2 + 1 << std::endl;
                std::cout << "Número:";
                std::cin >> n;
                setNumber(i2, j2, n);
            }
        }
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
        return l;
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
    void multiplica(Matriz A, Matriz B)
    {
        for (int i = 0; i < A.getLines(); i++)
            for (int j = 0; j < B.getColumn(); j++)
                Mat[i][j] = 0;

        for (int i = 0; i < A.getLines(); i++)
            for (int j = 0; j < B.getColumn(); j++)
                for (int k = 0; k < A.getColumn(); k++)
                    Mat[i][j] += A.getNumber(i, k) * B.getNumber(k, j);
    };
    void transposta()
    {
        Matriz T(c, l);
        for (int i = 0; i < l; i++)
        {
            for (int j = 0; j < c; j++)
            {
                T.setNumber(j, i, Mat[i][j]);
            }
        }
        this->setLines(c);
        this->setColumns(l);
        for (int i = 0; i < getLines(); i++)
            for (int j = 0; j < getColumn(); j++)
                this->setNumber(i, j, T.getNumber(i, j));
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
    std::cout << "Bem vindo ao Menu das Matrizes, quantas matrizes você deseja alocar?" << std::endl;
    cin >> numMatrizes;
    /*Pede linha e colunas de cada matriz*/

    Matriz matrizes[numMatrizes];
    for (int i = 0; i < numMatrizes; i++)
    {
        cout << "Matriz " << i + 1 << "\n";
        cout << "Linhas:";
        cin >> l;
        cout << "Colunas:";
        cin >> c;
        matrizes[i].setLines(l);
        matrizes[i].setColumns(c);
        cout << "=========" << endl;
    }

    system("clear");
    do
    {
        system("clear");
        cout << "Menu das Matrizes\n";
        cout << "1 - Mostrar matriz\n";
        cout << "2 - Preecnher Matriz\n";
        cout << "3 - Alterar Matriz\n";
        cout << "4 - Somar Matrizes\n";
        cout << "5 - Multiplicar Matruizes\n";
        cout << "6 - Transposição\n";
        cout << "7 - Finalizar\n";
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
            cout << "1 - Digitado\n";
            cout << "2 - Aleatoriamente\n";
            cin >> op2;
            if (op2 == 1)
            {
                matrizes[op - 1].userFill();
            }
            else if (op2 == 2)
            {
                matrizes[op - 1].fillRandNumbers(9);
            }
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
            cout << "Alterada com sucesso! (aperte enter)";
            cin.ignore().get();
            break;
        case 4:
            cout << "Quais matrizes deseja somar?";
            cout << "Matriz A:";
            cin >> op;
            cout << "Matriz B:";
            cin >> op2;

            if (matrizes[op - 1].getColumn() == matrizes[op2 - 1].getColumn() && matrizes[op - 1].getLines() == matrizes[op2 - 1].getLines())
            {
                cout << "Qual matriz você deseja desalocar para isso? ";
                cin >> op3;

                matrizes[op3 - 1].setLines(matrizes[op2 - 1].getLines());
                matrizes[op3 - 1].setColumns(matrizes[op - 1].getColumn());
                matrizes[op3 - 1].soma(matrizes[op2 - 1], matrizes[op - 1]);
            }
            else
            {
                cout << endl << "As Matrizes não são do mesmo tipo";
                cin.ignore().get();
            }
            break;

        case 5:
            cout << "Quais matrizes deseja multiplicar?";
            cout << "Matriz A:";
            cin >> op;
            cout << "Matriz B:";
            cin >> op2;

            if (matrizes[op - 1].getColumn() == matrizes[op2 - 1].getLines())
            {
                cout << "Qual matriz você deseja desalocar para isso? ";
                cin >> op3;
                matrizes[op3 - 1].setLines(matrizes[op - 1].getLines());
                matrizes[op3 - 1].setColumns(matrizes[op2 - 1].getColumn());
                matrizes[op3 - 1].multiplica(matrizes[op - 1], matrizes[op2 - 1]);
            }
            break;
        case 6:
            cout << "Em qual matriz você deseja fazer a transposição? ";
            cin >> op;
            matrizes[op - 1].transposta();
            cout << "Transposta com sucesso! (aperte enter)";
            cin.ignore().get();
            break;
        case 7:
            return 0;
        }
    } while (op != 7);

    return 0;
}
