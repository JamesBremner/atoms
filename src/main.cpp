#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <wex.h>
#include "cRunWatch.h"
#include "cStarterGUI.h"

class cLoc
{
public:
    float x, y, z;
    cLoc(float X, float Y, float Z)
        : x(X), y(Y), z(Z)
    {
    }
    float dist2(const cLoc &other) const
    {
        float dx = x - other.x;
        float dy = y - other.y;
        float dz = z - other.z;
        return dx *dx + dy *dy + dz *dz;
    }
};

class cAtoms
{
public:
    /// vector storing atom locations
    std::vector<cLoc> myAtomLocs;

    /** vector storing index numbers of close neighbors
     * v[ks][0] index of source atom in myAtomLocs
     * v[ks][1] to v[ks][...] index of atoms located near-by to ks
     */
    std::vector<std::vector<int>> myClose;

    /// maximum distance beyond which atoms are not considered close
    float myMaxDist2;

    void generateTest1();
    void generateRandom();
    void neighbors();
    std::string text();
};

void cAtoms::generateTest1()
{
    myAtomLocs = {
        cLoc(0, 0, 0),
        cLoc(1, 0, 0),
        cLoc(1, 1, 0)};
    myMaxDist2 = 1;
}
 void cAtoms::generateRandom()
 {
    srand(time(NULL));

    for( int k = 0; k < 12100; k++ ) {
        myAtomLocs.push_back( cLoc(
            (rand() % 100 ) / 10.0f,
            (rand() % 100 ) / 10.0f,
            (rand() % 100 ) / 10.0f
           ));
    }
    myMaxDist2 = 1;
 }

void cAtoms::neighbors()
{
    // timing profile
    raven::set::cRunWatch aWatcher("neighbours");

    // loop over every atom
    for (int ks = 0; ks < myAtomLocs.size(); ks++)
    {
        std::vector<int> v;
        v.push_back(ks);

        // loop over every atom with a greater index
        for (int kd = ks + 1; kd < myAtomLocs.size(); kd++)
        {
            //compare square of distance between two atoms with square of maximum distance allowed
            if (myAtomLocs[ks].dist2(myAtomLocs[kd]) <= myMaxDist2) {
                // the atoms are close neighbors
                // add the index of kd to the neighbours of ks
                v.push_back(kd);
            }
        }
        // store all the close neighbors of ks
        myClose.push_back(v);
    }
}

std::string cAtoms::text()
{
    std::stringstream ss;
    for( auto& v : myClose ) {
        if( !v.size() )
            continue;
        ss << v[0] <<": ";
        for( int k = 1; k < v.size(); k++ )
        {
            ss << v[k] << " ";
        }
        ss << "\n";
    }
    return ss.str();
}

class cGUI : public cStarterGUI
{
public:
    cGUI()
        : cStarterGUI(
              "Starter",
              {50, 50, 1000, 500}),
          lb(wex::maker::make<wex::label>(fm))
    {
        raven::set::cRunWatch::Start();
        myAtoms.generateRandom();
        myAtoms.neighbors();
        std::cout << myAtoms.text();
        raven::set::cRunWatch::Report();

        lb.move(50, 50, 100, 30);
        lb.text("Hello World");

        show();
        run();
    }

private:
    wex::label &lb;
    cAtoms myAtoms;
};

main()
{
    cGUI theGUI;
    return 0;
}
