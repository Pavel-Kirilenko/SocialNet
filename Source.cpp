#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class SocialNetwork {
private:
    vector<vector<int>> adjacencyMatrix;
    int numVertices;

public:
    SocialNetwork(int numVertices) {
        this->numVertices = numVertices;
        adjacencyMatrix.resize(numVertices, vector<int>(numVertices, 0));
    }

    // Добавление связи между двумя пользователями (ребро графа)
    void addConnection(int person1, int person2) {
        adjacencyMatrix[person1][person2] = 1;
        adjacencyMatrix[person2][person1] = 1; // для неориентированного графа
    }

    // Проверка и вывод всех знакомых через "три рукопожатия"
    void findConnectionsWithinThreeHandshakes(int startPerson) {
        vector<bool> visited(numVertices, false);
        queue<pair<int, int>> q; // Пара: человек и количество рукопожатий

        q.push({startPerson, 0});
        visited[startPerson] = true;

        cout << "Знакомые через три рукопожатия от " << startPerson << ":\n";

        while (!q.empty()) {
            int currentPerson = q.front().first;
            int handshakeCount = q.front().second;
            q.pop();

            if (handshakeCount < 3) {
                for (int i = 0; i < numVertices; ++i) {
                    if (adjacencyMatrix[currentPerson][i] == 1 && !visited[i]) {
                        q.push({i, handshakeCount + 1});
                        visited[i] = true;

                        if (handshakeCount + 1 <= 3) {
                            cout << "Человек " << currentPerson << " знаком с человеком " << i 
                                 << " через " << handshakeCount + 1 << " рукопожатие(ий).\n";
                        }
                    }
                }
            }
        }
    }
};

int main() {
    setlocale(LC_ALL, "");
    system("chcp 1251");   // строка для корректного отображения кириллических символов
    int numPeople = 6;
    SocialNetwork network(numPeople);

    // Добавляем связи (ребра графа)
    network.addConnection(0, 1);
    network.addConnection(1, 2);
    network.addConnection(2, 3);
    network.addConnection(3, 4);
    network.addConnection(4, 5);

    // Проверка знакомых через три рукопожатия для человека 0
    network.findConnectionsWithinThreeHandshakes(0);

    return 0;
}