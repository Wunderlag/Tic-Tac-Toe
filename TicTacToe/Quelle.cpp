// Tic Tac Toe Spiel mit Eingabe per NumPad
// Grid ist 3x3, Spieler 1 = X Spieler 2 = O
//

#include <iostream>
#include <string>
#include <Windows.h>
#include <random>

using namespace std;

// Funktion:
/*

- 2 Spielernamen eingeben und speichern

- Grid Zeichnen (3x3)

"Spielername" ist am Zug:
 _ _ _
|_|_|_|
|_|_|_|
|_|_|_|

- Auf Benutzereingabe warten

- Benutzereingabe überprüfen (ist Feld bereits besetzt?)

- Benutzereingabe Zeichnen

- Spieler abwechseln

- Testen ob 3er Reihe voll ist (auch diagonal) (Sieg?)

- Sieger anzeigen

- zum Beenden [ESC]
*/

// Funktionsprototypen

// Spielernamen abfragen
string spieler1(void);
string spieler2(void);

// Spielern ein Symbol zuweisen (random)
int randomXO(void);
// dazu ein array initialisieren
string spielerArray[4];

// Grid Zeichnen
void drawGrid(int);

// Benutzereingabe verarbeiten
int userInput(char, char);

// Testen ob ein Gewinner feststeht
int winstate();

// initialisieren aller Felder mit "_"
char num1{ '_' }, num2{ '_' }, num3{ '_' }, num4{ '_' }, num5{ '_' }, num6{ '_' }, num7{ '_' }, num8{ '_' }, num9{ '_' };

// Variable für X und O (winstate() konnte keine const chars mit chars vergleichen?)
const char X{ 'X' }, O{ 'O' };

int main()
{
	locale::global(locale("German_germany"));
	cout << "Willkommen zu Tic Tac Toe!\nDie Steuerung erfolgt über das NumPad." << endl;
	string spielerName1 = spieler1();
	string spielerName2 = spieler2();

	// per randomXO() 1 oder 2 ausgeben, Ergebnis dice_roll zuweisen, dann Spielername in spielerArray[] zuweisen
	int dice_roll = randomXO();
	if (dice_roll == 1)
	{
		spielerArray[0] = X;
		spielerArray[1] = spielerName1;
		spielerArray[2] = O;
		spielerArray[3] = spielerName2;
	}
	else if (dice_roll == 2)
	{
		spielerArray[0] = X;
		spielerArray[1] = spielerName2;
		spielerArray[2] = O;
		spielerArray[3] = spielerName1;
	}

	cout << "Glückwunsch " << spielerArray[1] << ", du darfst anfangen und hast das Symbol X!";
	Sleep(3000);

	// Vor Spielbegin das Fenster leeren (system() soll angeblich schlecht sein (Sicherheit?), trotzdem das einfachste unter Windows)
	if (system("CLS")) system("clear");

	// Variable zum abwechseln der Spieler deklarieren
	int i{ 1 };

	// Loop zum Abwechseln der Spieler bis winstate() == 1
	while (winstate() == 0)
	{
		// Spieleranweisung ausgeben
		cout << spielerArray[i] << ", bitte gib das Feld an, in dem du dein " << spielerArray[i - 1] << " setzen möchtest." << endl;

		// Spieler abwechseln (verbesserungswürdig)
		if (i == 3)
		{
			i -= 2;
		}
		else if (i == 1)
		{
			i += 2;
		}

		// Spielfeld zeichnen & Benutzeingabe inkl Errorhandling
		drawGrid(i);

		// Bildschirm löschen
		if (system("CLS")) system("clear");

		// nach 7 Zügen abbrechen, da kein Gewinner mehr festegestellt werden kann
		int zaehler{};
		if (zaehler >= 7)
		{
			cout << "Unentschieden!" << endl;
			break;
		}
		zaehler++;
	}

	// letzte Ausgabe des Grids
	cout << "Der Endstand:" << endl;
	cout << " _ _ _ \n|" << num7 << "|" << num8 << "|" << num9 << "|\n|" << num4 << "|" << num5 << "|" << num6 << "|\n|" << num1 << "|" << num2 << "|" << num3 << "|\n" << endl;

	system("PAUSE");
}


// Name von Spieler1 abfragen
string spieler1()
{
	string spieler;
	cout << "Bitte gib den Namen von Spieler 1 ein:" << endl;
	getline (cin, spieler);
	return spieler;
}
// Name von Spieler 2 abfragen
string spieler2()
{
	string spieler;
	cout << "Bitte gib den Namen von Spieler 2 ein:" << endl;
	getline(cin, spieler );
	return spieler;
}

// Zufällig 1 oder 2 ausgeben
int randomXO()
{
	random_device generator;
	uniform_int_distribution<int> distribution(1, 2);
	return distribution(generator);
}

// Zeichnet kontinuierlich das Spielfeld und fragt die Spielereingabe ab (inkl. Errorhandling)
void drawGrid(int i)
{
	// Displayausgabe des Grids
	cout << " _ _ _ \n|" << num7 << "|" << num8 << "|" << num9 << "|\n|" << num4 << "|" << num5 << "|" << num6 << "|\n|" << num1 << "|" << num2 << "|" << num3 << "|" << endl;

	// Spielereingabe
	char neuesZeichen{};
	cin >> neuesZeichen;

	// Benutzsymbole zuweisen
	char neuesZeichenSymbol{};	
	if (i == 3)
	{
		neuesZeichenSymbol = X;
	}
	else if (i == 1)
	{
		neuesZeichenSymbol = O;
	}

	// Errorhandling
	switch (userInput(neuesZeichen, neuesZeichenSymbol))
	{
	case 1:
	{
		cout << "Feld bereits belegt, bitte anderes Feld wählen!" << endl;
		Sleep(3000);
	}
		break;
	case 2:
	{
		cout << "Bitte den NumBlock (1-9) benutzen um ein Feld zu wählen!" << endl;
		Sleep(3000);
	}
		break;
	}
}

// Fragt die Eingabe ab und prüft ob Feld bereits belegt ist
int userInput(char neuesZeichen, char neuesZeichenSymbol)
{
	// initialisiseren des ErrorCodes
	int errorTicTacToe{ 0 };

	switch (neuesZeichen)
	{
	case '1':
	{
		if (num1 == '_')
		{
			num1 = neuesZeichenSymbol;
		}
		else
		{
			errorTicTacToe = 1;
		}
		break;
	}
	case '2':
	{
		if (num2 == '_')
		{
			num2 = neuesZeichenSymbol;
		}
		else
		{
			errorTicTacToe = 1;
		}
		break;
	}
	case '3':
	{
		if (num3 == '_')
		{
			num3 = neuesZeichenSymbol;
		}
		else
		{
			errorTicTacToe = 1;
		}
		break;
	}
	case '4':
	{
		if (num4 == '_')
		{
			num4 = neuesZeichenSymbol;
		}
		else
		{
			errorTicTacToe = 1;
		}
		break;
	}
	case '5':
	{
		if (num5 == '_')
		{
			num5 = neuesZeichenSymbol;
		}
		else
		{
			errorTicTacToe = 1;
		}
		break;
	}
	case '6':
	{
		if (num6 == '_')
		{
			num6 = neuesZeichenSymbol;
		}
		else
		{
			errorTicTacToe = 1;
		}
		break;
	}
	case '7':
	{
		if (num7 == '_')
		{
			num7 = neuesZeichenSymbol;
		}
		else
		{
			errorTicTacToe = 1;
		}
		break;
	}
	case '8':
	{
		if (num8 == '_')
		{
			num8 = neuesZeichenSymbol;
		}
		else
		{
			errorTicTacToe = 1;
		}
		break;
	}
	case '9':
	{
		if (num9 == '_')
		{
			num9 = neuesZeichenSymbol;
		}
		else
		{
			errorTicTacToe = 1;
		}
		break;
	}
	default:
	{
		errorTicTacToe = 2;
	}
	}
	return errorTicTacToe;
}

// Testet ob eine Reihe gleicher Zeichen vorhandne ist und wählt den Gewinner aus
int winstate()
{
	if ((num1 == X) && (num2 == X) && (num3 == X) ||
		(num4 == X) && (num5 == X) && (num6 == X) ||
		(num7 == X) && (num8 == X) && (num9 == X) ||
		(num1 == X) && (num4 == X) && (num7 == X) ||
		(num2 == X) && (num5 == X) && (num8 == X) ||
		(num3 == X) && (num6 == X) && (num9 == X) ||
		(num1 == X) && (num5 == X) && (num9 == X) ||
		(num3 == X) && (num5 == X) && (num7 == X))
	{
		cout << spielerArray[1] << " gewinnt!\a\a\a" << endl;
		Sleep(2000);
		return 1;
	}
	else if ((num1 == O) && (num2 == O) && (num3 == O) ||
		     (num4 == O) && (num5 == O) && (num6 == O) ||
			 (num7 == O) && (num8 == O) && (num9 == O) ||
			 (num1 == O) && (num4 == O) && (num7 == O) ||
			 (num2 == O) && (num5 == O) && (num8 == O) ||
			 (num3 == O) && (num6 == O) && (num9 == O) ||
			 (num1 == O) && (num5 == O) && (num9 == O) ||
			 (num3 == O) && (num5 == O) && (num7 == O))
	{
		cout << spielerArray[3] << " gewinnt!\a\a\a" << endl;
		Sleep(2000);
		return 1;
	}
	else
	{
		return 0;
	}
}