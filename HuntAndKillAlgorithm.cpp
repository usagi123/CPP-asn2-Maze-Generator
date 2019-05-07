//
// Created by Mai Pham Quang Huy on 2019-05-06.
//

#include "HuntAndKillAlgorithm.h"

vector<Edge> HuntAndKill::generate() {
    //create an array to monitize visited cells
    long seed = getSeed();
    int height = getHeight();
    int width = getWidth();
    bool withSeed = isWithSeed();
    bool visitedArray[height][width];
    for (int m = 0; m < height; ++m) {
        for (int i = 0; i < width; ++i) {
            visitedArray[m][i] = false;
        }
    }

    //create vector to store edges
    vector<Edge> edges;
    //check user input seed
    if (!withSeed) {
        seed = time(NULL);
    }
    srand((int) seed);

    bool keepHunting = true;
    bool keepKilling = true;

    //generate a random stating cell
    Coordinator startingCell;
    startingCell.setX(rand() % height);
    startingCell.setY(rand() % width);
    //flag it as visited
    visitedArray[startingCell.getX()][startingCell.getY()] = true;
    //bool starting = true;

    //loop as hunting continuously
    while (keepHunting) {
        //check if whe need to killing
        for (int j = 0; j < height; ++j) {
            for (int i = 0; i < width; ++i) {
                if (!visitedArray[j][i]) {
                    keepKilling = true;
                    break;
                } else {
                    keepKilling = false;
                }
            }
            if (keepKilling) {
                break;
            }
        }
        //loop as killing continuously
        while (keepKilling) {
            vector<Coordinator> neighbours;
            if (startingCell.getX() - 1 > -1) {
                Coordinator topCell;
                topCell.setX(startingCell.getX() - 1);
                topCell.setY(startingCell.getY());
                neighbours.push_back(topCell);
            }
            if (startingCell.getY() + 1 < width) {
                Coordinator rightCell;
                rightCell.setX(startingCell.getX());
                rightCell.setY(startingCell.getY() + 1);
                neighbours.push_back(rightCell);
            }
            if (startingCell.getX() + 1 < height) {
                Coordinator bottomCell;
                bottomCell.setX(startingCell.getX() + 1);
                bottomCell.setY(startingCell.getY());
                neighbours.push_back(bottomCell);
            }
            if (startingCell.getY() - 1 > -1) {
                Coordinator leftCell;
                leftCell.setX(startingCell.getX());
                leftCell.setY(startingCell.getY() - 1);
                neighbours.push_back(leftCell);
            }
            //create vector to store checked neighbours randomly
            vector<int> randomizedNeighbours;
            //loop to check all neighbours randomly to find a not visited neighbour
            bool keepSeeking = true;
            while (keepSeeking) {
                int currentRandom = rand() % neighbours.size();
                bool addingRandom = true;
                //check if randomized neighbour is checked or not
                for (int i = 0; i < randomizedNeighbours.size(); ++i) {
                    if (randomizedNeighbours[i] == currentRandom) {
                        addingRandom = false;
                        break;
                    }
                }
                //if not checked, add to checked vector
                if (addingRandom) {
                    randomizedNeighbours.push_back(currentRandom);
                    Coordinator neighbour = neighbours[currentRandom];
                    //check if not visited
                    if (!visitedArray[neighbour.getX()][neighbour.getY()]) {
                        keepSeeking = false;
                        //mark as visited
                        visitedArray[neighbour.getX()][neighbour.getY()] = true;
                        //add edge
                        Edge edge1;
                        edge1.setCoordinator1(startingCell);
                        edge1.setCoordinator2(neighbour);
                        edges.push_back(edge1);
                        startingCell.setX(neighbour.getX());
                        startingCell.setY(neighbour.getY());
                    }
                } else {
                    //else check if the neighbours vector is all checked
                    if (randomizedNeighbours.size() == neighbours.size()) {
                        keepSeeking = false;
                        keepKilling = false;
                    }
                }
            }
        }
        //hunting
        bool foundStarting = false;
        //loop from left to right, top to bottom to find unvisited cell
        for (int k = 0; k < height; ++k) {
            for (int i = 0; i < width; ++i) {
                //if unvisited step into an check
                if (!visitedArray[k][i]) {
                    //assume it has a least one
                    startingCell.setX(k);
                    startingCell.setY(i);
                    //create a vector to store neighbour cell
                    vector<Coordinator> neighbours;
                    //neighbours.clear();
                    if (startingCell.getX() - 1 > -1) {
                        Coordinator topCell;
                        topCell.setX(startingCell.getX() - 1);
                        topCell.setY(startingCell.getY());
                        neighbours.push_back(topCell);
                    }

                    //bool hasRight = false;
                    if (startingCell.getY() + 1 < width) {
                        Coordinator rightCell;
                        rightCell.setX(startingCell.getX());
                        rightCell.setY(startingCell.getY() + 1);
                        neighbours.push_back(rightCell);
                    }
                    //bool hasBottom = false;
                    if (startingCell.getX() + 1 < height) {
                        Coordinator bottomCell;
                        bottomCell.setX(startingCell.getX() + 1);
                        bottomCell.setY(startingCell.getY());
                        neighbours.push_back(bottomCell);
                    }
                    //bool hasLeft = false;
                    if (startingCell.getY() - 1 > -1) {
                        Coordinator leftCell;
                        leftCell.setX(startingCell.getX());
                        leftCell.setY(startingCell.getY() - 1);
                        neighbours.push_back(leftCell);
                    }
                    //check if any neighbour is visited, if not break to find the next cel
                    for (int j = 0; j < neighbours.size(); ++j) {
                        Coordinator neighbour = neighbours[j];
                        if (visitedArray[neighbour.getX()][neighbour.getY()]) {
                            foundStarting = true;
                            break;
                        }
                    }
                    //if any neighbour is visited
                    if (foundStarting) {
                        //create a checked neighbours vector
                        vector<int> randomizedNeighbours;
                        //loop to randomized through neighbours vector
                        bool keepSeeking = true;
                        while (keepSeeking) {
                            int currentRandom = rand() % neighbours.size();
                            bool addingRandom = true;
                            //check if randomized neighbour is checked or not
                            for (int m = 0; m < randomizedNeighbours.size(); ++m) {
                                if (randomizedNeighbours[m] == currentRandom) {
                                    addingRandom = false;
                                    break;
                                }
                            }
                            //if not checked, add to checked vector
                            if (addingRandom) {
                                randomizedNeighbours.push_back(currentRandom);
                                Coordinator neighbour = neighbours[currentRandom];
                                //check if visited
                                if (visitedArray[neighbour.getX()][neighbour.getY()]) {
                                    keepSeeking = false;
                                    //mark the starting cell is visisted
                                    visitedArray[startingCell.getX()][startingCell.getY()] = true;
                                    //add edge
                                    Edge edge1;
                                    edge1.setCoordinator1(startingCell);
                                    edge1.setCoordinator2(neighbour);
                                    edges.push_back(edge1);
                                }
                            } else {
                                //else check if the neighbours vector is all checked
                                if (randomizedNeighbours.size() == neighbours.size()) {
                                    keepSeeking = false;
                                    foundStarting = false;
                                }
                            }
                        }
                    }
                    if (foundStarting) {
                        break;
                    }
                }
            }
            if (foundStarting) {
                break;
            }
        }
        //check if need hunting by scanning the maze from top to bottom, left to right
        for (int l = 0; l < height; ++l) {
            for (int i = 0; i < width; ++i) {
                if (!visitedArray[l][i]) {
                    keepHunting = true;
                    break;
                } else {
                    keepHunting = false;
                }
            }
            if (keepHunting) {
                break;
            }
        }
    }

    for (int n = 0; n < edges.size(); ++n) {
        Edge edge1 = edges[n];
    }

    return edges;
}
