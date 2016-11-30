#pragma once
#include <vector>
#include <iostream>
#include <string>
using namespace::std;


class HoffmanCode
{
public:
	HoffmanCode();
	~HoffmanCode();

	vector<int> freqTree; // H�ufigkeitsbaum; eigentlich kein vector, sondern entsprechende Baumstruktur
	vector<vector<char>> codeTable; //Codetabelle f�r sp�tere Zuordnung char -> bin�r, vector weil unbestimmt lang

	//	3a)
	//z�hlt H�ufigkeiten jedes chars und gibt es als array zur�ck
	//f�gt in Klassenvariable codeTable die chars distinct ein
	int* charCount(char* sentence);

	//bekommt int array mit den H�ufigkeitswerten aller chars
	//setzt jeweils die zwei kleinsten Knoten zu Zweig zusammen, bis Baum �brig bleibt
	//Baumstruktur als Klassenvariable... geeignete Struktur vorhanden? int Liste?
	void setTree(int* countArray);

	//bekommen nichts �bergeben (oder Baum, wenn Baum keine Klassenvariable)
	//codiert jeden Weg bin�r (links 0, rechts 1)
	//erstellt Code f�r jedes Blatt, indem es die Bits des jeweiligen Wegs zusammenh�ngt
	//gibt Code aus (vector<bool> oder die map?)
	//hier muss noch eine Zuordnung char -> Bin�rcode stattfinden  (wie?)
	vector<bool> codeTree();

	//bekommt eine Bin�rkette �bergeben und die Zuordnungstabelle char -> bin�rcode
	//geht Bin�rkette durch und sucht l�ngst m�glichen Bin�rcode, der auch in der Tabelle ist (es gibt keine codes mit gleichen zwei Bits am Anfang)
	//schreibt entsprechenden char und wdh. bis Kette leer
	//gibt String aus
	char* decodeTree(vector<bool> binaryChain, vector<vector<char>> codeTable);

	//-------------------------------------------

	//	3b)
	//anstatt die zwei kleinsten Knoten zusammen zu setzen:
	//neuen Knoten k(i) mit vorhandenen Knoten vergleichen
	//k(i-1) < k(i) => ja? k(i-1) zu rechtem Knoten von k(i) machen; nein?: 
	//checken, ob k(i+1) vorhanden. ja?:
	//k(i-1) > k(i) < k(i+1) => k(i) zu rechtem Knoten von k(i+1) machen
	//k(i-1) > k(i) > k(i+1) => k(i) zu rechtem Knoten von k(i-1) machen und k(i+1) zu rechtem Knoten von k(i)
	//nein?:
	//k(i-1) > k(i) => k(i) zu rechtem Knoten von k(i+1) machen
	void setTree2(int* countArray);

	//--------------------------------------------

	//3c)
	//Problemstellung: keine reinen 1-Codes
	//checken: wenn letzter rechter Knoten erreicht, muss Blatt links angeh�ngt werden statt rechts
	//--> ganz rechtes Blatt des Baumes muss leer sein
	//sonst wie oben
	void codeTree3(int* countArray);

	//--------------------------------------------

	//	3d)
	//bekommt maximale Tiefe �bergeben
	//h�rt auf, �ste aneinander zu setzen, wenn depth Knoten erreicht sind
	//Problem: Was passiert, wenn mehr Knoten �brig sind??
	void setTree4(int* countArray, int depth);

	//--------------------------------------------

	//	3e)
	//

};

