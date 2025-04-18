#include <iostream>
#include <ctime>
#include <string>

using namespace std;

const int numMax = 100;

int main() {
    srand(time(0));

    int tabuleiro;
    string navios[numMax][numMax];
    string tabuleiroVisivel[numMax][numMax];

    cout << "\t=== BATALHA NAVAL ===" << endl;
    cout << "\n=== Escolha o tamanho do seu tabuleiro naval 🌊🚤 ===\n" << endl;
    cout << "Qual vai ser o tamanho do seu tabuleiro: ";
    cin >> tabuleiro;

    cout << "\n=== O seu tabuleiro é de " << tabuleiro << " por " << tabuleiro << " ===\n" << endl;

    for (int i = 0; i < tabuleiro; i++) {
        for (int j = 0; j < tabuleiro; j++) {
            navios[i][j] = "🌊";
        }
    }

    for (int i = 0; i < tabuleiro; i++) {
        for (int j = 0; j < tabuleiro; j++) {
            cout << navios[i][j] << " ";
        }
        cout << endl;
    }

    for (int i = 0; i < tabuleiro; i++) {
        for (int j = 0; j < tabuleiro; j++) {
            navios[i][j] = "🌊";
            tabuleiroVisivel[i][j] = "🌊"; // <-- novo
        }
    }

    int totalNavios = tabuleiro;  
    int colocados = 0;

    while (colocados < totalNavios){
        int i = rand() % tabuleiro;
        int j = rand() % tabuleiro;

        if (navios[i][j] == "🌊") {  
            navios[i][j] = "🚢";  
            colocados++;
        }
    }

    const int totalBombas = 3;
    int bombasColocadas = 0;

    while (bombasColocadas < totalBombas){
        int i = rand() % tabuleiro;
        int j = rand() % tabuleiro;

        if (navios[i][j] == "🌊") {
            navios[i][j] = "💣";
            bombasColocadas++;
        }
    }

    int tentativaLinha, tentativaColuna;
    int acertos = 0;

    while (acertos < totalNavios) {
        cout << "\n=== 🏹  Tente acertar um navio! (" << acertos << "/" << totalNavios << ") ===\n";
        cout << "Digite a linha (0 até " << tabuleiro - 1 << "): ";
        cin >> tentativaLinha;
        cout << "Digite a coluna (0 até " << tabuleiro - 1 << "): ";
        cin >> tentativaColuna;

        if (tentativaLinha >= 0 && tentativaLinha < tabuleiro && tentativaColuna >= 0 && tentativaColuna < tabuleiro) {
            
            if (tabuleiroVisivel[tentativaLinha][tentativaColuna] == "💥" || tabuleiroVisivel[tentativaLinha][tentativaColuna] == "❌") {
                cout << "\n⚠️ Você já tentou essa posição. Tente outra!\n";
            } else if (navios[tentativaLinha][tentativaColuna] == "🚢") {
                cout << "\n 💥 BOOM! Você acertou um navio! 🚢💥\n";
                tabuleiroVisivel[tentativaLinha][tentativaColuna] = "💥";
                acertos++;
            } else if (navios[tentativaLinha][tentativaColuna] == "💣") {
                cout << "\n💣 KABOOM! Você acertou uma bomba! Fim de jogo. 💥💥💥\n";
                tabuleiroVisivel[tentativaLinha][tentativaColuna] = "💣";

                cout << "\n=== 💥 Tabuleiro revelado! 💥 ===\n";
                for (int i = 0; i < tabuleiro; i++) {
                    for (int j = 0; j < tabuleiro; j++) {
                        if (navios[i][j] == "🚢" || navios[i][j] == "💣") {
                            tabuleiroVisivel[i][j] = navios[i][j];
                        }
                        cout << tabuleiroVisivel[i][j] << " ";
                    }
                    cout << endl;
                }
                break;
            } else {
                cout << "\n 🌊 VIXI! Só água por aqui...\n";
                tabuleiroVisivel[tentativaLinha][tentativaColuna] = "❌";

                int naviosAoRedor = 0;
                for (int x = tentativaLinha - 1; x <= tentativaLinha + 1; x++) {
                    for (int y = tentativaColuna - 1; y <= tentativaColuna + 1; y++) {
                        if (x >= 0 && x < tabuleiro && y >= 0 && y < tabuleiro) {
                            if (!(x == tentativaLinha && y == tentativaColuna)) {
                                if (navios[x][y] == "🚢") {
                                    naviosAoRedor++;
                                }
                            }
                        }
                    }
                }
                cout << "📡 Radar: Existem " << naviosAoRedor << " navio(s) ao redor dessa posição.\n";
            }

            cout << "\nTabuleiro após sua tentativa:\n";
            for (int i = 0; i < tabuleiro; i++) {
                for (int j = 0; j < tabuleiro; j++) {
                    cout << tabuleiroVisivel[i][j] << " ";
                }
                cout << endl;
            }

        } else {
            cout << "\n❌ Coordenadas inválidas. Que tal tentar dentro do tabuleiro!\n";
        }
    }

    if (acertos == totalNavios) {
        cout << "\n🎉 Parabéns! Você encontrou todos os navios! Fim de jogo. 🚢🏁\n";
    }

    return 0;
}
