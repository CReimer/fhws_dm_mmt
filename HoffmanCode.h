#pragma once

#include <vector>
#include <iostream>
#include <string>

using namespace std;

class HoffmanCode {
public:
    HoffmanCode();

    ~HoffmanCode();

    vector<int> freqTree; // Häufigkeitsbaum; eigentlich kein vector, sondern entsprechende Baumstruktur
    vector<vector<char>> codeTable; //Codetabelle für spätere Zuordnung char -> binär, vector weil unbestimmt lang

    //	3a)
    //zählt Häufigkeiten jedes chars und gibt es als array zurück
    //fügt in Klassenvariable codeTable die chars distinct ein
    int *charCount(char *sentence);

    //bekommt int array mit den Häufigkeitswerten aller chars
    //setzt jeweils die zwei kleinsten Knoten zu Zweig zusammen, bis Baum übrig bleibt
    //Baumstruktur als Klassenvariable... geeignete Struktur vorhanden? int Liste?
    void setTree(int *countArray);

    //bekommen nichts übergeben (oder Baum, wenn Baum keine Klassenvariable)
    //codiert jeden Weg binär (links 0, rechts 1)
    //erstellt Code für jedes Blatt, indem es die Bits des jeweiligen Wegs zusammenhängt
    //gibt Code aus (vector<bool> oder die map?)
    //hier muss noch eine Zuordnung char -> Binärcode stattfinden  (wie?)
    vector<bool> codeTree();

    //bekommt eine Binärkette übergeben und die Zuordnungstabelle char -> binärcode
    //geht Binärkette durch und sucht längst möglichen Binärcode, der auch in der Tabelle ist (es gibt keine codes mit gleichen zwei Bits am Anfang)
    //schreibt entsprechenden char und wdh. bis Kette leer
    //gibt String aus
    char *decodeTree(vector<bool> binaryChain, vector<vector<char>> codeTable);

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
    void setTree2(int *countArray);

    //--------------------------------------------

    //3c)
    //Problemstellung: keine reinen 1-Codes
    //checken: wenn letzter rechter Knoten erreicht, muss Blatt links angehängt werden statt rechts
    //--> ganz rechtes Blatt des Baumes muss leer sein
    //sonst wie oben
    void codeTree3(int *countArray);

    //--------------------------------------------

    //	3d)
    //bekommt maximale Tiefe übergeben
    //hört auf, Äste aneinander zu setzen, wenn depth Knoten erreicht sind
    //Problem: Was passiert, wenn mehr Knoten übrig sind??
    void setTree4(int *countArray, int depth);

    //--------------------------------------------

    //	3e)
    //

};
