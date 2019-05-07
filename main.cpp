#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include "Maze.h"
#include "Coordinator.h"
#include "Edge.h"
#include "HuntAndKillAlgorithm.h"

using namespace std;

typedef pair<int, int> coord;
typedef pair<coord, coord> mazePath, mazeEdges;

void saveSvg(string fileName, const vector<Edge>& vector, int width, int height);
vector<mazeEdges> whereIsYourEdge(const vector<Edge>& mazeVector); //Find edges between 2 cells in maze path
void drawThatSVGMazeForMe(string fileName, const vector<Edge>& mazeVector, int width, int height); //Draw maze details into SVG files

int main() {

    vector<Edge> edgesVector;

    HuntAndKill huntAndKill;
    Maze *maze = &huntAndKill;
    maze->setWithSeed(true);
    maze->setSeed(3);
    maze->setWidth(3);
    maze->setHeight(3);

    edgesVector = huntAndKill.generate();

//    saveSvg("mymaze.svg", edgesVector, 3, 3);
    drawThatSVGMazeForMe("3x3.svg", edgesVector, 3, 3);
    return 0;
}

vector<mazeEdges> whereIsYourEdge(const vector<Edge>& mazeVector) {
    //using returned maze path cell's coordinator, we can calculate the edge between 2 cells in that maze path
    vector<mazeEdges> edgePathVector;

    for (auto i = 0; i < mazeVector.size(); i++) {
        //TODO: Think a way implement lambda function here for better readability
        if (mazeVector[i].getCoordinator1().getX() < mazeVector[i].getCoordinator2().getX() && mazeVector[i].getCoordinator1().getY() == mazeVector[i].getCoordinator2().getY()) { //x increase, y not change
            edgePathVector.push_back(make_pair(make_pair(mazeVector[i].getCoordinator2().getX(), mazeVector[i].getCoordinator2().getY()), make_pair(mazeVector[i].getCoordinator2().getX(), mazeVector[i].getCoordinator2().getY() + 1)));
        }
        if (mazeVector[i].getCoordinator1().getX() == mazeVector[i].getCoordinator2().getX() && mazeVector[i].getCoordinator1().getY() < mazeVector[i].getCoordinator2().getY()) {//x not change, y increase
            edgePathVector.push_back(make_pair(make_pair(mazeVector[i].getCoordinator2().getX(), mazeVector[i].getCoordinator2().getY()), make_pair(mazeVector[i].getCoordinator2().getX() + 1, mazeVector[i].getCoordinator2().getY())));
        }
        if (mazeVector[i].getCoordinator1().getX() == mazeVector[i].getCoordinator2().getX() && mazeVector[i].getCoordinator1().getX() > mazeVector[i].getCoordinator2().getY()) {//x not change, y decrease
            edgePathVector.push_back(make_pair(make_pair(mazeVector[i].getCoordinator1().getX(), mazeVector[i].getCoordinator1().getY()), make_pair(mazeVector[i].getCoordinator1().getX() + 1, mazeVector[i].getCoordinator1().getY())));
        }
        if (mazeVector[i].getCoordinator1().getX() > mazeVector[i].getCoordinator2().getX() && mazeVector[i].getCoordinator1().getY() == mazeVector[i].getCoordinator2().getY()) {//x decrease, y not change
            edgePathVector.push_back(make_pair(make_pair(mazeVector[i].getCoordinator1().getX(), mazeVector[i].getCoordinator1().getY()), make_pair(mazeVector[i].getCoordinator1().getX(), mazeVector[i].getCoordinator1().getY() + 1)));
        }
    }

    return edgePathVector;
}

void drawThatSVGMazeForMe(string fileName, const vector<Edge>& mazeVector,int width, int height) {
    float w = width;
    float h = height;
    vector<mazeEdges> edgePathVector = whereIsYourEdge(mazeVector);

    //Got edges from whereIsYourEdge function above, we convert those edges coordinate into an SVG line
    vector<string> deleteSVGLineVector;

    for (vector<mazeEdges>::iterator it = edgePathVector.begin(); it != edgePathVector.end() ; it++) {
        stringstream ssd;
        ssd << "<line stroke='white' stroke-width='0.005' x1='" << setprecision(2) << (it->first.first)/w << "' y1='" << setprecision(2) << (it->first.second)/h << "' x2='" << setprecision(2) << (it->second.first)/w << "' y2='" << setprecision(2) << (it->second.second)/h << "'/> \n";
        deleteSVGLineVector.push_back(ssd.str());
    }

    for (vector<mazeEdges>::iterator it = edgePathVector.begin(); it != edgePathVector.end() ; it++) {
        stringstream ssd;
        ssd << "<line stroke='white' stroke-width='0.005' x1='" << setprecision(2) << (it->second.first)/w << "' y1='" << setprecision(2) << (it->second.second)/h << "' x2='" << setprecision(2) << (it->first.first)/w << "' y2='" << setprecision(2) << (it->first.second)/h << "'/> \n";
        deleteSVGLineVector.push_back(ssd.str());
    }

    //Generate a SVG grid
    stringstream ss;

    ss << "<svg viewBox='0 0 1 1' width='500' height='500' xmlns='http://www.w3.org/2000/svg'> \n";
    ss << "<rect width='1' height='1' style='fill: black' /> \n";
    ss << "<line stroke='white' stroke-width='0.005' x1='0' y1='0' x2='1' y2='0'/> \n";
    ss << "<line stroke='white' stroke-width='0.005' x1='1' y1='0' x2='1' y2='1'/> \n";
    ss << "<line stroke='white' stroke-width='0.005' x1='1' y1='1' x2='0' y2='1'/> \n";
    ss << "<line stroke='white' stroke-width='0.005' x1='0' y1='1' x2='0' y2='0'/> \n";

    //Draw SVG grid based on column loop
    float x1 = 0;
    float y1 = 0;
    float x2 = 0;
    float y2 = 0;

    for (auto i = 1; i <= h; i++) {

        float x1CP = 0;
        float y1CP = 0;
        float x2CP = 0;
        float y2CP = 0;

        for (auto j = 0; j < w; j++) {
            x1 = (1/w)*i;
            y1 = y1CP;
            x2 = x1;
            y2 = y1CP + (1/w);

            x1CP = x1;
            y1CP = y1;
            x2CP = x2;
            y2CP = y2;

            ss << "<line stroke='white' stroke-width='0.005' x1='" << setprecision(2) << x1 << "' y1='" << setprecision(2) << y1 << "' x2='" << setprecision(2) << x2 << "' y2='" << setprecision(2) << y2 << "'/> \n";

            x1 = (1/w)*i;
            y1 = y1CP + (1/w);
            x2 = x2CP - (1/w);
            y2 = y1CP + (1/w);

            x1CP = x1;
            y1CP = y1;
            x2CP = x2;
            y2CP = y2;

            ss << "<line stroke='white' stroke-width='0.005' x1='" << setprecision(2) << x1 << "' y1='" << setprecision(2) << y1 << "' x2='" << setprecision(2) << x2 << "' y2='" << setprecision(2) << y2 << "'/> \n";
        }
    }
    ss << "</svg> \n";

    string mazeString = ss.str();

    //Find converted edges into SVG line that match in a SVG grid, remove that line. Which result in a maze
    for (auto k = 0; k < deleteSVGLineVector.size(); k++) {
        string target = deleteSVGLineVector[k];

        int found = -1;
        do {
            found = mazeString.find(target, found + 1);
            if (found != -1) {
                mazeString = mazeString.substr(0, found) + mazeString.substr(found + target.length());
            }
        } while (found != -1);
    }

    ofstream file;
    file.open(fileName);
    file << mazeString;
    file.close();
}

void saveSvg(string fileName, const vector<Edge>& vector, int width, int height) {
    ofstream svg(fileName, ofstream::out);
    svg << "<svg" << " viewBox=" << "\"0 0 " << width << " " << height << "\""<< " width" << "=" << "\"" << width*10
        << "\"" << " height=\"" << height*10 << "\"" << " xmlns=" << "\"http://www.w3.org/2000/svg\">" << endl;
    svg << "<rect width =" << "\'" << width << "\' " << "height=\'" << height << "\' " << "style=\'"
        << "fill: black\' " << "/>" << endl;
    for (auto & edge : vector) {
        int x1 =  edge.getCoordinator1().getX();
        int y1 =  edge.getCoordinator1().getY();
        int x2 =  edge.getCoordinator2().getX();
        int y2 =  edge.getCoordinator2().getY();
        svg << "<line stroke=\'" << "white\' " << "stroke-width=\'" << "0.5\'" << " x1=\'" << x1 << "\' y1=\'" << y1
            << "\' x2=\'" << x2 << "\' y2=\'" << y2 << "\'/>" << endl;
    }
    svg << "</svg>";
    svg.close();
}