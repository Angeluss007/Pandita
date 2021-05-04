/********************************************************                                           *
*             Mauricio Istúriz - 28.286.521             *
*             Karla Colmenarez - 28.425.101             *
*             Leonel Lizardado - 28.646.863             *
********************************************************/

// Librerías utilizadas
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <ctime>
#include <windows.h>

// Liberamos el encapsulamiento de la librería estandar
using namespace std;

// Declaración de variables
int cantidad = 1;
int yPunt = 0;
string letra = "";
string auxInicial;
int indiceLetra = 0;
int repeticiones[2]; // El indice [0] es doble y [1] es triple
int penalizaciones[3];
int ganador[3];
int puntajes[3][3][5];
int puntosRonda[3][3];
string palabraJugador[3][3][5];
string categoria[5] = {"nombre", "apellido", "ciudad", "animal", "cosa"};

// Declaración de funciones
void bienvenida();
void plantilla();
void rellenarNULL();
void ingresarPalabras();
void compararPalabras();
void imprimirPuntosTotales();
void imprimirPenalizaciones();
void generarLetra();


int main(){

	srand(time(NULL)); // Se inicializa la semilla para rand en función a la hora del ordenador

	bienvenida();
	ingresarPalabras();
	//rellenarNULL(); // Esta es una función de test que evita introducir las palabras de cada jugador y muestra el resultado final
	compararPalabras();
	imprimirPuntosTotales();
	imprimirPenalizaciones();
    return 0;
}

// Es el mensaje inicial que se le da al usuario y solo se muestra al inicio del programa
void bienvenida()
{
    system("Color 5B");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),117);
	cout << " __^__                                      __^__ "<<"\n";
	cout << "( ___ )------------------------------------( ___ )" << "\n";
	cout << " | / |                                      | / | "<<"\n";
	cout << " | / |  BIENVENIDOS AL VIDEOJUEGO DE STOP   | / | "<<"\n";
	cout << " |___|                                      |___| "<<"\n";
	cout << "(_____)------------------------------------(_____)"<<"\n\n";
	cout << "El juego consta de tres rondas, en cada ronda" << "\n";
	cout << "los jugadores deberán escribir palabras acor-" << "\n";
	cout << "des a las diferentes categorias y dispondrán "<< "\n";
	cout << "de un turno en cada ronda.                   "<< "\n";

	cout << "\n";

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),117);
	cout << "Palabra sin repetir -----------> 16 puntos"<< "\n";
	cout << "Palabra repetida dos veces ---->  7 puntos"<< "\n";
	cout << "Palabra repetida tres veces --->  3 puntos"<< "\n";

	cout << "\n";

	cout << "Para empezar a jugar presiona cualquier tecla.";
	_getch();
	system("cls");
}

// Es la plantilla que aparece en cada turno de los jugadores
void plantilla()
{
    system("Color 3D");
	// La variable letre indica la letra por la que deben comenzar las palabras
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),241);
	cout << "------> " << letra[indiceLetra] << " <---LETRA DE LA RONDA---\n\n";
	cout << "---------------STOP---------------\n";

	// Un ciclo for para imprimir el nombre de cada categoria
	for (int i = 0; i < 5; i++)
	{
		cout << categoria[i] << " ";
	}
	cout << "\n";
}

void ingresarPalabras()
{
	for (int z = 0; z < 3; z++)
	{
		// Se llama a la función para que genere la letra aleatoria de cada ronda
		generarLetra();
		for (int y = 0; y < 3; y++)
		{
			// Aquí comienza el turno de cada jugador y por ende imprime la plantilla base de cada turno
			plantilla();
			cout << "\n";
			//Un ciclo for para leer cada palabra de cada categoría
			for (int x = 0; x < 5; x++)
			{
				cout << categoria[x] << ": ";
				cin >> palabraJugador[z][y][x];
			}
			// Elimina el texto de la consola para dar inicio a la ronda del siguiente jugador
			system("cls");
			system("Color 0D");
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),113);
			cout << "Turno del siguiente jugador, presione ENTER para iniciar \n";
			_getch();
			system("cls");
		}
		// Se aumenta el valor del indice de la variable letra para que muestre en consola la nueva letra de la nueva ronda
		indiceLetra++;
	}
}

// Función para generar letras aleatorias
void generarLetra()
{
	letra += 97 + rand() % (123-97);
}

// Evita tener que introducir cada palabra de cada jugador
void rellenarNULL()
{
	for (int z = 0; z < 3; z++)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 5; x++)
			{
				palabraJugador[z][y][x] = "NULL";
			}
		}
	}
}

void compararPalabras()
{
	// Recorre el eje [][][Z] de palabraJugador[][][]
	for (int z = 0; z < 3; z++)
	{
		// Recorre el eje [X][][] de palabraJugador[][][]
		for (int x = 0; x < 5; x++)
		{
			// Recorre el eje [][Y][] de palabraJugador[][][]
			for (int yJug = 0; yJug < 3; yJug++)
			{
				cantidad = 1; // Se resetea la variable a 1 para comparar una nueva casilla

				// Se creo un eje Y auxiliar para poder realizar las comparaciones correctamente
				for (int yAux = 0; yAux < 3; yAux++)
				{
					// Se revisa que sean diferentes para que no se compare la casilla con ella misma
					if (yJug != yAux)
					{
						if (palabraJugador[z][yJug][x] == palabraJugador[z][yAux][x])
						{
							// Al aumentar en 1 la variable cantidad indicamos la cantidad de veces que se repite esa palabra
							cantidad++;
						}
					}
				}
				// Verifica que la cadena no esté vacía y así no asignar puntos
				if (palabraJugador[z][yJug][x] != "")
				{
					// Hacemos uso de la variable auxInicial para guardar la inicial de la palabra introducida por el usuario
					auxInicial = palabraJugador[z][yJug][x];

					// Comparamos la inicial con la letra de la ronda para validar la palabra
					if (auxInicial[0] == letra[z])
					{
						// Dependiendo de la cantidad de veces que se encontró esa palabra se asigna el valor
						if (cantidad == 1)
						{
							puntajes[z][yJug][x] = 16;
						}
						else if (cantidad == 2)
						{
							puntajes[z][yJug][x] = 7;
							repeticiones[0]++;
						}
						else if (cantidad == 3)
						{
							puntajes[z][yJug][x] = 3;
							repeticiones[1]++;
						}
					}
					// En caso ser falsa la validación penalizamos al jugador
					else
					{
						puntajes[z][yJug][x] = -5;
						penalizaciones[yJug]++;
					}
				}
			}
		}
	}
}

void imprimirPuntosTotales()
{
	//Sumamos los puntos de los jugadores en cada ronda
	for (int z = 0; z < 3; z++)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 5; x++)
			{
				puntosRonda[z][y] +=  puntajes[z][y][x];
			}
		}
	}

	// Imprimimos los puntos de cada ronda
	for (int y = 0; y < 3; y++)
	{
		int i = 0;
		cout << "El jugador " << y+1 << " obtuvo " << puntosRonda[i][y] << ", " << puntosRonda[i+1][y] << " y " << puntosRonda[i+2][y] << " en cada ronda respectivamente";
		cout << "\n";
	}

	cout << "\n";

	// Sumamos los puntos de cada ronda para tener el total de puntos de cada jugador
	for (int i = 0; i < 3; i++)
	{
		ganador[i] = puntosRonda[0][i] + puntosRonda[1][i] + puntosRonda[2][i];
	}

	// Imprimimos el total de puntos de cada jugador
	for (int i = 0; i < 3; i++)
	{
		cout << "El jugador " << i+1 << " obtuvo un total de " << ganador[i];
		cout << "\n";
	}
	cout << "\n";

	// Se comprueba el ganador
	if (ganador[0] > ganador[1] && ganador[0] > ganador[2])
	{
		cout << "El jugador 1 ha ganado";
	}
	else if (ganador[1] > ganador[0] && ganador[1] > ganador[2])
	{
		cout << "El jugador 2 ha ganado";
	}
	else if (ganador[2] > ganador[0] && ganador[2] > ganador[1])
	{
		cout << "El jugador 3 ha ganado";
	}
	else
	{
		cout << "Empate, al menos dos jugadores obtuvieron el mejor puntaje";
	}
    cout<<"\n"<<"________$$$$"<<"\n";
    cout<<"_______$$__$"<<"\n";
    cout<<"_______$___$$"<<"\n";
    cout<<"_______$___$$"<<"\n";
    cout<<"_______$$___$$"<<"\n";
    cout<<"________$____$$"<<"\n";
    cout<<"________$$____$$$"<<"\n";
    cout<<"_________$$_____$$"<<"\n";
    cout<<"_________$$______$$"<<"\n";
    cout<<"__________$_______$$"<<"\n";
    cout<<"____$$$$$$$________$$"<<"\n";
    cout<<"__$$$_______________$$$$$$"<<"\n";
    cout<<"_$$____$$$$____________$$$"<<"\n";
    cout<<"_$___$$$__$$$____________$$"<<"\n";
    cout<<"_$$________$$$____________$"<<"\n";
    cout<<"__$$____$$$$$$____________$"<<"\n";
    cout<<"__$$$$$$$____$$___________$"<<"\n";
    cout<<"__$$_______$$$$___________$"<<"\n";
    cout<<"___$$$$$$$$$__$$_________$$"<<"\n";
    cout<<"____$________$$$$_____$$$$"<<"\n";
    cout<<"____$$____$$$$$$____$$$$$$"<<"\n";
    cout<<"_____$$$$$$____$$__$$"<<"\n";
    cout<<"_______$_____$$$_$$$"<<"\n";
    cout<<"________$$$$$$$$$$"<<"\n";
}

void imprimirPenalizaciones()
{
	cout << "\n";
	// Se imprime las penalizaciones de cada jugador
	for (int i = 0; i < 3; i++)
	{
		cout << "\n" << "El jugador " << i + 1 << " tuvo " << penalizaciones[i] << " penalizaciones";
	}
	cout << "\n\n";
    system("Color 3D");
	// Se imprime las repeticiones doble y tripes totales
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),241);
	cout << "Total de palabras repetidas dos veces:  " << repeticiones[0] << "\n";
	cout << "Total de palabras repetidas tres veces: " << repeticiones[1];
}
